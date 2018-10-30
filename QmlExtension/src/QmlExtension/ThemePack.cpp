#include <QmlExtension/ThemePack.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QStandardPaths>
#include <QtCore/QTemporaryFile>
#include <QtGui/QDesktopServices>

ThemePack::ThemePack(QObject *parent)
  : QObject(parent)
  , _networkManager(new QNetworkAccessManager(this))
  , _status(ThemePack::Null)
  , _progress(0)
  , _size(0)
  , _themeFolder("Themes")
  , _source("")
{
  this->setupTargetFolder();
}

ThemePack::~ThemePack()
{
}

qreal ThemePack::progress() const
{
  return this->_progress;
}

void ThemePack::setProgress(qreal value)
{
  if (qFuzzyCompare(this->_progress, value))
    return;
 
  this->_progress = value;
  emit this->progressChanged();
}

const QString& ThemePack::source() const
{
  return this->_source;
}

void ThemePack::setSource(const QString& value)
{
  if (0 == this->_source.compare(value, Qt::CaseInsensitive))
    return;

  this->_source = value;
  emit this->sourceChanged();

  this->checkDownloaded();
}

qint64 ThemePack::size() const
{
  return this->_size;
}

void ThemePack::setSize(qint64 value)
{
  if (this->_size == value)
    return;

  this->_size = value;
  emit this->sizeChanged();
}

ThemePack::Status ThemePack::status() const
{
  return this->_status;
}

void ThemePack::setStatus(Status value)
{
  if (this->_status == value)
    return;

  this->_status = value;
  emit this->statusChanged();
}

Q_INVOKABLE bool ThemePack::install()
{
  if (this->_status != ThemePack::Ready)
    return false;
  
  this->_fileName = this->targetFilePath();

  qDebug() << "Install" << this->_fileName;
  //INFO http://stackoverflow.com/questions/546818/how-do-i-change-the-current-windows-theme-programatically/3178625#3178625
  return QDesktopServices::openUrl(QUrl::fromLocalFile(this->_fileName));
}

Q_INVOKABLE void ThemePack::download()
{
  this->downloadSource();
}

const QString& ThemePack::themeFolder() const
{
  return this->_themeFolder;
}

void ThemePack::setThemeFolder(const QString& value)
{
  if (value.isEmpty())
    return; 

  if (0 == this->_themeFolder.compare(value, Qt::CaseInsensitive))
    return;

  this->_themeFolder = value;
  this->setupTargetFolder();

  emit this->themeFolderChanged();  
}

void ThemePack::downloadSource()
{
  QUrl requestUri(this->_source);
  if (requestUri.isRelative())
    return;
    
  this->_progress = 0;
  this->_size = 0;
  this->_fileName = this->targetFilePath();

  if (this->checkDownloaded()) 
    return;
  
  this->setupPath();
  this->setStatus(ThemePack::Loading);

  qDebug() << "Download theme" << requestUri << "to file" << this->_fileName;

  QNetworkRequest networkRequest(requestUri);
  QNetworkReply *reply = this->_networkManager->get(networkRequest);
  
  connect(this, &ThemePack::sourceChanged, reply, &QNetworkReply::abort);
  connect(reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal) {
    this->setProgress(1.0f * bytesReceived / bytesTotal);
    this->setSize(bytesTotal);
  });

  connect(reply, &QNetworkReply::finished, [this, reply]() {
    if (!reply->isFinished()) {
      qDebug() << "Request abort";

      this->setStatus(ThemePack::Null);
      reply->deleteLater();
      return;
    }

    if (QNetworkReply::NoError != reply->error()) {
      qDebug() << "QNetworkReply error" << reply->errorString();

      this->setStatus(ThemePack::Error);
      reply->deleteLater();
      return;
    }

    QTemporaryFile file;
    if (!file.open()) {
      qDebug() << "Can`t open temporary file";

      this->setStatus(ThemePack::Error);
      reply->deleteLater();
    }

    file.write(reply->readAll());
    file.flush();
    file.setAutoRemove(false);
    file.close();

    if (!file.rename(this->_fileName)) {
      qDebug() << "Can`t move" << file.fileName() << "to" << this->_fileName;
      this->setStatus(ThemePack::Error);
    }
    else {
      this->setStatus(ThemePack::Ready);
    }

    reply->deleteLater();
  });
}

void ThemePack::setupPath()
{ 
  this->setupTargetFolder();

  QDir dir;
  if (!dir.exists(this->_targetFolder))
    dir.mkdir(this->_targetFolder);
}

void ThemePack::setupTargetFolder()
{
  QDir themeFolder(this->_themeFolder);
  if (themeFolder.isAbsolute()) {
    this->_targetFolder = this->_themeFolder;
  }
  else {
    this->_targetFolder = QString("%1/%2/")
      .arg(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation))
      .arg(this->_themeFolder);
  }
}

bool ThemePack::checkDownloaded()
{
  QFile targetFile(this->targetFilePath());
  if (targetFile.exists()) {
    this->setProgress(1);
    this->setSize(targetFile.size());
    this->setStatus(ThemePack::Ready);
    return true;
  }

  return false;
}

QString ThemePack::targetFilePath()
{
  QUrl sourceUri(this->_source);
  return this->_targetFolder + sourceUri.fileName() + ".themepack";
}
