QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include(ToolCreateQtProjectZipFileConsole.pri)

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppFileIo \
    ../../Classes/CppHelp \
    ../../Classes/CppMenuDialog \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppFileIo/fileio.cpp \
    ../../Classes/CppMenuDialog/menudialog.cpp \
    ../../Classes/CppHelp/help.cpp \
    main.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppFileIo/fileio.h \
    ../../Classes/CppMenuDialog/menudialog.h \
    ../../Classes/CppHelp/help.h
