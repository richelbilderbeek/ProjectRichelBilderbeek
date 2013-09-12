TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

win32 {
  INCLUDEPATH += \
    ../../Libraries/ode-0.12
}

