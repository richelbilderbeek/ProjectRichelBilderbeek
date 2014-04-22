include(../../WebApplication.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)

!win32 {
  error(Must be native Windows)
}

SOURCES += main.cpp
