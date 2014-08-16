#ifndef QTDIALOG_H
#define QTDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QDialog>

struct QwtPlotCurve;

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private slots:
  void on_button_clicked();

private:
  Ui::QtDialog *ui;

  QwtPlotCurve * const m_curve_inputs;
  QwtPlotCurve * const m_curve_outputs;
};

#endif // QTDIALOG_H
