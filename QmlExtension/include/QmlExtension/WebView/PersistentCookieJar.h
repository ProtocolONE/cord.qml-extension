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

#include <QtNetwork/QNetworkCookieJar>

namespace GGS {
  namespace WebView {

    class PersistentCookieJar : public QNetworkCookieJar 
    {
    public:
      PersistentCookieJar(QObject *parent);
      ~PersistentCookieJar();

    public:
      void clearAllCookies();

      void setCookiesFromUrl(const QString &cookies, const QString &url);
      QString cookiesForUrl(const QString &url);
    protected:
      QByteArray cookiesFromList(const QList<QNetworkCookie> &list);
    private:
      void save();
      void load();
    };
  }
}
