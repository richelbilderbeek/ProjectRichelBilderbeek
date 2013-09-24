QT       += core gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppTrace \
    ../../Projects/RichelbilderbeekNl

SOURCES += \
    main.cpp\
    richelbilderbeekgallerymenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp

HEADERS  += \
    richelbilderbeekgallerymenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h

RESOURCES += \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

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
  LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_system
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
