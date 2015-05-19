#include <QmlExtension/FileSystem.h>

#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore/QTextCodec>

#include <QtQML/QJSEngine>

FileSystem::FileSystem(QObject *parent)
  : QObject(parent)
{
}

FileSystem::~FileSystem()
{
}

Q_INVOKABLE QVariantList FileSystem::findFiles(const QString &path, const QString &mask)
{
  QDir currentDir(path);

  QStringList maskList = mask.split("|");
  if (maskList.isEmpty()) {
    maskList.append("*.*");
  }

  QFileInfoList files = currentDir.entryInfoList(maskList, QDir::Files | QDir::NoSymLinks);

  QVariantList map;
  foreach(QFileInfo fileInfo, files) {
    map.append(fileInfo.absoluteFilePath());
  }

  return map;
}

Q_INVOKABLE bool FileSystem::exists(const QString &path)
{
  QFileInfo tmp(path);
  return tmp.exists();
}

Q_INVOKABLE QString FileSystem::readFile(const QString &path, const QString &encoding/*="UTF-8"*/)
{
  QFile file(path);
  if (!file.open(QFile::ReadOnly | QFile::Unbuffered)) {
    QJSEngine engine;
    engine.evaluate("throw new Error('" + file.errorString() + "')");
    return QString();
  }

  QByteArray data = file.readAll();
  if (0 == encoding.compare("UTF-8", Qt::CaseInsensitive)) 
    return QString::fromUtf8(data);
  
  QTextCodec *codec = QTextCodec::codecForName(encoding.toLatin1());
  QString unicodeString = codec->toUnicode(data);

  return QString(unicodeString.toUtf8());

}

Q_INVOKABLE qint64 FileSystem::writeFile(const QString &path, const QString &content, const QString &encoding/*="UTF-8"*/)
{
  QFileInfo fileInfo(path);

  QDir fileDir = fileInfo.absoluteDir();
  if (!fileDir.exists() && !fileDir.mkpath(fileInfo.absolutePath())) {
      QJSEngine engine;
      engine.evaluate("throw new Error('Can`t create folder " + fileInfo.absolutePath() + "')");
      return -1;
  }
  
  QFile file(path);
  if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Unbuffered)) {
    QJSEngine engine;
    engine.evaluate("throw new Error('" + file.errorString() + "')");
    return -1;
  }

  if (0 == encoding.compare("UTF-8", Qt::CaseInsensitive)) 
    return file.write(content.toUtf8());
  
  QTextCodec *codec = QTextCodec::codecForName(encoding.toLatin1());
  return file.write(codec->fromUnicode(content));
}

FileSystem* FileSystem::qmlAttachedProperties(QObject *obj)
{
  return new FileSystem(obj); 
}
