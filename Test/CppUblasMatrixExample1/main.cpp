#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main()
{
  const int n_cols = 2;
  const int n_rows = 3;
  {
    boost::numeric::ublas::matrix<int> m(n_rows,n_cols);
    assert(n_rows == static_cast<int>(m.size1()));
    assert(n_cols == static_cast<int>(m.size2()));
    for (int y = 0; y != n_rows; ++y)
    {
      for (int x = 0; x != n_cols; ++x)
      {
        m(y,x) = (y * 10) + x;
      }
    }
    std::cout << m << std::endl;
    assert(m(0,0) ==  0); assert(m(0,1) ==  1);
    assert(m(1,0) == 10); assert(m(1,1) == 11);
    assert(m(2,0) == 20); assert(m(2,1) == 21);
  }
  {
    boost::numeric::ublas::matrix<int,boost::numeric::ublas::column_major> m(n_cols,n_rows);
    assert(n_cols == static_cast<int>(m.size1()));
    assert(n_rows == static_cast<int>(m.size2()));
    for (int x = 0; x != n_cols; ++x)
    {
      for (int y = 0; y != n_rows; ++y)
      {
        m(x,y) = (y * 10) + x;
      }
    }
    std::cout << m << std::endl;
    assert(m(0,0) ==  0); assert(m(1,0) ==  1);
    assert(m(0,1) == 10); assert(m(1,1) == 11);
    assert(m(0,2) == 20); assert(m(1,2) == 21);
  }
}

/*

[3,2]((0,1),(10,11),(20,21))
[2,3]((0,10,20),(1,11,21))

*/

