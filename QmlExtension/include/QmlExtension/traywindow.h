#pragma once

#include <QtWidgets/QSystemTrayIcon>
#include <QtQuick/QQuickItem>

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
  void install();
  void clearAnimatedIcon();

  QSystemTrayIcon* _systray;
  QMovie *_animatedIcon;
};

QML_DECLARE_TYPEINFO(TrayWindow, QML_HAS_ATTACHED_PROPERTIES)

