include(../../DesktopApplication.pri)

include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppTestTimer/CppTestTimer.pri)
include(../../Classes/CppTrace/CppTrace.pri)

SOURCES += main.cpp \
        qttestphylogenyrdialog.cpp

HEADERS  += qttestphylogenyrdialog.h

FORMS    += qttestphylogenyrdialog.ui
