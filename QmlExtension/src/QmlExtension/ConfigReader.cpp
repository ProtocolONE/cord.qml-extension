#include <QmlExtension/ConfigReader.h>
#include <QtYaml/ConfigManager.h>

ConfigReader::ConfigReader(QObject* parent) : QObject(parent)
{
}

ConfigReader* ConfigReader::qmlAttachedProperties(QObject *obj)
{
  return new ConfigReader(obj);
}

QVariantMap ConfigReader::read(const QString& path) const
{
  QString prefix = "file:///";
  QString configPath = path.indexOf(prefix) == -1 ? path : path.right(path.size() - prefix.size());
  QVariantMap result;
  try {

    YAML::Node config = YAML::LoadFile(configPath.toStdString());
    for (YAML::iterator it = config.begin(); it != config.end(); ++it) {
      result.insert(it->first.as<QString>(), it->second.as<QVariant>());
    }
  }
  catch (const YAML::Exception& ex) {
    qWarning() << "Cannot read config file:" << configPath;
    qWarning() << "YAML::Exception:" << ex.what();
  }
  return result;
}
      