#include "paperrockscissorssimulation.h"

#include <array>
#include <cassert>
#include <algorithm>
#include <cstdlib>


PaperRockScissorsSimulation::PaperRockScissorsSimulation(
  const int width,
  const int height,
  const Initialization initialization
)
  : m_grid{
      std::vector<std::vector<CellType>>(
        height,
        std::vector<CellType>(width,CellType::paper)
      )
    },
  m_initialization{initialization}
{
  SetInitialization(m_initialization);
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
      next[y][x] = DoesBeat(neighbour,here) ? neighbour : here;
    }
  }
  std::swap(m_grid,next);
}

void PaperRockScissorsSimulation::SetInitialization(const Initialization initialization) noexcept
{
  m_initialization = initialization;

  //Initialize the grid
  const int height{static_cast<int>(m_grid.size())};
  assert(!m_grid.empty());
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      CellType& celltype = m_grid[y][x];
      switch(m_initialization)
      {
        case Initialization::random:
          switch (std::rand() % 3)
          {
            case 0: celltype = CellType::paper; break;
            case 1: celltype = CellType::rock; break;
            case 2: celltype = CellType::scissors; break;
          }
          break;
        case Initialization::vertical_bands:
          {
            switch ((y / (height / 15)) % 3)
            {
              case 0: celltype = CellType::paper; break;
              case 1: celltype = CellType::rock; break;
              case 2: celltype = CellType::scissors; break;
            }
          }
        break;
      }
    }
  }

}
