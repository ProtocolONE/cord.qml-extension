#pragma once

#include <QtNetwork/QNetworkAccessManager>

namespace GGS {
  namespace WebView {

    // INFO QGNA-1004 Перенес обработку ошибок сертификата в этот класс, так как в обработчике сигнал
    // QNetworkAccessManager::sslErrors QNetworkReply уже не валидный из QML Image.
    class NetworkAccessManager : public QNetworkAccessManager
    {
      Q_OBJECT
    public:
      explicit NetworkAccessManager(QObject * parent = 0);
      virtual ~NetworkAccessManager();

      virtual QNetworkReply * createRequest(
        Operation op, 
        const QNetworkRequest &request, 
        QIODevice *outgoingData = 0) override;
    };

  }
}