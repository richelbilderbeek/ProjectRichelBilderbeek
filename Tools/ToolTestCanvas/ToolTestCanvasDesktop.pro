QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

#
#
# Common
#
#

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCanvas \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppCanvas/canvas.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qttooltestcanvasmaindialog.cpp \
    qttooltestcanvasmenudialog.cpp \
    tooltestcanvasmenudialog.cpp \
    ../../Classes/CppQtCanvas/qtcanvas.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppCanvas/canvas.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qttooltestcanvasmaindialog.h \
    qttooltestcanvasmenudialog.h \
    tooltestcanvasmenudialog.h \
    ../../Classes/CppQtCanvas/qtcanvas.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttooltestcanvasmaindialog.ui \
    qttooltestcanvasmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppCanvas/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolTestCanvas.qrc

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}



#
#
# Qwt
#
#

unix {

  exists(/usr/include/qwt-qt4) {
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}

win32 {

  exists (../../Libraries/qwt-6.1.0/src) {
    INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
    LIBS+= -L../../Libraries/qwt-6.1.0/lib

    CONFIG(release, debug|release) {
      LIBS += -lqwt
    }

    CONFIG(debug, debug|release) {
      LIBS += -lqwtd
    }
  }
}
