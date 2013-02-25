/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QtCore/QCoreApplication>
#include <QmlExtension/App.h>

App::App(QObject *parent)
  : QObject(parent)
{
}

App::~App()
{
}

App* App::qmlAttachedProperties(QObject *obj)
{
  return new App(obj);
}

QStringList App::arguments() {
  return QCoreApplication::arguments();
}