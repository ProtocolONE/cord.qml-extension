#include <QmlExtension/WebView/NetworkAccessManagerInteractor.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>

namespace GGS {
  namespace WebView {
    QDeclarativeEngine* NetworkAccessManagerInteractor::_declarativeEngine = 0;

    NetworkAccessManagerInteractor::NetworkAccessManagerInteractor(QObject *parent) 
      : QObject(parent)
    {
    }

    NetworkAccessManagerInteractor::~NetworkAccessManagerInteractor()
    {
    }

    void NetworkAccessManagerInteractor::clearCookies()
    {
      if (!NetworkAccessManagerInteractor::_declarativeEngine) {
        return;
      }

      QNetworkAccessManager *nam = NetworkAccessManagerInteractor::_declarativeEngine->networkAccessManager();
      if (!nam) {
        return;
      }

      // QNetworkAccessManager takes ownership of the cookieJar object.
      QNetworkCookieJar *emptyCookieJar = new QNetworkCookieJar(nam);
      nam->setCookieJar(emptyCookieJar);
    }

    NetworkAccessManagerInteractor *NetworkAccessManagerInteractor::qmlAttachedProperties(QObject *obj) 
    {
      return new NetworkAccessManagerInteractor(obj);
    }

    void NetworkAccessManagerInteractor::setDeclarativeView(QDeclarativeEngine* view)
    {
      NetworkAccessManagerInteractor::_declarativeEngine = view;
    }
  }
}
