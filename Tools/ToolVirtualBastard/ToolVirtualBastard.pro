QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppVirtualBastard

SOURCES += \
    qtmain.cpp \
    qtvirtualbastardmaindialog.cpp \
    ../../Classes/CppVirtualBastard/virtualbastard.cpp \
    qtvirtualbastardmenudialog.cpp \
    qtvirtualbastardexample1dialog.cpp \
    ../../Classes/CppVirtualBastard/virtualbastardcommand.cpp \
    ../../Classes/CppVirtualBastard/virtualbastardcommandfactory.cpp

HEADERS  += \
    qtvirtualbastardmaindialog.h \
    ../../Classes/CppVirtualBastard/virtualbastard.h \
    qtvirtualbastardmenudialog.h \
    qtvirtualbastardexample1dialog.h \
    ../../Classes/CppVirtualBastard/virtualbastardcommand.h \
    ../../Classes/CppVirtualBastard/virtualbastardcommandfactory.h


FORMS    += \
    qtvirtualbastardmaindialog.ui \
    qtvirtualbastardmenudialog.ui \
    qtvirtualbastardexample1dialog.ui

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

#
#
# libcvautomation
#
# add path to #include paths, link statically to code
#
#
INCLUDEPATH += ../../Libraries/libcvautomation/include
SOURCES += \
    ../../Libraries/libcvautomation/libcvautomation/libcvautomation-xtest.c \
    ../../Libraries/libcvautomation/libcvautomation/libcvautomation-xlib.c \
    ../../Libraries/libcvautomation/libcvautomation/libcvautomation-opencv.c

# Link to X11 library
# undefined reference to `XOpenDisplay'
LIBS += -lX11

# Link to Xtst library
# undefined reference to `XTestQueryExtension'
LIBS += -lXtst

# Link to OpenCV library
# undefined reference to `cvFree_'
unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += opencv
}
