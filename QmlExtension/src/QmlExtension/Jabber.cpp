/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#include <QmlExtension/Jabber.h>

#include <QXmppConfiguration.h>
#include <QXmppClient.h>
#include <QXmppLogger.h>

namespace GGS {

  Jabber::Jabber(QDeclarativeItem *parent /*= 0*/) 
    : QDeclarativeItem(parent)
    , _client(new QXmppClient(this))
    , _debug(false)
  {
    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::NoLogging);
  }

  Jabber::~Jabber()
  {
  }

  void Jabber::auth()
  {
    QXmppConfiguration config;
    config.setHost(this->_host);
    config.setDomain(this->_domain);
    config.setUser(this->_login);
    config.setPassword(this->_password);
    config.setKeepAliveInterval(0); //мы не хотим пинговать сервер
    config.setAutoReconnectionEnabled(true);

    this->_client->connectToServer(config);
  }

  void Jabber::logout()
  {
    this->_client->disconnectFromServer();
  }

  const QString& Jabber::login() const
  {
    return this->_login;
  }

  void Jabber::setLogin(const QString& value)
  {
    if (this->_login == value)
      return;

    this->_login = value;
    emit this->loginChanged();
  }

  const QString& Jabber::password() const
  {
    return this->_password;
  }

  void Jabber::setPassword(const QString& value)
  {
    if (this->_password == value)
      return;

    this->_password = value;
    emit this->passwordChanged();  
  }

  const QString& Jabber::host() const
  {
    return this->_host;
  }

  void Jabber::setHost(const QString& value)
  {
    if (this->_host == value)
      return;

    this->_host = value;
    emit this->hostChanged();  
  }

  const QString& Jabber::domain() const
  {
    return this->_domain;
  }

  void Jabber::setDomain(const QString& value)
  {    
    if (this->_domain == value)
      return;

    this->_domain = value;
    emit this->domainChanged();  
  }

  bool Jabber::debug() const
  {
    return this->_debug;
  }

  void Jabber::setDebug(bool value)
  {
    if (this->_debug == value)
      return;

    this->_debug = value;
    QXmppLogger::getLogger()->setLoggingType(value ? QXmppLogger::StdoutLogging : QXmppLogger::NoLogging);

    emit this->debugChanged(); 
  }

}