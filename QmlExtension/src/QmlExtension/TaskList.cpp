#include <QmlExtension/TaskList.h>

#include <Core/System/TaskList/TaskItem.h>

#include <QtCore/QCoreApplication>

using namespace P1::Core::System::TaskList;

TaskList::TaskList(QObject* parent) 
  : QObject(parent)
{
}

TaskList::~TaskList() 
{
}

void TaskList::apply()
{
  this->_manager.apply();
}

int TaskList::addItem(int categoryId, QString icon, QString name, QString description, QString params)
{
    TaskItem item;
    item.setIcon(icon);
    item.setName(name);
    item.setDescription(description);
    item.setUrl("protocolone://" + params);
    item.setParams("");

    return this->_manager.addItem(categoryId, item);
}

int TaskList::addTask(QString icon,  QString name, QString description, QString params)
{
    TaskItem item;
    item.setIcon(icon);
    item.setName(name);
    item.setDescription(description);
    item.setUrl("protocolone://" + params);
    item.setParams("");

    return this->_manager.addTask(item);
}

TaskList *TaskList::qmlAttachedProperties(QObject *obj)
{
  return new TaskList(obj);
}

int TaskList::addCategory( const QString& name )
{
  return this->_manager.addCategory(name);
}

void TaskList::removeCategory(int id)
{
  this->_manager.removeCategory(id);
}

void TaskList::setGuid(const QString& guid)
{
  this->_manager.setGuid(guid);
}

void TaskList::removeAllTasks()
{
  this->_manager.removeAllTasks();
}

void TaskList::removeAll()
{
  this->_manager.removeAll();
}
