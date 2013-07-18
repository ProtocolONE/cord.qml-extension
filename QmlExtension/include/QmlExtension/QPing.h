/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_QMLEXTENSION_QPING_H_
#define _GGS_QMLEXTENSION_QPING_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtDeclarative/QtDeclarative>

/*!
\class Phonon
\brief Реализует возможность отправлять icmp пакеты
\author Igor.Bugaev
\date 19.07.2013
*/
class QPing : public QObject
{
    Q_OBJECT

public:
    QPing(QObject* parent = 0);
    ~QPing();

    Q_INVOKABLE int pingHost(QString url);

    static QPing *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(QPing, QML_HAS_ATTACHED_PROPERTIES)

#endif // _GGS_QMLEXTENSION_QPING_H_