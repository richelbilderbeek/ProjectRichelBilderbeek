INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppFileIo \
    ../../Classes/CppHelp \
    ../../Classes/CppMenuDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppAsciiArter/asciiarter.cpp \
    asciiartermaindialog.cpp \
    asciiartermenudialog.cpp \
    ../../Classes/CppFileIo/fileio.cpp \
    ../../Classes/CppMenuDialog/menudialog.cpp \
    ../../Classes/CppHelp/help.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    asciiartermaindialog.h \
    asciiartermenudialog.h \
    ../../Classes/CppFileIo/fileio.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppMenuDialog/menudialog.h \
    ../../Classes/CppHelp/help.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
    Licence.txt \
    ../../Classes/CppFileIo/Licence.txt \
    ../../Classes/CppTrace/Licence.txt

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
