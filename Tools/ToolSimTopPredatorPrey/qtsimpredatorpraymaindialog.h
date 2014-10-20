#ifndef QTSIMPREDATORPRAYMAINDIALOG_H
#define QTSIMPREDATORPRAYMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSimPredatorPrayMainDialog;
}

struct QtFractionImage;

class QtSimPredatorPrayMainDialog : public QDialog
{
  Q_OBJECT

public:
  typedef std::vector<std::vector<double>> Grid;
  explicit QtSimPredatorPrayMainDialog(QWidget *parent = 0);
  ~QtSimPredatorPrayMainDialog();

private:
  Ui::QtSimPredatorPrayMainDialog *ui;
  QtFractionImage * const m_widget_prey;
  QtFractionImage * const m_widget_pred;
  Grid m_grid_prey;
  Grid m_grid_pred;

  //Creates a delta-density grid based on diffusion
  static Grid CreateDiffusion(const Grid& grid) noexcept;
  static Grid CreateGrid() noexcept;
  static double GetRandomUniform();

  /// Fraction of area with predators
  static constexpr double m_frac_pred{0.1};
  static constexpr double m_diffusion_coefficient{0.05};
  static double Limit(const double x);
private slots:
  void OnTimer() noexcept;
};

#endif // QTSIMPREDATORPRAYMAINDIALOG_H
