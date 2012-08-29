#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include <QtDeclarative>

namespace GGS {
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

      Q_INVOKABLE QVariantMap loadOldAuth();

      static RegistryCredentialStorage *qmlAttachedProperties(QObject *obj);

    private:
      QString _path;
      QString calcHash(const QString &userId, const QString &appKey, const QString &cookie);
    };
  }
}

QML_DECLARE_TYPEINFO(GGS::Auth::RegistryCredentialStorage, QML_HAS_ATTACHED_PROPERTIES)