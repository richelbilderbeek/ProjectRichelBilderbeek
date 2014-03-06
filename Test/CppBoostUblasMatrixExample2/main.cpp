#include <boost/numeric/ublas/matrix.hpp>


const boost::numeric::ublas::matrix<int> CreateMatrix(const int n_cols, const int n_rows)
{
  boost::numeric::ublas::matrix<int> m(n_rows,n_cols); //y-x-ordered
  for (int y = 0; y != n_rows; ++y)
  {
    for (int x = 0; x != n_cols; ++x)
    {
      m(y,x) = (y * 10) + x;
    }
  }
  return m;
}

int main()
{
  const int n_cols = 3;
  const int n_rows = 2;
  const boost::numeric::ublas::matrix<int> m = CreateMatrix(n_cols,n_rows);

  //boost::numeric::ublas::matrix is y-x-ordered
  assert(m(0,0) ==  0); assert(m(0,1) ==  1); assert(m(0,2) ==  2);
  assert(m(1,0) == 10); assert(m(1,1) == 11); assert(m(1,2) == 12);

  //Transpose
  const boost::numeric::ublas::matrix<int> n = boost::numeric::ublas::trans(m);
  assert(n(0,0) ==  0); assert(n(0,1) == 10);
  assert(n(1,0) ==  1); assert(n(1,1) == 11);
  assert(n(2,0) ==  2); assert(n(2,1) == 12);
}
