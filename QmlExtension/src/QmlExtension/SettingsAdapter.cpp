/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/SettingsAdapter.h>

#include <Settings/Settings>
#include <QtCore/QSettings>

using GGS::Settings::Settings;

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
    QSettings settings("GGS", "Qml viewer");
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

  QSettings settings("GGS", "Qml viewer");
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

    QSettings settings("GGS", "Qml viewer");
    settings.beginGroup(group);
    settings.remove(key);
}