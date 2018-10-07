#include <QmlExtension/QmlExtension.h>
#include <QmlExtension/WheelArea.h>

#include <QmlExtension/QDesktopItem.h>
#include <QmlExtension/SettingsAdapter.h>
#include <QmlExtension/MarketingAdapter.h>
#include <QmlExtension/GoogleAnalytics.h>
#include <QmlExtension/QFileDialogAdapter.h>

#include <QmlExtension/traywindow.h>
#include <QmlExtension/TaskList.h>
#include <QmlExtension/MouseCursor.h>

#include <QmlExtension/Auth/RegistryCredentialStorage.h>
#include <QmlExtension/Host.h>
#include <QmlExtension/StyleReader.h>
#include <QmlExtension/Shortcut.h>
#include <QmlExtension/ThemePack.h>
#include <QmlExtension/BrowserDetect.h>
#include <QmlExtension/TextDocumentHelper.h>
#include <QmlExtension/Uuid.h>
#include <QmlExtension/StandardPaths.h>

#include <QmlExtension/LocalStorage/LocalStorage.h>
#include <QmlExtension/LocalStorage/QmlSqlDatabaseData.h>

#include <QmlExtension/FileSystem.h>
#include <QmlExtension/ClipboardAdapter.h>
#include <QmlExtension/ConfigReader.h>

#include <QtCore/QCoreApplication>

#include <QmlExtension/SslWebSocketServer.h>
#include <QmlExtension/SslWebSocket.h>

void QmlExtension::registerTypes(const char *uri)
{
  qmlRegisterType<WheelArea>("Tulip", 1, 0, "WheelArea");
  qmlRegisterType<P1::MarketingAdapter>("Tulip", 1, 0, "Marketing");
  qmlRegisterType<Shortcut>("Tulip", 1, 0, "Shortcut");
  qmlRegisterType<ThemePack>("Tulip", 1, 0, "ThemePack");

  qmlRegisterUncreatableType<QDesktopItem>("Tulip", 1, 0, "Desktop", QLatin1String("Do not create objects of type Desktop"));
  qmlRegisterUncreatableType<SettingsAdapter>("Tulip", 1, 0, "Settings", QLatin1String("Do not create objects of type Settings"));
  qmlRegisterUncreatableType<Host>("Tulip", 1, 0, "Host", QLatin1String("Do not create objects of type Host"));

  qmlRegisterUncreatableType<P1::Auth::RegistryCredentialStorage>("Tulip", 1, 0, "CredentialStorage", QLatin1String("Do not create objects of type CredentialStorage"));
  qmlRegisterUncreatableType<GoogleAnalytics>("Tulip", 1, 0, "GoogleAnalyticsHelper", QLatin1String("Do not create objects of type GoogleAnalyticsHelper"));
  qmlRegisterUncreatableType<TrayWindow>("Tulip", 1, 0, "TrayWindow", QLatin1String("Do not create objects of type TrayWindow"));
  qmlRegisterUncreatableType<TaskList>("Tulip", 1, 0, "TaskList", QLatin1String("Do not create objects of type TaskList"));
  qmlRegisterUncreatableType<P1::MouseCursor>("Tulip", 1, 0, "MouseCursor", QLatin1String("Do not create objects of type MouseCursor"));
  qmlRegisterUncreatableType<QFileDialogAdapter>("Tulip", 1, 0, "QFileDialog", QLatin1String("Do not create objects of type QFileDialog"));
  qmlRegisterUncreatableType<StyleReader>("Tulip", 1, 0, "StyleReader", QLatin1String("Do not create objects of type StyleReader"));
  qmlRegisterUncreatableType<BrowserDetect>("Tulip", 1, 0, "BrowserDetect", QLatin1String("Do not create objects of type BrowserDetect"));
  qmlRegisterUncreatableType<TextDocumentHelper>("Tulip", 1, 0, "TextDocumentHelper", QLatin1String("Do not create objects of type TextDocumentHelper"));

  qmlRegisterUncreatableType<LocalStorage>("Tulip", 1, 0, "LocalStorage", QLatin1String("Do not create objects of type LocalStorage"));
  qmlRegisterUncreatableType<QmlSqlDatabaseData>("Tulip", 1, 0, "QmlSqlDatabaseData", QLatin1String("Do not create objects of type QmlSqlDatabaseData"));
  qmlRegisterUncreatableType<Uuid>("Tulip", 1, 0, "Uuid", QLatin1String("Do not create objects of type Uuid"));
  qmlRegisterUncreatableType<StandardPaths>("Tulip", 1, 0, "StandardPaths", QLatin1String("Do not create objects of type StandardPaths"));
  qmlRegisterUncreatableType<FileSystem>("Tulip", 1, 0, "FileSystem", QLatin1String("Do not create objects of type FileSystem"));
  qmlRegisterUncreatableType<ClipboardAdapter>("Tulip", 1, 0, "ClipboardAdapter", QLatin1String("Do not create objects of type ClipboardAdapter"));
  qmlRegisterUncreatableType<ConfigReader>("Tulip", 1, 0, "ConfigReader", QLatin1String("Do not create objects of type ConfigReader"));

  qmlRegisterType<SslWebSocketServer>("Tulip", 1, 0, "SslWebSocketServer");
  qmlRegisterType<SslWebSocket>("Tulip", 1, 0, "SslWebSocket");
}

void QmlExtension::initializeEngine(QQmlEngine *engine, const char *uri)
{
}