#include <QmlExtension/MarketingAdapter.h>

using GGS::Core::Marketing;

namespace GGS {

  MarketingAdapter::MarketingAdapter(QObject* parent) : Marketing(parent)
  {
  }

  MarketingAdapter::~MarketingAdapter()
  {
  }

  MarketingAdapter* MarketingAdapter::qmlAttachedProperties(QObject *obj)
  {
    return new MarketingAdapter(obj);
  }

  void MarketingAdapter::send(int target, const QString& serviceId, const QVariantMap& params)
  {
    Marketing::send(static_cast<Marketing::MarketingTargets>(target), serviceId, params);
  }

  void MarketingAdapter::sendOnceByService(Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params)
  {
    Marketing::sendOnceByService(target, serviceId, params);
  }

  void MarketingAdapter::sendOnce(Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params)
  {
    Marketing::sendOnce(target, serviceId, params);
  }

  QString MarketingAdapter::mid()
  {
    QSettings settings("HKEY_LOCAL_MACHINE\\Software\\GGS\\QGNA", QSettings::NativeFormat);
    return settings.value("MID", "").toString();
  }

}