#include <QmlExtension/GoogleAnalytics.h>
#include <QtCore/QLocale>
#include <windows.h>

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
  OSVERSIONINFOEX osvi;

  ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  GetVersionEx((OSVERSIONINFO*) &osvi);
  BOOL isWow64 = FALSE;
  IsWow64Process(GetCurrentProcess(),&isWow64);
  
  QString result = QString("( Windows NT %1.%2;").arg(osvi.dwMajorVersion).arg(osvi.dwMinorVersion);
  if (isWow64) {
    result += " WOW64;";
  }

  result += ")";

  return result;
}
