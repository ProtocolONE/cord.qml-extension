#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtDeclarative/QDeclarative.h>

class TextDocumentHelper : public QObject
{
  Q_OBJECT

public:
  explicit TextDocumentHelper(QObject* obj);
  virtual ~TextDocumentHelper();

  static TextDocumentHelper *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString stripHtml(const QString& html);
};

QML_DECLARE_TYPEINFO(TextDocumentHelper, QML_HAS_ATTACHED_PROPERTIES)
