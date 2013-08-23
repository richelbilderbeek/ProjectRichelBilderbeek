#include <QApplication>
#include <QIcon>
#include "pvdbfile.h"
#include "qtpvdbconceptmapdialog.h"
#include "trace.h"

const std::string CreateStyleSheet()
{
  const std::string s =
    "QDialog { "
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #606060, stop: 1 #ffffff);"
    "}"
    ""
    "QLabel { font: 24px, \"Courier\" }"
    "#title { "
    "  font-size: 32px;"
    "  font-family: \"Courier\";"
    "  font-weight: bold"
    "}"
    ""
    "QPushButton { "
    "  color: black;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #888, stop: 0.1 #999, stop: 0.49 #ccc, stop: 0.5 #bbb, stop: 1 #ccc);"
    "  border-width: 3px;"
    "  border-color: #444;"
    "  border-style: solid;"
    "  border-radius: 7;"
    "  padding: 3px;"
    "  font-size: 24px;"
    "  font-family: \"Courier New\";"
    "  padding-left: 5px;"
    "  padding-right: 5px;"
    "}";

  return s;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  a.setStyleSheet(CreateStyleSheet().c_str());
  a.setWindowIcon(QIcon(":/images/R.png"));
  pvdb::File::Test();
  QtPvdbConceptMapDialog d;
  d.show();
  a.exec();
}

