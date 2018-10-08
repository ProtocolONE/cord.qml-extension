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

#include <QtWidgets/QApplication>
#include <QQuickWindow>
#include <QMenuBar>

/*!
  \class QWindowItem
  \brief Реализует логику по созданию дочернего окна приложения.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class QWindowItem : public QQuickWindow
{
    Q_OBJECT

    Q_PROPERTY(bool windowDecoration READ windowDecoration WRITE setWindowDecoration NOTIFY windowDecorationChanged)
    Q_PROPERTY(Qt::WindowModality modality READ modality WRITE setModality NOTIFY modalityChanged)
    Q_PROPERTY(bool deleteOnClose READ deleteOnClose WRITE setDeleteOnClose NOTIFY deleteOnCloseChanged)

    Q_PROPERTY(bool topMost READ topMost WRITE setTopMost NOTIFY topMostChanged)
    Q_PROPERTY(Qt::WindowFlags flags READ flags WRITE setFlags)

public:
    QWindowItem(QWindow *parent = 0);
    ~QWindowItem();

    bool windowDecoration() const { return !(this->flags() & Qt::FramelessWindowHint); }
    Qt::WindowState windowState() const { return static_cast<Qt::WindowState>(static_cast<int>(this->windowState()) & ~Qt::WindowActive); }
    bool deleteOnClose() const { return _deleteOnClose; }
    bool topMost() const { return this->flags() & Qt::WindowStaysOnTopHint; }

    void setWindowDecoration(bool s);
    void setWindowState(Qt::WindowState state) { this->setWindowState(state); }
    void setModality(Qt::WindowModality modality);
    void setDeleteOnClose(bool close);
    void setTopMost(bool value);

    void setFlags(Qt::WindowFlags flags);


public Q_SLOTS:
    void close();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

signals:
    void windowDecorationChanged();
    void modalityChanged();
    void deleteOnCloseChanged();
    void topMostChanged();
    void beforeClosed();

private:
    bool _complete;
    bool _positionIsDefined;
    bool _delayedVisible;
    bool _deleteOnClose;
};