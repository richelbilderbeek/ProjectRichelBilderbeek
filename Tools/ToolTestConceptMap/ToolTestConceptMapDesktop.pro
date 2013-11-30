include(../../DesktopApplication.pri)

#Libs
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)

#Console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Desktop
include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific for this application
#Console
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Classes/CppXml/CppXml.pri)
#Desktop
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppQtArrowItem/CppQtArrowItem.pri)
include(../../Classes/CppQtConceptMap/CppQtConceptMap.pri)
include(../../Classes/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../../Classes/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../../Classes/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../../Classes/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../../Classes/CppQtRoundedTextRectItem/CppQtRoundedTextRectItem.pri)
include(../../Classes/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../../Tools/ToolTestConceptMap/ToolTestConceptMapDesktop.pri)

SOURCES += qtmain.cpp

