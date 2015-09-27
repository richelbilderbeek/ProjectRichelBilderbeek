#DEFINES += BRAINWEAVER_MOVE_ITEMS_ON_COLLISION

#Don't enable Effective C++ warnings when using Qwt
include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppGrabber/CppGrabber.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppQtImage/CppQtImage.pri)
include(../../Classes/CppRibiRandom/CppRibiRandom.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppStopwatch/CppStopwatch.pri)

include(../../Classes/CppQtArrowItem/CppQtArrowItem.pri)
include(../../Classes/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../../Classes/CppQtGraphics/CppQtGraphics.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../../Classes/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../../Classes/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../../Classes/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Tools/ToolStyleSheetSetter/ToolStyleSheetSetterDesktop.pri)
include(../../Tools/ToolTestConceptMap/ToolTestConceptMapDesktop.pri)
include(../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItemsDesktop.pri)
include(../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItemDesktop.pri)
include(../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItemDesktop.pri)

#Desktop
include(../../Classes/CppQtConceptMap/CppQtConceptMap.pri)
include(ProjectBrainweaverDesktop.pri)

SOURCES += qtmain_developer.cpp
