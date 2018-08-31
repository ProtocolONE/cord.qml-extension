#include <QmlExtension/GoogleAnalytics.h>
#include <QtCore/QLocale>
#include <QSysInfo>

#include <windows.h>

inline bool isWow64()
{
  typedef NTSTATUS(WINAPI *fnNtQueryInformationProcess)(
    _In_      HANDLE           ProcessHandle,
    _In_      DWORD            ProcessInformationClass,
    _Out_     PVOID            ProcessInformation,
    _In_      ULONG            ProcessInformationLength,
    _Out_opt_ PULONG           ReturnLength
    );

  fnNtQueryInformationProcess queryProcessInfo = reinterpret_cast<fnNtQueryInformationProcess>(
    GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess"));
  if (!queryProcessInfo)
    return false;

  DWORD ProcessInformation = 0;
  DWORD infoType = 0x1A; // ProcessPriorityClass | ProcessExceptionPort
  NTSTATUS res = queryProcessInfo(GetCurrentProcess(), infoType, &ProcessInformation, 4u, 0);

  return (res >= 0) && (ProcessInformation != 0);
}


GoogleAnalytics::GoogleAnalytics(QObject* obj)  : QObject(obj)
{
}

GoogleAnalytics::~GoogleAnalytics()
{
}

GoogleAnalytics *GoogleAnalytics::qmlAttachedProperties(QObject *obj) {
  return new GoogleAnalytics(obj);
}

QString GoogleAnalytics::systemLanguage()
{
  return QLocale::system().bcp47Name();
}

Q_INVOKABLE QString GoogleAnalytics::systemVersion()
{
  QString winVersion;
  switch (QSysInfo::windowsVersion()) {
  case QSysInfo::WV_5_1: winVersion = "5.1"; break;
  case QSysInfo::WV_6_0: winVersion = "6.0"; break;
  case QSysInfo::WV_6_1: winVersion = "6.1"; break;
  case QSysInfo::WV_6_2: winVersion = "6.2"; break;
  case QSysInfo::WV_6_3: winVersion = "6.3"; break;
  case QSysInfo::WV_10_0: winVersion = "10.0"; break;
  default: winVersion = "6.1"; break;
  }

  QString result = QString("(Windows NT %1").arg(winVersion);
  if (isWow64())
    result += "; WOW64";

  result += ")";

  return result;
}

QString GoogleAnalytics::winVersion()
{
  return QString::number(QSysInfo::windowsVersion());
}
