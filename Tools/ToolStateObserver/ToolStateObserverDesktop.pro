#Use static when crosscompiling from Lubuntu to Windows
win32 {
  #CONFIG += static
}

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppStateObserver \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppStateObserver/alphabetafilter.cpp \
    ../../Classes/CppStateObserver/alphabetagammafilter.cpp \
    ../../Classes/CppStateObserver/alphafilter.cpp \
    ../../Classes/CppStateObserver/integeralphafilter.cpp \
    ../../Classes/CppStateObserver/integerstateobserver.cpp \
    ../../Classes/CppStateObserver/integersymmetricalphafilter.cpp \
    ../../Classes/CppStateObserver/multialphafilter.cpp \
    ../../Classes/CppStateObserver/multiintegerstateobserver.cpp \
    lsqfilter.cpp \
    noisefunctionparser.cpp \
    qtmain.cpp \
    qtstateobservermaindialog.cpp \
    qtstateobservermenudialog.cpp \
    slidingmodeobserver.cpp \
    slsqfilter.cpp \
    stateobservermenudialog.cpp \
    ../../Classes/CppStateObserver/floatingpointstateobserver.cpp \
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppStateObserver/alphabetafilter.h \
    ../../Classes/CppStateObserver/alphabetagammafilter.h \
    ../../Classes/CppStateObserver/alphafilter.h \
    ../../Classes/CppStateObserver/integeralphafilter.h \
    ../../Classes/CppStateObserver/integerstateobserver.h \
    ../../Classes/CppStateObserver/integersymmetricalphafilter.h \
    ../../Classes/CppStateObserver/multialphafilter.h \
    ../../Classes/CppStateObserver/multiintegerstateobserver.h \
    ../../Classes/CppStateObserver/stateobserverfwd.h \
    ../../Classes/CppTrace/trace.h \
    lsqfilter.h \
    noisefunctionparser.h \
    qtstateobservermaindialog.h \
    qtstateobservermenudialog.h \
    slsqfilter.h \
    stateobservermenudialog.h \
    ../../Classes/CppStateObserver/floatingpointstateobserver.h \
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtstateobservermaindialog.ui \
    qtstateobservermenudialog.ui \
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.ui

RESOURCES += \
    ToolStateObserver.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/ToolStateObserver/Licence.txt \
    crosscompiletowindows.sh \
    zip.sh


#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -Wall -Wextra

unix {
  message(Unix)
  #Strict error handling
  QMAKE_CXXFLAGS += -std=c++11 -Werror
}

win32 {
  !static {
    message(Native Windows)
    #Allow native Windows to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++11 #-Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++11 #-Werror
  }


  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  #DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED
}

#
#
# Boost
#
#

unix {
  message(Unix dynamic link to Boost)

  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  message(Windows dynamic link to Boost)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  debug {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  }
  release {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  }
}

#
#
# Warp's function parser
#
#
#unix {
  INCLUDEPATH += \
    ../../Libraries/fparser4.5.1

  HEADERS += \
    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
    ../../Libraries/fparser4.5.1/fpconfig.hh

  SOURCES += \
    ../../Libraries/fparser4.5.1/fparser.cc \
    ../../Libraries/fparser4.5.1/fpoptimizer.cc


  OTHER_FILES += \
    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
#}

#
#
# Qwt
#
#

unix {
  INCLUDEPATH += /usr/include/qwt-qt4
  LIBS += -lqwt-qt4
}

win32 {
  message(Windows: Qwt: link dynamically)
  INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
  LIBS+= -L../../Libraries/qwt-6.1.0/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}
