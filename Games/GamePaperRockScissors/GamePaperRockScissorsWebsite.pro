QT       -= core
QT       -= gui
  
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog

SOURCES += \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  wtmain.cpp \
  wtpaperrockscissorsdialog.cpp \
  wtpaperrockscissorsdialogstate.cpp \
  wtpaperrockscissorsevent.cpp \
  wtpaperrockscissorsserver.cpp

HEADERS += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppTrace/trace.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  wtpaperrockscissorsdialog.h \
  wtpaperrockscissorsdialogstate.h \
  wtpaperrockscissorsevent.h \
  wtpaperrockscissorsserver.h

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
# Wt
#
#

unix {
  LIBS += -lwt -lwthttp
}