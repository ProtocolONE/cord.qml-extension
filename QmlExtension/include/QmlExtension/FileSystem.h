#pragma once
#include <QtCore/QObject>

#include <QtCore/QVariantList>
#include <QtQuick/QQuickItem>

class FileSystem : public QObject
{
  Q_OBJECT
public:
    explicit FileSystem(QObject *parent = 0);
    virtual ~FileSystem();
    
    Q_INVOKABLE QVariantList findFiles(const QString &path, const QString &mask);
    Q_INVOKABLE bool exists(const QString &path);
    Q_INVOKABLE QString readFile(const QString &path, const QString &encoding="UTF-8");
    Q_INVOKABLE qint64 writeFile(const QString &path, const QString &content, const QString &encoding="UTF-8");

    static FileSystem* qmlAttachedProperties(QObject *obj);
};

QML_DECLARE_TYPEINFO(FileSystem, QML_HAS_ATTACHED_PROPERTIES)