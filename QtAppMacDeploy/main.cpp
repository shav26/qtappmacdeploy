#include <QtCore>
#include <QApplication>
#include <QtQuick>
#include <qqml.h>
#include <QQmlApplicationEngine>
#include "qmdmanager.h"
#include "qmdsettings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:///qml/images/icon/icon_512x512.icns"));
    app.setOrganizationDomain("com.shav");
    app.setOrganizationName("SHAV Software");
    app.setApplicationVersion("1.1.0");
    app.setApplicationName("Qt App Mac Deploy");
    app.setFont(QFont("Helvetica Neue", 13));

    qmlRegisterType<QmdSettings>("com.shav.qtappmacdeploy", 1, 0, "QmdSettings");
    qmlRegisterType<QmdManager>("com.shav.qtappmacdeploy", 1, 0, "QmdManager");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

    return app.exec();
}
