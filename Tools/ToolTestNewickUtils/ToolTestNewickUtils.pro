include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)


SOURCES += main.cpp \
        qttestnewickutilsdialog.cpp

HEADERS  += qttestnewickutilsdialog.h

FORMS    += qttestnewickutilsdialog.ui
