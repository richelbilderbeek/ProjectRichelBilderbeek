TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

win32 {
  INCLUDEPATH += \
    ../../Libraries/ode-0.12/include

  #Getting close!
  LIBS += ../../Libraries/ode-0.12/lib/DebugDoubleDLL/drawstuffd.lib
  LIBS += ../../Libraries/ode-0.12/lib/DebugDoubleDLL/ode_doubled.lib
}

