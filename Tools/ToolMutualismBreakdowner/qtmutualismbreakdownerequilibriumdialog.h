#ifndef QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H
#define QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H
/*
#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;
struct QtMutualismBreakdownerParametersWidget;

namespace Ui {
  class QtMutualismBreakdownerEquilibriumDialog;
}

class QtMutualismBreakdownerEquilibriumDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtMutualismBreakdownerEquilibriumDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerEquilibriumDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:

  void on_button_run_clicked();

private:
  Ui::QtMutualismBreakdownerEquilibriumDialog *ui;

  QwtPlotCurve * const m_curve_equilbrium_from_low;
  QwtPlotCurve * const m_curve_equilbrium_from_high;

  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;

  #ifndef NDEBUG
  static void Test() noexcept {}
  #endif
};
*/
#endif // QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H
