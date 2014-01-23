#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <vector>

namespace ribi {
namespace maziak {

struct IntMaze
{
  IntMaze(const int sz) : IntMaze(CreateMaze(sz)) {}
  const std::vector<std::vector<int>> Get() const noexcept { return m_maze; }

  const std::vector<std::pair<int,int> > GetShuffledDeadEnds() const noexcept;

  private:
  IntMaze(const std::vector<std::vector<int> >& maze);

  const std::vector<std::pair<int,int> > m_dead_ends;
  const std::vector<std::vector<int>> m_maze;

  //Creates a maze
  // 0 : path
  // 1 : wall
  //From http://www.richelbilderbeek.nl/CppCreateMaze.htm
  static const std::vector<std::vector<int> > CreateMaze(const int sz) noexcept;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
