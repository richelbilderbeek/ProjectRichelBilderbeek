#ifndef QTFRACTIONIMAGE_H
#define QTFRACTIONIMAGE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QWidget>
#include <QImage>

#include "species.h"
#include "space.h"
#pragma GCC diagnostic pop

class QtFractionImage : public QWidget
{
  Q_OBJECT
  public:

  using TraitGrid = std::vector<std::vector<double>>;
  using SpeciesGrid = std::vector<std::vector<Species>>;
  using SpatialGrid = std::vector<std::vector<Space>>;

  explicit QtFractionImage(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);

  static double GetMinValue(
    const SpatialGrid& spatial_grid,
    const SpeciesGrid& species_grid,
    const TraitGrid& trait_grid
  ) noexcept;

  static double GetMaxValue(
    const SpatialGrid& spatial_grid,
    const SpeciesGrid& species_grid,
    const TraitGrid& trait_grid
  ) noexcept;

  int GetHeight() const noexcept;
  int GetWidth() const noexcept;

  static double Map(
    const double x,
    const double x_min,
    const double x_max,
    const double new_range_min,
    const double new_range_max
  );

  void Set(
    const SpatialGrid& spatial_grid,
    const SpeciesGrid& species_grid,
    const TraitGrid& trait_grid
  );

  signals:

  public slots:

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  QImage m_image;
};

#endif // QTFRACTIONIMAGE_H
