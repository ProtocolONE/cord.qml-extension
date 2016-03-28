#include <QmlExtension/SslWebSocket.h>

SslWebSocket::SslWebSocket(QObject *parent) 
  : QObject(parent)
  , _webSocket()
  , _status(Closed)
  , _url()
  , _isActive(false)
  , _componentCompleted(true)
  , _errorString()
{
}

SslWebSocket::SslWebSocket(QWebSocket *socket, QObject *parent)
  : QObject(parent)
  , _status(Closed)
  , _url(socket->requestUrl())
  , _isActive(true)
  , _componentCompleted(true)
  , _errorString(socket->errorString())
{
  this->setSocket(socket);
  this->onStateChanged(socket->state());
}

SslWebSocket::~SslWebSocket()
{
}

qint64 SslWebSocket::sendTextMessage(const QString &message)
{
  if (this->_status != Open) {
    this->setErrorString(tr("Messages can only be sent when the socket is open."));
    this->setStatus(Error);
    return 0;
  }

  return this->_webSocket->sendTextMessage(message);
}

QUrl SslWebSocket::url() const
{
  return this->_url;
}

void SslWebSocket::setUrl(const QUrl &url)
{
  if (this->_url == url)
    return;

  if (this->_webSocket && (this->_status == Open))
    this->_webSocket->close();

  this->_url = url;
  emit this->urlChanged();

  if (this->_webSocket)
    this->_webSocket->open(this->_url);
}

SslWebSocket::Status SslWebSocket::status() const
{
  return this->_status;
}

QString SslWebSocket::errorString() const
{
  return this->_errorString;
}

void SslWebSocket::classBegin()
{
  this->_componentCompleted = false;
  this->_errorString = tr("SslWebSocket is not ready.");
  this->_status = Closed;
}

void SslWebSocket::componentComplete()
{
  this->setSocket(new QWebSocket);
  this->_componentCompleted = true;
  this->open();
}

void SslWebSocket::setSocket(QWebSocket *socket)
{
  this->_webSocket.reset(socket);
  if (!this->_webSocket)
    return;

  this->_webSocket->setParent(nullptr);

  QObject::connect(this->_webSocket.data(), &QWebSocket::textMessageReceived,
    this, &SslWebSocket::textMessageReceived);

  typedef void (QWebSocket::* ErrorSignal)(QAbstractSocket::SocketError);
  QObject::connect(this->_webSocket.data(), static_cast<ErrorSignal>(&QWebSocket::error),
    this, &SslWebSocket::onError);

  QObject::connect(this->_webSocket.data(), &QWebSocket::stateChanged,
    this, &SslWebSocket::onStateChanged);
}

void SslWebSocket::onError(QAbstractSocket::SocketError error)
{
  Q_UNUSED(error);
  this->setErrorString(this->_webSocket->errorString());
  this->setStatus(Error);
}

void SslWebSocket::onStateChanged(QAbstractSocket::SocketState state)
{
  switch (state)
  {
  case QAbstractSocket::ConnectingState:
  case QAbstractSocket::BoundState:
  case QAbstractSocket::HostLookupState:
    this->setStatus(Connecting);
    break;
  case QAbstractSocket::UnconnectedState:
    this->setStatus(Closed);
    break;
  case QAbstractSocket::ConnectedState:
    this->setStatus(Open);
    break;
  case QAbstractSocket::ClosingState:
    this->setStatus(Closing);
    break;
  default:
    this->setStatus(Connecting);
    break;
  }
}

void SslWebSocket::setStatus(SslWebSocket::Status status)
{
  if (this->_status == status)
    return;

  this->_status = status;
  if (status != Error)
    this->setErrorString();

  emit this->statusChanged(this->_status);
}

void SslWebSocket::setActive(bool value)
{
  if (this->_isActive == value)
    return;

  this->_isActive = value;

  emit this->activeChanged(this->_isActive);

  if (!this->_componentCompleted)
    return;

  if (this->_isActive)
    this->open();
  else
    this->close();
}

bool SslWebSocket::isActive() const
{
  return this->_isActive;
}

void SslWebSocket::open()
{
  if (this->_componentCompleted && this->_isActive && this->_url.isValid() && this->_webSocket)
    this->_webSocket->open(this->_url);
}

void SslWebSocket::close()
{
  if (this->_componentCompleted && this->_webSocket)
    this->_webSocket->close();
}

void SslWebSocket::setErrorString(QString errorString)
{
  if (this->_errorString == errorString)
    return;

  this->_errorString = errorString;
  emit this->errorStringChanged(this->_errorString);
}

