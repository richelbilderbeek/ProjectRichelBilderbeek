QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

QMAKE_CXXFLAGS += -Wall -Wextra -Werror

unix {
  QMAKE_CXXFLAGS += -std=c++11

  #Warp's function parser
  INCLUDEPATH += ../../Libraries/fparser4.5.1
  SOURCES += ../../Libraries/fparser4.5.1/fparser.cc
  HEADERS += ../../Libraries/fparser4.5.1/fparser.hh
}

win32 {
  QMAKE_CXXFLAGS += -std=c++0x

  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

  #Boost
  INCLUDEPATH += E:/boost_1_50_0
  LIBS += -LE:/boost_1_50_0/stage/lib

  #Warp's function parser
  INCLUDEPATH += ../../Libraries/fparser4.4.3
  SOURCES += ../../Libraries/fparser4.4.3/fparser.cc
  HEADERS += ../../Libraries/fparser4.4.3/fparser.hh
}

INCLUDEPATH+= \
    ../../Classes/CppAbout \
    ../../Classes/CppMatrix \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtModel \
    ../../Classes/CppTrace

SOURCES+= \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp \
    qtmain.cpp \
    qttooltestqtmodelsmaindialog.cpp \
    qttooltestqtmodelsmenudialog.cpp \
    tooltestqtmodelsmenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.h \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.h \
    ../../Classes/CppTrace/trace.h \
    qttooltestqtmodelsmaindialog.h \
    qttooltestqtmodelsmenudialog.h \
    tooltestqtmodelsmenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttooltestqtmodelsmaindialog.ui \
    qttooltestqtmodelsmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    zip.sh
