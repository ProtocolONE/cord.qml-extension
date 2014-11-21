#include <QmlExtension/LocalStorage/QmlSqlDatabaseData.h>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

QmlSqlDatabaseData::QmlSqlDatabaseData(QObject *parent, QString dbName)
  : QObject(parent)
  , _dbName(dbName)
  , _openedTrasaction(false)
{
}

QmlSqlDatabaseData::~QmlSqlDatabaseData()
{
  if (this->_openedTrasaction)
    this->rollback();
}

QVariantMap QmlSqlDatabaseData::executeSql(QString sql)
{
  return this->executeSql(sql, QVariant());
}

bool QmlSqlDatabaseData::transaction()
{
  QSqlDatabase db = QSqlDatabase::database(this->_dbName);
  if (db.transaction()) {
    this->_openedTrasaction = true;
    return true;
  }

  return false;
}

bool QmlSqlDatabaseData::commit()
{
  this->_openedTrasaction = false;
  QSqlDatabase db = QSqlDatabase::database(this->_dbName);
  return db.commit();
}

bool QmlSqlDatabaseData::rollback()
{
  this->_openedTrasaction = false;
  QSqlDatabase db = QSqlDatabase::database(this->_dbName);
  return db.rollback();
}

void QmlSqlDatabaseData::bindQueryValues(QSqlQuery &query, QVariant &args)
{
  if (args.isNull() || !args.isValid())
    return;

  if (args.canConvert(QVariant::List)) {
    QVariantList list = args.toList();
    int size = list.length();

    for (quint32 ii = 0; ii < size; ++ii)
      query.bindValue(ii, list.at(ii));
  } else if (args.canConvert(QVariant::Map)) {
    QVariantMap map = args.toMap();

    for(QVariantMap::const_iterator iter = map.begin(); iter != map.end(); ++iter) 
      query.bindValue(iter.key() , iter.value());
  } else {
    query.bindValue(0, args);
  }
}

QVariantMap QmlSqlDatabaseData::executeSql(QString sql, QVariant args)
{
  QSqlDatabase db = QSqlDatabase::database(this->_dbName);

  QSqlQuery query(db);

  if (!query.prepare(sql))
    return this->buildErrorResponse(query.lastError());

  this->bindQueryValues(query, args);

  if (!query.exec())
    return this->buildErrorResponse(query.lastError());

  QVariantList dataSet;
  while (query.next()) {
    QSqlRecord record = query.record();

    QVariantMap row;
    for (int ii = 0; ii < record.count(); ++ii) {
      QString key(record.fieldName(ii).data());
      QVariant value = this->castValue(record.value(ii));
      row.insert(key, value);
    }
    dataSet.push_front(row);
  }

  query.clear();

  QVariantMap returnValue;
  returnValue.insert("rowsAffected", QVariant(query.numRowsAffected()));
  returnValue.insert("insertId", query.lastInsertId());
  returnValue.insert("rows", dataSet);
  return returnValue;
}

QVariant QmlSqlDatabaseData::castValue(const QVariant &value)
{
  QVariant newValue;

  switch (value.userType()) {
  case QVariant::String: 
    newValue = QVariant(QString(value.toString().data()));
    break;
  case QVariant::Int: 
    newValue = QVariant(value.toInt());
    break;
  case QVariant::LongLong: 
    newValue = QVariant(value.toLongLong());
    break;
  case  QVariant::Double: 
    newValue = QVariant(value.toDouble());
    break;
  default:
    newValue = QVariant();
    break;
  }

  return newValue;
}

QVariantMap QmlSqlDatabaseData::buildErrorResponse(QSqlError &error)
{ 
  QVariantMap returnValue;
  returnValue.insert("error", true);
  if (error.isValid()) {
    returnValue.insert("errorText", error.text());
    returnValue.insert("errorNumber", error.number());
  } else {
    returnValue.insert("errorText", "");
    returnValue.insert("errorNumber", 0);
  }

  return returnValue;
}
