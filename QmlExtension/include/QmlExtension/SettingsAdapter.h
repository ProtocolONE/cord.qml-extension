#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtQuick/QQuickItem>

/*!
  \class SettingsAdapter
  \brief Реализует возможность работать с P1::Settings::Settings, если они настроены, или использовать станданртные 
         QSettings в QML.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class SettingsAdapter : public QObject
{
  Q_OBJECT
public:
  explicit SettingsAdapter(QObject* parent = 0);
  virtual ~SettingsAdapter();

  Q_INVOKABLE void setValue(const QString& group, const QString& key, const QVariant& value) const;
  Q_INVOKABLE QVariant value(const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;
  Q_INVOKABLE void remove(const QString& group, const QString& key) const;

  static SettingsAdapter *qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(SettingsAdapter, QML_HAS_ATTACHED_PROPERTIES)