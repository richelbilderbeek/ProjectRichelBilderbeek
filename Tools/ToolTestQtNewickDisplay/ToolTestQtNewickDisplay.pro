include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppQtNewickDisplay/CppQtNewickDisplay.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)


SOURCES += main.cpp \
        qttestqtnewickdisplay.cpp

HEADERS  += qttestqtnewickdisplay.h

FORMS    += qttestqtnewickdisplay.ui
