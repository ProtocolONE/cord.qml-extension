/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2014, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/StyleReader.h>

#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QJsonDocument>
#include <QtCore/QFile>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>

StyleReader::StyleReader(QObject *parent)
  : QObject(parent)
{
}

StyleReader::~StyleReader()
{
}

Q_INVOKABLE QVariantList StyleReader::read(const QString &path)
{
  QDir currentDir(path);

  QFileInfoList files = currentDir.entryInfoList(QStringList("*.style"), QDir::Files | QDir::NoSymLinks);
  QVariantList map;
  QJsonParseError parseError;

  foreach(QFileInfo fileInfo, files) {
    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QFile::ReadOnly | QFile::Text)) 
      continue;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error == QJsonParseError::NoError) 
      map.append(doc.toVariant());
  }

  return map;
}

StyleReader * StyleReader::qmlAttachedProperties(QObject *obj)
{
  return new StyleReader(obj);
}
