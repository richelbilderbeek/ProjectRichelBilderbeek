#ifndef QTSTATEOBSERVERMAINDIALOG_H
#define QTSTATEOBSERVERMAINDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include "qthideandshowdialog.h"

struct QwtPlotCurve;

namespace Ui {
  class QtStateObserverMainDialog;
}

class QtStateObserverMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtStateObserverMainDialog(QWidget *parent = 0);
  ~QtStateObserverMainDialog();
  
private slots:
  void Run();

  void on_button_rerun_clicked();

private:
  Ui::QtStateObserverMainDialog *ui;

  QwtPlotCurve * const m_curve_inputs;
  QwtPlotCurve * const m_curve_outputs_alpha;
  QwtPlotCurve * const m_curve_outputs_alpha_beta;
  QwtPlotCurve * const m_curve_outputs_alpha_beta_gamma;
  QwtPlotCurve * const m_curve_outputs_lsq;
  QwtPlotCurve * const m_curve_outputs_ma;
};

#endif // QTSTATEOBSERVERMAINDIALOG_H
