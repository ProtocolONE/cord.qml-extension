/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_QMLEXTENSION_QMULTIMEDIA_H_
#define _GGS_QMLEXTENSION_QMULTIMEDIA_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtDeclarative/QDeclarative.h>

/*!
  \class Phonon
  \brief Реализует возможность работать с аудио потоком
  \author Igor.Bugaev
  \date 21.05.2013
*/
class QMultimedia : public QObject
{
  Q_OBJECT
public:
  QMultimedia(QObject* parent = 0);
  ~QMultimedia();

  Q_INVOKABLE void playSound(QString url);

  static QMultimedia *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(QMultimedia, QML_HAS_ATTACHED_PROPERTIES)

#endif // _GGS_QMLEXTENSION_QMULTIMEDIA_H_