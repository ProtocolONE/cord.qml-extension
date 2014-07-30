#include <QmlExtension/LocalStorage/LocalStorage.h>

#include <QtSql/QSqlDriver>

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

QmlSqlDatabaseData * LocalStorage::openDatabaseSync(QString dbname, QString version, QString description, int estimated_size)
{
  
    QSqlDatabase db;
    if (QSqlDatabase::contains(dbname)) {
      db = QSqlDatabase::database(dbname);
    } else {
      QString basename = qApp->applicationDirPath() + dbname;
      db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), dbname);
      db.setDatabaseName(basename + QLatin1String(".sqlite"));
    }

    db.close();
  
  
   

   QmlSqlDatabaseData *sqlDb = new QmlSqlDatabaseData(this, dbname);
   QDeclarativeEngine::setObjectOwnership(sqlDb, QDeclarativeEngine::JavaScriptOwnership);
   // 
   //QSqlDatabase::isDriverAvailable ( const QString & name )
   return  sqlDb;

//   if (!db.isOpen())
//     if (!db.open()) {
//       qDebug() << db.lastError().text();
//     };

   
//  QmlSqlDatabaseData *sqlDb = new QmlSqlDatabaseData(this->parent(), dbname);
  //QDeclarativeEngine::setObjectOwnership(sqlDb, QDeclarativeEngine::JavaScriptOwnership);

  return sqlDb;


  /*
  if (engine->engine()->offlineStoragePath().isEmpty())
  V4THROW_SQL2(SQLEXCEPTION_DATABASE_ERR, QQmlEngine::tr("SQL: can't create database, offline storage is disabled."));

  qmlsqldatabase_initDatabasesPath(engine);

  QSqlDatabase database;

  QV4::ScopedValue v(scope);
  QString dbname = (v = (*args)[0])->toQStringNoThrow();
  QString dbversion = (v = (*args)[1])->toQStringNoThrow();
  QString dbdescription = (v = (*args)[2])->toQStringNoThrow();
  int dbestimatedsize = (v = (*args)[3])->toInt32();
  FunctionObject *dbcreationCallback = (v = (*args)[4])->asFunctionObject();

  QCryptographicHash md5(QCryptographicHash::Md5);
  md5.addData(dbname.toUtf8());
  QString dbid(QLatin1String(md5.result().toHex()));

  QString basename = qmlsqldatabase_databaseFile(dbid, engine);
  bool created = false;
  QString version = dbversion;

  {
  QSettings ini(basename+QLatin1String(".ini"),QSettings::IniFormat);

  if (QSqlDatabase::connectionNames().contains(dbid)) {
  database = QSqlDatabase::database(dbid);
  version = ini.value(QLatin1String("Version")).toString();
  if (version != dbversion && !dbversion.isEmpty() && !version.isEmpty())
  V4THROW_SQL2(SQLEXCEPTION_VERSION_ERR, QQmlEngine::tr("SQL: database version mismatch"));
  } else {
  created = !QFile::exists(basename+QLatin1String(".sqlite"));
  if (created) {
  ini.setValue(QLatin1String("Name"), dbname);
  if (dbcreationCallback)
  version = QString();
  ini.setValue(QLatin1String("Version"), version);
  ini.setValue(QLatin1String("Description"), dbdescription);
  ini.setValue(QLatin1String("EstimatedSize"), dbestimatedsize);
  ini.setValue(QLatin1String("Driver"), QLatin1String("QSQLITE"));
  } else {
  if (!dbversion.isEmpty() && ini.value(QLatin1String("Version")) != dbversion) {
  // Incompatible
  V4THROW_SQL2(SQLEXCEPTION_VERSION_ERR,QQmlEngine::tr("SQL: database version mismatch"));
  }
  version = ini.value(QLatin1String("Version")).toString();
  }
  database = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), dbid);
  database.setDatabaseName(basename+QLatin1String(".sqlite"));
  }
  if (!database.isOpen())
  database.open();
  }

  QV4::Scoped<QQmlSqlDatabaseWrapper> db(scope, new (ctx->engine->memoryManager) QQmlSqlDatabaseWrapper(engine));
  QV4::ScopedObject p(scope, databaseData(engine)->databaseProto.value());
  db->setPrototype(p.getPointer());
  db->database = database;
  db->version = version;

  if (created && dbcreationCallback) {
  Scope scope(ctx);
  ScopedCallData callData(scope, 1);
  callData->thisObject = engine->global();
  callData->args[0] = db;
  dbcreationCallback->call(callData);
  }

  args->setReturnValue(db.asReturnedValue());
  #endif // QT_NO_SETTINGS
  */
}