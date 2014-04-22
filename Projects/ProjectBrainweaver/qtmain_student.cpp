#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <iostream>

#include <QApplication>
#include <QIcon>
#include <QVBoxLayout>
#include <QFileDialog>

#include "pvdbfile.h"
#include "pvdbhelper.h"
#include "qtpvdbclusterdialog.h"
#include "qtconceptmapcompetency.h"
#include "qtpvdbclusterwidget.h"
#include "qtpvdbconceptmapdialog.h"
//#include "qtpvdbconcepteditdialog.h"
//#include "qtpvdbconceptmapeditwidget.h"
//#include "qtpvdbrateexamplesdialog.h"
//#include "qtpvdbconceptmapratewidget.h"
#include "qtpvdbstudentmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

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

  //QtPvdbMenuDialog::Test();
  a.setStyleSheet(CreateStyleSheet().c_str());
  a.setWindowIcon(QIcon(":/images/R.png"));

  const std::string filter_str = std::string("*.") + ribi::pvdb::File::GetFilenameExtension();
  const std::string filename
    = QFileDialog::getOpenFileName(0,"Kies een assessment bestand",QString(),
      filter_str.c_str()).toStdString();
  if (!filename.empty())
  {
    try
    {
      const boost::shared_ptr<ribi::pvdb::File> file(ribi::pvdb::File::Load(filename));
      assert(file);
      ribi::pvdb::QtPvdbStudentMenuDialog d(file);
      d.show();
      return a.exec();
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }
  return 1;
}
