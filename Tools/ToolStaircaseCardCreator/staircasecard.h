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

struct QImage;

namespace ribi {

struct TextCanvas;

namespace scc {

struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);
  StaircaseCard(const std::vector<Column>& v) noexcept : m_v{v} {}

  static boost::shared_ptr<StaircaseCard> GetTest(const int i) noexcept;

  void Shuffle() noexcept;

  boost::shared_ptr<QImage> ToImage() const noexcept;
  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;
  boost::shared_ptr<TextCanvas> ToTextCanvasCompact() const noexcept;

  private:
  std::vector<Column> m_v;

  static std::vector<int> ColumnToMap(const Column& c) noexcept;
  static std::vector<Column> CreateGrid(const int n_cols, const int n_rows) noexcept;
};

std::ostream& operator<<(std::ostream& os, const StaircaseCard& c);

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARD_H
