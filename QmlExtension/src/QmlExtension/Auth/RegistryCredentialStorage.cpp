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

    void RegistryCredentialStorage::setCredentialPath(const QString& path)
    {
      this->_path = path;
    }

    Q_INVOKABLE void RegistryCredentialStorage::saveGuest(const QString& userId, const QString& appKey, const QString& cookie)
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      settings.setValue("guestUserId", userId);
      settings.setValue("guestAppKey", appKey);
      settings.setValue("guestCookie", cookie);
      settings.setValue("guestCrc", this->calcGuestHash(userId, appKey, cookie));
    }

    Q_INVOKABLE QVariantMap RegistryCredentialStorage::loadGuest()
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      if ( !settings.contains("guestUserId")
        || !settings.contains("guestAppKey")
        || !settings.contains("guestCookie")
        || !settings.contains("guestCrc"))
      {
        return QVariantMap();
      }

      QString userId = settings.value("guestUserId", "").toString();
      QString appKey = settings.value("guestAppKey", "").toString();
      QString cookie = settings.value("guestCookie", "").toString();
      QString crc = settings.value("guestCrc", "").toString();

      if (this->calcGuestHash(userId, appKey, cookie) != crc)
        return QVariantMap();

      QVariantMap result;
      result["userId"] = userId;
      result["appKey"] = appKey;
      result["cookie"] = cookie;
      return result;
    }

    QString RegistryCredentialStorage::calcGuestHash(const QString &userId, const QString &appKey, const QString &cookie)
    {
      return this->calcHash(userId + "guest", appKey + "guest", cookie + "guest");
    }

    Q_INVOKABLE void RegistryCredentialStorage::saveEx(
      const QString& prefix, 
      const QString& userId, 
      const QString& appKey, 
      const QString& cookie)
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      settings.setValue(prefix + "userId", userId);
      settings.setValue(prefix + "appKey", appKey);
      settings.setValue(prefix + "cookie", cookie);
      settings.setValue(prefix + "crc", this->calcHashEx(prefix, userId, appKey, cookie));
    }

    Q_INVOKABLE QVariantMap RegistryCredentialStorage::loadEx(const QString& prefix)
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      if ( !settings.contains(prefix + "userId")
        || !settings.contains(prefix + "appKey")
        || !settings.contains(prefix + "cookie")
        || !settings.contains(prefix + "crc"))
      {
        this->resetEx(prefix);
        return QVariantMap();
      }

      QString userId = settings.value(prefix + "userId", "").toString();
      QString appKey = settings.value(prefix + "appKey", "").toString();
      QString cookie = settings.value(prefix + "cookie", "").toString();
      QString crc = settings.value(prefix + "crc", "").toString();

      if (this->calcHashEx(prefix, userId, appKey, cookie) != crc) {
        this->resetEx(prefix);
        return QVariantMap();
      }

      QVariantMap result;
      result["userId"] = userId;
      result["appKey"] = appKey;
      result["cookie"] = cookie;
      return result;
    }

    Q_INVOKABLE void RegistryCredentialStorage::resetEx(const QString& prefix)
    {
      QSettings settings(this->_path, QSettings::NativeFormat);
      settings.remove(prefix + "userId");
      settings.remove(prefix + "appKey");
      settings.remove(prefix + "cookie");
      settings.remove(prefix + "crc");
    }

    QString RegistryCredentialStorage::calcHashEx(
      const QString& prefix, 
      const QString& userId, 
      const QString& appKey, 
      const QString& cookie)
    {
      return this->calcHash(userId + prefix, appKey + prefix, cookie + prefix);
    }

  }
}
