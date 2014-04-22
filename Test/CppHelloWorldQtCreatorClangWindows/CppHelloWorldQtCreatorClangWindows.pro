QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

#TARGET_EXT = .bc
#QMAKE_EXT_OBJ = .bc
#QMAKE_CXXFLAGS += -emit-llvm

#QMAKE_CXXFLAGS -= -no-keep-inline-dllexport
#QMAKE_CXXFLAGS -= -mthreads

#exists(C:/LLVM/bin/clang++.exe ) {
#  QMAKE_CXX = C:/LLVM/bin/clang++.exe
#}
#!exists(C:/LLVM/bin/clang++.exe ) {
#  error("LLVM clang++.exe not found")
#}

#exists(C:/LLVM/bin/clang.exe ) {
#  QMAKE_CC = C:/LLVM/bin/clang.exe
#}
#!exists(C:/LLVM/bin/clang.exe ) {
#  error("LLVM clang.exe not found")
#}

#QMAKE_LIB = llvm-ld -link-as-library -o
#QMAKE_RUN_CXX = $(CXX) $(CXXFLAGS) $(INCPATH) -c $src -o $obj
#QMAKE_RUN_CC = $(CC) $(CCFLAGS) $(INCPATH) -c $src -o $obj
