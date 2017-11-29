#include <QmlExtension/BrowserDetect.h>

#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QSysInfo>

BrowserDetect::BrowserDetect(QObject* obj) : QObject(obj)
{
}

BrowserDetect::~BrowserDetect()
{
}

BrowserDetect *BrowserDetect::qmlAttachedProperties(QObject *obj) {
  return new BrowserDetect(obj);
}

Q_INVOKABLE QString BrowserDetect::getBrowserName()
{
  QSettings userChoise("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\http\\UserChoice", QSettings::NativeFormat);
  QString browserProgId = userChoise.value("ProgId").toString();

  if (browserProgId == "IE.HTTP" || browserProgId == "AppXq0fevzme2pys62n3e0fbqa7peapykr8v") {
    return "iexplore";
  }

  if (browserProgId.startsWith("FirefoxURL")) {
    return "firefox";
  }

  if (!browserProgId.isEmpty())
    return browserProgId.toLower();

  QSettings startupSettings("HKEY_CURRENT_USER\\Software\\Clients\\StartMenuInternet\\", QSettings::NativeFormat);
  QString browserStartupName = startupSettings.value("Default").toString();

  if (browserProgId.toLower().startsWith("firefox"))
    return "firefox";

  if (!browserStartupName.isEmpty())
    return browserStartupName.toLower().remove(".exe");

  QSettings settings("HKEY_CURRENT_USER\\Software\\Classes\\http\\shell\\open\\command\\", QSettings::NativeFormat);
  QString browserUrl = settings.value("Default").toString();

  if (browserUrl.isEmpty())
    return QString();

  browserUrl = browserUrl.mid(1, browserUrl.indexOf('"', 1) - 1);

  QFileInfo file(browserUrl);
  return file.fileName().toLower().remove(".exe");
}
