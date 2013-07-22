/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/QmlExtension.h>
#include <QmlExtension/QCursorArea.h>
#include <QmlExtension/WheelArea.h>
#include <QmlExtension/QWindowItem.h>
#include <QmlExtension/QDesktopItem.h>
#include <QmlExtension/SettingsAdapter.h>
#include <QmlExtension/MarketingAdapter.h>
#include <QmlExtension/GoogleAnalytics.h>
#include <QmlExtension/QFileDialogAdapter.h>
#include <QmlExtension/QMultimedia.h>
#include <QmlExtension/QPing.h>
#include <QmlExtension/traywindow.h>

#include <QmlExtension/WebView/CustomNetworkManagerFactory.h>
#include <QmlExtension/WebView/NetworkAccessManagerInteractor.h>

#include <QmlExtension/Auth/RegistryCredentialStorage.h>
#include <QmlExtension/App.h>

#include <QtCore/QCoreApplication>

using GGS::WebView::CustomNetworkManagerFactory;
using GGS::WebView::NetworkAccessManagerInteractor;

void QmlExtension::registerTypes(const char *uri)
{
  qmlRegisterType<QCursorArea>("Tulip", 1, 0, "CursorArea");
  qmlRegisterType<WheelArea>("Tulip", 1, 0, "WheelArea");
  qmlRegisterType<QWindowItem>("Tulip", 1, 0, "Window");
  qmlRegisterType<QPing>("Tulip", 1, 0, "PingEx");
  qmlRegisterType<GGS::MarketingAdapter>("Tulip", 1, 0, "Marketing");

  qmlRegisterUncreatableType<QDesktopItem>("Tulip", 1, 0, "Desktop", QLatin1String("Do not create objects of type Desktop"));
  qmlRegisterUncreatableType<SettingsAdapter>("Tulip", 1, 0, "Settings", QLatin1String("Do not create objects of type Settings"));
  qmlRegisterUncreatableType<App>("Tulip", 1, 0, "App", QLatin1String("Do not create objects of type App"));
  qmlRegisterUncreatableType<NetworkAccessManagerInteractor>("Tulip", 1, 0, "WebViewHelper", QLatin1String("Do not create objects of type WebViewHelper"));
  qmlRegisterUncreatableType<GGS::Auth::RegistryCredentialStorage>("Tulip", 1, 0, "CredentialStorage", QLatin1String("Do not create objects of type CredentialStorage"));
  qmlRegisterUncreatableType<GoogleAnalytics>("Tulip", 1, 0, "GoogleAnalyticsHelper", QLatin1String("Do not create objects of type GoogleAnalyticsHelper"));
  qmlRegisterUncreatableType<QMultimedia>("Tulip", 1, 0, "QMultimedia", QLatin1String("Do not create objects of type QMultimedia"));
  qmlRegisterUncreatableType<TrayWindow>("Tulip", 1, 0, "TrayWindow", QLatin1String("Do not create objects of type TrayWindow"));
  
  // UNDONE: решить какой вариант регистрации подойдет  
  //qmlRegisterUncreatableType<GGS::MarketingAdapter>("Tulip", 1, 0, "Marketing", QLatin1String("Do not create objects of type Marketing"));
  
  qmlRegisterUncreatableType<QFileDialogAdapter>("Tulip", 1, 0, "QFileDialog", QLatin1String("Do not create objects of type QFileDialog"));
}

void QmlExtension::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
  CustomNetworkManagerFactory *customFactory = new CustomNetworkManagerFactory(engine);
  engine->setNetworkAccessManagerFactory(customFactory);
  
  NetworkAccessManagerInteractor::setDeclarativeView(engine);
  NetworkAccessManagerInteractor::setCookieJar(customFactory->cookieJar());

  //HACK Это единственный адекватный способ пробросить в дефолтный user-agent часть строки GNA
  QCoreApplication::setApplicationName(QCoreApplication::applicationName() + " GNA");
}

#ifdef _DEBUG
Q_EXPORT_PLUGIN2(QmlExtensionX86d, QmlExtension);
#else
Q_EXPORT_PLUGIN2(QmlExtensionX86, QmlExtension);
#endif