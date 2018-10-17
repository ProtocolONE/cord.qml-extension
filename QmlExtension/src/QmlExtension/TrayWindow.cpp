#include <QmlExtension/traywindow.h>

#include <QtGui/QMovie>
#include <QtGui/QCursor>

TrayWindow::TrayWindow(QObject* parent) 
  : QObject(parent)
  , _systray(0)
  , _animatedIcon(0)
{
}

TrayWindow::~TrayWindow()
{
  clearAnimatedIcon();
  if (this->_systray) 
    this->_systray->setVisible(false);

  this->hide();
}

void TrayWindow::install() {
  if (this->_systray) {
    this->_systray->hide();
    delete this->_systray;
  }

  this->_systray = new QSystemTrayIcon(this);

  QObject::connect(this->_systray, &QSystemTrayIcon::activated,
    this, &TrayWindow::mouseClicked);
}

void TrayWindow::setToolTip(const QString& toolTip)
{
  if (this->_systray) 
    this->_systray->setToolTip(toolTip);
}

void TrayWindow::setIcon(const QString &source)
{
  if (!this->_systray)
    this->install();

  this->clearAnimatedIcon();

  if (source.isEmpty()) {
    this->hide();
    return;
  }

  QIcon trayIcon = QIcon(source);  
  this->_systray->setIcon(trayIcon);
  this->_systray->show();
}

void TrayWindow::setAnimatedSource(const QString &source)
{
  if (!this->_systray)
    this->install();

  this->clearAnimatedIcon();

  if (source.isEmpty()) {
    this->hide();
    return;
  }

  this->_animatedIcon = new QMovie(source);
  QObject::connect(this->_animatedIcon, &QMovie::frameChanged,
    this, &TrayWindow::updateIcon);

  this->_animatedIcon->start();
}

QString TrayWindow::animatedSource() const
{
  if (!this->_animatedIcon)
    return QString();

  if (this->_animatedIcon->isValid())
    this->_animatedIcon->fileName();
  
  return QString();
}

void TrayWindow::updateIcon()
{
  if (!this->_animatedIcon)
    return;

  this->_systray->setIcon(this->_animatedIcon->currentPixmap());
  this->_systray->show();
}

void TrayWindow::hide()
{
  if (this->_systray)
    this->_systray->hide();
}

void TrayWindow::mouseClicked(QSystemTrayIcon::ActivationReason reason)   
{
  switch(reason) {
  case QSystemTrayIcon::Trigger:
    emit this->activate();
    break;

  case QSystemTrayIcon::Context: 
    this->activateWindow(QCursor::pos().x(), QCursor::pos().y());
    break;
  }
}

TrayWindow* TrayWindow::qmlAttachedProperties(QObject *obj)
{
  return new TrayWindow(obj);
}

void TrayWindow::clearAnimatedIcon()
{
  if (!this->_animatedIcon)
    return;

  delete this->_animatedIcon;
  this->_animatedIcon = 0;
}