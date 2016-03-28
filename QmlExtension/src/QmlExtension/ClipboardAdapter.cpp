#include <QmlExtension/ClipboardAdapter.h>

#include <QApplication>
#include <QClipboard>
#include <QMimeData>

ClipboardAdapter::ClipboardAdapter(QObject *parent /*= 0*/)
  : QObject(parent), _clipboard(QApplication::clipboard())
{
}

ClipboardAdapter::~ClipboardAdapter()
{
}

ClipboardAdapter* ClipboardAdapter::qmlAttachedProperties(QObject *obj)
{
  return new ClipboardAdapter(obj);
}

bool ClipboardAdapter::hasText() const
{
  const QMimeData* data = _clipboard->mimeData();
  return data->hasText();
}

QString ClipboardAdapter::text() const
{
  return _clipboard->text();
}
