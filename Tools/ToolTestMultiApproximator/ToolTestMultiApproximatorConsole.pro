TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    ../../Classes/CppApproximator \
    ../../Classes/CppCanvas \
    ../../Classes/CppMultiApproximator \
    ../../Classes/CppTrace

SOURCES += main.cpp \
    ../../Classes/CppApproximator/approximator.cpp \
    ../../Classes/CppApproximator/exceptionnoextrapolation.cpp \
    ../../Classes/CppCanvas/canvas.cpp \
    ../../Classes/CppMultiApproximator/multiapproximator.cpp

HEADERS += \
    ../../Classes/CppApproximator/approximator.h \
    ../../Classes/CppApproximator/exceptionnoextrapolation.h \
    ../../Classes/CppCanvas/canvas.h \
    ../../Classes/CppMultiApproximator/multiapproximator.h \
    ../../Classes/CppTrace/trace.h

OTHER_FILES += \
    ../../Classes/CppApproximator/Licence.txt \
    ../../Classes/CppCanvas/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppMultiApproximator/Licence.txt

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
