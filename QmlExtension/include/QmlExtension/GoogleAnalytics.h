#pragma once

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarative.h>

class GoogleAnalytics : public QObject
{
  Q_OBJECT

public:
  GoogleAnalytics(QObject* obj);
  ~GoogleAnalytics();

  static GoogleAnalytics *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString systemLanguage();
  Q_INVOKABLE QString systemVersion();
};

QML_DECLARE_TYPEINFO(GoogleAnalytics, QML_HAS_ATTACHED_PROPERTIES)
