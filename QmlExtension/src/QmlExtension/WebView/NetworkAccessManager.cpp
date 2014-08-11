#include <QmlExtension/WebView/NetworkAccessManager.h>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

#include <QtCore/QList>
#include <QtCore/QDebug>

namespace GGS {
  namespace WebView {

    NetworkAccessManager::NetworkAccessManager(QObject * parent /*= 0*/)
      : QNetworkAccessManager(parent)
    {
    }

    NetworkAccessManager::~NetworkAccessManager()
    {
    }

    QNetworkReply * NetworkAccessManager::createRequest(
      Operation op, 
      const QNetworkRequest &request, 
      QIODevice *outgoingData /*= 0*/)
    {
      QNetworkReply *reply = this->QNetworkAccessManager::createRequest(op, request, outgoingData);
      QObject::connect(reply, &QNetworkReply::sslErrors, [reply] (QList<QSslError> error) {
        reply->ignoreSslErrors(error);
      });

      return reply;
    }

  }
}