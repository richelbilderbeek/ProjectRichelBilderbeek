QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog


SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtmain.cpp \
    qtmaziakmenudialog.cpp \
    qtmaziakmaindialog.cpp \
    qtmaziakinstructionsdialog.cpp \
    maziakmenudialog.cpp \
    qtmaziakgameoverdialog.cpp \
    qtmaziakgamewondialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtmaziakmenudialog.h \
    qtmaziakmaindialog.h \
    qtmaziakinstructionsdialog.h \
    maziakmenudialog.h \
    qtmaziakgameoverdialog.h \
    qtmaziakgamewondialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtmaziakmenudialog.ui \
    qtmaziakmaindialog.ui \
    qtmaziakinstructionsdialog.ui \
    qtmaziakgameoverdialog.ui \
    qtmaziakgamewondialog.ui

RESOURCES += \
    gamemaziak.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt

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
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  !static {
    message(Native Windows)
    QMAKE_CXXFLAGS += -Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += #-Werror
  }


  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  #DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}
