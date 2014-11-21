#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtSql/QSqlDatabase>

class QmlSqlDatabaseData: public QObject
{
  Q_OBJECT
public:
  QmlSqlDatabaseData(QObject *parent, QString dbName);
  virtual ~QmlSqlDatabaseData();

  Q_INVOKABLE QVariantMap executeSql(QString sql);
  Q_INVOKABLE QVariantMap executeSql(QString sql, QVariant args);

  Q_INVOKABLE bool transaction();
  Q_INVOKABLE bool commit();
  Q_INVOKABLE bool rollback();

private:
  void bindQueryValues(QSqlQuery &query, QVariant &args);
  QVariant castValue(const QVariant &value);
  QVariantMap buildErrorResponse(QSqlError &error);

  QString _dbName;
  bool _openedTrasaction;
};
