#pragma once

#include <QtCore/QObject>
#include <QtCore/QStandardPaths>
#include <QtQml/QtQml>

class StandardPaths : public QObject
{
  Q_OBJECT
public:

  enum StandardLocation {
    DesktopLocation = QStandardPaths::DesktopLocation,
    DocumentsLocation = QStandardPaths::DocumentsLocation,
    FontsLocation = QStandardPaths::FontsLocation,
    ApplicationsLocation = QStandardPaths::ApplicationsLocation,
    MusicLocation = QStandardPaths::MusicLocation,
    MoviesLocation = QStandardPaths::MoviesLocation,
    PicturesLocation = QStandardPaths::PicturesLocation,
    TempLocation = QStandardPaths::TempLocation,
    HomeLocation = QStandardPaths::HomeLocation,
    DataLocation = QStandardPaths::DataLocation,
    CacheLocation = QStandardPaths::CacheLocation,
    GenericCacheLocation = QStandardPaths::GenericCacheLocation,
    GenericDataLocation = QStandardPaths::GenericDataLocation,
    RuntimeLocation = QStandardPaths::RuntimeLocation,
    ConfigLocation = QStandardPaths::ConfigLocation,
    GenericConfigLocation = QStandardPaths::GenericConfigLocation,
    DownloadLocation = QStandardPaths::DownloadLocation,
  };
  Q_ENUMS(StandardLocation)

  explicit StandardPaths(QObject* parent = 0);
  virtual ~StandardPaths();

  static StandardPaths* qmlAttachedProperties(QObject *obj);

public slots:
  QString writableLocation(uint type);
};

QML_DECLARE_TYPEINFO(StandardPaths, QML_HAS_ATTACHED_PROPERTIES);
