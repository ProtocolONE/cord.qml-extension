#include <QmlExtension/WebView/CustomNetworkManagerFactory.h>

namespace GGS {
  namespace WebView {

    CustomNetworkManagerFactory::CustomNetworkManagerFactory(QObject *parent) : QObject(parent)
    {
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
      this->_networkManager = new QNetworkAccessManager(this);

      connect(this->_networkManager,SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
        this,SLOT(onIgnoreSSLErrors(QNetworkReply*, QList<QSslError>)));

      return this->_networkManager;
    }

    void CustomNetworkManagerFactory::onIgnoreSSLErrors(QNetworkReply *reply, QList<QSslError> error)
    {
      reply->ignoreSslErrors(error);
    }
  }
}