QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TEMPLATE = app

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
  ../../Classes/CppTrace

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
    qtmain_assessor.cpp \
    qtpvdbaboutdialog.cpp \
    qtpvdbassessormenudialog.cpp \
    qtpvdbbrushfactory.cpp \
    qtpvdbcenternodeitem.cpp \
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
    qtpvdbedgeitem.cpp \
    qtpvdbeditconceptitem.cpp \
    qtpvdbexamplesitem.cpp \
    qtpvdbitemhighlighter.cpp \
    qtpvdbnewarrow.cpp \
    qtpvdbnodeitem.cpp \
    qtpvdbprintratingdialog.cpp \
    qtpvdbrateconceptdialog.cpp \
    qtpvdbrateconceptitem.cpp \
    qtpvdbrateconceptmapdialog.cpp \
    qtpvdbrateexamplesdialog.cpp \
    qtpvdbratingdialog.cpp \
    qtpvdbtoolsitem.cpp \
    qtpvdbratedconceptwidget.cpp \
    qtpvdbdisplay.cpp \
    pvdbrating.cpp \
    qtpvdbrateconcepttallydialog.cpp \
    pvdbcenternodefactory.cpp \
    pvdbcenternode.cpp \
    qtpvdbfiledialog.cpp \
    test_qtpvdbconceptmapwidget.cpp \
    test_qtpvdbconceptmapratewidget.cpp \
    test_qtpvdbconceptmapeditwidget.cpp \
    test_qtpvdbconceptmapdialog.cpp \
    test_pvdbconceptmap.cpp \
    test_pvdbconcept.cpp \
    test_pvdbcluster.cpp \
    qtpvdbprintconceptmapdialog.cpp

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
    qtpvdbclusterwidget.h \
    qtpvdbcompetency.h \
    qtpvdbconcepteditdialog.h \
    qtpvdbconceptitem.h \
    qtpvdbconceptmapdisplaywidget.h \
    qtpvdbconceptmapeditwidget.h \
    qtpvdbconceptmapitem.h \
    qtpvdbconceptmapratewidget.h \
    qtpvdbconceptmapwidget.h \
    qtpvdbcreateassessmentcompletedialog.h \
    qtpvdbcreateassessmentmenudialog.h \
    qtpvdbcreateassessmentpartialdialog.h \
    qtpvdbdisplayconceptitem.h \
    qtpvdbedgeitem.h \
    qtpvdbeditconceptitem.h \
    qtpvdbexamplesitem.h \
    qtpvdbitemhighlighter.h \
    qtpvdbnewarrow.h \
    qtpvdbnodeitem.h \
    qtpvdbprintratingdialog.h \
    qtpvdbrateconceptdialog.h \
    qtpvdbconceptmapdialog.h \
    qtpvdbrateconceptitem.h \
    qtpvdbrateconceptmapdialog.h \
    qtpvdbrateexamplesdialog.h \
    qtpvdbratingdialog.h \
    qtpvdbtoolsitem.h \
    qtpvdbratedconceptwidget.h \
    qtpvdbdisplay.h \
    pvdbrating.h \
    qtpvdbrateconcepttallydialog.h \
    pvdbcenternodefactory.h \
    pvdbcenternode.h \
    qtpvdbfiledialog.h \
    qtpvdbprintconceptmapdialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtpvdbassessormenudialog.ui \
    qtpvdbconceptmapdialog.ui \
    qtpvdbconcepteditdialog.ui \
    qtpvdbcreateassessmentcompletedialog.ui \
    qtpvdbcreateassessmentmenudialog.ui \
    qtpvdbcreateassessmentpartialdialog.ui \
    qtpvdbprintratingdialog.ui \
    qtpvdbrateconceptdialog.ui \
    qtpvdbrateconceptmapdialog.ui \
    qtpvdbrateexamplesdialog.ui \
    qtpvdbratingdialog.ui \
    qtpvdbratedconceptwidget.ui \
    qtpvdbrateconcepttallydialog.ui \
    qtpvdbprintconceptmapdialog.ui

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
    doxygen_config.txt

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
