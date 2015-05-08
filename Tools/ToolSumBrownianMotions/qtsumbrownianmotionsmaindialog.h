#ifndef QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H
#define QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;

namespace Ui {
  class QtSumBrownianMotionsMainDialog;
}

class QtSumBrownianMotionsMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtSumBrownianMotionsMainDialog(QWidget *parent = 0);
  ~QtSumBrownianMotionsMainDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:
  void Run();

private:
  Ui::QtSumBrownianMotionsMainDialog *ui;

  QwtPlotCurve * const m_curve_a;
  QwtPlotCurve * const m_curve_b;
  QwtPlotCurve * const m_curve_sum;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H
