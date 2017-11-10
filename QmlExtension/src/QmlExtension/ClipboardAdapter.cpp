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

void ClipboardAdapter::setText(QString text)
{
  _clipboard->setText(text);
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

void ClipboardAdapter::setQuote(QString text, QString author, QString date)
{
  QMimeData* data = new QMimeData;
  data->setText(text);

  QString quote = "[quote author=\"" + author + "\" date=\"" + date + "\"]" + text + "[/quote]";
  data->setData("qGNAQuoteFormat", quote.toUtf8());

  _clipboard->setMimeData(data);
}

bool ClipboardAdapter::hasQuote() const
{
  const QMimeData* data = _clipboard->mimeData();
  return data->hasFormat("qGNAQuoteFormat");
}

QString ClipboardAdapter::quote() const
{
  const QMimeData* data = _clipboard->mimeData();
  return data->data("qGNAQuoteFormat");
}
