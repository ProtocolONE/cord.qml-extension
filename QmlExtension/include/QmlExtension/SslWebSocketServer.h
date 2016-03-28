#pragma once

#include <QtCore/QUrl>
#include <QtCore/QObject>
#include <QQmlParserStatus>
#include <QtWebSockets/QWebSocketServer>

class SslWebSocket;
class SslWebSocketServer : public QObject, public QQmlParserStatus
{
  Q_OBJECT
  Q_DISABLE_COPY(SslWebSocketServer)
  Q_INTERFACES(QQmlParserStatus)

  Q_ENUMS(SslMode)

  Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
  Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
  Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
  Q_PROPERTY(bool listen READ listen WRITE setListen NOTIFY listenChanged)
  Q_PROPERTY(bool accept READ accept WRITE setAccept NOTIFY acceptChanged)

  Q_PROPERTY(SslMode ssl READ ssl WRITE setSsl NOTIFY sslChanged)
  Q_PROPERTY(QString sslCertificate READ sslCertificate WRITE setSslCertificate NOTIFY sslCertificateChanged)
  Q_PROPERTY(QString sslKey READ sslKey WRITE setSslKey NOTIFY sslKeyChanged)
public:
  enum SslMode {
    SecureMode,
    NonSecureMode
  };

  explicit SslWebSocketServer(QObject *parent = 0);
  virtual ~SslWebSocketServer();

  void classBegin() override;
  void componentComplete() override;

  QUrl url() const;

  QString host() const;
  void setHost(const QString &host);

  int port() const;
  void setPort(int port);

  QString name() const;
  void setName(const QString &name);

  QString errorString() const;

  bool listen() const;
  void setListen(bool listen);

  bool accept() const;
  void setAccept(bool accept);

  SslMode ssl() const;
  void setSsl(SslMode value);

  QString sslCertificate() const;
  void setSslCertificate(const QString &value);

  QString sslKey() const;
  void setSslKey(const QString &value);

signals:
  void clientConnected(SslWebSocket *webSocket);
  void errorStringChanged(const QString &errorString);
  void urlChanged(const QUrl &url);
  void portChanged(int port);
  void nameChanged(const QString &name);
  void hostChanged(const QString &host);
  void listenChanged(bool listen);
  void acceptChanged(bool accept);

  void sslChanged(SslWebSocketServer::SslMode ssl);
  void sslCertificateChanged(const QString &certificate);
  void sslKeyChanged(const QString &key);

private:
  void init();
  void updateListening();
  void newConnection();
  void serverError();
  void closed();
  void onSslErrors(const QList<QSslError> &);

  QScopedPointer<QWebSocketServer> _server;
  QString _host;
  QString _name;
  int _port;
  bool _listen;
  bool _accept;
  bool _componentCompleted;
  SslMode _ssl;

  QString _sslCertificate;
  QString _sslKey;
};

