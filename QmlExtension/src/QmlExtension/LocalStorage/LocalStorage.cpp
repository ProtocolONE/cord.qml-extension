#include <QmlExtension/LocalStorage/LocalStorage.h>

#include <QtSql/QSqlDriver>
#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QCryptographicHash>
#include <QtCore/QDir>

LocalStorage * LocalStorage::qmlAttachedProperties(QObject *obj)
{
  return new LocalStorage(obj);
}

LocalStorage::LocalStorage(QObject *parent)
  : QObject(parent)
{
}

LocalStorage::~LocalStorage()
{
}

QmlSqlDatabaseData* LocalStorage::openDatabaseSync(
  QString folder,
  QString dbname,
  QString version,
  QString description,
  int estimated_size)
{
  QString applicationDbRoot = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/db";
  QString dirPath = QString("%1/%2")
    .arg(applicationDbRoot)
    .arg(folder);

  QDir dir(dirPath);
  if (!dir.exists())
    dir.mkpath(dirPath);

  QString basename = QString("%1/%2.sqlite")
    .arg(dirPath)
    .arg(dbname);

  QCryptographicHash md5(QCryptographicHash::Md5);
  md5.addData(basename.toUtf8());
  QString dbid(QLatin1String(md5.result().toHex()));

  if (!QSqlDatabase::contains(dbid)) {
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), dbid);
    db.setDatabaseName(basename);
    db.close();
  }

  QmlSqlDatabaseData *sqlDb = new QmlSqlDatabaseData(this, dbid);
  //QDeclarativeEngine::setObjectOwnership(sqlDb, QDeclarativeEngine::JavaScriptOwnership);
  return  sqlDb;
}