/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2013, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#pragma once

#include <Core/System/TaskList/TaskManager.h>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtDeclarative/QtDeclarative>

// UNDONE Ужасная строчка без, которой не компилиться moc_TaskList. 
// Очень бы хотелось найти того кто ее написал когда писала этот код и убить.
using namespace GGS::Core::System::TaskList;

class TaskList: public QObject
{
  Q_OBJECT
  Q_ENUMS(TaskManager::Type)

public:
  explicit TaskList(QObject* parent = 0);
  virtual ~TaskList();

  public:
    Q_INVOKABLE int addCategory(const QString& name);
    Q_INVOKABLE void removeCategory(int id);

    Q_INVOKABLE int addItem(int categoryId, QString icon, QString name, QString description, QString params);
    Q_INVOKABLE int addTask(QString icon, QString name, QString description, QString params);

    Q_INVOKABLE void setGuid(const QString& guid);

    Q_INVOKABLE void removeAllTasks();
    Q_INVOKABLE void removeAll();

    Q_INVOKABLE void apply();

    static TaskList *qmlAttachedProperties(QObject *obj);

private:
  ::GGS::Core::System::TaskList::TaskManager _manager;
};

QML_DECLARE_TYPEINFO(TaskList, QML_HAS_ATTACHED_PROPERTIES)
