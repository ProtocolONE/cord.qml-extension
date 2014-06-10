/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/


#include <QmlExtension/App.h>
#include <Core/System/HardwareId.h>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QCoreApplication>

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

QString App::hwid(bool async)
{
    if (!async)
        return GGS::Core::System::HardwareId::value();

    QtConcurrent::run([](App* obj){
        emit obj->hwidChanged(GGS::Core::System::HardwareId::value());
    }, this);

    return QString();
}