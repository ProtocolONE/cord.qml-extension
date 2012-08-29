#include <QmlExtension/Auth/RegistryCredentialStorage.h>
#include <Core/System/Registry/RegistryKey.h>

#include <QtCore/QSettings>
#include <QtCore/QCryptographicHash>

namespace GGS {
  namespace Auth {

    RegistryCredentialStorage::RegistryCredentialStorage(QObject* parent)
      : QObject(parent)
      , _path("HKEY_CURRENT_USER\\Software\\GGS\\QGNA\\")
    {
    }

    RegistryCredentialStorage::~RegistryCredentialStorage()
    {
    }

    RegistryCredentialStorage* RegistryCredentialStorage::qmlAttachedProperties(QObject *obj)
    {
      return new RegistryCredentialStorage(obj);
    }

    void RegistryCredentialStorage::save(const QString& userId, const QString& appKey, const QString& cookie, bool guest)
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      settings.setValue("userId", userId);
      settings.setValue("appKey", appKey);
      settings.setValue("cookie", cookie);
      settings.setValue("crc", this->calcHash(userId, appKey, cookie));
      settings.setValue("guest", guest ? 1 : 0);
    }

    QVariantMap RegistryCredentialStorage::load()
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      if ( !settings.contains("userId")
        || !settings.contains("appKey")
        || !settings.contains("cookie")
        || !settings.contains("crc"))
      {
        this->reset();
        return QVariantMap();
      }

      QString userId = settings.value("userId", "").toString();
      QString appKey = settings.value("appKey", "").toString();
      QString cookie = settings.value("cookie", "").toString();
      QString crc = settings.value("crc", "").toString();

      if (this->calcHash(userId, appKey, cookie) != crc) {
        this->reset();
        return QVariantMap();
      }

      bool guest = settings.value("guest", 0).toInt() == 1;
      QVariantMap result;
      result["userId"] = userId;
      result["appKey"] = appKey;
      result["cookie"] = cookie;
      result["guest"] = guest;
      return result;
    }

    void RegistryCredentialStorage::reset()
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      settings.remove("userId");
      settings.remove("appKey");
      settings.remove("cookie");
      settings.remove("crc");
      settings.remove("guest");
    }

    QString RegistryCredentialStorage::calcHash(const QString &userId, const QString &appKey, const QString &cookie)
    {
      //ВАЖНО! Код сохраняющий данные в реестр и вычисляющий CRC нельзя
      //менять не исправляя синхронно код gnalogin/getCredential который нужен
      //для работы фичи "авторизация из инсталлятора" 
      QCryptographicHash hash(QCryptographicHash::Sha1);
      hash.addData(userId.toAscii());
      hash.addData(appKey.toAscii());
      hash.addData(cookie.toAscii());
      return QString(hash.result().toHex());
    }

    QVariantMap RegistryCredentialStorage::loadOldAuth()
    {
      using GGS::Core::System::Registry::RegistryKey;
      RegistryKey registry(RegistryKey::HKCU, "SOFTWARE\\GGS\\GNA\\");
      QString login;
      QString passhash;
      registry.value("user", login);
      registry.value("hash", passhash);
      QVariantMap result;
      result["login"] = login;
      result["hash"] = passhash;
      return result;
    }

  }
}
