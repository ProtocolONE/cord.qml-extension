#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

class QNetworkAccessManager;

class ThemePack : public QObject
{
  Q_OBJECT
  Q_ENUMS(Status)
  Q_PROPERTY(QString themeFolder READ themeFolder WRITE setThemeFolder NOTIFY themeFolderChanged)
  Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
  Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
  Q_PROPERTY(qint64 size READ size NOTIFY sizeChanged)
  Q_PROPERTY(Status status READ status NOTIFY statusChanged)

public:
  enum Status { Null, Ready, Loading, Error };

  explicit ThemePack(QObject *parent = 0);
  virtual ~ThemePack();
  
  const QString &source() const;
  void setSource(const QString& value);

  qreal progress() const;
  void setProgress(qreal value);
  
  qint64 size() const;
  void setSize(qint64 value);

  ThemePack::Status status() const;
  void setStatus(ThemePack::Status value);

  const QString &themeFolder() const;
  void setThemeFolder(const QString& value);

  Q_INVOKABLE bool install();
  Q_INVOKABLE void download();

signals:
  void progressChanged();
  void sourceChanged();
  void sizeChanged();
  void statusChanged();
  void themeFolderChanged();

private:
  Status _status;
  qreal _progress;
  qint64 _size;

  QString _themeFolder;
  QString _source;  

  QString _targetFolder;
  QString _fileName;

  QNetworkAccessManager *_networkManager;

  QString targetFilePath();
  void downloadSource();
  void setupPath();

  void setupTargetFolder();

  bool checkDownloaded();
};