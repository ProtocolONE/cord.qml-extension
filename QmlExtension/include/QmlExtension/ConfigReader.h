#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQuick/QQuickItem>

class ConfigReader : public QObject
{
  Q_OBJECT
public:
  explicit ConfigReader(QObject* parent = 0);

  static ConfigReader* qmlAttachedProperties(QObject *obj);

public:
  Q_INVOKABLE QVariantMap read(const QString& path) const;
};

QML_DECLARE_TYPEINFO(ConfigReader, QML_HAS_ATTACHED_PROPERTIES)
