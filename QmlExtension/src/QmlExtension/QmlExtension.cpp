#include <QmlExtension/QmlExtension.h>
#include <QmlExtension/QCursorArea.h>
#include <QmlExtension/WheelArea.h>
#include <QmlExtension/QWindowItem.h>

void QmlExtension::registerTypes(const char *uri)
{
  qmlRegisterType<QCursorArea>("Tulip", 1, 0, "CursorArea");
  qmlRegisterType<WheelArea>("Tulip", 1, 0, "WheelArea");
  
  qmlRegisterType<QWindowItem>("Tulip", 1, 0, "Window");
}

void QmlExtension::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{

}

#ifdef _DEBUG
Q_EXPORT_PLUGIN2(QmlExtensionX86d, QmlExtension);
#else
Q_EXPORT_PLUGIN2(QmlExtensionX86, QmlExtension);
#endif