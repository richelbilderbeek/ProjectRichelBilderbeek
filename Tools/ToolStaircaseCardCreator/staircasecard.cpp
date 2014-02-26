#include <cassert>

#include "staircasecard.h"

StaircaseCard::StaircaseCard(const int n_cols, const int n_rows)
  : m_grid(n_cols,boost::dynamic_bitset<>(n_rows))
{
  assert(GetCols() == n_cols);
  assert(GetRows() == n_rows);
}

