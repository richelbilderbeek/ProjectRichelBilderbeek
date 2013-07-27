#include "mydata.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

MyData::MyData(const int n_rows, const int n_cols)
  : m_v(n_rows,n_cols)
{
  for (int row = 0; row!=n_rows; ++row)
  {
    const double denominator = boost::numeric_cast<double>(row + 1);
    for (int col = 0; col!=n_cols; ++col)
    {
      const double numerator = boost::numeric_cast<double>(col + 1);
      m_v(row,col) = numerator / denominator;
    }
  }
}

double MyData::Get(const int row, const int col) const
{
  assert(row < boost::numeric_cast<int>(m_v.size1()));
  assert(col < boost::numeric_cast<int>(m_v.size2()));
  return m_v(row,col);
}

int MyData::GetColCount() const
{
  return boost::numeric_cast<int>(m_v.size2());
}

int MyData::GetRowCount() const
{
  return boost::numeric_cast<int>(m_v.size1());
}

void MyData::Set(const int row, const int col, const double value)
{
  assert(row < boost::numeric_cast<int>(m_v.size1()));
  assert(col < boost::numeric_cast<int>(m_v.size2()));
  m_v(row,col) = value;
}
