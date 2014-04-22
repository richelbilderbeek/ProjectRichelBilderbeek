QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

!exists(../build-CppStaticLibraryQtCreatorExample1Library-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/libCppStaticLibraryQtCreatorExample1.a) {
  error(Could not find correct path to built library)
}

LIBS += ../build-CppStaticLibraryQtCreatorExample1Library-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/libCppStaticLibraryQtCreatorExample1.a
