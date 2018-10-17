#pragma once
#include <QtQuick/QQuickItem>

//More in http://kdeblog.mageprojects.com/2012/12/07/application-wide-shortcuts-in-qml-this-time-without-qshortcut/
class Shortcut : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QVariant key READ key WRITE setKey NOTIFY keyChanged)
public:
  explicit Shortcut(QObject *parent = 0);
  virtual ~Shortcut();

  void setKey(QVariant key);
  QVariant key() { return _keySequence; }

  bool eventFilter(QObject *obj, QEvent *e);

signals:
  void keyChanged();
  void activated();
  void pressedAndHold();

  public slots:

private:
  QKeySequence _keySequence;
  bool _keypressAlreadySend;
};