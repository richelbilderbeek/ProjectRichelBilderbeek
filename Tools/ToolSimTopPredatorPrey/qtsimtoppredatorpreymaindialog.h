#ifndef QTSIMTOPPREDATORPRAYMAINDIALOG_H
#define QTSIMTOPPREDATORPRAYMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimTopPredatorPrayMainDialog;
}

struct QtFractionImage;
struct QtSimTopPredatorPreyParametersWidget;


class QtSimTopPredatorPrayMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  using ParametersWidget = QtSimTopPredatorPreyParametersWidget;

  typedef std::vector<std::vector<double>> Grid;
  explicit QtSimTopPredatorPrayMainDialog(QWidget *parent = 0);
  QtSimTopPredatorPrayMainDialog(const QtSimTopPredatorPrayMainDialog&) = delete;
  QtSimTopPredatorPrayMainDialog& operator=(const QtSimTopPredatorPrayMainDialog&) = delete;
  ~QtSimTopPredatorPrayMainDialog();

private:
  Ui::QtSimTopPredatorPrayMainDialog *ui;
  ParametersWidget * const m_widget_parameters;
  QtFractionImage * const m_widget_prey;
  QtFractionImage * const m_widget_pred;
  QtFractionImage * const m_widget_top;
  Grid m_grid_prey;
  Grid m_grid_pred;
  Grid m_grid_top;

  //Creates a delta-density grid based on diffusion
  Grid CreateDiffusion(
    const Grid& grid,
    const double diffusion_coefficient
  ) noexcept;

  static Grid CreateGrid() noexcept;
  static double GetRandomUniform();
  static double Limit(const double x);

private slots:
  void OnTimer() noexcept;
  void OnAnyChange() noexcept;
};

#endif // QTSIMTOPPREDATORPRAYMAINDIALOG_H
