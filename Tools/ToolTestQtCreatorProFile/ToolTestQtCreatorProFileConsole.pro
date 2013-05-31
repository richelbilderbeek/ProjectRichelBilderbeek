QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_system

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppTrace

SOURCES += main.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppAbout/about.cpp \
    testqtcreatorprofilemenudialog.cpp

HEADERS += \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    testqtcreatorprofilemenudialog.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt
