#ifdef _WIN32
#undef __STRICT_ANSI__
#endif

#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/lu.hpp>


///Calculate the determinant
//Adapted from the code Maik Beckmann posted at
//  http://boost.2283326.n4.nabble.com/How-to-compute-determinant-td2710896.html
double CalcDeterminant(boost::numeric::ublas::matrix<double> m)
{
  assert(m.size1() == m.size2() && "Can only calculate the determinant of square matrices");
  boost::numeric::ublas::permutation_matrix<std::size_t> pivots(m.size1() );

  const int is_singular = boost::numeric::ublas::lu_factorize(m, pivots);

  if (is_singular) return 0.0;

  double d = 1.0;
  const std::size_t sz = pivots.size();
  for (std::size_t i=0; i != sz; ++i)
  {
    if (pivots(i) != i)
    {
      d *= -1.0;
    }
    d *= m(i,i);
  }
  return d;
}

double CalcDeterminantSmall(const boost::numeric::ublas::matrix<double>& m)
{
  assert(m.size1() == m.size2() && "Can only calculate the determinant of square matrices");
  switch(m.size1())
  {
    case 0: return 1.0;
    case 1:
    {
      return m(0,0);
    }
    case 2:
    {
      const double a = m(0,0);
      const double b = m(0,1);
      const double c = m(1,0);
      const double d = m(1,1);
      const double determinant = (a * d) - (b * c);
      return determinant;
    }
    case 3:
    {
      assert(m.size1() == 3 && m.size2() == 3 && "Only for 3x3 matrices");
      const double a = m(0,0);
      const double b = m(0,1);
      const double c = m(0,2);
      const double d = m(1,0);
      const double e = m(1,1);
      const double f = m(1,2);
      const double g = m(2,0);
      const double h = m(2,1);
      const double k = m(2,2);
      const double determinant
        = (a * ((e*k) - (f*h)))
        - (b * ((k*d) - (f*g)))
        + (c * ((d*h) - (e*g)));
      return determinant;
    }
    default:
      assert("Cannot handle matrix bigger than 3x3");
      throw std::logic_error("Cannot handle matrix bigger than 3x3");
  }
}

///Chop returns a std::vector of sub-matrices
//[ A at [0]   B at [1] ]
//[ C at [2]   D at [4] ]
const std::vector<boost::numeric::ublas::matrix<double> > Chop(
  const boost::numeric::ublas::matrix<double>& m)
{
  using boost::numeric::ublas::range;
  using boost::numeric::ublas::matrix;
  using boost::numeric::ublas::matrix_range;
  std::vector<matrix<double> > v;
  v.reserve(4);
  const int midy = m.size1() / 2;
  const int midx = m.size2() / 2;
  const matrix_range<const matrix<double> > top_left(    m,range(0   ,midy     ),range(0   ,midx     ));
  const matrix_range<const matrix<double> > bottom_left( m,range(midy,m.size1()),range(0   ,midx     ));
  const matrix_range<const matrix<double> > top_right(   m,range(0   ,midy     ),range(midx,m.size2()));
  const matrix_range<const matrix<double> > bottom_right(m,range(midy,m.size1()),range(midx,m.size2()));
  v.push_back(matrix<double>(top_left));
  v.push_back(matrix<double>(top_right));
  v.push_back(matrix<double>(bottom_left));
  v.push_back(matrix<double>(bottom_right));
  return v;
}

const boost::numeric::ublas::matrix<double> CreateRandomMatrix(const std::size_t n_rows, const std::size_t n_cols)
{
  boost::numeric::ublas::matrix<double> m(n_rows,n_cols);
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      m(row,col) = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    }
  }
  return m;
}



int main()
{
  using boost::numeric::ublas::matrix;
  //Compare CalcDeterminant for smaller matrices
  for (std::size_t sz = 0; sz!=4; ++sz)
  {
    const matrix<double> m = CreateRandomMatrix(sz,sz);
    const double determinant = CalcDeterminant(m);
    const double determinant_small = CalcDeterminantSmall(m);
    const double epsilon = 0.0001; //Rounding error
    assert(std::abs(determinant - determinant_small) < epsilon);
  }
  //Calculate larger and larger matrices their determinants
  //Notice that the computation takes longer and longer
  for (std::size_t sz = 0; sz!=10; ++sz)
  {
    const matrix<double> m = CreateRandomMatrix(sz,sz);
    const double determinant = CalcDeterminant(m);
    std::cout << determinant << '\n';
  }
}


/* Screen output:

1
0.95223
-0.326259
-0.0324396
-0.0537625
0.0014962
0.023256
0.0172371
-0.0193395
0.00152402

*/
