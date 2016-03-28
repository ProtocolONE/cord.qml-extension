#include <QmlExtension/SslWebSocketServer.h>
#include <QmlExtension/SslWebSocket.h>

#include <QtCore/QDebug>

SslWebSocketServer::SslWebSocketServer(QObject *parent /*= 0*/)
  : QObject(parent)
  , _host(QHostAddress(QHostAddress::LocalHost).toString())
  , _port(0)
  , _listen(false)
  , _accept(true)
  , _componentCompleted(true)
  , _ssl(NonSecureMode)
{
}

SslWebSocketServer::~SslWebSocketServer()
{
}

void SslWebSocketServer::classBegin()
{
  this->_componentCompleted = false;
}

void SslWebSocketServer::componentComplete()
{
  this->init();
  this->_componentCompleted = true;
}

QUrl SslWebSocketServer::url() const
{
  QUrl url;
  url.setPort(this->_port);
  url.setHost(this->_host);
  url.setScheme(this->_ssl == SecureMode ? "wss" : "ws");
  return url;
}

QString SslWebSocketServer::host() const
{
  return this->_host;
}

void SslWebSocketServer::setHost(const QString &host)
{
  if (this->_host == host)
    return;

  this->_host = host;
  emit this->hostChanged(host);
  emit this->urlChanged(this->url());

  this->updateListening();
}

int SslWebSocketServer::port() const
{
  return this->_port;
}

void SslWebSocketServer::setPort(int port)
{
  if (this->_port == port)
    return;

  if (port < 0 || port > 65535)
    return;

  this->_port = port;
  emit this->portChanged(port);
  emit this->urlChanged(this->url());

  if (this->_componentCompleted && this->_server->isListening())
    this->updateListening();
}

QString SslWebSocketServer::errorString() const
{
  return this->_server 
    ? this->_server->errorString() 
    : tr("SslWebSocketServer is not ready.");
}

QString SslWebSocketServer::name() const
{
  return this->_name;
}

void SslWebSocketServer::setName(const QString &name)
{
  if (this->_name == name)
    return;

  this->_name = name;
  emit this->nameChanged(name);

  if (this->_componentCompleted)
    this->init();
}

bool SslWebSocketServer::listen() const
{
  return this->_listen;
}

void SslWebSocketServer::setListen(bool listen)
{
  if (this->_listen == listen)
    return;

  this->_listen = listen;
  emit this->listenChanged(listen);

  this->updateListening();
}

bool SslWebSocketServer::accept() const
{
  return this->_accept;
}

void SslWebSocketServer::setAccept(bool accept)
{
  if (this->_accept == accept)
    return;

  this->_accept = accept;
  emit this->acceptChanged(accept);

  if (this->_componentCompleted)
    return;

  if (!accept)
    this->_server->pauseAccepting();
  else
    this->_server->resumeAccepting();
}

SslWebSocketServer::SslMode SslWebSocketServer::ssl() const
{
  return this->_ssl;
}

void SslWebSocketServer::setSsl(SslWebSocketServer::SslMode value)
{
  if (this->_ssl == value)
    return;

  this->_ssl = value;
  emit this->sslChanged(value);

  if (this->_componentCompleted)
    this->init();
}

QString SslWebSocketServer::sslCertificate() const
{
  return this->_sslCertificate;
}

void SslWebSocketServer::setSslCertificate(const QString &value)
{
  if (this->_sslCertificate == value)
    return;

  this->_sslCertificate = value;
  emit this->sslCertificateChanged(value);

  if (this->_listen && (this->_ssl == SecureMode) && this->_componentCompleted)
    this->init();
}

QString SslWebSocketServer::sslKey() const
{
  return this->_sslKey;
}

void SslWebSocketServer::setSslKey(const QString &value)
{
  if (this->_sslKey == value)
    return;

  this->_sslKey = value;
  emit this->sslKeyChanged(value);

  if (this->_listen && (this->_ssl == SecureMode) && this->_componentCompleted)
    this->init();
}

void SslWebSocketServer::init()
{
  this->_server.reset(
    new QWebSocketServer(
      this->_name, 
      (this->_ssl == SecureMode 
        ? QWebSocketServer::SecureMode
        : QWebSocketServer::NonSecureMode)
      )
  );

  QObject::connect(this->_server.data(), &QWebSocketServer::newConnection,
    this, &SslWebSocketServer::newConnection);
  QObject::connect(this->_server.data(), &QWebSocketServer::serverError,
    this, &SslWebSocketServer::serverError);
  QObject::connect(this->_server.data(), &QWebSocketServer::closed,
    this, &SslWebSocketServer::closed);
  QObject::connect(this->_server.data(), &QWebSocketServer::sslErrors,
    this, &SslWebSocketServer::onSslErrors);

  this->updateListening();
}

void SslWebSocketServer::updateListening()
{
  if (!this->_server)
    return;

  if (this->_server->isListening())
    this->_server->close();

  if (this->_ssl == QWebSocketServer::SecureMode) {
    if (this->_sslCertificate.isEmpty() || this->_sslKey.isEmpty()) {
      qDebug() << "Ssl certificate or key is empty.";
      return;
    }

    QSslCertificate certificate(this->_sslCertificate.toUtf8(), QSsl::Pem);
    QSslKey sslKey(this->_sslKey.toUtf8(), QSsl::Rsa, QSsl::Pem);

    QSslConfiguration sslConfiguration;
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setProtocol(QSsl::TlsV1_0OrLater);

    this->_server->setSslConfiguration(sslConfiguration);
  }

  if (!this->_listen || !this->_server->listen(QHostAddress(this->_host), this->_port))
    return;
  
  this->setPort(this->_server->serverPort());
  this->setHost(this->_server->serverAddress().toString());
}

void SslWebSocketServer::newConnection()
{
  emit this->clientConnected(new SslWebSocket(this->_server->nextPendingConnection(), this));
}

void SslWebSocketServer::serverError()
{
  emit this->errorStringChanged(this->errorString());
}

void SslWebSocketServer::closed()
{
  this->setListen(false);
}

void SslWebSocketServer::onSslErrors(const QList<QSslError> & errorList)
{
  qDebug() << "Ssl errors occurred";
  Q_FOREACH(const QSslError& error, errorList) {
    qDebug() << error;
  }
}
