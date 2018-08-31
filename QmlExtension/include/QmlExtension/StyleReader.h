#pragma once

#include <QtCore/QString>
#include <QtCore/QObject>

#include <QtCore/QVariantList>
#include <QtQuick/QQuickItem>

class StyleReader : public QObject
{
  Q_OBJECT
public:
  explicit StyleReader(QObject *parent = 0);
  virtual ~StyleReader();

  Q_INVOKABLE QVariantList read(const QString &path);

  static StyleReader *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(StyleReader, QML_HAS_ATTACHED_PROPERTIES)