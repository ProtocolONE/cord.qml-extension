#pragma once

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

class GoogleAnalytics : public QObject
{
  Q_OBJECT

public:
  explicit GoogleAnalytics(QObject* obj = nullptr);
  virtual ~GoogleAnalytics();

  static GoogleAnalytics *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString systemLanguage();
  Q_INVOKABLE QString systemVersion();
  Q_INVOKABLE QString winVersion();

};

QML_DECLARE_TYPEINFO(GoogleAnalytics, QML_HAS_ATTACHED_PROPERTIES)
