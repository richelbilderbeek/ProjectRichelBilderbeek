#ifndef QTSIMTOPPREDATORPRAYMAINDIALOG_H
#define QTSIMTOPPREDATORPRAYMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSimTopPredatorPrayMainDialog;
}

struct SimTopPredatorPreyWidget;

class QtSimTopPredatorPrayMainDialog : public QDialog
{
  Q_OBJECT

public:
  typedef std::vector<std::vector<double>> Grid;
  explicit QtSimTopPredatorPrayMainDialog(QWidget *parent = 0);
  ~QtSimTopPredatorPrayMainDialog();

private:
  Ui::QtSimTopPredatorPrayMainDialog *ui;
  SimTopPredatorPreyWidget * const m_widget_prey;
  SimTopPredatorPreyWidget * const m_widget_pred;
  SimTopPredatorPreyWidget * const m_widget_top;
  Grid m_grid_prey;
  Grid m_grid_pred;
  Grid m_grid_top;

  //Creates a delta-density grid based on diffusion
  static Grid CreateDiffusion(const Grid& grid) noexcept;
  static Grid CreateGrid() noexcept;

  /// Fraction of area with predators
  static constexpr double m_frac_pred{0.1};
  /// Fraction of area with toppredators
  static constexpr double m_frac_top{0.01};
  static constexpr double m_diffusion_coefficient{0.1};

private slots:
  void OnTimer() noexcept;
};

#endif // QTSIMTOPPREDATORPRAYMAINDIALOG_H
