#Don't enable Effective C++ warnings when using Qwt
include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtArrowItem/CppQtArrowItem.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../../Classes/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../../Classes/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../../Classes/CppQtRoundedTextRectItem/CppQtRoundedTextRectItem.pri)
include(../../Classes/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(../../Classes/CppXml/CppXml.pri)
include(../../Tools/ToolStyleSheetSetter/ToolStyleSheetSetterDesktop.pri)
include(../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItemsDesktop.pri)
include(../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItemDesktop.pri)
include(../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItemDesktop.pri)

include(ProjectBrainweaverDesktop.pri)

SOURCES += qtmain_developer.cpp
