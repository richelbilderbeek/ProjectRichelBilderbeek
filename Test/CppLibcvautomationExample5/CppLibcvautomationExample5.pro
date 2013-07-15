QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    main.cpp \
    qtdialog.cpp

HEADERS  += \
  qtdialog.h


FORMS    += qtdialog.ui

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

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
