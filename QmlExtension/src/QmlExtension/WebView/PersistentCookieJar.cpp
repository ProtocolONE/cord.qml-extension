#include <QmlExtension/WebView/PersistentCookieJar.h>
#include <QmlExtension/SettingsAdapter.h>

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QByteArray>

#include <QtNetwork/QNetworkCookie>

namespace GGS {
  namespace WebView {
    static inline bool isParentDomain(QString domain, QString reference)
    {
      if (!reference.startsWith(QLatin1Char('.')))
        return domain == reference;

      return domain.endsWith(reference) || domain == reference.mid(1);
    }

    PersistentCookieJar::PersistentCookieJar(QObject *parent = 0) : QNetworkCookieJar(parent)
    {
      this->load();
    }

    PersistentCookieJar::~PersistentCookieJar()
    {
      this->save();
    }

    void PersistentCookieJar::clearAllCookies()
    {
      this->setAllCookies(QList<QNetworkCookie>());
    }

    void PersistentCookieJar::save()
    {
      QByteArray data = this->cookiesFromList(this->allCookies());
     
      SettingsAdapter settings;
      settings.setValue("PersistentCookieJar", "cookies", qCompress(data));
    }

    QByteArray PersistentCookieJar::cookiesFromList(const QList<QNetworkCookie> &list)
    {
      QByteArray data;
      foreach (QNetworkCookie cookie, list) {
        if (!cookie.isSessionCookie()) {
          data.append(cookie.toRawForm());
          data.append("\n");
        }
      }

      return data;
    }

    void PersistentCookieJar::load()
    {
      SettingsAdapter settings;
      QByteArray data = settings.value("PersistentCookieJar", "cookies").toByteArray();

      if (data.length()) 
        this->setAllCookies(QNetworkCookie::parseCookies(qUncompress(data)));
    }

    void PersistentCookieJar::setCookiesFromUrl(const QString &cookies, const QString &url)
    {
      if (cookies.length() > 0) {
         QNetworkCookieJar::setCookiesFromUrl(QNetworkCookie::parseCookies(cookies.toAscii()), QUrl(url));
         return;
      }
        
      QUrl urlObj = url;

      QList<QNetworkCookie> list = this->allCookies();
      QList<QNetworkCookie> newlist;

      foreach (QNetworkCookie cookie, list) {
          if (isParentDomain(urlObj.host(), cookie.domain())) 
            continue;

          newlist.append(cookie);
      }

      this->setAllCookies(newlist);
      this->save();
    }

    QString PersistentCookieJar::cookiesForUrl(const QString &url)
    {
      return QString(this->cookiesFromList(QNetworkCookieJar::cookiesForUrl(QUrl(url))));
    }
  }
}
