#pragma once

#include <QObject>
#include <QVariant>
#include <QtSql/QSqlDatabase>

class QmlSqlDatabaseData: public QObject
{
  Q_OBJECT
public:
  explicit QmlSqlDatabaseData(QObject *parent, QString dbName);
  virtual ~QmlSqlDatabaseData();

  Q_INVOKABLE QVariantMap executeSql(QString sql);
  Q_INVOKABLE QVariantMap executeSql(QString sql, QVariant args);

private:
  void bindQueryValues(QSqlQuery &query, QVariant &args);
  QVariant castValue(const QVariant &value);
  QVariantMap buildErrorResponse(QSqlError &error);

  QString _dbName;
};
