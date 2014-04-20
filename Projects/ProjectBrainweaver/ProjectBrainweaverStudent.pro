#Don't enable Effective C++ warnings when using Qwt
include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

#Specific, console
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop

include(../../Classes/CppQtArrowItem/CppQtArrowItem.pri)
include(../../Classes/CppQtConceptMap/CppQtConceptMap.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../../Classes/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../../Classes/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../../Classes/CppQtRoundedTextRectItem/CppQtRoundedTextRectItem.pri)
include(../../Classes/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../../Tools/ToolStyleSheetSetter/ToolStyleSheetSetterDesktop.pri)
include(../../Tools/ToolTestConceptMap/ToolTestConceptMapDesktop.pri)
include(../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItemsDesktop.pri)
include(../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItemDesktop.pri)
include(../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItemDesktop.pri)

include(ProjectBrainweaverDesktop.pri)

SOURCES += \
    qtmain_student.cpp
