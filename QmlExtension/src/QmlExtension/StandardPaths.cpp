#include <QmlExtension/StandardPaths.h>

StandardPaths::StandardPaths(QObject* parent)
  : QObject(parent)
{
}

StandardPaths::~StandardPaths()
{
}

StandardPaths* StandardPaths::qmlAttachedProperties(QObject *obj)
{
  return new StandardPaths(obj);
}

QString StandardPaths::writableLocation(uint type)
{
  return QStandardPaths::writableLocation(static_cast<QStandardPaths::StandardLocation>(type));
}
