#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

namespace Ui {
  class QtDialog;
}

struct QwtPlotCurve;
struct QwtPlot;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();

  QwtPlotCurve * const m_curve;
  QwtPlot * const m_plot;

private:
  Ui::QtDialog *ui;

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  ///GetBoostVersion returns the version of the current Boost library.
  ///From http://www.richelbilderbeek.nl/CppGetBoostVersion.htm
  static const std::string GetBoostVersion();

  ///GetGccVersion returns the version number of GCC currently installed.
  ///From http://www.richelbilderbeek.nl/CppGetGccVersion.htm
  static const std::string GetGccVersion();

  ///GetQtCreatorVersion obtains the version of Qt Creator
  ///Fails under Windows
  ///From http://www.richelbilderbeek.nl/CppGetQtCreatorVersion.htm
  static const std::string GetQtCreatorVersion();

  ///GetStlVersion returns the version number of the GCC STL currently installed.
  ///From http://www.richelbilderbeek.nl/CppGetStlVersion.htm
  static const std::string GetStlVersion();


};

#endif // QTDIALOG_H
