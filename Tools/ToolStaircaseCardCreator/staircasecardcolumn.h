#ifndef STAIRCASECARDCOLUMN_H
#define STAIRCASECARDCOLUMN_H

#include <string>
#include <vector>
#include "staircasecardorientation.h"

namespace ribi {
namespace scc {

///A column in a staircase card
struct Column
{
  Column(const int n_vertical, const int n_horizontal);
  Column(const std::vector<int>& v);

  Orientation GetOrientation(const int row) const noexcept;

  int GetMax() const noexcept { return static_cast<int>(m_v.size()); }

  //Swap two orientations
  void Swap(const int a, const int b) noexcept;

  std::string ToStr() const noexcept;

  private:
  std::vector<Orientation> m_v;

  static std::vector<Orientation> Create(const int n_vertical, const int n_horizontal) noexcept;
  static std::vector<Orientation> Create(const std::vector<int>& v);
};

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCOLUMN_H
