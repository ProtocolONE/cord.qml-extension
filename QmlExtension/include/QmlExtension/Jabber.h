/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtDeclarative/QDeclarativeItem>

class QXmppClient;

namespace GGS {

  class Jabber : public QDeclarativeItem
  {
    Q_OBJECT

    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString domain READ domain WRITE setDomain NOTIFY domainChanged)

    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

  public:
    explicit Jabber(QDeclarativeItem *parent = 0); 
    ~Jabber();

    const QString& login() const;
    void setLogin(const QString& value);

    const QString& password() const;
    void setPassword(const QString& value);

    const QString& host() const;
    void setHost(const QString& value);

    const QString& domain() const;
    void setDomain(const QString& value);

    bool debug() const;
    void setDebug(bool value);

  public slots:
    void auth();
    void logout();

  signals:
    void loginChanged();
    void passwordChanged();
    void hostChanged();
    void domainChanged();
    void debugChanged();

  private:
    QXmppClient *_client;

    QString _login;
    QString _password;
    QString _host;
    QString _domain;

    bool _debug;
  };

}