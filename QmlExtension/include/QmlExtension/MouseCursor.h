/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtDeclarative/QtDeclarative>

#include <Windows.h>

namespace GGS {

  class MouseCursor : public QObject
  {
    Q_OBJECT
  public:
    explicit MouseCursor(QObject *parent = 0);
    virtual ~MouseCursor();

    static MouseCursor *qmlAttachedProperties(QObject *obj);
    Q_INVOKABLE QPoint mousePos();
    Q_INVOKABLE QPoint debugOnlyWindowPos();

  private:
    HWND _mainWindow;
  };
}

QML_DECLARE_TYPEINFO(GGS::MouseCursor, QML_HAS_ATTACHED_PROPERTIES)