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

class QMovie;

class TrayWindow : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString animatedSource READ animatedSource WRITE setAnimatedSource NOTIFY animatedSourceChanged)
public:
  TrayWindow(QObject* parent = 0);
  virtual ~TrayWindow();

  static TrayWindow *qmlAttachedProperties(QObject *obj);

  void setAnimatedSource(const QString &source);
  QString animatedSource() const;

public slots:
  void install(const QString& icon);
  void setIcon(const QString &iconSource);
  void setToolTip(const QString& toolTip);
  void hide();

signals:
  void activate();
  void activateWindow(int mouseX, int mouseY);
  void animatedSourceChanged();

private slots:
  void mouseClicked(QSystemTrayIcon::ActivationReason reason); 
  void updateIcon();

private:
  void clearAnimatedIcon();

  QSystemTrayIcon* _systray;
  QMovie *_animatedIcon;
};

QML_DECLARE_TYPEINFO(TrayWindow, QML_HAS_ATTACHED_PROPERTIES)


#endif // TRAYWINDOW_H
