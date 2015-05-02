#ifndef GRID_H
#define GRID_H

#include <vector>

#include "treedatapoint.h"

struct TreeDataPoint;
//#include "treedatapoint.h"

///Grid supplies TreeDataPoints a spatial context
///and the ability to index them
struct Grid
{
  Grid() {}
  Grid(const Grid& other);
  Grid& operator=(const Grid& other);

  Grid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& v
  );

  TreeDataPoint * Get(
    const int x,
    const int y
  ) const;

  void Set(
    const int x,
    const int y,
    TreeDataPoint * const p
  );

  private:
  std::vector<std::vector<TreeDataPoint*>> m_v;

  static std::vector<std::vector<TreeDataPoint*>> CreateGrid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& v
  ) noexcept;

  static const int sm_gridsize{4000};

};

#endif // GRID_H
