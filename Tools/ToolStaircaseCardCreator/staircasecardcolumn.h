#ifndef STAIRCASECARDCOLUMN_H
#define STAIRCASECARDCOLUMN_H

#include <vector>
#include "staircasecardorientation.h"

namespace ribi {
namespace scc {

///A column in a staircase card
struct Column
{
  Column(const std::vector<Orientation>& v);

  private:
  std::vector<Orientation> m_v;
};

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCOLUMN_H
