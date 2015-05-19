#include "paperrockscissorswithtraitsimulation.h"

#include <array>
#include <cassert>
#include <algorithm>
#include <cstdlib>


PaperRockScissorsSimulation::PaperRockScissorsSimulation(const int width, const int height)
  : m_grid{
      std::vector<std::vector<CellType>>(
        height,
        std::vector<CellType>(width,Individual(0.0,PaperRockScissors::paper))
      )
    }
{
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      CellType& celltype = m_grid[y][x];
      const bool do_initialize_randomly{false};
      if (do_initialize_randomly)
      {
        switch (std::rand() % 3)
        {
          case 0: celltype = CellType(0.0,PaperRockScissors::paper); break;
          case 1: celltype = CellType(0.0,PaperRockScissors::rock); break;
          case 2: celltype = CellType(0.0,PaperRockScissors::scissors); break;
        }
      }
      else
      {
        switch ((y / (height / 15)) % 3)
        {
          case 0: celltype = CellType(0.0,PaperRockScissors::paper); break;
          case 1: celltype = CellType(0.0,PaperRockScissors::rock); break;
          case 2: celltype = CellType(0.0,PaperRockScissors::scissors); break;
        }
      }
    }
  }
}

void PaperRockScissorsSimulation::Next()
{
  std::vector<std::vector<CellType>> next(m_grid);
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      int dx{0};
      int dy{0};
      switch (rand() % 4)
      {
        case 0: --dy; break;
        case 1: ++dx; break;
        case 2: ++dy; break;
        case 3: --dx; break;
      }
      CellType& here{m_grid[y][x]};
      const CellType& neighbour{m_grid[(y+dy+height)%height][(x+dx+width)%width]};
      next[y][x] = DoesBeat(neighbour.m_type,here.m_type) ? neighbour : here;
    }
  }
  std::swap(m_grid,next);
}
