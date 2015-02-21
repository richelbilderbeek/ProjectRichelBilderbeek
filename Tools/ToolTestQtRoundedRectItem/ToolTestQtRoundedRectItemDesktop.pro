include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)

include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRandom/CppRibiRandom.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
#include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
#include(../../Classes/CppQtRoundedTextRectItem/CppQtRoundedTextRectItem.pri)

include(ToolTestQtRoundedRectItemDesktop.pri)

SOURCES += qtmain.cpp
