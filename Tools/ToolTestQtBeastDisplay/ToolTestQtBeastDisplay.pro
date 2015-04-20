include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppBeast/CppBeast.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDnaR/CppDnaR.pri)
include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppFastaFile/CppFastaFile.pri)
include(../../Classes/CppQtDnaSequencesDialog/CppQtDnaSequencesDialog.pri)
include(../../Classes/CppQtBeastDisplay/CppQtBeastDisplay.pri)


SOURCES += main.cpp \
        qttestqtbeastdisplay.cpp

HEADERS  += qttestqtbeastdisplay.h

FORMS    += qttestqtbeastdisplay.ui
