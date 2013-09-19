QT       += core
QT       -= gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppRubiksClock \
    ../../Classes/CppRubiksClockWidget \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtDialWidget \
    ../../Classes/CppWtRubiksClockWidget \
    ../../Classes/CppWtToggleButtonWidget

SOURCES += \
    wtmain.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    wtrubiksclockmenudialog.cpp \
    wtrubiksclockmaindialog.cpp \
    rubiksclockmenudialog.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp

HEADERS += \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppTrace/trace.h \
    wtrubiksclockmenudialog.h \
    wtrubiksclockmaindialog.h \
    rubiksclockmenudialog.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h

RESOURCES += \
    GameRubiksClock.qrc

OTHER_FILES += \
    GameRubiksClockWelcome.png

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

unix {
  LIBS += -lboost_filesystem -lboost_signals -lboost_system -lboost_program_options
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

#
#
# Wt
#
#

unix {
  LIBS += -lwt -lwthttp
}
