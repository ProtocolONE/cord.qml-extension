/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QSystemTrayIcon.h>
#include <QtDeclarative\QDeclarativeView>
#include <QtDeclarative\QDeclarativeItem>

class TrayWindow : public QObject
{
  Q_OBJECT
public:
  TrayWindow(QObject* parent = 0);
  virtual ~TrayWindow();

  static TrayWindow *qmlAttachedProperties(QObject *obj);

public slots:
  void install(const QString& icon);
  void setToolTip(const QString& toolTip);
  void hide();

signals:
  void activate();
  void activateWindow(int mouseX, int mouseY);

private slots:
  void mouseClicked(QSystemTrayIcon::ActivationReason reason); 

private:
  QSystemTrayIcon* _systray;
};

QML_DECLARE_TYPEINFO(TrayWindow, QML_HAS_ATTACHED_PROPERTIES)


#endif // TRAYWINDOW_H
