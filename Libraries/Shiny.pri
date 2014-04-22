win32 {
  # Windows only
  message("Shiny, built for Windows")
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

macx {
  # Mac only
  message("Don't use Shiny on Mac")
}

unix:!macx{
  # Linux only
  message("Don't use Shiny on Linux")
}

cross_compile {
  # Crosscompile only
  message("Don't use Shiny when cross-compiling from Linux to Windows")
}

