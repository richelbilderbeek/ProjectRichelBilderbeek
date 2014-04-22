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
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.cpp \
    ../../Classes/CppStateObserver/alphabetafilter.cpp \
    ../../Classes/CppStateObserver/alphabetagammafilter.cpp \
    ../../Classes/CppStateObserver/alphafilter.cpp \
    ../../Classes/CppStateObserver/floatingpointstateobserver.cpp \
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
    stateobservermenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.h \
    ../../Classes/CppStateObserver/alphabetafilter.h \
    ../../Classes/CppStateObserver/alphabetagammafilter.h \
    ../../Classes/CppStateObserver/alphafilter.h \
    ../../Classes/CppStateObserver/floatingpointstateobserver.h \
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
    stateobservermenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtStateObserver/qtalphafilterdialog.ui \
    qtstateobservermaindialog.ui \
    qtstateobservermenudialog.ui

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

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ 

unix {
  QMAKE_CXXFLAGS +=  -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
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
  INCLUDEPATH += /usr/include/qwt
  LIBS += -L/usr/lib -lqwt
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
