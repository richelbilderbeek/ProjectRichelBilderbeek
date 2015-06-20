#ifndef QTSPECIESOFTHERINGSMAINDIALOG_H
#define QTSPECIESOFTHERINGSMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "species.h"
#include "space.h"
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
  using TraitGrid = std::vector<std::vector<double>>;
  using SpeciesGrid = std::vector<std::vector<Species>>;
  using SpatialGrid = std::vector<std::vector<Space>>;

  explicit QtSpeciesOfTheRingsMainDialog(QWidget *parent = 0);
  QtSpeciesOfTheRingsMainDialog(const QtSpeciesOfTheRingsMainDialog&) = delete;
  QtSpeciesOfTheRingsMainDialog& operator=(const QtSpeciesOfTheRingsMainDialog&) = delete;
  ~QtSpeciesOfTheRingsMainDialog();


  int GetHeight() const noexcept;
  int GetWidth() const noexcept;

private:
  Ui::QtSpeciesOfTheRingsMainDialog *ui;
  std::normal_distribution<double> m_normal_distribution;
  std::uniform_real_distribution<double> m_uniform_distribution;
  QtFractionImage * const m_qtgrid;
  std::mt19937 m_rng_engine;
  SpatialGrid m_spatial_grid;
  SpeciesGrid m_species_grid;
  int m_t;
  TraitGrid m_trait_grid;

  std::vector<double> CollectTraits() const noexcept;

  void Display();
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnParametersChanged() noexcept;
  void OnTimer() noexcept;
};

} //~namespace ribi
#endif // QTSPECIESOFTHERINGSMAINDIALOG_H
