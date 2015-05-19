/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_QMLEXTENSION_APP_H_
#define _GGS_QMLEXTENSION_APP_H_

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtQuick/QQuickItem>

class Host : public QObject
{
  Q_OBJECT
public:
  Host(QObject* parent = 0);
  ~Host();

  Q_INVOKABLE QStringList arguments();
  Q_INVOKABLE QString hwid(bool async = false);

signals:
  void hwidChanged(QString hwid);

public:
  static Host *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(Host, QML_HAS_ATTACHED_PROPERTIES)

#endif // _GGS_QMLEXTENSION_APPLICATION_EXTENSION_H_