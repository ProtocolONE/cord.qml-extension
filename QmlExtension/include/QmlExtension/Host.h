#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtQuick/QQuickItem>

class Host : public QObject
{
  Q_OBJECT
public:
  explicit Host(QObject* parent = 0);
  virtual ~Host();

  Q_INVOKABLE QStringList arguments();
  Q_INVOKABLE QString hwid(bool async = false);

signals:
  void hwidChanged(QString hwid);

public:
  static Host *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(Host, QML_HAS_ATTACHED_PROPERTIES)
