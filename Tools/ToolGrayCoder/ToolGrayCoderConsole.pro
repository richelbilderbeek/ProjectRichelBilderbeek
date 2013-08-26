QT += core
QT -= gui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    toolgraycodermenudialog.cpp \
    toolgraycodermaindialog.cpp \
    main.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    toolgraycodermenudialog.h \
    toolgraycodermaindialog.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

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
  #Strict error handling
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
