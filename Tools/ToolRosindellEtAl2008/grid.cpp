#include "grid.h"

#include <cassert>
#include "treedatapoint.h"
Grid::Grid(
  const int width,
  const int height,
  std::vector<TreeDataPoint>& v
) : m_v{CreateGrid(width,height,v)}
{
}

Grid::Grid(const Grid& other)
  : m_v{other.m_v}
{

}

Grid& Grid::operator=(const Grid& other)
{
  m_v = other.m_v;
  return *this;
}

std::vector<std::vector<TreeDataPoint*>>
  Grid::CreateGrid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& active
) noexcept
{
  assert(width > 0);
  assert(height > 0);

  const int sz
    = sm_gridsize < width * 2 ? width * 2
    : (sm_gridsize < height*2 ? height*2 : sm_gridsize)
  ;
  assert(sz > 0);

  std::vector<std::vector<TreeDataPoint*>> v(
    sz,
    std::vector<TreeDataPoint*>(sz,nullptr)
  );
  for (TreeDataPoint& p: active)
  {
    const int x{p.GetXpos()};
    const int y{p.GetYpos()};
    v[x][y] = &p;
  }
  return v;
}

TreeDataPoint * Grid::Get(
  const int x,
  const int y
) const
{
  assert(x >= 0);
  assert(x < static_cast<int>(m_v.size()));
  assert(y >= 0);
  assert(y < static_cast<int>(m_v[0].size()));
  return m_v[x][y];
}

void Grid::Set(
  const int x,
  const int y,
  TreeDataPoint * const p
)
{
  assert(x >= 0);
  assert(x < static_cast<int>(m_v.size()));
  assert(y >= 0);
  assert(y < static_cast<int>(m_v[0].size()));
  m_v[x][y] = p;
}
