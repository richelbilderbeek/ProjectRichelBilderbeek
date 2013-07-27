#ifndef MYDATA_H
#define MYDATA_H

#include <boost/numeric/ublas/matrix.hpp>

///Plain interface to a matrix
struct MyData
{
  MyData(const int n_rows = 4, const int n_cols = 3);
  double Get(const int row, const int col) const;
  int GetColCount() const;
  int GetRowCount() const;
  void Set(const int row, const int col, const double value);
  private:
  boost::numeric::ublas::matrix<double> m_v;
};

#endif // MYDATA_H
