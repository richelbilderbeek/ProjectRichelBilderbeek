#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <qglobal.h>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  #include <QtWidgets/QApplication>
#else
  #include <QtGui/QApplication>
#endif


#include "qtkalmanfilterermenudialog.h"
#include "trace.h"

const std::string CreateStyleSheet()
{

  const std::string style_sheet
    =
    "QtKalmanFiltererMainDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #bbb, stop: 1 #fff);"
    "}"
    "QtKalmanFilterExperimentDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #fbb, stop: 1 #fff);"
    "}"
    "QtKalmanFilterDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #bfb, stop: 1 #fff);"
    "}"
    "QtWhiteNoiseSystemParametersDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #bbf, stop: 1 #fff);"
    "}"
    "QtKalmanFilterExamplesDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #bbb, stop: 1 #fff);"
    "}"
    ;
  return style_sheet;
}


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  a.setStyleSheet(CreateStyleSheet().c_str());
  QtKalmanFiltererMenuDialog w;
  w.show();
  return a.exec();
}
