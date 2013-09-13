TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp

CONFIG(debug, debug|release) {
  message(Building debug version)

} else {
  DEFINES += NDEBUG
  message(Building release version)
}

# Note: when 'Build all' the following compiler output is generated:
#
# Project MESSAGE: Building debug version
# Project MESSAGE: Building debug version
# Project MESSAGE: Building release version
#
# This is because there are three makefiles generated:
# - A debug makefile
# - A release makefile
# - A makefile following the programmer's selected build, in this case a debug build
