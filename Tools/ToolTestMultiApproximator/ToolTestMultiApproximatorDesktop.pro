QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# undefined reference to `_imp___ZNK8QWebView8settingsEv'
#greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

TEMPLATE = app

#
#
# Common
#
#

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppApproximator \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppMultiApproximator \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppApproximator/approximator.cpp \
    ../../Classes/CppApproximator/exceptionnoextrapolation.cpp \
    ../../Classes/CppMultiApproximator/multiapproximator.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qttooltestmultiapproximatormaindialog.cpp \
    tooltestmultiapproximatormenudialog.cpp \
    qttooltestmultiapproximatormenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppApproximator/approximator.h \
    ../../Classes/CppMultiApproximator/multiapproximator.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qttooltestmultiapproximatormaindialog.h \
    qttooltestmultiapproximatormenudialog.h \
    tooltestmultiapproximatormenudialog.h \
    ../../Classes/CppApproximator/exceptionnoextrapolation.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttooltestmultiapproximatormaindialog.ui \
    qttooltestmultiapproximatormenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppApproximator/Licence.txt \
    ../../Classes/CppMultiApproximator/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolTestMultiApproximator.qrc

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
    message(Linux: Qwt: use qwt-qt4)
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    message(Linux: Qwt: link to qwt)
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}

win32 {

  exists (../../Libraries/qwt-6.1.0/src) {
    message(Windows: Qwt: link dynamically)
    INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
    LIBS+= -L../../Libraries/qwt-6.1.0/lib

    CONFIG(release, debug|release) {
      message(Windows: Qwt: Linking to qwt)
      LIBS += -lqwt
    }

    CONFIG(debug, debug|release) {
      message(Windows: Qwt: Linking to qwtd)
      LIBS += -lqwtd
    }
  }
}
