#ifndef QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H
#define QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;
struct QtMutualismBreakdownerParametersWidget;

namespace Ui {
  class QtMutualismBreakdownerTimePlotDialog;
}

class QtMutualismBreakdownerTimePlotDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtMutualismBreakdownerTimePlotDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerTimePlotDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:

  void on_button_run_clicked();

private:
  Ui::QtMutualismBreakdownerTimePlotDialog *ui;

  QwtPlotCurve * const m_curve_loripes_density;
  QwtPlotCurve * const m_curve_seagrass_density;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  QwtPlotCurve * const m_curve_organic_matter_density;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H
