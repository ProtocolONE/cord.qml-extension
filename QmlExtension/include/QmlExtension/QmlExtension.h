#pragma once

#include <QmlExtension/qmlextension_global.h>
#include <QtQml/QQmlExtensionPlugin>

class QmlExtension : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "vab.pone.Tulip" FILE "tulip.json")

public:
  void registerTypes(const char *uri);
  void initializeEngine(QQmlEngine *engine, const char *uri);
};
