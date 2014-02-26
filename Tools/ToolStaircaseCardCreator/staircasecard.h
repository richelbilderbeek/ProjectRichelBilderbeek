#ifndef STAIRCASECARD_H
#define STAIRCASECARD_H

#include <iosfwd>
#include <vector>
#include "staircasecardcolumn.h"

namespace ribi {
namespace scc {

struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);

  private:
  std::vector<Column> m_v;

  static const std::vector<Column> CreateGrid(const int n_cols, const int n_rows) noexcept;
};

std::ostream& operator<<(std::ostream& os, const StaircaseCard& c);

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARD_H
