QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += main.cpp\
        qttestaboutmaindialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp

HEADERS  += qttestaboutmaindialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h

FORMS    += qttestaboutmaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

#
#
# Boost
#
#

unix {
  message(Unix dynamic link to Boost)

  #LIBS += \
  #-lboost_date_time \
  #-lboost_filesystem \
  #-lboost_program_options \
  #-lboost_regex \
  #-lboost_signals \
  #-lboost_system
}

win32 {

  message(Windows dynamic link to Boost)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  #debug {
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-d-1_54.a
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  #}
  #release {
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-1_54.a
  #  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  #}
}

RESOURCES += \
    ToolTestAbout.qrc
