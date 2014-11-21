#include <QmlExtension/LocalStorage/LocalStorage.h>

#include <QtSql/QSqlDriver>
#include <QtCore/QCoreApplication>
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
  if (!QSqlDatabase::contains(dbname)) {
    QSqlDatabase db;

    QString dirPath = QString("%1/%2")
      .arg(qApp->applicationDirPath())
      .arg(folder);

    QDir dir(dirPath);
    if (!dir.exists())
      dir.mkpath(dirPath);

    QString basename = QString("%1/%2.sqlite")
      .arg(dirPath)
      .arg(dbname);

    db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), dbname);
    db.setDatabaseName(basename);
    db.close();
  }

   QmlSqlDatabaseData *sqlDb = new QmlSqlDatabaseData(this, dbname);
   QDeclarativeEngine::setObjectOwnership(sqlDb, QDeclarativeEngine::JavaScriptOwnership);
   return  sqlDb;
}