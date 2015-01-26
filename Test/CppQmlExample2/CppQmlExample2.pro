include(../../DesktopApplication.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Classes/CppCaesarCipher/CppCaesarCipher.pri)
include(../../Classes/CppLoopReader/CppLoopReader.pri)

TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
