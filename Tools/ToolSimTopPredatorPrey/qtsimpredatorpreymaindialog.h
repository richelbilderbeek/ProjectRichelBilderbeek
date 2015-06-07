#ifndef QTSIMPREDATORPRAYMAINDIALOG_H
#define QTSIMPREDATORPRAYMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimPredatorPrayMainDialog;
}

struct QtFractionImage;
struct QtSimTopPredatorPreyParametersWidget;

namespace ribi {

class QtSimPredatorPrayMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  using ParametersWidget = QtSimTopPredatorPreyParametersWidget;
  using Grid = std::vector<std::vector<double>>;

  explicit QtSimPredatorPrayMainDialog(QWidget *parent = 0);
  QtSimPredatorPrayMainDialog(const QtSimPredatorPrayMainDialog&) = delete;
  QtSimPredatorPrayMainDialog& operator=(const QtSimPredatorPrayMainDialog&) = delete;
  ~QtSimPredatorPrayMainDialog();

private:
  Ui::QtSimPredatorPrayMainDialog *ui;
  ParametersWidget * const m_widget_parameters;
  QtFractionImage * const m_widget_prey;
  QtFractionImage * const m_widget_pred;
  Grid m_grid_prey;
  Grid m_grid_pred;

  //Creates a delta-density grid based on diffusion
  static Grid CreateDiffusion(
    const Grid& grid,
    const double diffusion_coefficient
  ) noexcept;
  static Grid CreateGrid() noexcept;

  /// Fraction of area with predators
  static constexpr double m_frac_pred{0.01};
  static constexpr double m_diffusion_coefficient{0.005};
  static double Limit(const double x);

  #ifndef NDEBUG
  void Test() noexcept;
  #endif

private slots:
  void OnAnyChange() noexcept;
  void OnTimer() noexcept;
};

} //~namespace ribi
#endif // QTSIMPREDATORPRAYMAINDIALOG_H
