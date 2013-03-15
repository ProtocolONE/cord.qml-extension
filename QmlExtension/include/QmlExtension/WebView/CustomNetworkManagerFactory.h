/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef __GGS_WEBVIEW_CUSTOMNETWORKMANAGERFACTORY_H
#define __GGS_WEBVIEW_CUSTOMNETWORKMANAGERFACTORY_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

namespace GGS {
  namespace WebView {
    class PersistentCookieJar;

    class CustomNetworkManagerFactory : public QObject, public QDeclarativeNetworkAccessManagerFactory
    {
      Q_OBJECT
    public:
      explicit CustomNetworkManagerFactory(QObject *parent = 0);
      virtual QNetworkAccessManager *create(QObject *parent);

      PersistentCookieJar* cookieJar() const;
    public slots:
      void onIgnoreSSLErrors(QNetworkReply* reply, QList<QSslError> error);

    private:
      QNetworkAccessManager* _networkManager;
      PersistentCookieJar *_cookieJar;
    };

  }
}

#endif // __GGS_WEBVIEW_CUSTOMNETWORKMANAGERFACTORY_H
