#include <QmlExtension/SettingsAdapter.h>

#include <Settings/Settings.h>
#include <QtCore/QSettings>

using P1::Settings::Settings;

SettingsAdapter::SettingsAdapter(QObject* parent) : QObject(parent)
{
}

SettingsAdapter::~SettingsAdapter()
{
}

SettingsAdapter* SettingsAdapter::qmlAttachedProperties(QObject *obj)
{
  return new SettingsAdapter(obj);
}

void SettingsAdapter::setValue(const QString& group, const QString& key, const QVariant& value) const
{
  if (Settings::isInitialized()) {
    Settings settings;
    settings.beginGroup(group);
    settings.setValue(key, value);
  } else {
    QSettings settings("P1", "Qml viewer");
    settings.beginGroup(group);
    settings.setValue(key, value);
  }
}

QVariant SettingsAdapter::value(const QString& group, const QString& key, const QVariant& defaultValue /*= QVariant()*/) const
{
  if (Settings::isInitialized()) {
    Settings settings;
    settings.beginGroup(group);
    return settings.value(key, defaultValue);
  } 

  QSettings settings("P1", "Qml viewer");
  settings.beginGroup(group);
  return settings.value(key, defaultValue);
}

void SettingsAdapter::remove(const QString& group, const QString& key) const
{
    if (Settings::isInitialized()) {
        Settings settings;
        settings.beginGroup(group);
        settings.remove(key);
        return;
    } 

    QSettings settings("P1", "Qml viewer");
    settings.beginGroup(group);
    settings.remove(key);
}