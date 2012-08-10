/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/QmlExtension.h>
#include <QmlExtension/QCursorArea.h>
#include <QmlExtension/WheelArea.h>
#include <QmlExtension/QWindowItem.h>
#include <QmlExtension/QDesktopItem.h>
#include <QmlExtension/SettingsAdapter.h>

void QmlExtension::registerTypes(const char *uri)
{
  qmlRegisterType<QCursorArea>("Tulip", 1, 0, "CursorArea");
  qmlRegisterType<WheelArea>("Tulip", 1, 0, "WheelArea");
  qmlRegisterType<QWindowItem>("Tulip", 1, 0, "Window");

  qmlRegisterUncreatableType<QDesktopItem>("Tulip", 1, 0, "Desktop", QLatin1String("Do not create objects of type Desktop"));
  qmlRegisterUncreatableType<SettingsAdapter>("Tulip", 1, 0, "Settings", QLatin1String("Do not create objects of type Settings"));
}

void QmlExtension::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
}

#ifdef _DEBUG
Q_EXPORT_PLUGIN2(QmlExtensionX86d, QmlExtension);
#else
Q_EXPORT_PLUGIN2(QmlExtensionX86, QmlExtension);
#endif