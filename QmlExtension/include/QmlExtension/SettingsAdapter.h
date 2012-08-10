/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_QMLEXTENSION_SETTINGSADPATER_H_
#define _GGS_QMLEXTENSION_SETTINGSADPATER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtDeclarative/QtDeclarative>


/*!
  \class SettingsAdapter
  \brief Реализует возможность работать с GGS::Settings::Settings, если они настроены, или использовать станданртные 
         QSettings в QML.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class SettingsAdapter : public QObject
{
  Q_OBJECT
public:
  SettingsAdapter(QObject* parent = 0);
  ~SettingsAdapter();

  Q_INVOKABLE void setValue(const QString& group, const QString& key, const QVariant& value) const;
  Q_INVOKABLE QVariant value(const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;

  static SettingsAdapter *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(SettingsAdapter, QML_HAS_ATTACHED_PROPERTIES)

#endif // _GGS_QMLEXTENSION_SETTINGSADPATER_H_