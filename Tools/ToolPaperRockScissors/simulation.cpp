#include "simulation.h"

#include <array>
#include <algorithm>
#include <cstdlib>

Simulation::Simulation(const int width, const int height)
  : m_grid{
      std::vector<std::vector<CellType>>(
        height,
        std::vector<CellType>(width,CellType::paper)
      )
    }
{
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      CellType& celltype = m_grid[y][x];
      switch (std::rand() % 3)
      {
        case 0: celltype = CellType::paper; break;
        case 1: celltype = CellType::rock; break;
        case 2: celltype = CellType::scissors; break;
      }
    }
  }
}

void Simulation::Next()
{
  std::vector<std::vector<CellType>> next(m_grid);
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      std::array<CellType,4> neighbours;
      //Up
      neighbours[0] = m_grid[(y-1+height)%height][x];
      //Right
      neighbours[1] = m_grid[y][(x+1)%width];
      //Down
      neighbours[2] = m_grid[(y+1)%height][x];
      //Left
      neighbours[3] = m_grid[y][(x-1+width)%width];
      int n_paper{0};
      int n_rock{0};
      int n_scissor{0};
      for(const CellType t: neighbours)
      {
        if (t == CellType::paper) ++n_paper;
        else if (t == CellType::rock) ++n_rock;
        else ++n_scissor;
      }
      next[y][x] = m_grid[y][x];
      switch (m_grid[y][x])
      {
        case CellType::paper: if (n_scissor >= 2) { next[y][x] = CellType::scissors; } break;
        case CellType::rock: if (n_paper >= 2) { next[y][x] = CellType::paper; } break;
        case CellType::scissors: if (n_rock >= 2) { next[y][x] = CellType::rock; } break;
      }
    }
  }
  std::swap(m_grid,next);
}
