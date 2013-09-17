QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtConnectThreeWidget \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    connectthreemenudialog.cpp \
    connectthreeresources.cpp \
    qtconnectthreegamedialog.cpp \
    qtconnectthreemenudialog.cpp \
    qtconnectthreeresources.cpp \
    qtmain.cpp \
    qtselectplayerwidget.cpp \
    qtshowwinnerdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../../Classes/CppTrace/trace.h \
    connectthreemenudialog.h \
    connectthreeresources.h \
    qtconnectthreegamedialog.h \
    qtconnectthreemenudialog.h \
    qtconnectthreeresources.h \
    qtselectplayerwidget.h \
    qtshowwinnerdialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtconnectthreegamedialog.ui \
    qtconnectthreemenudialog.ui \
    qtshowwinnerdialog.ui

RESOURCES += \
    GameConnectThree.qrc


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

unix {
  message(Unix build)
}

win32 {
  cross_compile {
    message(Windows cross-compile build)
  }

  cross_compile {
    message(Native Windows build)
  }
}

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++


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
  message(Unix dynamic link to Boost)

  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
