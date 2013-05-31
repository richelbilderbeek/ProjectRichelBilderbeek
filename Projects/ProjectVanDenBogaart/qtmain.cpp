#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <iostream>

#include <QtGui/QApplication>
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

const std::string CreateStyleSheet()
{
  const std::string s =
    "QDialog { "
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
  QtPvdbMenuDialog::Test(); //Tests all
  #else
  std::clog << "RELEASE mode" << std::endl;
  assert(1==2 && "Assume debugging is really disabled");
  #endif

  //Delete the test file
  std::remove(pvdb::File::GetTempFileName().c_str());

  //QtPvdbMenuDialog::Test();
  a.setStyleSheet(CreateStyleSheet().c_str());
  a.setWindowIcon(QIcon(":/images/R.png"));

  QtPvdbMenuDialog d;

  d.show();
  a.exec();
}

///TODO
///- Prettyprint printing for student result
///- Prettyprint printing for assessor result
///- Create multiple executables: (1) student (release) (2) assessor (release) (3) developer (debug)
///- In assessor final report screen, set the column widths to the right width (depends on font)
///
///TODO PERHAPS ONCE
///- Allow copy-paste of XML code to display the corresponding concept map
///- Add all hints when using the QtConceptMap
///- Allow movement of items by keyboard in cluster dialog
///
///DO NEVER FORGET
/// - Do not use std::all_of, because cross-compiler has trouble with it
/// - Do not change a QGraphicItem (that is: call a paint event) outside of the paint event
///   (this was the case by signals that caused a repaint)
/// - Instead of overloading operator== for all combinations of smart pointers,
///   block operator== and use IsEqual(const T&)
