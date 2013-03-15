#include <QmlExtension/WebView/NetworkAccessManagerInteractor.h>
#include <QmlExtension/WebView/PersistentCookieJar.h>

#include <QtNetwork/QNetworkAccessManager>

namespace GGS {
  namespace WebView {
    QDeclarativeEngine* NetworkAccessManagerInteractor::_declarativeEngine = 0;
    PersistentCookieJar* NetworkAccessManagerInteractor::_cookieJar = 0;
    
    NetworkAccessManagerInteractor::NetworkAccessManagerInteractor(QObject *parent) 
      : QObject(parent)
    {
    }

    NetworkAccessManagerInteractor::~NetworkAccessManagerInteractor()
    {
    }

    NetworkAccessManagerInteractor *NetworkAccessManagerInteractor::qmlAttachedProperties(QObject *obj) 
    {
      return new NetworkAccessManagerInteractor(obj);
    }

    void NetworkAccessManagerInteractor::setDeclarativeView(QDeclarativeEngine* view)
    {
      NetworkAccessManagerInteractor::_declarativeEngine = view;
    }

    void NetworkAccessManagerInteractor::setCookieJar(PersistentCookieJar* value)
    {
      NetworkAccessManagerInteractor::_cookieJar = value;
    }

    void NetworkAccessManagerInteractor::clearCookies()
    {
      this->clearAllCookies();
    }

    void NetworkAccessManagerInteractor::clearAllCookies()
    {
      if (!NetworkAccessManagerInteractor::_cookieJar) {
        return;
      }

      NetworkAccessManagerInteractor::_cookieJar->clearAllCookies();
    }

    void NetworkAccessManagerInteractor::setCookiesFromUrl(const QString &cookies, const QString &url)
    {
      if (!NetworkAccessManagerInteractor::_cookieJar) 
        return;

      NetworkAccessManagerInteractor::_cookieJar->setCookiesFromUrl(cookies, url);
    }

    QString & NetworkAccessManagerInteractor::cookiesForUrl(const QString &url)
    {
      if (!NetworkAccessManagerInteractor::_cookieJar) 
        return QString();

      return NetworkAccessManagerInteractor::_cookieJar->cookiesForUrl(url);
    }
  }
}
