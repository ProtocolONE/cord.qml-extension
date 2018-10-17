#pragma once

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

#include <QmlExtension/LocalStorage/QmlSqlDatabaseData.h>

class LocalStorage : public QObject
{
  Q_OBJECT
public:
  explicit LocalStorage(QObject *parent = 0);
  virtual ~LocalStorage();

  Q_INVOKABLE QmlSqlDatabaseData *openDatabaseSync(
    QString folder,
    QString dbname,
    QString version,
    QString description,
    int estimated_size);

  static LocalStorage *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(LocalStorage, QML_HAS_ATTACHED_PROPERTIES)