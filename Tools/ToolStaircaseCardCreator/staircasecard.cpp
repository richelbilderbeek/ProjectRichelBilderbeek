#include "staircasecard.h"

#include <cassert>


ribi::scc::StaircaseCard::StaircaseCard(const int n_cols, const int n_rows)
  : m_grid(CreateGrid(n_cols,n_rows))
{
}

static const std::vector<Column> CreateGrid(const int n_cols, const int n_rows) noexcept;
