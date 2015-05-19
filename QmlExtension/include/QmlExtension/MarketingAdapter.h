#pragma once

#include <Core/Marketing.h>
#include <QtQuick/QQuickItem>

namespace GGS {

  class MarketingAdapter : public GGS::Core::Marketing
  {
    Q_OBJECT
  public:
    MarketingAdapter(QObject* parent = 0);
    ~MarketingAdapter();

    static MarketingAdapter *qmlAttachedProperties(QObject *obj);

    /*!
    \fn Q_INVOKABLE void Marketing::send(MarketingTargets target, const QString& serviceId,
    const QVariantMap& params);
    \brief Генерирует событие на отправку маркетингово шага.
    \author Ilya.Tkachenko
    \date 30.07.2012
    \param target    Маркетинговая цель.
    \param serviceId Идентификатор сервиса. Если его нету, то следует указать "0" или воспользоваться 
                    перегруженными методами.
    \param params    Дополнительные параметры.
    */
    Q_INVOKABLE void send(int target, const QString& serviceId, const QVariantMap& params);


    /*!
    \fn Q_INVOKABLE void Marketing::sendOnceByService(MarketingTargets target, const QString& serviceId, const QVariantMap& params);
    \brief Метод аналогичный send, но подразумевается, что указанная маркетинговая цель будет послана
          один раз для каждого сервиса. Это обеспечивает непосредственно обработчик события 
          sendOnceByServiceMarketingRequest в самом приложении.
    \author Ilya.Tkachenko
    \date 30.07.2012
    \param target    Маркетинговая цель.
    \param serviceId Идентификатор сервиса. Так как ключь отправленности сохраняется по каждому сервису, 
                    этот параметр является обязательным.
    \param params    Дополнительные параметры.
    */
    Q_INVOKABLE void sendOnceByService(GGS::Core::Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params);

    /*!
    \fn Q_INVOKABLE void Marketing::sendOnce(MarketingTargets target, const QString& serviceId,
    const QVariantMap& params);
    \brief Метод аналогичный send, но подразумевается, что указанная маркетинговая цель будет послана
          один раз на все приложение. Это обеспечивает непосредственно обработчик события 
          sendOnceMarketingRequest в самом приложении.
    \author Ilya.Tkachenko
    \date 30.07.2012
    \param target    Маркетинговая цель.
    \param serviceId Идентификатор сервиса. Если его нету, то следует указать "0" или воспользоваться 
                    перегруженными методами.
    \param params    Дополнительные параметры.
    */
    Q_INVOKABLE void sendOnce(GGS::Core::Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params);

    Q_INVOKABLE QString mid();
  };
}

QML_DECLARE_TYPEINFO(GGS::MarketingAdapter, QML_HAS_ATTACHED_PROPERTIES)