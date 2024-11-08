#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <saltGenerator.h>
#include <sha-256.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/PasswordManager/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    std::string data = "Hello, World!";
    std::string hash = sha256(data);
    std::cout << "SHA-256: " << hash << std::endl;

    return app.exec();
}
