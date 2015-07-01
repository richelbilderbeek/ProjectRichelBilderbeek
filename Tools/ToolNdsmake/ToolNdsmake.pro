include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
#include(../../Libraries/GeneralDesktop.pri)

include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)

SOURCES += \
    main.cpp \
    ndsmake.cpp

HEADERS += \
    createholymakefile.h \
    createmakefile.h \
    ndsmake.h
