#ifndef STAIRCASECARD_H
#define STAIRCASECARD_H

#include <vector>
#include <boost/dynamic_bitset.hpp>

struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);

  const std::vector<boost::dynamic_bitset<> > Get() const { return m_grid; }
  int GetCols() const { return m_grid.size(); }
  int GetRows() const { return m_grid[0].size(); }
  bool GetValue(const int col, const int row) const { return m_grid[col][row]; }
  void ResizeCols(const int n_cols);
  void ResizeRows(const int n_rows);
  void Swap(const int col, const int row1, const int row2);

  private:
  std::vector<boost::dynamic_bitset<> > m_grid;
};

#endif // STAIRCASECARD_H
