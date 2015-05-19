#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQuick/QQuickItem>

class BrowserDetect : public QObject
{
  Q_OBJECT

public:
  explicit BrowserDetect(QObject* obj);
  virtual ~BrowserDetect();

  static BrowserDetect *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString getBrowserName();
};

QML_DECLARE_TYPEINFO(BrowserDetect, QML_HAS_ATTACHED_PROPERTIES)
