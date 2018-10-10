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

#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantList>
#include <QtWidgets/QDesktopWidget>
#include <QtQuick/QQuickItem>

/*!
  \class QDesktopItem
  \brief Позволяет получать гемотрию экрана и уведомления о изменениях.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class QDesktopItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY screenGeometryChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenGeometryChanged)
    Q_PROPERTY(int availableWidth READ availableWidth NOTIFY availableGeometryChanged)
    Q_PROPERTY(int availableHeight READ availableHeight NOTIFY availableGeometryChanged)
    Q_PROPERTY(int screenCount READ screenCount NOTIFY screenCountChanged)
    Q_PROPERTY(int primaryScreen READ primaryScreen NOTIFY screenCountChanged)

    Q_PROPERTY(QRect primaryScreenAvailableGeometry READ primaryScreenAvailableGeometry NOTIFY primaryScreenAvailableGeometryChanged)

public:
    QDesktopItem(QObject* obj);

    int screenCount() const;
    Q_INVOKABLE QRect screenGeometry(int screen) const;
    Q_INVOKABLE int screenNumber(int xpos, int ypos) const;
    Q_INVOKABLE QRect availableGeometry(int screen) const;
    Q_INVOKABLE QVariantList availableResolutions();
    int screenWidth() const;
    int screenHeight() const;
    int availableWidth() const;
    int availableHeight() const;
    int primaryScreen() const;
    QRect primaryScreenAvailableGeometry() const;

    static QDesktopItem *qmlAttachedProperties(QObject *obj);
public slots:
    void anythingChanged();

Q_SIGNALS:
    void screenGeometryChanged();
    void availableGeometryChanged();
    void screenCountChanged();

    void primaryScreenAvailableGeometryChanged();
};

QML_DECLARE_TYPEINFO(QDesktopItem, QML_HAS_ATTACHED_PROPERTIES)
