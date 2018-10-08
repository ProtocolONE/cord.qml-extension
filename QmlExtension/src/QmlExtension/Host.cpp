/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/


#include <QmlExtension/Host.h>
#include <Core/System/HardwareId.h>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QCoreApplication>

Host::Host(QObject *parent)
  : QObject(parent)
{
}

Host::~Host()
{
}

Host* Host::qmlAttachedProperties(QObject *obj)
{
  return new Host(obj);
}

QStringList Host::arguments() {
  return QCoreApplication::arguments();
}

QString Host::hwid(bool async)
{
    if (!async)
        return GGS::Core::System::HardwareId::value();

    QtConcurrent::run([](Host* obj){
        emit obj->hwidChanged(GGS::Core::System::HardwareId::value());
    }, this);

    return QString();
}