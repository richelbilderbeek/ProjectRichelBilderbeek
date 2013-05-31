#ifndef QTKALMANFILTERERPARAMETERSDIALOG
#define QTKALMANFILTERERPARAMETERSDIALOG

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include <vector>

#include <QDialog>
//#include <QTableWidget>

//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include "kalmanfilterexample.h"

namespace Ui {
  class QtKalmanFilterExamplesDialog;
}

class QtKalmanFilterExamplesDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFilterExamplesDialog(QWidget *parent = 0);
  ~QtKalmanFilterExamplesDialog();

  ///Click one of the buttons
  void ClickButton(const int n);

signals:
  void signal_example(const boost::shared_ptr<KalmanFilterExample> example);

private:
  Ui::QtKalmanFilterExamplesDialog *ui;

private slots:
  void on_button_1_clicked();
  void on_button_2_clicked();
  void on_button_3_clicked();
  void on_button_4_clicked();
  void on_button_5_clicked();
  void on_button_6_clicked();
  void on_button_7_clicked();
  void on_button_8_clicked();
  void on_button_9_clicked();
  void on_button_10_clicked();
};

#endif // QTKALMANFILTERERPARAMETERSDIALOG
