/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/QMultimedia.h>
#include <QtGui/QSound>

QMultimedia::QMultimedia(QObject* parent) {
}

QMultimedia::~QMultimedia() {
}

void QMultimedia::playSound(QString url) {
	QSound::play(url);
}

QMultimedia *QMultimedia::qmlAttachedProperties(QObject *obj) {
  return new QMultimedia(obj);
}