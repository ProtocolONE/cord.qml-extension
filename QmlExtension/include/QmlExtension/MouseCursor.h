#pragma once

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtQuick/QQuickItem>

#include <Windows.h>

namespace P1 {

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

QML_DECLARE_TYPEINFO(P1::MouseCursor, QML_HAS_ATTACHED_PROPERTIES)