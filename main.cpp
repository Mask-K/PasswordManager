#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <saltGenerator.h>
#include <sha-256.h>
#include <iostream>

#include <QFile>
#include <QFileInfo>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/PasswordManager/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QString data = "Hello, World!";
    auto hash = sha256(data);
    std::cout << "SHA-256: " << hash.toStdString() << std::endl;

    if(QFileInfo::exists(hash + ".json") && QFileInfo(hash + ".json").isFile()){
        std::cout << "File exists";
    }
    else{
        std::cout<< "File not exist";
    }

    return app.exec();
}
