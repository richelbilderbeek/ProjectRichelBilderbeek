TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

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

# Compile as C code
QMAKE_CXX = gcc
QMAKE_CXXFLAGS = -x c

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
