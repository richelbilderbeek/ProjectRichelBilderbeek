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
  const QtFractionImage::SpeciesGrid& species_grid
) noexcept
{
  double min_value{species_grid[0][0]};
  for (const auto& line: species_grid)
  {
    const double this_min{
      *std::min_element(std::begin(line),std::end(line))
    };
    min_value = std::min(this_min,min_value);
  }
  return min_value;
}

double QtFractionImage::GetMaxValue(
  const QtFractionImage::SpeciesGrid& species_grid
) noexcept
{
  double max_value{species_grid[0][0]};
  for (const auto& line: species_grid)
  {
    const double this_max{
      *std::max_element(std::begin(line),std::end(line))
    };
    max_value = std::max(this_max,max_value);
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
  const SpeciesGrid& species_grid,
  const SpatialGrid& spatial_grid
)
{
  assert(species_grid.size() == spatial_grid.size());
  assert(species_grid[0].size() == spatial_grid[0].size());
  if (GetHeight() != static_cast<int>(species_grid.size()))
  {
    assert(!species_grid.empty());
    const int new_height = species_grid.size();
    const int new_width = species_grid[0].size();
    m_image = QImage(new_width,new_height,QImage::Format::Format_RGB32);
  }

  const auto height = GetHeight();
  const auto width  = GetWidth();

  const double min_value = GetMinValue(species_grid);
  const double max_value = GetMaxValue(species_grid);

  for (int y{0}; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < height);
    const auto& species_line = species_grid[y];
    const auto& spatial_line = spatial_grid[y];
    for (int x{0}; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < width);
      if (spatial_line[x] == 0)
      {
        m_image.setPixel(x,y,qRgb(0,0,0));
        continue;
      }
      const double species_value = species_line[x];
      const double color_angle{
        Map(species_value,min_value,max_value,0.0,270.0)
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
