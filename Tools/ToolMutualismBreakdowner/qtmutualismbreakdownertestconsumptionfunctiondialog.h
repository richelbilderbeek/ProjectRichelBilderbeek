#ifndef QTMUTUALISMBREAKDOWNERTESTCONSUMPTIONFUNCTIONDIALOG_H
#define QTMUTUALISMBREAKDOWNERTESTCONSUMPTIONFUNCTIONDIALOG_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;
struct QtMutualismBreakdownerParametersWidget;

namespace Ui {
  class QtMutualismBreakdownerTestConsumptionFunctionDialog;
}

class QtMutualismBreakdownerTestConsumptionFunctionDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtMutualismBreakdownerTestConsumptionFunctionDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerTestConsumptionFunctionDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:

  void Run();

private:
  Ui::QtMutualismBreakdownerTestConsumptionFunctionDialog *ui;

  QwtPlotCurve * const m_curve;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;

  #ifndef NDEBUG
  static void Test() noexcept {}
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERTESTCONSUMPTIONFUNCTIONDIALOG_H
