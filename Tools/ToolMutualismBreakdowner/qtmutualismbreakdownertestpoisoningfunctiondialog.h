#ifndef QTMUTUALISMBREAKDOWNERTESTPOISONINGFUNCTIONDIALOG_H
#define QTMUTUALISMBREAKDOWNERTESTPOISONINGFUNCTIONDIALOG_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;
struct QtMutualismBreakdownerParametersWidget;

namespace Ui {
  class QtMutualismBreakdownerTestPoisoningFunctionDialog;
}

class QtMutualismBreakdownerTestPoisoningFunctionDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtMutualismBreakdownerTestPoisoningFunctionDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerTestPoisoningFunctionDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:

  void Run();

private:
  Ui::QtMutualismBreakdownerTestPoisoningFunctionDialog *ui;

  QwtPlotCurve * const m_curve;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;

  #ifndef NDEBUG
  static void Test() noexcept {}
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERTESTPOISONINGFUNCTIONDIALOG_H
