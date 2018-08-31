#pragma once

#include <Core/System/TaskList/TaskManager.h>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtQuick/QQuickItem>

class TaskList: public QObject
{
  Q_OBJECT
  Q_ENUMS(P1::Core::System::TaskList::TaskManager::Type)

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
  ::P1::Core::System::TaskList::TaskManager _manager;
};

QML_DECLARE_TYPEINFO(TaskList, QML_HAS_ATTACHED_PROPERTIES)
