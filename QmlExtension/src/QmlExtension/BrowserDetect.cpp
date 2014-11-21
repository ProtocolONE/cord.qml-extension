#include <QmlExtension/BrowserDetect.h>

#include <QtCore/QFileInfo>
#include <QtCore/QSettings>

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
  QSettings startupSettings("HKEY_CURRENT_USER\\Software\\Clients\\StartMenuInternet\\", QSettings::NativeFormat);
  QString browserStartupName = startupSettings.value("Default").toString();

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
