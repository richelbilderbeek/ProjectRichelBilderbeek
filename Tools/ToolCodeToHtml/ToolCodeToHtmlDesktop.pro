win32 {
  #Add the line below when cross-compiling
  CONFIG += static
}

QT += core gui
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# undefined reference to `_imp___ZNK8QWebView8settingsEv'
# :-1: error: Unknown module(s) in QT: location sensors
#greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    codetohtmlmenudialog.cpp \
    qtcodetohtmlmaindialog.cpp \
    qtcodetohtmlmenudialog.cpp \
    qtmain.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    codetohtmlmenudialog.h \
    qtcodetohtmlmaindialog.h \
    qtcodetohtmlmenudialog.h \
    ../../Classes/CppQrcFile/qrcfile.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtcodetohtmlmaindialog.ui \
    qtcodetohtmlmenudialog.ui

RESOURCES += \
    ToolCodeToHtml.qrc

OTHER_FILES += \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
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
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra


unix {
  message(Unix)
  #Strict error handling
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  !static {
    message(Native Windows)
    #Allow native Windows to emit warnings without terminating
    QMAKE_CXXFLAGS += -Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++0x #-Werror

    #See http://www.richelbilderbeek.nl/CppCompileErrorParseErrorAtBOOST_JOIN.htm
    #Prevents error:
    #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
    DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

  }


}

#
#
# Boost
#
#

unix {
  message(Unix: Boost already in INCLUDEPATH)
  #Don't link to Boost when crosscompiling is desired
}

win32 {
  message(Windows: add Boost to INCLUDEPATH)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  #Don't link to Boost when crosscompiling is desired
}

#
#
# Warp's function parser
#
#
#unix {
#  INCLUDEPATH += \
#    ../../Libraries/fparser4.5.1
#
#  HEADERS += \
#    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
#    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
#    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
#    ../../Libraries/fparser4.5.1/fparser.hh \
#    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
#    ../../Libraries/fparser4.5.1/fpconfig.hh
#
#  SOURCES += \
#    ../../Libraries/fparser4.5.1/fparser.cc \
#    ../../Libraries/fparser4.5.1/fpoptimizer.cc
#
#  OTHER_FILES += \
#    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
#    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
#}

#
#
# Qwt
#
#

#unix {
#  INCLUDEPATH += /usr/include/qwt-qt4
#  LIBS += -lqwt-qt4
#}

#win32 {
#  message(Windows: Qwt: link dynamically)
#  INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
#  LIBS+= -L../../Libraries/qwt-6.1.0/lib
#
#  CONFIG(release, debug|release) {
#    message(Windows: Qwt: Linking to qwt)
#    LIBS += -lqwt
#  }
#
#  CONFIG(debug, debug|release) {
#    message(Windows: Qwt: Linking to qwtd)
#    LIBS += -lqwtd
#  }
#}

