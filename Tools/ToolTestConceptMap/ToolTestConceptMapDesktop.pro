include(../../DesktopApplication.pri)

#Libs
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Classes/CppQtArrowItem/CppQtArrowItem.pri)
include(../../Classes/CppQtConceptMap/CppQtConceptMap.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
#include(../../Classes/CppQtRoundedTextRectItem/CppQtRoundedTextRectItem.pri)
include(../../Classes/CppQtScopedDisable/CppQtScopedDisable.pri)
include(ToolTestConceptMapDesktop.pri)

SOURCES += qtmain.cpp

