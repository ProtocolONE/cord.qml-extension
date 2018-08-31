#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include <QtQuick/QQuickItem>

namespace P1 {
  namespace Auth {

    /*!
      \class RegistryCredentialStorage
      \brief Реализует методы по сохранению и загрузки авторизации в реестре. 
      \author Ilya.Tkachenko
      \date 23.08.2012
    */
    class RegistryCredentialStorage : public QObject
    {
      Q_OBJECT
    public:
      RegistryCredentialStorage(QObject* parent = 0);
      ~RegistryCredentialStorage();
      
      Q_INVOKABLE void save(const QString& userId, const QString& appKey, const QString& cookie, bool guest = false);
      Q_INVOKABLE QVariantMap load();
      Q_INVOKABLE void reset();
      
      Q_INVOKABLE void setCredentialPath(const QString& path);

      Q_INVOKABLE QVariantMap loadOldAuth();

      Q_INVOKABLE void saveGuest(const QString& userId, const QString& appKey, const QString& cookie);
      Q_INVOKABLE QVariantMap loadGuest();

      Q_INVOKABLE void saveEx(const QString& prefix, const QString& userId, const QString& appKey, const QString& cookie);
      Q_INVOKABLE QVariantMap loadEx(const QString& prefix);
      Q_INVOKABLE void resetEx(const QString& prefix);

      static RegistryCredentialStorage *qmlAttachedProperties(QObject *obj);

    private:
      QString _path;
      QString calcHash(const QString &userId, const QString &appKey, const QString &cookie);
      QString calcGuestHash(const QString &userId, const QString &appKey, const QString &cookie);
      QString calcHashEx(const QString& prefix, const QString &userId, const QString &appKey, const QString &cookie);
    };
  }
}

QML_DECLARE_TYPEINFO(P1::Auth::RegistryCredentialStorage, QML_HAS_ATTACHED_PROPERTIES)