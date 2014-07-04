exists (../../DesktopApplication.pri) {
  include(../../DesktopApplication.pri)
}
!exists (../../DesktopApplication.pri) {
  QT       += core gui
  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
  TEMPLATE = app
  SOURCES += main.cpp
  QMAKE_CXXFLAGS += -Wall -Wextra -Werror
}

exists (../../Libraries/Boost.pri) {
  include(../../Libraries/Boost.pri)
}
!exists (../../Libraries/Boost.pri) {
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
}

exists (../../Libraries/Qwt.pri) {
  include(../../Libraries/Qwt.pri)
}
!exists (../../Libraries/Qwt.pri) {
  INCLUDEPATH+= ../../Libraries/qwt-6.1/src
  LIBS+= -L../../Libraries/qwt-6.1/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}

SOURCES += main.cpp \
    myplot.cpp \
    mydialog.cpp \
    myzoomer.cpp \
    mydata.cpp \
    mycolormap.cpp

HEADERS += \
    myplot.h \
    mydialog.h \
    myzoomer.h \
    mydata.h \
    mycolormap.h

FORMS += \
    mydialog.ui
