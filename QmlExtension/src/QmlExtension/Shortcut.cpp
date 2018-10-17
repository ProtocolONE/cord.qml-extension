#include <QmlExtension/Shortcut.h>
#include <QtGui/QKeyEvent>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

Shortcut::Shortcut(QObject *parent)
  : QObject(parent)
  , _keySequence()
  , _keypressAlreadySend(false)
{
  qApp->installEventFilter(this);
}

Shortcut::~Shortcut()
{
}

void Shortcut::setKey(QVariant key)
{
  QKeySequence newKey = key.value<QKeySequence>();
  if(_keySequence != newKey) {
    _keySequence = key.value<QKeySequence>();
    emit keyChanged();
  }
}

bool Shortcut::eventFilter(QObject *obj, QEvent *e)
{
  if(e->type() == QEvent::KeyPress && !_keySequence.isEmpty()) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    // Just mod keys is not enough for a shortcut, block them just by returning.
    if (keyEvent->key() >= Qt::Key_Shift && keyEvent->key() <= Qt::Key_Alt) {
      return QObject::eventFilter(obj, e);
    }

    int keyInt = keyEvent->modifiers() + keyEvent->key();

    if(!_keypressAlreadySend && QKeySequence(keyInt) == _keySequence) {
      _keypressAlreadySend = true;
      emit activated();
    }
  }
  else if(e->type() == QEvent::KeyRelease) {
    _keypressAlreadySend = false;
  }
  return QObject::eventFilter(obj, e);
}