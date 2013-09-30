QT += core
QT -= gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    codetohtmlmenudialog.cpp \
    main.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    codetohtmlmenudialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQrcFile/qrcfile.h

OTHER_FILES += \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt


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
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

unix {
  LIBS += -lboost_program_options
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
