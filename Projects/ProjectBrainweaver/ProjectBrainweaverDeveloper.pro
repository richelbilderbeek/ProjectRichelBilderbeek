QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TEMPLATE = app


DEFINES += PVDB_USE_FORWARD_DECLARATIONS_248738
#DEFINES += PVDB_KEEP_NAMESPACE_IN_CPP_FILES
QMAKE_CXXFLAGS += -std=c++11 -Wextra #-Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
  #The crosscompiler does not support threads yet, as of 2013-05-02
  #DEFINES += COMPILER_SUPPORTS_THREADS_20130507
}

INCLUDEPATH += \
  ../../Classes/CppAbout \
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
  ../../Tools/ToolStyleSheetSetter \
  ../../Tools/ToolTestQtArrowItems \
  ../../Tools/ToolTestQtRoundedEditRectItem \
  ../../Tools/ToolTestQtRoundedTextRectItem

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
    qtmain_developer.cpp \
    qtpvdbaboutdialog.cpp \
    qtpvdbassessormenudialog.cpp \
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
    qtpvdbconceptmapratewidget.cpp \
    qtpvdbconceptmapwidget.cpp \
    qtpvdbcreateassessmentcompletedialog.cpp \
    qtpvdbcreateassessmentmenudialog.cpp \
    qtpvdbcreateassessmentpartialdialog.cpp \
    qtpvdbdisplayconceptitem.cpp \
    qtpvdbdisplay.cpp \
    qtpvdbedgeitem.cpp \
    qtpvdbeditconceptitem.cpp \
    qtpvdbexamplesitem.cpp \
    qtpvdbitemhighlighter.cpp \
    qtpvdbmenudialog.cpp \
    qtpvdbnewarrow.cpp \
    qtpvdbnodeitem.cpp \
    qtpvdboverviewdialog.cpp \
    qtpvdboverviewwidget.cpp \
    qtpvdbprintconceptmapdialog.cpp \
    qtpvdbprintratingdialog.cpp \
    qtpvdbrateconceptdialog.cpp \
    qtpvdbrateconceptitem.cpp \
    qtpvdbrateconceptmapdialog.cpp \
    qtpvdbratedconceptwidget.cpp \
    qtpvdbrateexamplesdialog.cpp \
    qtpvdbratingdialog.cpp \
    qtpvdbstudentmenudialog.cpp \
    qtpvdbstudentstartcompletedialog.cpp \
    qtpvdbtestconceptitemdialog.cpp \
    qtpvdbtestconceptmapdisplaywidgetdialog.cpp \
    qtpvdbtestconceptmapeditwidgetdialog.cpp \
    qtpvdbtestconceptmapratewidgetdialog.cpp \
    qtpvdbtestedgeitemdialog.cpp \
    qtpvdbtestnodeitemdialog.cpp \
    qtpvdbtoolsitem.cpp \
    qtpvdbviewfilesdialog.cpp \
    qtpvdbviewtestsdialog.cpp \
    test_pvdbcluster.cpp \
    test_pvdbconcept.cpp \
    test_pvdbconceptmap.cpp \
    test_qtpvdbconceptmapdialog.cpp \
    test_qtpvdbconceptmapeditwidget.cpp \
    test_qtpvdbconceptmapratewidget.cpp \
    test_qtpvdbconceptmapwidget.cpp \
    pvdbrating.cpp \
    qtpvdbtestcreatesubconceptmapdialog.cpp \
    ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.cpp \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.cpp \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.cpp \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp \
    qtpvdbrateconcepttallydialog.cpp \
    qtpvdbrateconcepttallymodel.cpp \
    pvdbcenternode.cpp \
    pvdbcenternodefactory.cpp \
    qtpvdbfiledialog.cpp

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
    qtpvdbassessormenudialog.h \
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
    qtpvdbcreateassessmentcompletedialog.h \
    qtpvdbcreateassessmentmenudialog.h \
    qtpvdbcreateassessmentpartialdialog.h \
    qtpvdbdisplayconceptitem.h \
    qtpvdbdisplay.h \
    qtpvdbedgeitem.h \
    qtpvdbeditconceptitem.h \
    qtpvdbexamplesitem.h \
    qtpvdbitemhighlighter.h \
    qtpvdbmenudialog.h \
    qtpvdbnewarrow.h \
    qtpvdbnodeitem.h \
    qtpvdboverviewdialog.h \
    qtpvdboverviewwidget.h \
    qtpvdbprintconceptmapdialog.h \
    qtpvdbprintratingdialog.h \
    qtpvdbrateconceptdialog.h \
    qtpvdbrateconceptitem.h \
    qtpvdbrateconceptmapdialog.h \
    qtpvdbratedconceptwidget.h \
    qtpvdbrateexamplesdialog.h \
    qtpvdbratingdialog.h \
    qtpvdbstudentmenudialog.h \
    qtpvdbstudentstartcompletedialog.h \
    qtpvdbtestconceptitemdialog.h \
    qtpvdbtestconceptmapdisplaywidgetdialog.h \
    qtpvdbtestconceptmapeditwidgetdialog.h \
    qtpvdbtestconceptmapratewidgetdialog.h \
    qtpvdbtestedgeitemdialog.h \
    qtpvdbtestnodeitemdialog.h \
    qtpvdbtoolsitem.h \
    qtpvdbviewfilesdialog.h \
    qtpvdbviewtestsdialog.h \
    pvdbrating.h \
    qtpvdbtestcreatesubconceptmapdialog.h \
    ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.h \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.h \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h \
    qtpvdbrateconcepttallydialog.h \
    qtpvdbrateconcepttallymodel.h \
    pvdbcenternode.h \
    pvdbcenternodefactory.h \
    qtpvdbfiledialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtpvdbassessormenudialog.ui \
    qtpvdbclusterdialog.ui \
    qtpvdbconcepteditdialog.ui \
    qtpvdbconceptmapdialog.ui \
    qtpvdbcreateassessmentcompletedialog.ui \
    qtpvdbcreateassessmentmenudialog.ui \
    qtpvdbcreateassessmentpartialdialog.ui \
    qtpvdbmenudialog.ui \
    qtpvdbprintconceptmapdialog.ui \
    qtpvdbprintratingdialog.ui \
    qtpvdbrateconceptdialog.ui \
    qtpvdbrateconceptmapdialog.ui \
    qtpvdbratedconceptwidget.ui \
    qtpvdbrateexamplesdialog.ui \
    qtpvdbratingdialog.ui \
    qtpvdbstudentmenudialog.ui \
    qtpvdbstudentstartcompletedialog.ui \
    qtpvdbtestconceptitemdialog.ui \
    qtpvdbtestconceptmapdisplaywidgetdialog.ui \
    qtpvdbtestconceptmapeditwidgetdialog.ui \
    qtpvdbtestconceptmapratewidgetdialog.ui \
    qtpvdbtestedgeitemdialog.ui \
    qtpvdbtestnodeitemdialog.ui \
    qtpvdbviewfilesdialog.ui \
    qtpvdbviewtestsdialog.ui \
    qtpvdbtestcreatesubconceptmapdialog.ui \
    ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.ui \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.ui \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.ui \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.ui \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.ui \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.ui \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.ui \
    qtpvdbrateconcepttallydialog.ui

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
    ../../Tools/ToolTestQtArrowItems/crosscompiletowindows.sh \
    ../../Tools/ToolTestQtArrowItems/Licence.txt \
    ../../Tools/ToolTestQtArrowItems/R.png \
    ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.png \
    ../../Tools/ToolTestQtRoundedEditRectItem/Licence.txt \
    ../../Tools/ToolTestQtRoundedTextRectItem/Licence.txt \
    zipexes.sh \
    BrainweaverTest.py

RESOURCES += \
    Brainweaver.qrc \
    ../../Tools/ToolStyleSheetSetter/ToolStyleSheetSetter.qrc \
    ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.qrc \
    ../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItem.qrc \
    ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.qrc

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
# Boost
#
#

# Do not link to the Boost libraries, as I cannot figure out how the crosscompiler detects these
