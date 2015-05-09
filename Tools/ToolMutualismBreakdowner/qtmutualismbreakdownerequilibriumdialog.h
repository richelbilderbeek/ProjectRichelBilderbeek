#ifndef QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H
#define QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;

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
  void Run();

  void on_button_fix_zoom_clicked();

  void on_button_set_random_values_clicked();

  void on_button_save_clicked();

  void on_button_load_clicked();

private:
  Ui::QtMutualismBreakdownerEquilibriumDialog *ui;

  QwtPlotCurve * const m_curve_equilbrium;

  void FixZoom();
  double GetRandom() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept {}
  #endif
};

#endif // QTMUTUALISMBREAKDOWNEREQUILIBRIUMDIALOG_H
