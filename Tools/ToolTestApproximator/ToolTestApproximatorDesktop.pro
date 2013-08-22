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
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppApproximator/approximator.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qttooltestapproximatormaindialog.cpp \
    tooltestapproximatormenudialog.cpp \
    qttooltestapproximatormenudialog.cpp \
    ../../Classes/CppApproximator/exceptionnoextrapolation.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppApproximator/approximator.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qttooltestapproximatormaindialog.h \
    qttooltestapproximatormenudialog.h \
    tooltestapproximatormenudialog.h \
    ../../Classes/CppApproximator/exceptionnoextrapolation.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttooltestapproximatormaindialog.ui \
    qttooltestapproximatormenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppApproximator/Licence.txt \
    Licence.txt

#RESOURCES += \
#    ToolTestApproximatorFilterer.qrc

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

  QMAKE_CXXFLAGS += -Werror

unix {
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

unix {
  # Cannot link to the the non-header-only libraries when crosscompiling
}

win32 {

  cross_compile {
    message(Lubuntu to Windows: Boost: link)
  }

  !cross_compile {
    message(Native Windows: Boost: include)
    INCLUDEPATH += \
      ../../Libraries/boost_1_54_0
  }


  # Cannot link to the the non-header-only libraries when crosscompiling
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

RESOURCES += \
    ToolTestApproximator.qrc
