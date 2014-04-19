#DEFINES += FIX_ISSUE_168
#DEFINES += ANSI_DECLARATORS
QMAKE_CXXFLAGS += -Werror

exists(../../ConsoleApplication.pri) {
  include(../../ConsoleApplication.pri)
}
!exists(../../ConsoleApplication.pri) {
  QT += core
  QT += gui
  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
  CONFIG(release, debug|release) {
    DEFINES += NDEBUG NTRACE_BILDERBIKKEL
  }
  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
  unix {
    QMAKE_CXXFLAGS += -Werror
  }
}

exists(../../Libraries/Boost.pri) {
  include(../../Libraries/Boost.pri)
}
!exists(../../Libraries/Boost.pri) {
  win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
  }
}

exists(../../Libraries/Shiny.pri) {
  include(../../Libraries/Shiny.pri)
}
!exists(../../Libraries/Shiny.pri) {
  INCLUDEPATH += \
      ../../Libraries/Shiny/include

  SOURCES += \
      ../../Libraries/Shiny/src/ShinyTools.cpp \
      ../../Libraries/Shiny/src/ShinyOutput.cpp \
      ../../Libraries/Shiny/src/ShinyNodePool.cpp \
      ../../Libraries/Shiny/src/ShinyNode.cpp \
      ../../Libraries/Shiny/src/ShinyManager.cpp

  HEADERS += \
      ../../Libraries/Shiny/include/ShinyZone.h \
      ../../Libraries/Shiny/include/ShinyTools.h \
      ../../Libraries/Shiny/include/ShinyPrereqs.h \
      ../../Libraries/Shiny/include/ShinyOutput.h \
      ../../Libraries/Shiny/include/ShinyNodePool.h \
      ../../Libraries/Shiny/include/ShinyNode.h \
      ../../Libraries/Shiny/include/ShinyManager.h \
      ../../Libraries/Shiny/include/ShinyMacros.h \
      ../../Libraries/Shiny/include/ShinyData.h \
      ../../Libraries/Shiny/include/ShinyConfig.h \
      ../../Libraries/Shiny/include/Shiny.h
}

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppOpenFoam/CppOpenFoam.pri)
include(../../Classes/CppPhp/CppPhp.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppTriangleFile/CppTriangleFile.pri)
include(../../Classes/CppTriangleMesh/CppTriangleMesh.pri)
include(../../Classes/CppXml/CppXml.pri)
include(../../Tools/ToolTestTriangleMesh/ToolTestTriangleMeshConsole.pri)
include(../../Tools/ToolTriangle/ToolTriangleConsole.pri)

SOURCES += main.cpp
