#include <QmlExtension/GoogleAnalytics.h>
#include <QtCore/QLocale>
#include <QSysInfo>

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

  BOOL isWow64 = FALSE;
  IsWow64Process(GetCurrentProcess(),&isWow64);

  QString result = QString("(Windows NT %1").arg(winVersion);
  if (isWow64)
    result += "; WOW64";

  result += ")";

  return result;
}

QString GoogleAnalytics::winVersion()
{
  return QString::number(QSysInfo::windowsVersion());
}
