#ifndef QTFRACTIONIMAGE_H
#define QTFRACTIONIMAGE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QWidget>
#include <QImage>
#pragma GCC diagnostic pop

class QtFractionImage : public QWidget
{
  Q_OBJECT
  public:

  using SpeciesGrid = std::vector<std::vector<double>>;
  using SpatialGrid = std::vector<std::vector<int>>;

  explicit QtFractionImage(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);

  static double GetMinValue(const SpeciesGrid& species_grid) noexcept;
  static double GetMaxValue(const SpeciesGrid& species_grid) noexcept;

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
    const SpeciesGrid& species_grid,
    const SpatialGrid& spatial_grid
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
