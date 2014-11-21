#include <QmlExtension/TextDocumentHelper.h>

#include <QtCore/QFileInfo>
#include <QtCore/QSettings>

#include <QtGui/QTextDocument>

TextDocumentHelper::TextDocumentHelper(QObject* obj) : QObject(obj)
{
}

TextDocumentHelper::~TextDocumentHelper()
{
}

TextDocumentHelper *TextDocumentHelper::qmlAttachedProperties(QObject *obj) 
{
  return new TextDocumentHelper(obj);
}

Q_INVOKABLE QString TextDocumentHelper::stripHtml(const QString& html)
{
  QTextDocument d;
  d.setHtml(html);
  return d.toPlainText();
}