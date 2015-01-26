#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml>
#include "caesarcipher.h"

struct QmlCaesarCipher : public QObject
{
  QmlCaesarCipher(const int key = 0) : m_cipher(key) {}
  ribi::CaesarCipher m_cipher;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //qmlRegisterType<testClass>("MyCustomQMLObjects", 2, 35, "testClassNameInQML");
    qmlRegisterType<QmlCaesarCipher>("QmlCaesarCipher", 2, 35, "QmlCaesarCipher1");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
