QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app


INCLUDEPATH += \
    ../../Classes/CppQtHideAndShowDialog


SOURCES += \
    main.cpp\
    toolstylesheetsettermaindialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += toolstylesheetsettermaindialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS    += toolstylesheetsettermaindialog.ui

RESOURCES += \
    ToolStyleSheetSetter.qrc

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

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
