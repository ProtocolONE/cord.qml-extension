#pragma once

#include <QtQuick/QQuickItem>
#include <QtCore/QObject>
#include <QtCore/QString>

class QClipboard;

class ClipboardAdapter : public QObject
{
  Q_OBJECT
public:
  explicit ClipboardAdapter(QObject *parent = 0);
  virtual ~ClipboardAdapter();

  static ClipboardAdapter* qmlAttachedProperties(QObject *obj);

public:
  Q_INVOKABLE bool hasText() const;
  Q_INVOKABLE QString text() const;

private:
  QClipboard* _clipboard = nullptr;
};

QML_DECLARE_TYPEINFO(ClipboardAdapter, QML_HAS_ATTACHED_PROPERTIES)
