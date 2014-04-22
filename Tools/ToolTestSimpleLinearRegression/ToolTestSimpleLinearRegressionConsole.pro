TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppApproximator \
    ../../Classes/CppCanvas \
    ../../Classes/CppSimpleLinearRegression \
    ../../Classes/CppTrace

SOURCES += \
    main.cpp \
    ../../Classes/CppApproximator/approximator.cpp \
    ../../Classes/CppApproximator/exceptionnoextrapolation.cpp \
    ../../Classes/CppCanvas/canvas.cpp \
    tooltestsimplelinearregressionmenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppSimpleLinearRegression/simplelinearregression.cpp

HEADERS += \
    ../../Classes/CppApproximator/approximator.h \
    ../../Classes/CppApproximator/exceptionnoextrapolation.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppCanvas/canvas.h \
    tooltestsimplelinearregressionmenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppSimpleLinearRegression/simplelinearregression.h

OTHER_FILES += \
    ../../Classes/CppApproximator/Licence.txt \
    ../../Classes/CppCanvas/Licence.txt \
    ../../Classes/CppAbout/Licence.txt
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
