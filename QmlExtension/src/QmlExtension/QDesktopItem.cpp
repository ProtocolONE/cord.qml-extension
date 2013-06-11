/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QmlExtension/QDesktopItem.h>

<<<<<<< HEAD
#include <QtCore/QPoint>
#include <QtGui/QApplication>
=======
#include <QtWidgets/QApplication>
<<<<<<< HEAD
#include <QtWidgets/QDesktopWidget>
>>>>>>> 10e6b27... QGNA-0 Qt5 support
=======
>>>>>>> 37f521a... QGNA-448 Qt5

QDesktopItem::QDesktopItem(QObject* obj) : QObject(obj) {
    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SIGNAL(screenGeometryChanged()));
    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SIGNAL(availableGeometryChanged()));
    connect(QApplication::desktop(), SIGNAL(workAreaResized(int)), this, SIGNAL(availableGeometryChanged()));
    connect(QApplication::desktop(), SIGNAL(screenCountChanged(int)), this, SIGNAL(screenCountChanged()));

    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(anythingChanged()));
    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(anythingChanged()));
    connect(QApplication::desktop(), SIGNAL(workAreaResized(int)), this, SLOT(anythingChanged()));
    connect(QApplication::desktop(), SIGNAL(screenCountChanged(int)), this, SLOT(anythingChanged()));
}

int QDesktopItem::screenCount() const
{
    return QApplication::desktop()->screenCount();
}

QRect QDesktopItem::screenGeometry(int screen) const {
    return QApplication::desktop()->screenGeometry(screen);
}

QRect QDesktopItem::availableGeometry(int screen) const {
    return QApplication::desktop()->availableGeometry(screen);
}

int QDesktopItem::screenWidth() const
{
    return QApplication::desktop()->screenGeometry().width();
}

int QDesktopItem::screenHeight() const
{
    return QApplication::desktop()->screenGeometry().height();
}

int QDesktopItem::availableWidth() const
{
    return QApplication::desktop()->availableGeometry().width();
}

int QDesktopItem::availableHeight() const
{
    return QApplication::desktop()->availableGeometry().height();
}

QDesktopItem *QDesktopItem::qmlAttachedProperties(QObject *obj) {
    return new QDesktopItem(obj);
}

void QDesktopItem::anythingChanged()
{
  emit this->primaryScreenAvailableGeometryChanged();
}

QRect QDesktopItem::primaryScreenAvailableGeometry() const
{
  return this->availableGeometry(QApplication::desktop()->primaryScreen());
}

int QDesktopItem::primaryScreen() const
{
  return QApplication::desktop()->primaryScreen();
}

Q_INVOKABLE int QDesktopItem::screenNumber(int xpos, int ypos) const
{
  return QApplication::desktop()->screenNumber(QPoint(xpos, ypos));
}

