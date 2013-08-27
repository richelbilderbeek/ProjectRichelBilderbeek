TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp
HEADERS +=


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
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

unix {
  message(Unix: Boost already in include path)
}

win32 {
  message(Windows: add Boost to include path)
  INCLUDEPATH += \
    E:/Projects/Libraries/boost_1_54_0
}

#
#
# alglib
#
#

unix {
  message(Lubuntu: alglib not tested)

}

win32 {
  message(Windows: alglib: include path)
  INCLUDEPATH += ../../Libraries/alglib-3.8.0/src

SOURCES += \
    ../../Libraries/alglib-3.8.0/src/statistics.cpp \
    ../../Libraries/alglib-3.8.0/src/specialfunctions.cpp \
    ../../Libraries/alglib-3.8.0/src/solvers.cpp \
    ../../Libraries/alglib-3.8.0/src/optimization.cpp \
    ../../Libraries/alglib-3.8.0/src/linalg.cpp \
    ../../Libraries/alglib-3.8.0/src/interpolation.cpp \
    ../../Libraries/alglib-3.8.0/src/integration.cpp \
    ../../Libraries/alglib-3.8.0/src/fasttransforms.cpp \
    ../../Libraries/alglib-3.8.0/src/diffequations.cpp \
    ../../Libraries/alglib-3.8.0/src/dataanalysis.cpp \
    ../../Libraries/alglib-3.8.0/src/ap.cpp \
    ../../Libraries/alglib-3.8.0/src/alglibmisc.cpp \
    ../../Libraries/alglib-3.8.0/src/alglibinternal.cpp

HEADERS += \
    ../../Libraries/alglib-3.8.0/src/statistics.h \
    ../../Libraries/alglib-3.8.0/src/specialfunctions.h \
    ../../Libraries/alglib-3.8.0/src/solvers.h \
    ../../Libraries/alglib-3.8.0/src/optimization.h \
    ../../Libraries/alglib-3.8.0/src/linalg.h \
    ../../Libraries/alglib-3.8.0/src/interpolation.h \
    ../../Libraries/alglib-3.8.0/src/integration.h \
    ../../Libraries/alglib-3.8.0/src/fasttransforms.h \
    ../../Libraries/alglib-3.8.0/src/diffequations.h \
    ../../Libraries/alglib-3.8.0/src/dataanalysis.h \
    ../../Libraries/alglib-3.8.0/src/ap.h \
    ../../Libraries/alglib-3.8.0/src/alglibmisc.h \
    ../../Libraries/alglib-3.8.0/src/alglibinternal.h
}
