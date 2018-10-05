#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QObject>
#include <QProcess>

#include "context.h"
#include "greeterutil.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Settings *settings = new Settings();
    GreeterUtil *util = new GreeterUtil(&app);
    Context ctx;
    ctx.util = util;
    ctx.settings = settings;
    util->settings = settings;
    util->user = settings->lastUser;
    util->session = settings->lastSession;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Context", &ctx);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *obj = engine.rootObjects().first();
    util->obj = obj;

    return app.exec();
}
