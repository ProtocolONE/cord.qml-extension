#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtQuick/QQuickItem>

class TextDocumentHelper : public QObject
{
  Q_OBJECT

public:
  explicit TextDocumentHelper(QObject* obj = nullptr);
  virtual ~TextDocumentHelper();

  static TextDocumentHelper *qmlAttachedProperties(QObject *obj);

  Q_INVOKABLE QString stripHtml(const QString& html);
};

QML_DECLARE_TYPEINFO(TextDocumentHelper, QML_HAS_ATTACHED_PROPERTIES)
