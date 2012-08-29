/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef __GGS_WEBVIEW_NETWORKACCESSMANAGERINTERACTOR_H
#define __GGS_WEBVIEW_NETWORKACCESSMANAGERINTERACTOR_H

#include <QtCore/QObject>
#include <QtDeclarative>

namespace GGS {
  namespace WebView {

    class NetworkAccessManagerInteractor : public QObject
    {
      Q_OBJECT
    public:
      explicit NetworkAccessManagerInteractor(QObject *parent = 0);
      ~NetworkAccessManagerInteractor();

      static void setDeclarativeView(QDeclarativeEngine* view);
      static NetworkAccessManagerInteractor *qmlAttachedProperties(QObject *obj);

    public slots:
      void clearCookies();

    private:
      static QDeclarativeEngine* _declarativeEngine;
    };
  }
}

QML_DECLARE_TYPEINFO(GGS::WebView::NetworkAccessManagerInteractor, QML_HAS_ATTACHED_PROPERTIES)
  
#endif // __GGS_WEBVIEW_NETWORKACCESSMANAGERINTERACTOR_H
