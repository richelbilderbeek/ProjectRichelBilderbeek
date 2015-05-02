#ifndef GRID_H
#define GRID_H

#include <vector>

struct TreeDataPoint;
//#include "treedatapoint.h"

///Grid supplies TreeDataPoints a spatial context
///and the ability to index them
struct Grid
{
  Grid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& v
  );

  TreeDataPoint * Find(
    const int x,
    const int y
  ) const;

  private:
  const std::vector<std::vector<TreeDataPoint*>> m_v;

  static std::vector<std::vector<TreeDataPoint*>> CreateGrid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& v
  ) noexcept;

  static const int sm_gridsize{4000};

};

#endif // GRID_H
