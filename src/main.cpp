/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 illusion <vladyslav.makarov1@nure.ua>
*/

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>
#include <QtQmlWorkerScript>

#include <QQuickStyle>
#include <QIcon>

#include "about.h"
#include "app.h"
//#include "version-kirigami_db.h"
#include <KAboutData>
//#include <KLocalizedContext>
//#include <KLocalizedString>
#include <QSqlQueryModel>

#include "kirigami_dbconfig.h"

#include "cardlistviewsqlquerymodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("NURE"));
    QCoreApplication::setApplicationName(QStringLiteral("Kirigami_DB"));

    QQmlApplicationEngine engine;
    QApplication::setStyle(QStringLiteral("breeze"));
    QQuickStyle::setStyle(QStringLiteral("breeze"));
    auto config = Kirigami_DBConfig::self();
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCommandLineParser parser;
#ifdef Q_OS_ANDROID
    QQuickStyle::setStyle(QStringLiteral("org.kde.breeze"));
#else
    QIcon::setFallbackThemeName(QStringLiteral("breeze"));
    // Default to org.kde.desktop style unless the user forces another style
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }
#endif

#ifdef Q_OS_WINDOWS
    QApplication::setStyle(QStringLiteral("breeze"));
#endif
    //qmlRegisterSingletonInstance("org.kde.Kirigami_DB", 1, 0, "Config", config);

    AboutType about;
    //qmlRegisterSingletonInstance("org.kde.Kirigami_DB", 1, 0, "AboutType", &about);

    App application;
    qmlRegisterSingletonInstance("org.kde.Kirigami_DB", 1, 0, "App", &application);

    QSqlDatabase localDB = QSqlDatabase::addDatabase("QSQLITE");
    localDB.setDatabaseName("LAB_1");
    localDB.open();

    CardListViewSqlQueryModel* model = new CardListViewSqlQueryModel();

    model->setQuery("SELECT Stone_name, Stone_mineral FROM Stones");


    engine.rootContext()->setContextObject(new QQmlContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    engine.rootContext()->setContextProperty("DBModel", model);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
