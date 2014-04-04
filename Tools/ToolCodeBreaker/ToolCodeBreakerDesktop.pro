include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

include(../../Classes/CppCaesarCipher/CppCaesarCipher.pri)
include(../../Classes/CppCodeBreaker/CppCodeBreaker.pri)
include(../../Classes/CppLoopReader/CppLoopReader.pri)
include(../../Classes/CppVigenereCipher/CppVigenereCipher.pri)

include(../../Tools/ToolCaesarCipher/ToolCaesarCipherDesktop.pri)
include(../../Tools/ToolVigenereCipher/ToolVigenereCipherDesktop.pri)

include(../../Tools/ToolCodeBreaker/ToolCodeBreakerDesktop.pri)

SOURCES += qtmain.cpp
