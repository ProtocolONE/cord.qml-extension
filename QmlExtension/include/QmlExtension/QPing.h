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
#include <QtCore/QString>
#include <QtCore/QFutureWatcher>
#include <QtDeclarative/QtDeclarative>

/*!
\class Ping
\brief Реализует возможность отправлять icmp пакеты
\author Igor.Bugaev
\date 19.07.2013
*/
class QPing : public QObject
{
    Q_OBJECT
public:
    explicit QPing(QObject* parent = 0);
    ~QPing();

    Q_INVOKABLE void start(const QString& url);

signals:
    void success(quint32 value);
    void failed();

private:
    QFutureWatcher<void> watcher;
    void sync(QString url);
};