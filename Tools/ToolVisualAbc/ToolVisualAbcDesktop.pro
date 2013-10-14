QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppFileIo \
    ../../Classes/CppMusic \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qttoolvisualabcchordsdialog.cpp \
    qttoolvisualabcmaindialog.cpp \
    qttoolvisualabcmenudialog.cpp \
    toolvisualabccheckprerequisites.cpp \
    toolvisualabcchords.cpp \
    toolvisualabcmaindialog.cpp \
    toolvisualabcmenudialog.cpp \
    ../../Classes/CppFileIo/fileio.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qttoolvisualabcchordsdialog.h \
    qttoolvisualabcmaindialog.h \
    qttoolvisualabcmenudialog.h \
    toolvisualabccheckprerequisites.h \
    toolvisualabcchords.h \
    toolvisualabcmaindialog.h \
    toolvisualabcmenudialog.h \
    ../../Classes/CppFileIo/fileio.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolvisualabcchordsdialog.ui \
    qttoolvisualabcmaindialog.ui \
    qttoolvisualabcmenudialog.ui

RESOURCES += \
    ToolVisualAbc.qrc

OTHER_FILES += \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

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
  LIBS += -lboost_program_options
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
