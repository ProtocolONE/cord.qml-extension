#pragma once

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include <QtQml/QQmlParserStatus>

#include <QtWebSockets/QWebSocket>

class SslWebSocket : public QObject, public QQmlParserStatus
{
  Q_OBJECT
  Q_DISABLE_COPY(SslWebSocket)
  Q_INTERFACES(QQmlParserStatus)

  Q_ENUMS(Status)
  Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
  Q_PROPERTY(Status status READ status NOTIFY statusChanged)
  Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
  Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)

public:
  explicit SslWebSocket(QObject *parent = 0);
  explicit SslWebSocket(QWebSocket *socket, QObject *parent = 0);
  virtual ~SslWebSocket();

  enum Status {
    Connecting = 0,
    Open = 1,
    Closing = 2,
    Closed = 3,
    Error = 4
  };

  QUrl url() const;
  void setUrl(const QUrl &url);
  Status status() const;
  QString errorString() const;

  void setActive(bool value);
  bool isActive() const;

  Q_INVOKABLE qint64 sendTextMessage(const QString &message);

signals:
  void textMessageReceived(QString message);
  void statusChanged(Status status);
  void activeChanged(bool isActive);
  void errorStringChanged(QString errorString);
  void urlChanged();

public:
  void classBegin() override;
  void componentComplete() override;

private slots:
  void onError(QAbstractSocket::SocketError error);
  void onStateChanged(QAbstractSocket::SocketState state);

private:
  QScopedPointer<QWebSocket> _webSocket;
  Status _status;
  QUrl _url;
  bool _isActive;
  bool _componentCompleted;
  QString _errorString;

  void setSocket(QWebSocket *socket);
  void setStatus(Status status);
  void open();
  void close();
  void setErrorString(QString errorString = QString());
};

