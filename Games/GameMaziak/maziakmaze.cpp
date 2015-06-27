#include "maziakmaze.h"

#include <cassert>

#include "ribi_random.h"
#include "testtimer.h"
#include "maziakintmaze.h"
#include "trace.h"

template <class Source, class Target>
    const std::vector<std::vector<Target> > ConvertMatrix(
        const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}

ribi::maziak::Maze::Maze(const int size,const int rng_seed)
  : m_int_maze{CreateIntMaze(size)},
    m_maze{},
    m_rng_engine(rng_seed)
{
  #ifndef NDEBUG
  Test();
  #endif
  m_maze = CreateMaze(m_int_maze);
  assert(IsSquare());
  assert(FindExit().first  >= 0);
  assert(FindStart().first >= 0);
}

void ribi::maziak::Maze::AnimateEnemiesAndPrisoners(
  const int x,
  const int y,
  const int view_width,
  const int view_height
  ) noexcept
{
  //Move them
  const int minx = std::max(0,x - view_width );
  const int miny = std::max(0,y - view_height);
  assert(IsSquare());
  const int maxy = std::min(GetSize(),y + view_height);
  const int maxx = std::min(GetSize(),x + view_width);
  assert(miny >= 0);
  assert(miny <= GetSize());
  assert(maxy >= 0);
  assert(maxy <= GetSize());
  assert(minx >= 0);
  assert(minx <= GetSize());
  assert(maxx >= 0);
  assert(maxx <= GetSize());
  assert(miny <= maxy);
  assert(minx <= maxx);
  for (int row=miny; row!=maxy; ++row)
  {
    assert(row >= 0);
    assert(row < GetSize());
    for (int col=minx; col!=maxx; ++col)
    {
      //msEnemy1 changes to msEnemy2
      //Only msEnemy2 moves, after moving turning to msEnemy1
      assert(col >= 0);
      assert(col < GetSize());
      const MazeSquare s = Get(col,row);

      if (s == MazeSquare::msEnemy1)
      {
        //msEnemy1 changes to msEnemy2
        Set(col,row,MazeSquare::msEnemy2);
        continue;
      }
      else if (s == MazeSquare::msEnemy2)
      {
        //msEnemy 2 tries to walk and becomes msEnemy1
        std::vector<std::pair<int,int> > moves;
        if (row > y && row >        1 && Get(col,row-1) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col,row-1));
        if (col < x && col < maxx - 1 && Get(col+1,row) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col+1,row));
        if (row < y && row < maxy - 1 && Get(col,row+1) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col,row+1));
        if (col > x && col >        1 && Get(col-1,row) == MazeSquare::msEmpty) moves.push_back(std::make_pair(col-1,row));
        //Pick a random move
        if (!moves.empty())
        {
          std::shuffle(std::begin(moves),std::end(moves),m_rng_engine);
          Set(moves[0].first,moves[0].second,MazeSquare::msEnemy1);
          Set(col,row,MazeSquare::msEmpty);
        }
      }
      else if (s==MazeSquare::msPrisoner1)
      {
        //Animate prisoners
        Set(col,row,MazeSquare::msPrisoner2);
      }
      else if (s==MazeSquare::msPrisoner2)
      {
        //Animate prisoners
        Set(col,row,MazeSquare::msPrisoner1);
      }
    }
  }
}

bool ribi::maziak::Maze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize()
    && y >= 0 && y < GetSize();
}

bool ribi::maziak::Maze::CanMoveTo(
  const int x, const int y,
  const bool hasSword,
  const bool showSolution) const noexcept
{
  //Bump into edge
  if (x < 0) return false;
  if (y < 0) return false;
  const int maxy = static_cast<int>(m_maze.size());
  if (y >= maxy) return false;
  if (x >= static_cast<int>(m_maze[y].size())) return false;
  const MazeSquare s = m_maze[y][x];
  //Bump into wall
  if (s == MazeSquare::msWall) return false;
  //Bump into sword
  if (s == MazeSquare::msSword && hasSword) return false;
  //Bump into prisoner
  if (showSolution
    && (s == MazeSquare::msPrisoner1
     || s == MazeSquare::msPrisoner2) ) return false;
  //Bump into empty/enemy/exit, so player can move there
  return true;
}

bool ribi::maziak::Maze::CanSet(const int x, const int y, const MazeSquare /* s */) const noexcept
{
  return CanGet(x,y);
}

ribi::maziak::IntMaze ribi::maziak::Maze::CreateIntMaze(const int size) noexcept
{
  assert( size > 4 && size % 4 == 3
    && "Size must be 3 + (n * 4) for n > 0");
  IntMaze maze(size);
  return maze;
}

