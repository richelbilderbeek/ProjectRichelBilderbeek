#ifndef QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H
#define QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H

#include "parameters.h"
#include "qthideandshowdialog.h"

struct QwtPlotCurve;

namespace Ui {
  class QtMutualismBreakdownerMainDialog;
}

class QtMutualismBreakdownerMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtMutualismBreakdownerMainDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerMainDialog();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:
  void Run();

  void on_button_fix_zoom_clicked();

  void on_button_set_random_values_clicked();

  void on_button_save_clicked();

  void on_button_load_clicked();

private:
  Ui::QtMutualismBreakdownerMainDialog *ui;

  QwtPlotCurve * const m_curve_seagrass_density;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  QwtPlotCurve * const m_curve_organic_matter_density;

  void FixZoom();
  double GetRandom() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERMAINDIALOG_H_H
