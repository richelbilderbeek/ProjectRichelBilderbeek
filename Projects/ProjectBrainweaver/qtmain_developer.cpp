#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <iostream>

#include <boost/lexical_cast.hpp>

#include <QApplication>
#include <QIcon>
#include <QVBoxLayout>

#include "pvdbfile.h"
#include "pvdbhelper.h"
#include "qtpvdbclusterdialog.h"
#include "qtpvdbcompetency.h"
#include "qtpvdbclusterwidget.h"
#include "qtpvdbconceptmapdialog.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "qtpvdbrateexamplesdialog.h"
#include "qtpvdbconceptmapratewidget.h"
#include "qtpvdbmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

const std::string CreateStyleSheet()
{
  const std::string s =
    "QDialog { "
//    "  background-image: url(:/images/PicLoomBackground.png);" //Sorry Joost!
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bbf, stop: 1 #bff);"
    "} "
    "QLabel { "
    "  font-size: 18px;"
    "  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "  font-weight: bold;"
    "  padding: 1px;"
    "} "
    ""
    "QPushButton {"
    "  font-family: \"Courier New\", \"Courier\", Courier, monospace;"
    "  font-size: 16px;"
    "  border-width: 1px;"
    "  border-style: solid;"
    "  padding: 3px;"
    "} "
    ""
    "QPushButton:enabled {"
    "  color: black;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #111;"
    "} "
    "QPushButton:disabled {"
    "  color: #888;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #fff;"
    "} "
    ""
    "QPlainTextEdit {"
    "  font-size: 12px;  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "}";

  return s;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();
  //Perform tests
  #ifndef NDEBUG
  std::clog << "DEBUG mode" << std::endl;
  ribi::pvdb::TestHelperFunctions();
  ribi::pvdb::QtPvdbMenuDialog::Test(); //Tests all
  #else
  std::clog << "RELEASE mode" << std::endl;
  assert(1==2 && "Assume debugging is really disabled");
  #endif

  //Delete the test file
  std::remove(ribi::pvdb::File::GetTempFileName().c_str());

  //QtPvdbMenuDialog::Test();
  a.setStyleSheet(CreateStyleSheet().c_str());
  a.setWindowIcon(QIcon(":/images/R.png"));

  ribi::pvdb::QtPvdbMenuDialog d;
  if (argc != 1)
  {
    const std::vector<boost::function<void(ribi::pvdb::QtPvdbMenuDialog *)> > v
      =
      {
        &ribi::pvdb::QtPvdbMenuDialog::on_button_about_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_assessor_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_create_test_files_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_modify_stylesheet_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_overview_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_print_concept_map_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_print_rating_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_auto_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_map_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_rate_examples_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_rating_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_student_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_arrowitems_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_cluster_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptedit_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptitem_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptmap_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_create_sub_concept_map_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_edge_item_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_node_item_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtconceptmapdisplaywidget_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtconceptmapeditwidget_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtconceptmapratewidget_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundededitrectitem_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundedtextrectitem_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_view_files_clicked,
        &ribi::pvdb::QtPvdbMenuDialog::on_button_view_test_concept_maps_clicked
      };
    try
    {
      const int i = boost::lexical_cast<int>(argv[1]);
      v.at(i)(&d);
    }
    catch (boost::bad_lexical_cast&)
    {
      std::cerr << "Incorrect argument: please supply a number from 0 to " << v.size() << std::endl;
    }
    catch (std::out_of_range&)
    {
      std::cerr << "Incorrect argument: please supply a number from 0 to " << v.size() << std::endl;
    }
  }
  d.show();
  return a.exec();
}

///TODO
///2013-05-20:
///- ?DONE: Increase the area of a QtNodeIdem
///    1) FAILS: by adding 'QPainterPath QtPvdbConceptItem::shape() const'
///    2) MIGHT WORK: Bypass in QtPvdbNodeItem::boundingRect
///- ?1st of May, when concluded it's a good thing to implement:
///  - cluster dialog: allow more than 2 levels in clustering
///  - concept map dialog: allow examples from concepts to be dragged out and promoted to new conpepts
///- ?DONE: in assessor printing dialog: too long concepts/examples run off the page
///- BIG

///BEFORE 2013-03-25:
///- In assessor final report screen, set the column widths to the correct width (depends on font)
///
///DONE:
///- in assessor printing dialog: resize concept map to page size
///- FIXED BUG: if an arrow is drawn between two nodes, creating another arrow between these two same nodes
///    in the opposite direction, program crashes
///- when saving in the cluster dialog, only save (i.e. do not go back to main menu)
///- when saving in the create concept map dialog, only save (i.e. do not go back to main menu)
///- sub-concept maps are messed up: relations are put at origin
///- let students print like assessors: to PDF
///- get to cross-compile the Student and Assessor versions again
///- FIXED BUG: Test concept maps do not show

///TODO PERHAPS ONCE
///- add Undo functionality to cluster screen
///- add Undo functionality to concept map screen
///- Allow copy-paste of XML code to display the corresponding concept map
///- Allow movement of items by keyboard in cluster dialog
///- Allow multithreaded testing, gives the following error now:
///  [xcb] Unknown request in queue while dequeuing
///  [xcb] Most likely this is a multi-threaded client and XInitThreads has not been called
///  [xcb] Aborting, sorry about that.
///  BrainweaverDeveloper: ../../src/xcb_io.c:178: dequeue_pending_request: Assertion `!xcb_xlib_unknown_req_in_deq' failed.
///- Make Violet Blue meet doktor Light (from Mega Man), assure they marry, so that her name becomes Violet Light-Blue
///
///DO NEVER FORGET
/// - Do not use std::all_of, because cross-compiler has trouble with it
/// - Do not change a QGraphicItem (that is: call a paint event) outside of the paint event
///   (this was the case by signals that caused a repaint)
///   -> trick: check for QGraphicsRectItem::paintingActive()
/// - Use the default operator== for pointer comparison of smart pointers
/// - Instead of overloading operator== to compare the content for all combinations of smart pointers,
///   use IsEqual(const T&,const T&)
/// - If a class connects its signals to some other class with a different lifetime,
///   disconnect these signals in its destructor
