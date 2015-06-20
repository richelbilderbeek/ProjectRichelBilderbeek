#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtfractionimage.h"

#include <cassert>

#include <QImage>
#include <QPainter>
#pragma GCC diagnostic pop

double QtFractionImage::GetMinValue(
  const QtFractionImage::SpatialGrid& spatial_grid,
  const QtFractionImage::SpeciesGrid& species_grid,
  const QtFractionImage::TraitGrid& trait_grid
) noexcept
{
  double min_value{std::numeric_limits<double>::max()};
  const int height{static_cast<int>(trait_grid.size())};
  const int width{static_cast<int>(trait_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      if (spatial_grid[y][x] == Space::Mountain) continue;
      if (species_grid[y][x] == Species::Absent) continue;
      min_value = std::min(min_value,trait_grid[y][x]);
    }
  }
  return min_value;
}

double QtFractionImage::GetMaxValue(
  const QtFractionImage::SpatialGrid& spatial_grid,
  const QtFractionImage::SpeciesGrid& species_grid,
  const QtFractionImage::TraitGrid& trait_grid
) noexcept
{
  double max_value{std::numeric_limits<double>::min()};
  const int height{static_cast<int>(trait_grid.size())};
  const int width{static_cast<int>(trait_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      if (spatial_grid[y][x] == Space::Mountain) continue;
      if (species_grid[y][x] == Species::Absent) continue;
      max_value = std::max(max_value,trait_grid[y][x]);
    }
  }
  return max_value;
}


double QtFractionImage::Map(
  const double x,
  const double x_min,
  const double x_max,
  const double new_range_min,
  const double new_range_max
)
{
  if (x_min == x_max) return 0.5 * (new_range_min + new_range_max);
  assert(x_min < x_max);
  assert(x >= x_min);
  assert(x <= x_max);
  const double cur_range{x_max - x_min};
  const double f{ (x - x_min) / cur_range};
  const double new_range{new_range_max - new_range_min};
  const double y{new_range_min + (f * new_range)};
  assert(y >= new_range_min);
  assert(y <= new_range_max);
  return y;

}


QtFractionImage::QtFractionImage(QWidget *parent) :
    QWidget(parent),
    m_image{}
{
  m_image = QImage(100,100,QImage::Format::Format_RGB32);
}

int QtFractionImage::GetHeight() const noexcept
{
  return m_image.height();
}

int QtFractionImage::GetWidth() const noexcept
{
  return m_image.width();
}

void QtFractionImage::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    0,0,this->width(),this->height(),QPixmap::fromImage(m_image)
  );
}

void QtFractionImage::Set(
  const SpatialGrid& spatial_grid,
  const SpeciesGrid& species_grid,
  const TraitGrid& trait_grid
)
{
  assert(trait_grid.size() == spatial_grid.size());
  assert(trait_grid[0].size() == spatial_grid[0].size());
  if (GetHeight() != static_cast<int>(trait_grid.size())
    || GetWidth() != static_cast<int>(trait_grid[0].size()))
  {
    assert(!trait_grid.empty());
    const int new_height = trait_grid.size();
    const int new_width = trait_grid[0].size();
    m_image = QImage(new_width,new_height,QImage::Format::Format_RGB32);
  }
  assert(GetHeight() == static_cast<int>(trait_grid.size()));
  assert(GetWidth() == static_cast<int>(trait_grid[0].size()));

  const auto height = GetHeight();
  const auto width  = GetWidth();

  const double min_value
    = GetMinValue(
      spatial_grid,
      species_grid,
      trait_grid
    );
  const double max_value
    = GetMaxValue(
      spatial_grid,
      species_grid,
      trait_grid
    );

  for (int y{0}; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < height);
    const auto& species_line = species_grid[y];
    const auto& spatial_line = spatial_grid[y];
    const auto& trait_line = trait_grid[y];
    for (int x{0}; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < width);
      if (spatial_line[x] == Space::Mountain)
      {
        m_image.setPixel(x,y,qRgb(0,0,0));
        continue;
      }
      if (species_line[x] == Species::Absent)
      {
        m_image.setPixel(x,y,qRgb(128,128,128));
        continue;
      }
      const double trait_value{trait_line[x]};
      const double color_angle{
        Map(trait_value,min_value,max_value,0.0,270.0)
      };
      QColor color;
      color.setHsv(color_angle,254,254);
      int r,g,b;
      color.getRgb(&r,&g,&b);
      m_image.setPixel(x,y,qRgb(r,g,b));
    }
  }
  repaint();
}
