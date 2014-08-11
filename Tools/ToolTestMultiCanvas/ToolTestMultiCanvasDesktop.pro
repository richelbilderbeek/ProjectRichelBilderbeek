include(../../DesktopApplication.pri)

include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific for this application
#Console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppMultiCanvas/CppMultiCanvas.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppXml/CppXml.pri)

#Desktop
include(../../Tools/ToolTestMultiCanvas/ToolTestMultiCanvasDesktop.pri)

SOURCES += qtmain.cpp

