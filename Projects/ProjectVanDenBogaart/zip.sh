#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Projects
mkdir temp_zip/Tools

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppFuzzy_equal_to
mkdir temp_zip/Classes/CppLazy_init
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtArrowItem
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
mkdir temp_zip/Classes/CppQtLabeledQuadBezierArrowItem
mkdir temp_zip/Classes/CppQtPathArrowItem
mkdir temp_zip/Classes/CppQtQuadBezierArrowItem
mkdir temp_zip/Classes/CppQtRoundedEditRectItem
mkdir temp_zip/Classes/CppQtRoundedRectItem
mkdir temp_zip/Classes/CppQtRoundedTextRectItem
mkdir temp_zip/Classes/CppQtScopedDisable
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Projects/ProjectVanDenBogaart
mkdir temp_zip/Tools/ToolStyleSheetSetter
mkdir temp_zip/Tools/ToolTestQtArrowItems
mkdir temp_zip/Tools/ToolTestQtRoundedEditRectItem
mkdir temp_zip/Tools/ToolTestQtRoundedTextRectItem

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppFuzzy_equal_to/Licence.txt temp_zip/Classes/CppFuzzy_equal_to/Licence.txt
cp ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h temp_zip/Classes/CppFuzzy_equal_to/fuzzy_equal_to.h
cp ../../Classes/CppLazy_init/Licence.txt temp_zip/Classes/CppLazy_init/Licence.txt
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtArrowItem/Licence.txt temp_zip/Classes/CppQtArrowItem/Licence.txt
cp ../../Classes/CppQtArrowItem/qtarrowitem.cpp temp_zip/Classes/CppQtArrowItem/qtarrowitem.cpp
cp ../../Classes/CppQtArrowItem/qtarrowitem.h temp_zip/Classes/CppQtArrowItem/qtarrowitem.h
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h
cp ../../Classes/CppQtLabeledQuadBezierArrowItem/Licence.txt temp_zip/Classes/CppQtLabeledQuadBezierArrowItem/Licence.txt
cp ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.cpp temp_zip/Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.cpp
cp ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.h temp_zip/Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.h
cp ../../Classes/CppQtPathArrowItem/Licence.txt temp_zip/Classes/CppQtPathArrowItem/Licence.txt
cp ../../Classes/CppQtPathArrowItem/qtpatharrowitem.cpp temp_zip/Classes/CppQtPathArrowItem/qtpatharrowitem.cpp
cp ../../Classes/CppQtPathArrowItem/qtpatharrowitem.h temp_zip/Classes/CppQtPathArrowItem/qtpatharrowitem.h
cp ../../Classes/CppQtQuadBezierArrowItem/Licence.txt temp_zip/Classes/CppQtQuadBezierArrowItem/Licence.txt
cp ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp temp_zip/Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp
cp ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h temp_zip/Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h
cp ../../Classes/CppQtRoundedEditRectItem/Licence.txt temp_zip/Classes/CppQtRoundedEditRectItem/Licence.txt
cp ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp temp_zip/Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp
cp ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h temp_zip/Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h
cp ../../Classes/CppQtRoundedRectItem/Licence.txt temp_zip/Classes/CppQtRoundedRectItem/Licence.txt
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.h
cp ../../Classes/CppQtRoundedTextRectItem/Licence.txt temp_zip/Classes/CppQtRoundedTextRectItem/Licence.txt
cp ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp temp_zip/Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp
cp ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h temp_zip/Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h
cp ../../Classes/CppQtScopedDisable/Licence.txt temp_zip/Classes/CppQtScopedDisable/Licence.txt
cp ../../Classes/CppQtScopedDisable/qtscopeddisable.h temp_zip/Classes/CppQtScopedDisable/qtscopeddisable.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Projects/ProjectVanDenBogaart/1.cmp temp_zip/Projects/ProjectVanDenBogaart/1.cmp
cp ../../Projects/ProjectVanDenBogaart/2.cmp temp_zip/Projects/ProjectVanDenBogaart/2.cmp
cp ../../Projects/ProjectVanDenBogaart/3.cmp temp_zip/Projects/ProjectVanDenBogaart/3.cmp
cp ../../Projects/ProjectVanDenBogaart/4.cmp temp_zip/Projects/ProjectVanDenBogaart/4.cmp
cp ../../Projects/ProjectVanDenBogaart/5.cmp temp_zip/Projects/ProjectVanDenBogaart/5.cmp
cp ../../Projects/ProjectVanDenBogaart/Cluster.png temp_zip/Projects/ProjectVanDenBogaart/Cluster.png
cp ../../Projects/ProjectVanDenBogaart/ClusterSkip.png temp_zip/Projects/ProjectVanDenBogaart/ClusterSkip.png
cp ../../Projects/ProjectVanDenBogaart/ConceptMapEdit.png temp_zip/Projects/ProjectVanDenBogaart/ConceptMapEdit.png
cp ../../Projects/ProjectVanDenBogaart/PicArrow.png temp_zip/Projects/ProjectVanDenBogaart/PicArrow.png
cp ../../Projects/ProjectVanDenBogaart/PicArrow14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicArrow14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicArrow28x28.png temp_zip/Projects/ProjectVanDenBogaart/PicArrow28x28.png
cp ../../Projects/ProjectVanDenBogaart/PicBlue.png temp_zip/Projects/ProjectVanDenBogaart/PicBlue.png
cp ../../Projects/ProjectVanDenBogaart/PicBlue14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicBlue14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicCyan.png temp_zip/Projects/ProjectVanDenBogaart/PicCyan.png
cp ../../Projects/ProjectVanDenBogaart/PicCyan14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicCyan14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicGreen.png temp_zip/Projects/ProjectVanDenBogaart/PicGreen.png
cp ../../Projects/ProjectVanDenBogaart/PicGreen14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicGreen14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicOrange.png temp_zip/Projects/ProjectVanDenBogaart/PicOrange.png
cp ../../Projects/ProjectVanDenBogaart/PicOrange14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicOrange14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicPurple.png temp_zip/Projects/ProjectVanDenBogaart/PicPurple.png
cp ../../Projects/ProjectVanDenBogaart/PicPurple14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicPurple14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicRed.png temp_zip/Projects/ProjectVanDenBogaart/PicRed.png
cp ../../Projects/ProjectVanDenBogaart/PicRed14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicRed14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicWhite.png temp_zip/Projects/ProjectVanDenBogaart/PicWhite.png
cp ../../Projects/ProjectVanDenBogaart/PicWhite14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicWhite14x14.png
cp ../../Projects/ProjectVanDenBogaart/PicYellow.png temp_zip/Projects/ProjectVanDenBogaart/PicYellow.png
cp ../../Projects/ProjectVanDenBogaart/PicYellow14x14.png temp_zip/Projects/ProjectVanDenBogaart/PicYellow14x14.png
cp ../../Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.css temp_zip/Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.css
cp ../../Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.pro temp_zip/Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.pro
cp ../../Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.qrc temp_zip/Projects/ProjectVanDenBogaart/ProjectVanDenBogaart.qrc
cp ../../Projects/ProjectVanDenBogaart/ProjectVanDenBogaartArchitecture.lyx~ temp_zip/Projects/ProjectVanDenBogaart/ProjectVanDenBogaartArchitecture.lyx~
cp ../../Projects/ProjectVanDenBogaart/ProjectVanDenBogaartSloccount.txt temp_zip/Projects/ProjectVanDenBogaart/ProjectVanDenBogaartSloccount.txt
cp ../../Projects/ProjectVanDenBogaart/R.png temp_zip/Projects/ProjectVanDenBogaart/R.png
cp ../../Projects/ProjectVanDenBogaart/crosscompiletowindows.sh temp_zip/Projects/ProjectVanDenBogaart/crosscompiletowindows.sh
cp ../../Projects/ProjectVanDenBogaart/doxygen_config.txt temp_zip/Projects/ProjectVanDenBogaart/doxygen_config.txt
cp ../../Projects/ProjectVanDenBogaart/pvdbcluster.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbcluster.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbcluster.h temp_zip/Projects/ProjectVanDenBogaart/pvdbcluster.h
cp ../../Projects/ProjectVanDenBogaart/pvdbclusterfactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbclusterfactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbclusterfactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbclusterfactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbcompetency.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbcompetency.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbcompetency.h temp_zip/Projects/ProjectVanDenBogaart/pvdbcompetency.h
cp ../../Projects/ProjectVanDenBogaart/pvdbconcept.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbconcept.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbconcept.h temp_zip/Projects/ProjectVanDenBogaart/pvdbconcept.h
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptfactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptfactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptfactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptfactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptmap.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptmap.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptmap.h temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptmap.h
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptmapfactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptmapfactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbconceptmapfactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbconceptmapfactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbedge.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbedge.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbedge.h temp_zip/Projects/ProjectVanDenBogaart/pvdbedge.h
cp ../../Projects/ProjectVanDenBogaart/pvdbedgefactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbedgefactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbedgefactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbedgefactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbexample.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbexample.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbexample.h temp_zip/Projects/ProjectVanDenBogaart/pvdbexample.h
cp ../../Projects/ProjectVanDenBogaart/pvdbexamplefactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbexamplefactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbexamplefactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbexamplefactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbexamples.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbexamples.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbexamples.h temp_zip/Projects/ProjectVanDenBogaart/pvdbexamples.h
cp ../../Projects/ProjectVanDenBogaart/pvdbexamplesfactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbexamplesfactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbexamplesfactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbexamplesfactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbfile.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbfile.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbfile.h temp_zip/Projects/ProjectVanDenBogaart/pvdbfile.h
cp ../../Projects/ProjectVanDenBogaart/pvdbfilefactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbfilefactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbfilefactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbfilefactory.h
cp ../../Projects/ProjectVanDenBogaart/pvdbfwd.h temp_zip/Projects/ProjectVanDenBogaart/pvdbfwd.h
cp ../../Projects/ProjectVanDenBogaart/pvdbhelper.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbhelper.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbhelper.h temp_zip/Projects/ProjectVanDenBogaart/pvdbhelper.h
cp ../../Projects/ProjectVanDenBogaart/pvdbhints.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbhints.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbhints.h temp_zip/Projects/ProjectVanDenBogaart/pvdbhints.h
cp ../../Projects/ProjectVanDenBogaart/pvdbmenudialog.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbmenudialog.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbmenudialog.h temp_zip/Projects/ProjectVanDenBogaart/pvdbmenudialog.h
cp ../../Projects/ProjectVanDenBogaart/pvdbnode.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbnode.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbnode.h temp_zip/Projects/ProjectVanDenBogaart/pvdbnode.h
cp ../../Projects/ProjectVanDenBogaart/pvdbnodefactory.cpp temp_zip/Projects/ProjectVanDenBogaart/pvdbnodefactory.cpp
cp ../../Projects/ProjectVanDenBogaart/pvdbnodefactory.h temp_zip/Projects/ProjectVanDenBogaart/pvdbnodefactory.h
cp ../../Projects/ProjectVanDenBogaart/qtmain.cpp temp_zip/Projects/ProjectVanDenBogaart/qtmain.cpp
cp ../../Projects/ProjectVanDenBogaart/qtmain_testconceptmap.cpp temp_zip/Projects/ProjectVanDenBogaart/qtmain_testconceptmap.cpp
cp ../../Projects/ProjectVanDenBogaart/qtmainassessor.cpp temp_zip/Projects/ProjectVanDenBogaart/qtmainassessor.cpp
cp ../../Projects/ProjectVanDenBogaart/qtmainstudent.cpp temp_zip/Projects/ProjectVanDenBogaart/qtmainstudent.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbaboutdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbaboutdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbaboutdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbaboutdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbassessormenudialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbbrushfactory.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbbrushfactory.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbbrushfactory.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbbrushfactory.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcenternodeitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcenternodeitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcenternodeitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcenternodeitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbclusterdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbclusterwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbclusterwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbclusterwidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbclusterwidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcompetency.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcompetency.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcompetency.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcompetency.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconcepteditdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdesignerwidget.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdesignerwidget.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdisplaywidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdisplaywidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapdisplaywidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapdisplaywidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapeditwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapeditwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapeditwidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapeditwidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapratewidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapratewidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapratewidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapratewidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbconceptmapwidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbconceptmapwidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentcompletedialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentmenudialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbcreateassessmentpartialdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbdisplayconceptitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbdisplayconceptitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbdisplayconceptitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbdisplayconceptitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbedgeitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbedgeitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbedgeitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbedgeitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbeditconceptitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbeditconceptitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbeditconceptitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbeditconceptitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbexamplesitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbexamplesitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbexamplesitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbexamplesitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbitemhighlighter.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbitemhighlighter.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbitemhighlighter.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbitemhighlighter.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbmenudialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbmenudialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbmenudialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbmenudialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbmenudialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbmenudialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbnewarrow.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbnewarrow.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbnewarrow.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbnewarrow.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbnodeitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbnodeitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbnodeitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbnodeitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdboverviewdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdboverviewdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdboverviewdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdboverviewdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdboverviewwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdboverviewwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdboverviewwidget.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdboverviewwidget.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintconceptmapdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbprintratingdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateconceptmapdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbrateexamplesdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbratingdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbratingdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbratingdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbratingdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbratingdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbratingdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentmenudialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbstudentstartcompletedialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptitemdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapeditwidgetdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestconceptmapratewidgetdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestedgeitemdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtestnodeitemdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtoolsitem.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtoolsitem.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbtoolsitem.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbtoolsitem.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewfilesdialog.ui
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.h temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.h
cp ../../Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.ui temp_zip/Projects/ProjectVanDenBogaart/qtpvdbviewtestsdialog.ui
cp ../../Projects/ProjectVanDenBogaart/sloccount.sh temp_zip/Projects/ProjectVanDenBogaart/sloccount.sh
cp ../../Projects/ProjectVanDenBogaart/test_pvdbcluster.cpp temp_zip/Projects/ProjectVanDenBogaart/test_pvdbcluster.cpp
cp ../../Projects/ProjectVanDenBogaart/test_pvdbconcept.cpp temp_zip/Projects/ProjectVanDenBogaart/test_pvdbconcept.cpp
cp ../../Projects/ProjectVanDenBogaart/test_pvdbconceptmap.cpp temp_zip/Projects/ProjectVanDenBogaart/test_pvdbconceptmap.cpp
cp ../../Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapdialog.cpp temp_zip/Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapdialog.cpp
cp ../../Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapeditwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapeditwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapratewidget.cpp temp_zip/Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapratewidget.cpp
cp ../../Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapwidget.cpp temp_zip/Projects/ProjectVanDenBogaart/test_qtpvdbconceptmapwidget.cpp
cp ../../Projects/ProjectVanDenBogaart/zip.sh temp_zip/Projects/ProjectVanDenBogaart/zip.sh
cp ../../Tools/ToolStyleSheetSetter/R.png temp_zip/Tools/ToolStyleSheetSetter/R.png
cp ../../Tools/ToolStyleSheetSetter/ToolStyleSheetSetter.qrc temp_zip/Tools/ToolStyleSheetSetter/ToolStyleSheetSetter.qrc
cp ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.cpp temp_zip/Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.cpp
cp ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.h temp_zip/Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.h
cp ../../Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.ui temp_zip/Tools/ToolStyleSheetSetter/toolstylesheetsettermaindialog.ui
cp ../../Tools/ToolTestQtArrowItems/Licence.txt temp_zip/Tools/ToolTestQtArrowItems/Licence.txt
cp ../../Tools/ToolTestQtArrowItems/R.png temp_zip/Tools/ToolTestQtArrowItems/R.png
cp ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.png temp_zip/Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.png
cp ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.qrc temp_zip/Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.qrc
cp ../../Tools/ToolTestQtArrowItems/crosscompiletowindows.sh temp_zip/Tools/ToolTestQtArrowItems/crosscompiletowindows.sh
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.cpp temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.cpp
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.h temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.h
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.ui temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.ui
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.cpp temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.cpp
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.h temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.h
cp ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.ui temp_zip/Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.ui
cp ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.cpp temp_zip/Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.cpp
cp ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h temp_zip/Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h
cp ../../Tools/ToolTestQtRoundedEditRectItem/Licence.txt temp_zip/Tools/ToolTestQtRoundedEditRectItem/Licence.txt
cp ../../Tools/ToolTestQtRoundedEditRectItem/R.png temp_zip/Tools/ToolTestQtRoundedEditRectItem/R.png
cp ../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItem.qrc temp_zip/Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItem.qrc
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.cpp temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.cpp
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.h temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.h
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.ui temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.ui
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.cpp temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.h temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.ui temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.ui
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.cpp temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.cpp
cp ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.h temp_zip/Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.h
cp ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.cpp temp_zip/Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.h temp_zip/Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/Licence.txt temp_zip/Tools/ToolTestQtRoundedTextRectItem/Licence.txt
cp ../../Tools/ToolTestQtRoundedTextRectItem/R.png temp_zip/Tools/ToolTestQtRoundedTextRectItem/R.png
cp ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.png temp_zip/Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.png
cp ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.qrc temp_zip/Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.qrc
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.ui temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.ui
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.ui temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.ui
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h

FILENAME="ProjectVanDenBogaartSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppFuzzy_equal_to/*.*
rm temp_zip/Classes/CppLazy_init/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtArrowItem/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/*.*
rm temp_zip/Classes/CppQtLabeledQuadBezierArrowItem/*.*
rm temp_zip/Classes/CppQtPathArrowItem/*.*
rm temp_zip/Classes/CppQtQuadBezierArrowItem/*.*
rm temp_zip/Classes/CppQtRoundedEditRectItem/*.*
rm temp_zip/Classes/CppQtRoundedRectItem/*.*
rm temp_zip/Classes/CppQtRoundedTextRectItem/*.*
rm temp_zip/Classes/CppQtScopedDisable/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Projects/ProjectVanDenBogaart/*.*
rm temp_zip/Tools/ToolStyleSheetSetter/*.*
rm temp_zip/Tools/ToolTestQtArrowItems/*.*
rm temp_zip/Tools/ToolTestQtRoundedEditRectItem/*.*
rm temp_zip/Tools/ToolTestQtRoundedTextRectItem/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppFuzzy_equal_to
rmdir temp_zip/Classes/CppLazy_init
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtArrowItem
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
rmdir temp_zip/Classes/CppQtLabeledQuadBezierArrowItem
rmdir temp_zip/Classes/CppQtPathArrowItem
rmdir temp_zip/Classes/CppQtQuadBezierArrowItem
rmdir temp_zip/Classes/CppQtRoundedEditRectItem
rmdir temp_zip/Classes/CppQtRoundedRectItem
rmdir temp_zip/Classes/CppQtRoundedTextRectItem
rmdir temp_zip/Classes/CppQtScopedDisable
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Projects/ProjectVanDenBogaart
rmdir temp_zip/Tools/ToolStyleSheetSetter
rmdir temp_zip/Tools/ToolTestQtArrowItems
rmdir temp_zip/Tools/ToolTestQtRoundedEditRectItem
rmdir temp_zip/Tools/ToolTestQtRoundedTextRectItem

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Projects
rmdir temp_zip/Tools

echo "Removing temporary folder"

rm temp_zip/*.*
rmdir temp_zip

echo "Done"

# CreateQtProjectZipFile, version 1.3
# Copyright (C) 2012 Richel Bilderbeek
# Programmed on the 10th of June 2012
# by Richel Bilderbeek
# 
# CreateQtProjectZipFile can be downloaded from http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
# Licenced under GPL 3.0
