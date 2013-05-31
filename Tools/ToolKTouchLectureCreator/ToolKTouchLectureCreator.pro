TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += ../../Classes/CppTrace

SOURCES += main.cpp \
    ktouchlecture.cpp \
    ktouchlevels.cpp \
    ktouchlevel.cpp

HEADERS += \
    ktouchlecture.h \
    ktouchlevels.h \
    ktouchlevel.h \
    ../../Classes/CppTrace/trace.h

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt

