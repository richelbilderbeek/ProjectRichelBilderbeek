#ifndef QTSPECIESOFTHERINGSMAINDIALOG_H
#define QTSPECIESOFTHERINGSMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSpeciesOfTheRingsMainDialog;
}

struct QtFractionImage;
struct QtSimTopPredatorPreyParametersWidget;

namespace ribi {

class QtSpeciesOfTheRingsMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:

  using ParametersWidget = QtSimTopPredatorPreyParametersWidget;
  using SpeciesGrid = std::vector<std::vector<double>>;
  using SpatialGrid = std::vector<std::vector<int>>;

  explicit QtSpeciesOfTheRingsMainDialog(
    const int width,
    const int height,
    QWidget *parent = 0
  );
  QtSpeciesOfTheRingsMainDialog(const QtSpeciesOfTheRingsMainDialog&) = delete;
  QtSpeciesOfTheRingsMainDialog& operator=(const QtSpeciesOfTheRingsMainDialog&) = delete;
  ~QtSpeciesOfTheRingsMainDialog();

  int GetHeight() const noexcept;
  int GetWidth() const noexcept;

private:
  Ui::QtSpeciesOfTheRingsMainDialog *ui;
  QtFractionImage * const m_qtgrid;
  std::mt19937 m_rng_engine;
  SpatialGrid m_spatial_grid;
  SpeciesGrid m_species_grid;
  static const double m_trait_distance;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnTimer() noexcept;
};

} //~namespace ribi
#endif // QTSPECIESOFTHERINGSMAINDIALOG_H
