#pragma once

#include <QObject>
#include <QDeclarativeEngine>

#include <QtCore/QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QtDeclarative/QtDeclarative>
#include <QmlExtension/LocalStorage/QmlSqlDatabaseData.h>

class LocalStorage : public QObject
{
  Q_OBJECT
public:
  explicit LocalStorage(QObject *parent = 0);
  virtual ~LocalStorage();

  Q_INVOKABLE QmlSqlDatabaseData *openDatabaseSync(QString dbname, QString version, QString description, int estimated_size);
  static LocalStorage *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(LocalStorage, QML_HAS_ATTACHED_PROPERTIES)