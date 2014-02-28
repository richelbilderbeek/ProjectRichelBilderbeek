#ifndef STAIRCASECARD_H
#define STAIRCASECARD_H

#include <iosfwd>
#include <vector>
#include "staircasecardcolumn.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace scc {

struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);

  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;
  const boost::shared_ptr<TextCanvas> ToTextCanvasCompact() const noexcept;

  private:
  std::vector<Column> m_v;

  static const std::vector<Column> CreateGrid(const int n_cols, const int n_rows) noexcept;
};

std::ostream& operator<<(std::ostream& os, const StaircaseCard& c);

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARD_H