std::vector<std::vector<ribi::maziak::MazeSquare> > ribi::maziak::Maze::CreateMaze(
  const IntMaze& int_maze) noexcept
{
  const bool verbose{true};
  const int sz = int_maze.GetSize();
  std::vector<std::vector<ribi::maziak::MazeSquare> > maze {
    ConvertMatrix<int,MazeSquare>(int_maze.GetMaze())
  };

  std::vector<std::pair<int,int> > dead_ends = int_maze.GetDeadEnds();
  const int nDeadEnds = dead_ends.size();
  std::uniform_int_distribution<int> distribution(0,nDeadEnds-1); //Inclusive max
  assert(nDeadEnds >= 2);
  const int nSwords    = (nDeadEnds - 2) / 3;
  const int nPrisoners = (nDeadEnds - 2) / 10;
  const int nEnemies   = (nDeadEnds - 2) / 4;
  {
    //Set a minimum distance for the player to travel
    //while (1)
    for (int i=0; ;++i)
    {
      if (static_cast<int>(std::log10(i)) != static_cast<int>(std::log10(i + 1)))
      {
        if (verbose) { TRACE(i + 1); }
      }
      const double x1 = static_cast<double>(dead_ends[0].first );
      const double y1 = static_cast<double>(dead_ends[0].second);
      const double x2 = static_cast<double>(dead_ends[1].first );
      const double y2 = static_cast<double>(dead_ends[1].second);
      const double a = x1 - x2;
      const double b = y1 - y2;
      // Use 0.65, as 0.75 could not always be solved
      const double minDist = 0.40 * static_cast<double>(sz);
      if (std::sqrt( (a * a) + (b * b) ) > minDist)
      {
        break;
      }
      else
      {
        const int de_a{distribution(m_rng_engine)};
        const int de_b{distribution(m_rng_engine)};
        assert(de_a < static_cast<int>(dead_ends.size()));
        assert(de_b < static_cast<int>(dead_ends.size()));
        std::swap(dead_ends[0],dead_ends[de_a]);
        std::swap(dead_ends[1],dead_ends[de_b]);
      }
    }
  }
  //Set start
  {
    const int x = dead_ends[0].first;
    const int y = dead_ends[0].second;
    assert(maze[y][x] == MazeSquare::msEmpty);
    maze[y][x] = MazeSquare::msStart;
  }
  //Set exit
  {
    const int x = dead_ends[1].first;
    const int y = dead_ends[1].second;
    assert(maze[y][x] == MazeSquare::msEmpty);
    maze[y][x] = MazeSquare::msExit;
  }


  std::vector<std::pair<int,int> >::const_iterator deadEndIterator = dead_ends.begin() + 2;

  {
    //Place swords in maze, only in dead ends
    for (int i=0; i!=nSwords; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msSword;
      ++deadEndIterator;
    }
    //Place prisoners in maze, only in dead ends
    for (int i=0; i!=nPrisoners; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msPrisoner1;
      ++deadEndIterator;
    }

    for (int i=0; i!=nEnemies; ++i)
    {
      assert(deadEndIterator != dead_ends.end());
      const int x = (*deadEndIterator).first;
      const int y = (*deadEndIterator).second;
      assert(maze[y][x] == MazeSquare::msEmpty);
      maze[y][x] = MazeSquare::msEnemy1;
      ++deadEndIterator;
    }
  }
  return maze;
}

const std::pair<int,int> ribi::maziak::Maze::FindExit() const noexcept
{
  for (std::pair<int,int> p: GetIntMaze().GetDeadEnds())
  {
    if (Get(p.first,p.second) == MazeSquare::msExit) return p;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot find exit");
}

const std::pair<int,int> ribi::maziak::Maze::FindStart() const noexcept
{
  for (std::pair<int,int> p: GetIntMaze().GetDeadEnds())
  {
    if (Get(p.first,p.second) == MazeSquare::msStart) return p;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot find start");
}

ribi::maziak::MazeSquare ribi::maziak::Maze::Get(const int x, const int y) const noexcept
{
  assert(CanGet(x,y));
  return m_maze[y][x];
}

bool ribi::maziak::Maze::IsSquare() const noexcept
{
  assert(!m_maze.empty());
  for(std::vector<MazeSquare> row: m_maze)
  {
    if (row.size()!=m_maze.size()) return false;
  }
  return true;
}

void ribi::maziak::Maze::Set(const int x, const int y, const MazeSquare s) noexcept
{
  assert(CanSet(x,y,s));
  m_maze[y][x] = s;
  assert(Get(x,y) == s);
}

#ifndef NDEBUG
void ribi::maziak::Maze::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Random();
    IntMaze(7);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  #ifdef FIX_ISSUE_280
  {
    Maze maze(11);
  }
  #endif

}
#endif
