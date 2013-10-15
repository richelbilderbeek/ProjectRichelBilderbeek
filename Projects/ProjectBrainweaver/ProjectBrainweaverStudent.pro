QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppFileIo \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtArrowItem \
  ../../Classes/CppQtHideAndShowDialog \
  ../../Classes/CppQtKeyboardFriendlyGraphicsView \
  ../../Classes/CppQtLabeledQuadBezierArrowItem \
  ../../Classes/CppQtPathArrowItem \
  ../../Classes/CppQtQuadBezierArrowItem \
  ../../Classes/CppQtRoundedEditRectItem \
  ../../Classes/CppQtRoundedRectItem \
  ../../Classes/CppQtRoundedTextRectItem \
  ../../Classes/CppQtScopedDisable \
  ../../Classes/CppTrace \
  ../../Classes/CppXml \

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtArrowItem/qtarrowitem.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.cpp \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.cpp \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp \
    pvdbcluster.cpp \
    pvdbclusterfactory.cpp \
    pvdbcompetency.cpp \
    pvdbconcept.cpp \
    pvdbconceptfactory.cpp \
    pvdbconceptmap.cpp \
    pvdbconceptmapfactory.cpp \
    pvdbedge.cpp \
    pvdbedgefactory.cpp \
    pvdbexample.cpp \
    pvdbexamplefactory.cpp \
    pvdbexamples.cpp \
    pvdbexamplesfactory.cpp \
    pvdbfile.cpp \
    pvdbfilefactory.cpp \
    pvdbhelper.cpp \
    pvdbmenudialog.cpp \
    pvdbnode.cpp \
    pvdbnodefactory.cpp \
    qtmain_student.cpp \
    qtpvdbaboutdialog.cpp \
    qtpvdbbrushfactory.cpp \
    qtpvdbcenternodeitem.cpp \
    qtpvdbclusterdialog.cpp \
    qtpvdbclusterwidget.cpp \
    qtpvdbcompetency.cpp \
    qtpvdbconcepteditdialog.cpp \
    qtpvdbconceptitem.cpp \
    qtpvdbconceptmapdialog.cpp \
    qtpvdbconceptmapdisplaywidget.cpp \
    qtpvdbconceptmapeditwidget.cpp \
    qtpvdbconceptmapitem.cpp \
    qtpvdbconceptmapwidget.cpp \
    qtpvdbdisplayconceptitem.cpp \
    qtpvdbedgeitem.cpp \
    qtpvdbeditconceptitem.cpp \
    qtpvdbexamplesitem.cpp \
    qtpvdbitemhighlighter.cpp \
    qtpvdbnewarrow.cpp \
    qtpvdbnodeitem.cpp \
    qtpvdbprintconceptmapdialog.cpp \
    qtpvdbrateconceptitem.cpp \
    qtpvdbstudentmenudialog.cpp \
    qtpvdbstudentstartcompletedialog.cpp \
    qtpvdbtoolsitem.cpp \
    qtpvdbratedconceptwidget.cpp \
    pvdbcenternodefactory.cpp \
    pvdbcenternode.cpp \
    qtpvdbfiledialog.cpp \
    test_qtpvdbconceptmapwidget.cpp \
    test_qtpvdbconceptmapeditwidget.cpp \
    test_qtpvdbconceptmapdialog.cpp \
    test_pvdbconceptmap.cpp \
    test_pvdbconcept.cpp \
    test_pvdbcluster.cpp \
    ../../Classes/CppFileIo/fileio.cpp \
    ../../Classes/CppXml/xml.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtArrowItem/qtarrowitem.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.h \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.h \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h \
    ../../Classes/CppQtScopedDisable/qtscopeddisable.h \
    ../../Classes/CppTrace/trace.h \
    pvdbclusterfactory.h \
    pvdbcluster.h \
    pvdbcompetency.h \
    pvdbconceptfactory.h \
    pvdbconcept.h \
    pvdbconceptmapfactory.h \
    pvdbconceptmap.h \
    pvdbedgefactory.h \
    pvdbedge.h \
    pvdbexamplefactory.h \
    pvdbexample.h \
    pvdbexamplesfactory.h \
    pvdbexamples.h \
    pvdbfilefactory.h \
    pvdbfile.h \
    pvdbfwd.h \
    pvdbhelper.h \
    pvdbmenudialog.h \
    pvdbnodefactory.h \
    pvdbnode.h \
    qtpvdbaboutdialog.h \
    qtpvdbbrushfactory.h \
    qtpvdbcenternodeitem.h \
    qtpvdbclusterdialog.h \
    qtpvdbclusterwidget.h \
    qtpvdbcompetency.h \
    qtpvdbconcepteditdialog.h \
    qtpvdbconceptitem.h \
    qtpvdbconceptmapdialog.h \
    qtpvdbconceptmapdisplaywidget.h \
    qtpvdbconceptmapeditwidget.h \
    qtpvdbconceptmapitem.h \
    qtpvdbconceptmapratewidget.h \
    qtpvdbconceptmapwidget.h \
    qtpvdbdisplayconceptitem.h \
    qtpvdbedgeitem.h \
    qtpvdbeditconceptitem.h \
    qtpvdbexamplesitem.h \
    qtpvdbitemhighlighter.h \
    qtpvdbnewarrow.h \
    qtpvdbnodeitem.h \
    qtpvdbprintconceptmapdialog.h \
    qtpvdbrateconceptitem.h \
    qtpvdbstudentmenudialog.h \
    qtpvdbstudentstartcompletedialog.h \
    qtpvdbtoolsitem.h \
    qtpvdbratedconceptwidget.h \
    pvdbcenternodefactory.h \
    pvdbcenternode.h \
    qtpvdbfiledialog.h \
    ../../Classes/CppFileIo/fileio.h \
    ../../Classes/CppXml/xml.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtpvdbclusterdialog.ui \
    qtpvdbconcepteditdialog.ui \
    qtpvdbconceptmapdialog.ui \
    qtpvdbprintconceptmapdialog.ui \
    qtpvdbstudentmenudialog.ui \
    qtpvdbstudentstartcompletedialog.ui \
    qtpvdbratedconceptwidget.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppFuzzy_equal_to/Licence.txt \
    ../../Classes/CppLazy_init/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtArrowItem/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtPathArrowItem/Licence.txt \
    ../../Classes/CppQtQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtRoundedEditRectItem/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt \
    ../../Classes/CppQtScopedDisable/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh \
    doxygen_config.txt \
    ../../Classes/CppFileIo/Licence.txt \
    ../../Classes/CppXml/Licence.txt

RESOURCES += \
    Brainweaver.qrc

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

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
