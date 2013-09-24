QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppTrace \
    ../../Projects/RichelbilderbeekNl

SOURCES += \
    qtmain.cpp\
    qtrichelbilderbeekgallerymenudialog.cpp \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.cpp \
    richelbilderbeekgallerymenudialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
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
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp

HEADERS  += qtrichelbilderbeekgallerymenudialog.h \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.h \
    richelbilderbeekgallerymenudialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
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
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h

FORMS    += qtrichelbilderbeekgallerymenudialog.ui \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc

OTHER_FILES += \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppRichelBilderbeekProgram/Licence.txt

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
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
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
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
