#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include <QtNetwork/QNetworkDiskCache>

#include <QmlExtension/WebView/CustomNetworkManagerFactory.h>
#include <QmlExtension/WebView/PersistentCookieJar.h>
#include <QmlExtension/WebView/NetworkAccessManager.h>

namespace GGS {
  namespace WebView {

    CustomNetworkManagerFactory::CustomNetworkManagerFactory(QObject *parent) : QObject(parent)
    {
      this->_cookieJar = new PersistentCookieJar(parent);
    }

    /*!
      \fn QNetworkAccessManager* CustomNetworkManagerFactory::create(QObject *parent)
    
      \brief this is a virtual method we need to implement this method , most important step
             we will create our custom QNetworkAccessManager here and return that 
             the second important thing we need to do here is to connect the sslErrors signal 
             from QNetworkAccessManager to our own slot which will ignore the sslErrors
    
      \param [in,out] parent If non-null, the parent.
    
      \return null if it fails, else.
    */

    QNetworkAccessManager* CustomNetworkManagerFactory::create(QObject *parent)
    {
      this->_networkManager = new NetworkAccessManager(parent);

      QString cacheDirectory = QString("%1/Cache/").arg(QCoreApplication::applicationDirPath());

      QNetworkDiskCache* cache = new QNetworkDiskCache();
      cache->setCacheDirectory(cacheDirectory);
      cache->setMaximumCacheSize(209715200i64);

      this->_networkManager->setCache(cache);
      this->_networkManager->setCookieJar(this->_cookieJar);
      this->_cookieJar->setParent(this->parent());

      return this->_networkManager;
    }

    PersistentCookieJar* CustomNetworkManagerFactory::cookieJar() const
    {
      return this->_cookieJar;
    }
  }
}
