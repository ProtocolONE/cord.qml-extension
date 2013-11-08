/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/TaskList.h>
#include <QtCore/QString>
#include <QCoreApplication>
#include <qDebug>

using namespace GGS::Core::System::TaskList;

TaskList::TaskList(QObject* parent) 
{
}

TaskList::~TaskList() 
{
}

void TaskList::apply() {
  this->_manager.apply();
}

int TaskList::addItem(int categoryId, QString icon, QString name, QString description, QString params) {
    TaskItem item;
    item.setIcon(icon);
    item.setName(name);
    item.setDescription(description);
    item.setUrl(QCoreApplication::applicationFilePath());
    item.setParams(params);

    return this->_manager.addItem(categoryId, item);
}

int TaskList::addTask(QString icon,  QString name, QString description, QString params) {
    TaskItem item;
    item.setIcon(icon);
    item.setName(name);
    item.setDescription(description);
    item.setUrl(QCoreApplication::applicationFilePath());
    item.setParams(params);

    return this->_manager.addTask(item);
}

TaskList *TaskList::qmlAttachedProperties(QObject *obj) {
  return new TaskList(obj);
}

int TaskList::addCategory( const QString& name ) {
  return this->_manager.addCategory(name);
}

void TaskList::removeCategory(int id) {
  this->_manager.removeCategory(id);
}

void TaskList::setGuid(const QString& guid) {
  this->_manager.setGuid(guid);
}

void TaskList::removeAllTasks() {
  this->_manager.removeAllTasks();
}

void TaskList::removeAll() {
  this->_manager.removeAll();
}
