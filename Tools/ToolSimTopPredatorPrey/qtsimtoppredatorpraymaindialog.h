#ifndef QTSIMTOPPREDATORPRAYMAINDIALOG_H
#define QTSIMTOPPREDATORPRAYMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimTopPredatorPrayMainDialog;
}

struct QtFractionImage;

class QtSimTopPredatorPrayMainDialog : public QDialog
{
  Q_OBJECT

public:
  typedef std::vector<std::vector<double>> Grid;
  explicit QtSimTopPredatorPrayMainDialog(QWidget *parent = 0);
  QtSimTopPredatorPrayMainDialog(const QtSimTopPredatorPrayMainDialog&) = delete;
  QtSimTopPredatorPrayMainDialog& operator=(const QtSimTopPredatorPrayMainDialog&) = delete;
  ~QtSimTopPredatorPrayMainDialog();

private:
  Ui::QtSimTopPredatorPrayMainDialog *ui;
  QtFractionImage * const m_widget_prey;
  QtFractionImage * const m_widget_pred;
  QtFractionImage * const m_widget_top;
  Grid m_grid_prey;
  Grid m_grid_pred;
  Grid m_grid_top;

  //Creates a delta-density grid based on diffusion
  static Grid CreateDiffusion(const Grid& grid) noexcept;
  static Grid CreateGrid() noexcept;
  static double GetRandomUniform();

  /// Fraction of area with predators
  static constexpr double m_frac_pred{0.1};
  /// Fraction of area with toppredators
  static constexpr double m_frac_top{0.1};
  static constexpr double m_diffusion_coefficient{0.05};
  static double Limit(const double x);
private slots:
  void OnTimer() noexcept;
};

#endif // QTSIMTOPPREDATORPRAYMAINDIALOG_H
