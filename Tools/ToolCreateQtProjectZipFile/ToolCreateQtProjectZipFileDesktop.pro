QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    createqtprojectzipfilemenudialog.cpp \
    createqtprojectzipfilepath.cpp \
    qtcreateqtprojectzipfilemaindialog.cpp \
    qtcreateqtprojectzipfilemenudialog.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    createqtprojectzipfilemenudialog.h \
    createqtprojectzipfilepath.h \
    qtcreateqtprojectzipfilemaindialog.h \
    qtcreateqtprojectzipfilemenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtcreateqtprojectzipfilemaindialog.ui \
    qtcreateqtprojectzipfilemenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    Licence.txt \
    zip.sh

RESOURCES += \
    ToolCreateQtProjectZipFile.qrc


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

unix {
  LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_system
}
