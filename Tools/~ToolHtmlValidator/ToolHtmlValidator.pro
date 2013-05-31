#-------------------------------------------------
#
# Project created by QtCreator 2010-09-19T14:22:14
#
#-------------------------------------------------
QT       += core gui
CONFIG(debug, debug|release) {
  TARGET = HtmlValidatorDebug
  message(Building debug version)

} else {
  TARGET = HtmlValidatorRelease
  DEFINES += NDEBUG
  message(Building release version)
}
TEMPLATE = app
LIBS+= -L/usr/lib -lboost_filesystem \
       -L/usr/lib -lboost_system \
       -L/usr/lib -lboost_regex
SOURCES += main.cpp\
        dialogmain.cpp \
    dialogwhatsnew.cpp \
    dialogabout.cpp
HEADERS  += dialogmain.h \
    dialogwhatsnew.h \
    dialogabout.h
FORMS    += dialogmain.ui \
    dialogwhatsnew.ui \
    dialogabout.ui

RESOURCES += \
    resources.qrc
