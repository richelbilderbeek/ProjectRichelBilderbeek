include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

include(../../Classes/CppAbcFile/CppAbcFile.pri)
include(../../Classes/CppMusic/CppMusic.pri)

# include(ToolMidiLessonCreatorDesktop.pri

SOURCES += \
    main.cpp \
    qtmidilessoncreatormaindialog.cpp \
    midilessoncreatormaindialog.cpp

HEADERS += \
    qtmidilessoncreatormaindialog.h \
    midilessoncreatormaindialog.h

FORMS += \
    qtmidilessoncreatormaindialog.ui
