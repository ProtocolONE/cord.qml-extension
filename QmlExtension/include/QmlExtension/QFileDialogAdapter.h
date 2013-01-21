#pragma once

#include <QtDeclarative>
#include <QtCore/QString>

class QFileDialogAdapter : public QObject
{
  Q_OBJECT
public:
  QFileDialogAdapter(QObject* obj);
  ~QFileDialogAdapter(void);

  static QFileDialogAdapter *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString getOpenFileName(const QString& caption, const QString& dir, const QString& filter) const;
  Q_INVOKABLE QString getExistingDirectory(const QString& caption, const QString& dir) const;
};

QML_DECLARE_TYPEINFO(QFileDialogAdapter, QML_HAS_ATTACHED_PROPERTIES)