#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <userAuthenticator.h>
#include <passwordManager.h>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/PasswordManager/Main.qml"_qs);

    UserAuthenticator userAuthenticator;
    PasswordManager passwordManager;

    engine.rootContext()->setContextProperty("authenticator", &userAuthenticator);
    engine.rootContext()->setContextProperty("manager", &passwordManager);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
