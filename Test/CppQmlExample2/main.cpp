#include <QGuiApplication>
#include <QQmlApplicationEngine>

<<<<<<< HEAD
=======
#include <QtQml>
#include "caesarcipher.h"

struct QmlCaesarCipher : public QObject
{
  QmlCaesarCipher(const int key = 0) : m_cipher(key) {}
  ribi::CaesarCipher m_cipher;
};

>>>>>>> c99017a2d230e590727b21cc2d7426112c8072b8
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

<<<<<<< HEAD
=======
    //qmlRegisterType<testClass>("MyCustomQMLObjects", 2, 35, "testClassNameInQML");
    qmlRegisterType<QmlCaesarCipher>("QmlCaesarCipher", 2, 35, "QmlCaesarCipher1");

>>>>>>> c99017a2d230e590727b21cc2d7426112c8072b8
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
