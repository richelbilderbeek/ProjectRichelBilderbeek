#ifdef _WIN32
#undef __STRICT_ANSI__
#endif

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

double CalcDeterminant(const boost::numeric::ublas::matrix<double>& m)
{
  assert(m.size1() == m.size2() && "Can only calculate the determinant of square matrices");
  switch(m.size1())
  {
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
      assert(!"Should not get here: unsupported matrix size");
      throw std::runtime_error("Unsupported matrix size");
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

const boost::numeric::ublas::matrix<double> CreateMatrix(
  const std::size_t n_rows,
  const std::size_t n_cols,
  const std::vector<double>& v)
{
  assert(n_rows * n_cols == v.size());
  boost::numeric::ublas::matrix<double> m(n_rows,n_cols);
  for (std::size_t row = 0; row!=n_rows; ++row)
  {
    for (std::size_t col = 0; col!=n_cols; ++col)
    {
      m(row,col) = v[ (col * n_rows) + row];
    }
  }
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

const boost::numeric::ublas::matrix<double> Inverse(
  const boost::numeric::ublas::matrix<double>& m)
{
  assert(m.size1() == m.size2() && "Can only calculate the inverse of square matrices");

  switch(m.size1())
  {
    case 1:
    {
      assert(m.size1() == 1 && m.size2() == 1 && "Only for 1x1 matrices");
      const double determinant = CalcDeterminant(m);
      assert(determinant != 0.0);
      assert(m(0,0) != 0.0 && "Cannot take the inverse of matrix [0]");
      boost::numeric::ublas::matrix<double> n(1,1);
      n(0,0) =  1.0 / determinant;
      return n;
    }
    case 2:
    {
      assert(m.size1() == 2 && m.size2() == 2 && "Only for 2x2 matrices");
      const double determinant = CalcDeterminant(m);
      assert(determinant != 0.0);
      const double a = m(0,0);
      const double b = m(0,1);
      const double c = m(1,0);
      const double d = m(1,1);
      boost::numeric::ublas::matrix<double> n(2,2);
      n(0,0) =  d / determinant;
      n(0,1) = -b / determinant;
      n(1,0) = -c / determinant;
      n(1,1) =  a / determinant;
      return n;
    }
    case 3:
    {
      assert(m.size1() == 3 && m.size2() == 3 && "Only for 3x3 matrices");
      const double determinant = CalcDeterminant(m);
      assert(determinant != 0.0);
      const double a = m(0,0);
      const double b = m(0,1);
      const double c = m(0,2);
      const double d = m(1,0);
      const double e = m(1,1);
      const double f = m(1,2);
      const double g = m(2,0);
      const double h = m(2,1);
      const double k = m(2,2);
      boost::numeric::ublas::matrix<double> n(3,3);
      const double new_a =  ((e*k)-(f*h)) / determinant;
      const double new_b = -((d*k)-(f*g)) / determinant;
      const double new_c =  ((d*h)-(e*g)) / determinant;
      const double new_d = -((b*k)-(c*h)) / determinant;
      const double new_e =  ((a*k)-(c*g)) / determinant;
      const double new_f = -((a*h)-(b*g)) / determinant;
      const double new_g =  ((b*f)-(c*e)) / determinant;
      const double new_h = -((a*f)-(c*d)) / determinant;
      const double new_k =  ((a*e)-(b*d)) / determinant;
      n(0,0) = new_a;
      n(1,0) = new_b;
      n(2,0) = new_c;
      n(0,1) = new_d;
      n(1,1) = new_e;
      n(2,1) = new_f;
      n(0,2) = new_g;
      n(1,2) = new_h;
      n(2,2) = new_k;
      return n;
    }
    default:
    {
      //Use blockwise inversion
      //Matrix::Chop returns a std::vector
      //[ A at [0]   B at [1] ]
      //[ C at [2]   D at [4] ]
      const std::vector<boost::numeric::ublas::matrix<double> > v = Chop(m);
      const boost::numeric::ublas::matrix<double>& a = v[0];
      assert(a.size1() == a.size2());
      const boost::numeric::ublas::matrix<double>  a_inv = Inverse(a);
      const boost::numeric::ublas::matrix<double>& b = v[1];
      const boost::numeric::ublas::matrix<double>& c = v[2];
      const boost::numeric::ublas::matrix<double>& d = v[3];
      const boost::numeric::ublas::matrix<double> term
        = d
        - prod(
            boost::numeric::ublas::matrix<double>(prod(c,a_inv)),
            b
          );
      const boost::numeric::ublas::matrix<double> term_inv = Inverse(term);
      const boost::numeric::ublas::matrix<double> new_a
        = a_inv
        + boost::numeric::ublas::matrix<double>(prod(
            boost::numeric::ublas::matrix<double>(prod(
              boost::numeric::ublas::matrix<double>(prod(
                boost::numeric::ublas::matrix<double>(prod(
                  a_inv,
                  b)),
                term_inv)),
             c)),
            a_inv));

      const boost::numeric::ublas::matrix<double> new_b
        =
        - boost::numeric::ublas::matrix<double>(prod(
            boost::numeric::ublas::matrix<double>(prod(
              a_inv,
              b)),
            term_inv));

      const boost::numeric::ublas::matrix<double> new_c
        =
        - boost::numeric::ublas::matrix<double>(prod(
            boost::numeric::ublas::matrix<double>(prod(
              term_inv,
              c)),
            a_inv));

      const boost::numeric::ublas::matrix<double> new_d = term_inv;
      const std::vector<boost::numeric::ublas::matrix<double> > w = { new_a, new_b, new_c, new_d };
      const boost::numeric::ublas::matrix<double> result = Unchop(w);
      return result;
    }
  }
}


int main()
{
  using boost::numeric::ublas::detail::equals;
  using boost::numeric::ublas::matrix;
  using boost::numeric::ublas::prod;
  using boost::numeric::ublas::vector;
  //Test CreateMatrix
  {
    // [1,4]
    // [2,5]
    // [3,6]
    const matrix<int> m = CreateMatrix(3,2, {1,2,3,4,5,6} );
    assert(m(0,0) == 1);
    assert(m(1,0) == 2);
    assert(m(2,0) == 3);
    assert(m(0,1) == 4);
    assert(m(1,1) == 5);
    assert(m(2,1) == 6);
  }
  //Test Chop on 3x3
  {
    //                     [ 1.0 ] | [ 2.0   3.0 ]
    // [ 1.0 2.0 3.0 ]     --------+--------------
    // [ 4.0 5.0 6.0 ]     [ 4.0 ] | [ 5.0   6.0 ]
    // [ 7.0 8.0 9.0 ] ->  [ 7.0 ] | [ 8.0   9.0 ]
    const matrix<double> m = CreateMatrix(3,3, {1.0,4.0,7.0,2.0,5.0,8.0,3.0,6.0,9.0} );
    assert(m(0,0) == 1.0); assert(m(0,1) == 2.0); assert(m(0,2) == 3.0);
    assert(m(1,0) == 4.0); assert(m(1,1) == 5.0); assert(m(1,2) == 6.0);
    assert(m(2,0) == 7.0); assert(m(2,1) == 8.0); assert(m(2,2) == 9.0);
    const std::vector<matrix<double> > n = Chop(m);
    assert(n.size() == 4);
    std::clog
      << "m   : " << m    << '\n'
      << "n[0]: " << n[0] << '\n'
      << "n[1]: " << n[1] << '\n'
      << "n[2]: " << n[2] << '\n'
      << "n[3]: " << n[3] << '\n';
    assert(n[0].size1() == 1);
    assert(n[0].size2() == 1);
    assert(n[1].size1() == 1);
    assert(n[1].size2() == 2);
    assert(n[2].size1() == 2);
    assert(n[2].size2() == 1);
    assert(n[3].size1() == 2);
    assert(n[3].size2() == 2);
    assert(n[0].size1() + n[2].size1() == m.size1());
    assert(n[1].size1() + n[3].size1() == m.size1());
    assert(n[0].size2() + n[1].size2() == m.size2());
    assert(n[2].size2() + n[3].size2() == m.size2());
  }
  //Test Chop on 5x5
  {
    const matrix<double> m = CreateMatrix(5,5,
      {
        1.0, 6.0,11.0,16.0,21.0,
        2.0, 7.0,12.0,17.0,22.0,
        3.0, 8.0,13.0,18.0,23.0,
        4.0, 9.0,14.0,19.0,24.0,
        5.0,10.0,15.0,20.0,25.0
      }
    );
    assert(m(0,0) ==  1.0); assert(m(0,1) ==  2.0); assert(m(0,2) ==  3.0); assert(m(0,3) ==  4.0); assert(m(0,4) ==  5.0);
    assert(m(1,0) ==  6.0); assert(m(1,1) ==  7.0); assert(m(1,2) ==  8.0); assert(m(1,3) ==  9.0); assert(m(1,4) == 10.0);
    assert(m(2,0) == 11.0); assert(m(2,1) == 12.0); assert(m(2,2) == 13.0); assert(m(2,3) == 14.0); assert(m(2,4) == 15.0);
    assert(m(3,0) == 16.0); assert(m(3,1) == 17.0); assert(m(3,2) == 18.0); assert(m(3,3) == 19.0); assert(m(3,4) == 20.0);
    assert(m(4,0) == 21.0); assert(m(4,1) == 22.0); assert(m(4,2) == 23.0); assert(m(4,3) == 24.0); assert(m(4,4) == 25.0);
    const std::vector<matrix<double> > n = Chop(m);
    assert(n.size() == 4);
    std::clog
      << "m   : " << m    << '\n'
      << "n[0]: " << n[0] << '\n'
      << "n[1]: " << n[1] << '\n'
      << "n[2]: " << n[2] << '\n'
      << "n[3]: " << n[3] << '\n';
    assert(n[0].size1() == 2);
    assert(n[0].size2() == 2);
    assert(n[1].size1() == 2);
    assert(n[1].size2() == 3);
    assert(n[2].size1() == 3);
    assert(n[2].size2() == 2);
    assert(n[3].size1() == 3);
    assert(n[3].size2() == 3);
    assert(n[0].size1() + n[2].size1() == m.size1());
    assert(n[1].size1() + n[3].size1() == m.size1());
    assert(n[0].size2() + n[1].size2() == m.size2());
    assert(n[2].size2() + n[3].size2() == m.size2());
  }
  //Test Unchop
  {
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
  //Test Inverse on 2x2 matrix
  {
    // [ 1.0 2.0 ] -1    [ -2.0   1.0 ]
    // [ 3.0 4.0 ]     = [  1.5  -0.5 ]
    const matrix<double> m = CreateMatrix(2,2, {1.0,3.0,2.0,4.0} );
    assert(m(0,0) == 1.0);
    assert(m(1,0) == 3.0);
    assert(m(0,1) == 2.0);
    assert(m(1,1) == 4.0);
    const matrix<double> n = Inverse(m);
    const double epsilon = 0.0000001; //Rounding error
    assert(n(0,0) > -2.0 - epsilon && n(0,0) < -2.0 + epsilon);
    assert(n(1,0) >  1.5 - epsilon && n(1,0) <  1.5 + epsilon);
    assert(n(0,1) >  1.0 - epsilon && n(0,1) <  1.0 + epsilon);
    assert(n(1,1) > -0.5 - epsilon && n(1,1) < -0.5 + epsilon);
    assert(prod(m,n)(0,0) > 1.0 - epsilon && prod(m,n)(0,0) < 1.0 + epsilon);
    assert(prod(m,n)(1,0) > 0.0 - epsilon && prod(m,n)(1,0) < 0.0 + epsilon);
    assert(prod(m,n)(0,1) > 0.0 - epsilon && prod(m,n)(0,1) < 0.0 + epsilon);
    assert(prod(m,n)(1,1) > 1.0 - epsilon && prod(m,n)(1,1) < 1.0 + epsilon);
  }


  {
    // [ 1.0 2.0 3.0] -1    [ -24.0   18.0   5.0]
    // [ 0.0 1.0 4.0]       [  20.0  -15.0  -4.0]
    // [ 5.0 6.0 0.0]     = [ - 5.0    4.0   1.0]
    const matrix<double> m = CreateMatrix(3,3, {1.0,0.0,5.0,2.0,1.0,6.0,3.0,4.0,0.0} );
    assert(m(0,0) == 1.0); assert(m(0,1) == 2.0); assert(m(0,2) == 3.0);
    assert(m(1,0) == 0.0); assert(m(1,1) == 1.0); assert(m(1,2) == 4.0);
    assert(m(2,0) == 5.0); assert(m(2,1) == 6.0); assert(m(2,2) == 0.0);
    const matrix<double> n = Inverse(m);
    const double epsilon = 0.0001; //Rounding error
    assert(n(0,0) > -24.0 - epsilon && n(0,0) < -24.0 + epsilon);
    assert(n(1,0) >  20.0 - epsilon && n(1,0) <  20.0 + epsilon);
    assert(n(2,0) > - 5.0 - epsilon && n(2,0) < - 5.0 + epsilon);
    assert(n(0,1) >  18.0 - epsilon && n(0,1) <  18.0 + epsilon);
    assert(n(1,1) > -15.0 - epsilon && n(1,1) < -15.0 + epsilon);
    assert(n(2,1) >   4.0 - epsilon && n(2,1) <   4.0 + epsilon);
    assert(n(0,2) >   5.0 - epsilon && n(0,2) <   5.0 + epsilon);
    assert(n(1,2) >  -4.0 - epsilon && n(1,2) < - 4.0 + epsilon);
    assert(n(2,2) >   1.0 - epsilon && n(2,2) <   1.0 + epsilon);
    const matrix<double> i = prod(m,n);
    assert(i(0,0) > 1.0 - epsilon && i(0,0) < 1.0 + epsilon);
    assert(i(1,0) > 0.0 - epsilon && i(1,0) < 0.0 + epsilon);
    assert(i(2,0) > 0.0 - epsilon && i(2,0) < 0.0 + epsilon);
    assert(i(0,1) > 0.0 - epsilon && i(0,1) < 0.0 + epsilon);
    assert(i(1,1) > 1.0 - epsilon && i(1,1) < 1.0 + epsilon);
    assert(i(2,1) > 0.0 - epsilon && i(2,1) < 0.0 + epsilon);
    assert(i(0,2) > 0.0 - epsilon && i(0,2) < 0.0 + epsilon);
    assert(i(1,2) > 0.0 - epsilon && i(1,2) < 0.0 + epsilon);
    assert(i(2,2) > 1.0 - epsilon && i(2,2) < 1.0 + epsilon);
  }
  //Test Inverse on 3x3 matrix
  {
    // [ 1.0 2.0 3.0] -1
    // [ 4.0 4.0 6.0]
    // [ 7.0 8.0 9.0]
    // Note: cannot make the center value equal to 5.0, as this makes
    // the matrix un-invertible (the determinant becomes equal to zero)
    const matrix<double> m = CreateMatrix(3,3, {1.0,4.0,7.0,2.0,4.0,8.0,3.0,6.0,9.0} );
    assert(m(0,0) == 1.0); assert(m(0,1) == 2.0); assert(m(0,2) == 3.0);
    assert(m(1,0) == 4.0); assert(m(1,1) == 4.0); assert(m(1,2) == 6.0);
    assert(m(2,0) == 7.0); assert(m(2,1) == 8.0); assert(m(2,2) == 9.0);
    const matrix<double> n = Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = prod(m,n);
    assert(i(0,0) > 1.0 - epsilon && i(0,0) < 1.0 + epsilon);
    assert(i(1,0) > 0.0 - epsilon && i(1,0) < 0.0 + epsilon);
    assert(i(2,0) > 0.0 - epsilon && i(2,0) < 0.0 + epsilon);
    assert(i(0,1) > 0.0 - epsilon && i(0,1) < 0.0 + epsilon);
    assert(i(1,1) > 1.0 - epsilon && i(1,1) < 1.0 + epsilon);
    assert(i(2,1) > 0.0 - epsilon && i(2,1) < 0.0 + epsilon);
    assert(i(0,2) > 0.0 - epsilon && i(0,2) < 0.0 + epsilon);
    assert(i(1,2) > 0.0 - epsilon && i(1,2) < 0.0 + epsilon);
    assert(i(2,2) > 1.0 - epsilon && i(2,2) < 1.0 + epsilon);
  }
  //Test Inverse on 4x4 matrix
  {
    const matrix<double> m = CreateRandomMatrix(4,4);
    const matrix<double> n = Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = prod(m,n);
    //Test if i is identity matrix
    assert(i(0,0) > 1.0 - epsilon && i(0,0) < 1.0 + epsilon);
    assert(i(1,0) > 0.0 - epsilon && i(1,0) < 0.0 + epsilon);
    assert(i(2,0) > 0.0 - epsilon && i(2,0) < 0.0 + epsilon);
    assert(i(3,0) > 0.0 - epsilon && i(3,0) < 0.0 + epsilon);
    assert(i(0,1) > 0.0 - epsilon && i(0,1) < 0.0 + epsilon);
    assert(i(1,1) > 1.0 - epsilon && i(1,1) < 1.0 + epsilon);
    assert(i(2,1) > 0.0 - epsilon && i(2,1) < 0.0 + epsilon);
    assert(i(3,1) > 0.0 - epsilon && i(3,1) < 0.0 + epsilon);
    assert(i(0,2) > 0.0 - epsilon && i(0,2) < 0.0 + epsilon);
    assert(i(1,2) > 0.0 - epsilon && i(1,2) < 0.0 + epsilon);
    assert(i(2,2) > 1.0 - epsilon && i(2,2) < 1.0 + epsilon);
    assert(i(3,2) > 0.0 - epsilon && i(3,2) < 0.0 + epsilon);
    assert(i(0,3) > 0.0 - epsilon && i(0,3) < 0.0 + epsilon);
    assert(i(1,3) > 0.0 - epsilon && i(1,3) < 0.0 + epsilon);
    assert(i(2,3) > 0.0 - epsilon && i(2,3) < 0.0 + epsilon);
    assert(i(3,3) > 1.0 - epsilon && i(3,3) < 1.0 + epsilon);
  }
  //Test Inverse on bigger matrices
  for (std::size_t sz = 5; sz!=20; ++sz)
  {
    const matrix<double> m = CreateRandomMatrix(sz,sz);
    const matrix<double> n = Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = prod(m,n);
    //Test if i is identity matrix
    for (std::size_t y = 0; y!=sz; ++y)
    {
      for (std::size_t x = 0; x!=sz; ++x)
      {
        assert(
             (x == y && i(y,x) > 1.0 - epsilon && i(y,x) < 1.0 + epsilon)
          || (x != y && i(y,x) > 0.0 - epsilon && i(y,x) < 0.0 + epsilon)
        );
      }
    }
  }
}

/* Screen output

m   : [3,3]((1,2,3),(4,5,6),(7,8,9))
n[0]: [1,1]((1))
n[1]: [1,2]((2,3))
n[2]: [2,1]((4),(7))
n[3]: [2,2]((5,6),(8,9))
m   : [5,5]((1,2,3,4,5),(6,7,8,9,10),(11,12,13,14,15),(16,17,18,19,20),(21,22,23,24,25))
n[0]: [2,2]((1,2),(6,7))
n[1]: [2,3]((3,4,5),(8,9,10))
n[2]: [3,2]((11,12),(16,17),(21,22))
n[3]: [3,3]((13,14,15),(18,19,20),(23,24,25))

*/
