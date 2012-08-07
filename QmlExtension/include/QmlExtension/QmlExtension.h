#ifndef QMLEXTENSION_H
#define QMLEXTENSION_H

#include <QmlExtension/qmlextension_global.h>

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class QmlExtension : public QDeclarativeExtensionPlugin
{
  Q_OBJECT

public:
  void registerTypes(const char *uri);
  void initializeEngine(QDeclarativeEngine *engine, const char *uri);

};

#endif // QMLEXTENSION_H
