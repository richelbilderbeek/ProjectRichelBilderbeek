#ifdef _WIN32
#undef __STRICT_ANSI__
#endif

#include <climits>
#include <vector>

#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/detail/matrix_assign.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

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

///Unchop merges the 4 std::vector of sub-matrices produced by Chop
const boost::numeric::ublas::matrix<double> Unchop(
  const std::vector<boost::numeric::ublas::matrix<double> >& v)
{
  //Chop returns a std::vector of sub-matrices
  //[ A at [0]   B at [1] ]
  //[ C at [2]   D at [4] ]

  using boost::numeric::ublas::range;
  using boost::numeric::ublas::matrix;
  using boost::numeric::ublas::matrix_range;
  assert(v.size() == 4);
  assert(v[0].size1() == v[1].size1());
  assert(v[2].size1() == v[3].size1());
  assert(v[0].size2() == v[2].size2());
  assert(v[1].size2() == v[3].size2());
  boost::numeric::ublas::matrix<double> m(v[0].size1() + v[2].size1(),v[0].size2() + v[1].size2());
  for (int quadrant=0; quadrant!=4; ++quadrant)
  {
    const boost::numeric::ublas::matrix<double>& w = v[quadrant];
    const std::size_t n_rows = v[quadrant].size1();
    const std::size_t n_cols = v[quadrant].size2();
    const int offset_x = quadrant % 2 ? v[0].size2() : 0;
    const int offset_y = quadrant / 2 ? v[0].size1() : 0;
    for (std::size_t row=0; row!=n_rows; ++row)
    {
      for (std::size_t col=0; col!=n_cols; ++col)
      {
        m(offset_y + row, offset_x + col) = w(row,col);
      }
    }
  }

  assert(v[0].size1() + v[2].size1() == m.size1());
  assert(v[1].size1() + v[3].size1() == m.size1());
  assert(v[0].size2() + v[1].size2() == m.size2());
  assert(v[2].size2() + v[3].size2() == m.size2());

  return m;
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
  using boost::numeric::ublas::detail::equals;
  using boost::numeric::ublas::matrix;

  //Check 0x0 to and including 9x9 matrices
  for (std::size_t n_rows = 0; n_rows!=10; ++n_rows)
  {
    for (std::size_t n_cols = 0; n_cols!=10; ++n_cols)
    {
      //Epsilon is more or less the smallest round-off error
      const double epsilon = std::numeric_limits<double>::epsilon();

      //Create a random matrix
      const matrix<double> m = CreateRandomMatrix(n_rows,n_cols);

      //Assume it is found identical to itself
      assert(equals(m,m,epsilon,epsilon));

      //Chop and unchop the input matrix
      const matrix<double> n = Unchop(Chop(m));

      //Assume input matrix and result are identical
      assert(equals(m,n,epsilon,epsilon));
    }
  }
}
