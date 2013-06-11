/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/traywindow.h>

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

TrayWindow::TrayWindow(QObject* parent) 
<<<<<<< HEAD
  : QObject(parent),
  _systray(0)
=======
	: QObject(parent),
	_systray(0)
>>>>>>> 37f521a... QGNA-448 Qt5
{
}

void TrayWindow::install(const QString& icon) {
  if (this->_systray) {
<<<<<<< HEAD
    this->_systray->hide();
    delete this->_systray;
=======
	  this->_systray->hide();
	  delete this->_systray;
>>>>>>> 37f521a... QGNA-448 Qt5
  }

  QIcon trayIcon = QIcon(icon);  

  this->_systray = new QSystemTrayIcon(this);
  this->_systray->setIcon(trayIcon);
  this->_systray->setVisible(true);
  this->_systray->show();

  SIGNAL_CONNECT_CHECK(connect(this->_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(mouseClicked(QSystemTrayIcon::ActivationReason))));
}

<<<<<<< HEAD
void TrayWindow::setToolTip(const QString& toolTip)
{
  if (this->_systray) 
    this->_systray->setToolTip(toolTip);
}

TrayWindow::~TrayWindow()
{
  if (this->_systray) 
    this->_systray->setVisible(false);

=======
TrayWindow::~TrayWindow()
{
  this->_systray->setVisible(false);
>>>>>>> 37f521a... QGNA-448 Qt5
  this->hide();
}

void TrayWindow::hide() {
  if (this->_systray)
<<<<<<< HEAD
    this->_systray->hide();
=======
	this->_systray->hide();
>>>>>>> 37f521a... QGNA-448 Qt5
}

void TrayWindow::mouseClicked(QSystemTrayIcon::ActivationReason reason)   
{
  switch(reason) {
  case QSystemTrayIcon::Trigger:
<<<<<<< HEAD
    emit this->activate();
    break;

  case QSystemTrayIcon::Context: 
    this->activateWindow(QCursor::pos().x(), QCursor::pos().y());
=======
		emit this->activate();
    break;

  case QSystemTrayIcon::Context: 
	  this->activateWindow(QCursor::pos().x(), QCursor::pos().y());
>>>>>>> 37f521a... QGNA-448 Qt5
    break;
  }
}

TrayWindow* TrayWindow::qmlAttachedProperties(QObject *obj)
{
  return new TrayWindow(obj);
<<<<<<< HEAD
}

=======
}
>>>>>>> 37f521a... QGNA-448 Qt5
