/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2014, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#pragma once

#include <QtCore/QString>
#include <QtCore/QObject>

#include <QtCore/QVariantList>
#include <QtQuick/QQuickItem>

class StyleReader : public QObject
{
  Q_OBJECT
public:
  explicit StyleReader(QObject *parent = 0);
  virtual ~StyleReader();

  Q_INVOKABLE QVariantList read(const QString &path);

  static StyleReader *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(StyleReader, QML_HAS_ATTACHED_PROPERTIES)