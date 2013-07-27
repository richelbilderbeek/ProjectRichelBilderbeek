QT += core
QT -= gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
TEMPLATE = app
LIBS += \
    -lboost_program_options \
    -lboost_regex

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTrace

SOURCES += main.cpp \
    regextestermaindialog.cpp \
    regextestermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    regextesterqtmaindialog.cpp \
    regextestercpp11maindialog.cpp \
    regextesterboostmaindialog.cpp \
    regextestertr1maindialog.cpp

HEADERS += \
    regextestermaindialog.h \
    regextestermenudialog.h \
    ../../Classes/CppAbout/about.h \
    regextesterqtmaindialog.h \
    regextestercpp11maindialog.h \
    regextesterboostmaindialog.h \
    ../../Classes/CppTrace/trace.h \
    regextestertr1maindialog.h

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh
