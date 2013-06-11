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
#include <QtDeclarative/QDeclarative.h>
#include <QtDeclarative/QDeclarativeEngine>

namespace GGS {
  namespace WebView {
    class PersistentCookieJar;

    class NetworkAccessManagerInteractor : public QObject
    {
      Q_OBJECT
    public:
      explicit NetworkAccessManagerInteractor(QObject *parent = 0);
      ~NetworkAccessManagerInteractor();

      static NetworkAccessManagerInteractor *qmlAttachedProperties(QObject *obj);
      
      static void setDeclarativeView(QDeclarativeEngine* view);
      static void setCookieJar(PersistentCookieJar* value);

    public slots:
      void clearCookies();
      void clearAllCookies();

      void setCookiesFromUrl(const QString &cookies, const QString &url);
      QString cookiesForUrl(const QString &url);

    private:
      static QDeclarativeEngine* _declarativeEngine;
      static PersistentCookieJar* _cookieJar;
    };
  }
}

QML_DECLARE_TYPEINFO(GGS::WebView::NetworkAccessManagerInteractor, QML_HAS_ATTACHED_PROPERTIES)