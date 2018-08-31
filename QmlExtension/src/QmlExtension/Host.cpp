#include <QmlExtension/Host.h>
#include <Core/System/HardwareId.h>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QCoreApplication>

Host::Host(QObject *parent)
  : QObject(parent)
{
}

Host::~Host()
{
}

Host* Host::qmlAttachedProperties(QObject *obj)
{
  return new Host(obj);
}

QStringList Host::arguments() {
  return QCoreApplication::arguments();
}

QString Host::hwid(bool async)
{
    if (!async)
        return P1::Core::System::HardwareId::value();

    QtConcurrent::run([](Host* obj){
        emit obj->hwidChanged(P1::Core::System::HardwareId::value());
    }, this);

    return QString();
}
