/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef QMLEXTENSION_H
#define QMLEXTENSION_H

#include <QmlExtension/qmlextension_global.h>

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class QmlExtension : public QDeclarativeExtensionPlugin
{
  Q_OBJECT

public:
  void registerTypes(const char *uri);
  void initializeEngine(QDeclarativeEngine *engine, const char *uri);

};

#endif // QMLEXTENSION_H
