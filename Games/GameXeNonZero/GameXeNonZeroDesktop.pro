QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    gamexenonzeroarea.cpp \
    gamexenonzerodialog.cpp \
    gamexenonzerosprite.cpp \
    qtmain.cpp \
    qtxenonzeromaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    gamexenonzeroarea.h \
    gamexenonzerodialog.h \
    gamexenonzerosprite.h \
    qtxenonzeromaindialog.h \
    gamexenonzerofwd.h

OTHER_FILES += \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    GameXeNonZero.txt

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtxenonzeromaindialog.ui

RESOURCES += \

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

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

unix {
  message(Unix: Boost already in include path)
}

win32 {
  message(Windows: add Boost to include path)
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
