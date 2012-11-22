#include <QmlExtension/QFileDialogAdapter.h>

QFileDialogAdapter::QFileDialogAdapter(QObject* obj)
   : QObject(obj)
{
}

QFileDialogAdapter::~QFileDialogAdapter(void)
{
}

QFileDialogAdapter * QFileDialogAdapter::qmlAttachedProperties(QObject *obj)
{
  return new QFileDialogAdapter(obj);
}

Q_INVOKABLE QString QFileDialogAdapter::getOpenFileName(const QString& caption, const QString& dir, const QString& filter) const
{
  return QFileDialog::getOpenFileName(0, caption, dir, filter);
}
