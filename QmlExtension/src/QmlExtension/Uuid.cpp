#include <QmlExtension/Uuid.h>
#include <QtCore/QUuid>

Uuid::Uuid(QObject* parent)
  : QObject(parent)
{

}

Uuid::~Uuid()
{
}

Uuid * Uuid::qmlAttachedProperties(QObject *obj)
{
  return new Uuid(obj);
}

Q_INVOKABLE QString Uuid::create()
{
  return QUuid::createUuid().toString();
}
