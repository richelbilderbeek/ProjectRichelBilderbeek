include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppQtDnaSequencesDisplay/CppQtDnaSequencesDisplay.pri)
include(../../Classes/CppQtDnaSequencesDialog/CppQtDnaSequencesDialog.pri)
include(../../Classes/CppDnaR/CppDnaR.pri)
include(../../Classes/CppFastaFile/CppFastaFile.pri)


SOURCES += main.cpp \
        qttestqtdnasequencesdisplay.cpp

HEADERS  += qttestqtdnasequencesdisplay.h

FORMS    += qttestqtdnasequencesdisplay.ui
