#ifndef QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H
#define QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;

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
  void Run();

  void on_button_fix_zoom_clicked();

  void on_button_set_random_values_clicked();

  void on_button_save_clicked();

  void on_button_load_clicked();

private:
  Ui::QtMutualismBreakdownerTimePlotDialog *ui;

  QwtPlotCurve * const m_curve_seagrass_density;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  QwtPlotCurve * const m_curve_organic_matter_density;

  void FixZoom();
  double GetRandom() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERTIMEPLOTDIALOG_H
