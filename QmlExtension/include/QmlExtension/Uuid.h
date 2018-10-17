#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQuick/QQuickItem>

class Uuid : public QObject
{
  Q_OBJECT

public:
  explicit Uuid(QObject* parent = nullptr);
  virtual ~Uuid();

  static Uuid *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString create();
};

QML_DECLARE_TYPEINFO(Uuid, QML_HAS_ATTACHED_PROPERTIES)
