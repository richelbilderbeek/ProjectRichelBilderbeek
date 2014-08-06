//---------------------------------------------------------------------------
/*
Matrix, functions working on vectors and matrices
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppMatrix.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "matrix.h"

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/blas.hpp> //boost::numeric::ublas::equals
#pragma GCC diagnostic pop

#include "ribi_random.h"
#include "testtimer.h"
#include "trace.h"

double ribi::Matrix::CalcDeterminant(boost::numeric::ublas::matrix<double> m)
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

const std::vector<boost::numeric::ublas::matrix<double> > ribi::Matrix::Chop(
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

boost::numeric::ublas::matrix<double> ribi::Matrix::CreateMatrix(
  const std::size_t n_rows,
  const std::size_t n_cols,
  const std::vector<double>& v) noexcept
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

boost::numeric::ublas::matrix<double> ribi::Matrix::CreateRandomMatrix(
  const std::size_t n_rows, const std::size_t n_cols) noexcept
{
  boost::numeric::ublas::matrix<double> m(n_rows,n_cols);
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      m(row,col) = Random().GetFraction();
    }
  }
  return m;
}

boost::numeric::ublas::vector<double> ribi::Matrix::CreateVector(
  const std::vector<double>& v) noexcept
{
  boost::numeric::ublas::vector<double> w(v.size());
  std::copy(v.begin(),v.end(),w.begin());
  return w;
}

const boost::numeric::ublas::vector<int> ribi::Matrix::CreateVectorInt(
  const std::vector<int>& v) noexcept
{
  boost::numeric::ublas::vector<int> w(v.size());
  std::copy(v.begin(),v.end(),w.begin());
  return w;
}

std::string ribi::Matrix::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::Matrix::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version",
    "2013-06-11: version 1.1: fixed bugs in MatricesAreEqual and MatricesAreAboutEqual",
    "2013-06-27: version 1.2: added tests, renamed VectorsAreEqual to VectorsDoubleAreEqual and VectorsIntAreEqual"
    "2013-09-16: version 1.3: noexcept"
  };
}

const boost::numeric::ublas::matrix<double> ribi::Matrix::Inverse(
  const boost::numeric::ublas::matrix<double>& m)
{
  assert(m.size1() == m.size2() && "Can only calculate the inverse of square matrices");

  switch(m.size1())
  {
    case 0:
    {
      return m;
    }
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
      //ribi::Matrix::Chop returns a std::vector
      //[ A at [0]   B at [1] ]
      //[ C at [2]   D at [4] ]
      assert(m.size1() > 3);
      assert(m.size2() > 3);
      const std::vector<boost::numeric::ublas::matrix<double> > v = Chop(m);
      const boost::numeric::ublas::matrix<double>& a = v[0];
      assert(a.size1() == a.size2());
      const boost::numeric::ublas::matrix<double>  a_inv = Inverse(a);
      const boost::numeric::ublas::matrix<double>& b = v[1];
      const boost::numeric::ublas::matrix<double>& c = v[2];
      const boost::numeric::ublas::matrix<double>& d = v[3];
      const boost::numeric::ublas::matrix<double> term
        = d
        - ribi::Matrix::Prod(
            boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(c,a_inv)),
            b
          );
      assert(term.size1() == term.size2());
      const boost::numeric::ublas::matrix<double> term_inv = Inverse(term);
      const boost::numeric::ublas::matrix<double> new_a
        = a_inv
        + boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
            boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
              boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
                boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
                  a_inv,
                  b)),
                term_inv)),
             c)),
            a_inv));

      const boost::numeric::ublas::matrix<double> new_b
        =
        - boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
            boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
              a_inv,
              b)),
            term_inv));

      const boost::numeric::ublas::matrix<double> new_c
        =
        - boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
            boost::numeric::ublas::matrix<double>(ribi::Matrix::Prod(
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


bool ribi::Matrix::IsAboutEqual(const double a, const double b) noexcept
{
  const double epsilon = 0.000001; //Rounding error
  return a - epsilon < b && a + epsilon > b;
}

const boost::numeric::ublas::matrix<double> ribi::Matrix::Power(
  const boost::numeric::ublas::matrix<double>& m,
  const int exponent)
{
  assert(exponent >= 0 && "Can only take the power of matrices with a positive exponent");
  assert(m.size1() == m.size2() && "Can only take the power of square matrices");
  const std::size_t sz = m.size1();
  if (exponent == 0) return boost::numeric::ublas::identity_matrix<double>(sz);
  if (exponent == 1) return m;
  boost::numeric::ublas::matrix<double> n(m);
  for (int i=1; i!=exponent; ++i)
  {
    n = ribi::Matrix::Prod(n,m);
  }
  return n;
}

bool ribi::Matrix::MatricesAreAboutEqual(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::matrix<double>& b) noexcept
{
  if (a.size1() != b.size1()) return false;
  if (a.size2() != b.size2()) return false;
  //return std::equal(a.begin1(),a.end1(),b.begin1(),&ribi::Matrix::IsAboutEqual); //DON'T USE STD::EQUAL!

  assert(a.size1() == b.size1());
  assert(a.size2() == b.size2());

  const std::size_t n_rows = a.size1();
  const std::size_t n_cols = a.size2();
  for (std::size_t row = 0; row != n_rows; ++row)
  {
    for (std::size_t col = 0; col != n_cols; ++col)
    {
      if (!IsAboutEqual(a(row,col),b(row,col))) return false;
    }
  }
  return true;
}

bool ribi::Matrix::MatricesAreEqual(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::matrix<double>& b) noexcept
{
  if ( a.size1() != b.size1()
    || a.size2() != b.size2()) return false;
  //const bool is_equal = std::equal(a.begin1(),a.end1(),b.begin1()); //DON'T USE STD::EQUAL!

  assert(a.size1() == b.size1());
  assert(a.size2() == b.size2());

  const std::size_t n_rows = a.size1();
  const std::size_t n_cols = a.size2();
  for (std::size_t row = 0; row != n_rows; ++row)
  {
    for (std::size_t col = 0; col != n_cols; ++col)
    {
      if (a(row,col) != b(row,col)) return false;
    }
  }
  return true;
}

bool ribi::Matrix::MatrixIsAboutEqual(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::matrix<double>& b) noexcept
{
  TRACE("Deprecated naming");
  return MatricesAreAboutEqual(a,b);
}

const boost::numeric::ublas::matrix<double> ribi::Matrix::MultiProd(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::matrix<double>& b,
  const boost::numeric::ublas::matrix<double>& c)
{
  return Prod(Prod(a,b),c);
}

const boost::numeric::ublas::matrix<double> ribi::Matrix::Prod(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::matrix<double>& b
  )
{
  assert(a.size2() == b.size1() && "A's width must be B's height");
  return boost::numeric::ublas::prod(a,b);
}

const boost::numeric::ublas::vector<double> ribi::Matrix::Prod(
  const boost::numeric::ublas::matrix<double>& a,
  const boost::numeric::ublas::vector<double>& b
  )
{
  assert(a.size2() == b.size() && "A's width must be B's height");
  return boost::numeric::ublas::prod(a,b);
}

const boost::numeric::ublas::matrix<double> ribi::Matrix::SimplifyMatrixOfMatrix(
  const boost::numeric::ublas::matrix<boost::numeric::ublas::matrix<double> >& m)
{
  // [ [A B]  [I J] ]
  // [ [C D]  [K L] ]    [ A B I J]
  // [              ]    [ C D K L]
  // [ [E F]  [M N] ]    [ E F M N]
  // [ [G H]  [O P] ] -> [ G H O P]
  //assert(m.size1() > 0);
  //assert(m.size2() > 0);
  //
  const int n_sub_rows = boost::numeric_cast<int>(m.size1());
  const int n_sub_cols = boost::numeric_cast<int>(m.size2());
  const int sub_rows   = n_sub_rows != 0 && n_sub_cols != 0 ? boost::numeric_cast<int>(m(0,0).size1()) : 0;
  const int sub_cols   = n_sub_cols != 0 && n_sub_cols != 0 ? boost::numeric_cast<int>(m(0,0).size2()) : 0;
  boost::numeric::ublas::matrix<double> v(n_sub_rows * sub_rows, n_sub_cols * sub_cols);
  for (int sub_row=0; sub_row!=n_sub_rows; ++sub_row)
  {
    for (int sub_col=0; sub_col!=n_sub_cols; ++sub_col)
    {
      assert(sub_row < boost::numeric_cast<int>(m.size1()));
      assert(sub_col < boost::numeric_cast<int>(m.size2()));
      const boost::numeric::ublas::matrix<double>& sub = m(sub_row,sub_col);
      const int offset_x = sub_col * sub_cols;
      const int offset_y = sub_row * sub_rows;
      for (int row=0; row!=sub_rows; ++row)
      {
        for (int col=0; col!=sub_cols; ++col)
        {
          assert(offset_y + row < boost::numeric_cast<int>(v.size1()));
          assert(offset_x + col < boost::numeric_cast<int>(v.size2()));
          assert(row < boost::numeric_cast<int>(sub.size1()));
          assert(col < boost::numeric_cast<int>(sub.size2()));
          v(offset_y + row,offset_x + col) = sub(row,col);
        }
      }
    }
  }
  //
  return v;
}


const boost::numeric::ublas::matrix<double> ribi::Matrix::SimplifyVectorOfMatrix(
  const boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> >& m)
{
  // [ [A B] ]
  // [ [C D] ]    [ A B ]
  // [       ]    [ C D ]
  // [ [E F] ]    [ E F ]
  // [ [G H] ] -> [ G H ]

  assert(!m.empty());
  const int n_subs   = boost::numeric_cast<int>(m.size());
  const int sub_rows = boost::numeric_cast<int>(m[0].size1());
  const int sub_cols = boost::numeric_cast<int>(m[0].size2());
  boost::numeric::ublas::matrix<double> v(n_subs * sub_rows, sub_cols);
  for (int sub_index=0; sub_index!=n_subs; ++sub_index)
  {
    assert(sub_index < boost::numeric_cast<int>(m.size()));
    const boost::numeric::ublas::matrix<double>& sub = m[sub_index];
    const int offset_x = 0;
    const int offset_y = sub_index * sub_rows;
    for (int row=0; row!=sub_rows; ++row)
    {
      for (int col=0; col!=sub_cols; ++col)
      {
        assert(offset_y + row < boost::numeric_cast<int>(v.size1()));
        assert(offset_x + col < boost::numeric_cast<int>(v.size2()));
        assert(row < boost::numeric_cast<int>(sub.size1()));
        assert(col < boost::numeric_cast<int>(sub.size2()));
        v(offset_y + row,offset_x + col) = sub(row,col);
      }
    }
  }
  return v;
}


const boost::numeric::ublas::vector<double> ribi::Matrix::SimplifyVectorOfVector(
  const boost::numeric::ublas::vector<boost::numeric::ublas::vector<double> >& m)
{
  // [ [A] ]
  // [ [B] ]    [ A ]
  // [     ]    [ B ]
  // [ [C] ]    [ C ]
  // [ [D] ] -> [ D ]
  //assert(!m.empty());
  const int n_subs = boost::numeric_cast<int>(m.size());
  const int subs_sz = n_subs > 0 ? boost::numeric_cast<int>(m[0].size()) : 0;
  boost::numeric::ublas::vector<double> v(n_subs * subs_sz);
  for (int i=0; i!=n_subs; ++i)
  {
    assert(i < boost::numeric_cast<int>(m.size()));
    const boost::numeric::ublas::vector<double>& sub = m[i];
    std::copy(sub.begin(),sub.end(),v.begin() + (i * subs_sz));
  }
  return v;

}


#ifndef NDEBUG
void ribi::Matrix::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //
  const TestTimer test_timer(__func__,__FILE__,1.0);
  using boost::numeric::ublas::detail::equals;
  using boost::numeric::ublas::matrix;
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
  //Simplify vector of vector
  {
    /// [ [A] ]
    /// [ [B] ]    [ A ]
    /// [     ]    [ B ]
    /// [ [C] ]    [ C ]
    /// [ [D] ] -> [ D ]
    boost::numeric::ublas::vector<boost::numeric::ublas::vector<double> > v(2);
    v[0] = CreateVector( { 1.0, 2.0 } );
    v[1] = CreateVector( { 3.0, 4.0 } );
    const boost::numeric::ublas::vector<double> w
      = SimplifyVectorOfVector(v);
    assert(w.size() == 4);
    assert(VectorsAreAboutEqual(w, CreateVector( { 1.0, 2.0, 3.0, 4.0 } )));
  }
  {
    ///Simplify a structure
    /// [ [A B] ]
    /// [ [C D] ]    [ A B ]
    /// [       ]    [ C D ]
    /// [ [E F] ]    [ E F ]
    /// [ [G H] ] -> [ G H ]
    boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> > v(2);
    v[0] = CreateMatrix(2,2, {1.0, 3.0, 2.0, 4.0} );
    v[1] = CreateMatrix(2,2, {5.0, 7.0, 6.0, 8.0} );
    const boost::numeric::ublas::matrix<double> w
      = SimplifyVectorOfMatrix(v);
    assert(w.size1() == 4);
    assert(w.size2() == 2);
    assert(MatricesAreAboutEqual(w, CreateMatrix(4,2, { 1.0, 3.0, 5.0, 7.0, 2.0, 4.0, 6.0, 8.0 } )));
  }
  {
    //Simplify a structure
    // [ [A B]  [I J] ]
    // [ [C D]  [K L] ]    [ A B I J]
    // [              ]    [ C D K L]
    // [ [E F]  [M N] ]    [ E F M N]
    // [ [G H]  [O P] ] -> [ G H O P]

    // [ [ 1  2]  [ 3  4] ]
    // [ [ 5  6]  [ 7  8] ]    [ A B I J]
    // [                  ]    [ C D K L]
    // [ [ 9 10]  [11 12] ]    [ E F M N]
    // [ [13 14]  [15 16] ] -> [ G H O P]
    boost::numeric::ublas::matrix<boost::numeric::ublas::matrix<double> > v(2,2);
    v(0,0) = CreateMatrix(2,2, { 1.0,  5.0,  2.0,  6.0} );
    v(1,0) = CreateMatrix(2,2, { 9.0, 13.0, 10.0, 14.0} );
    v(0,1) = CreateMatrix(2,2, { 3.0,  7.0,  4.0,  8.0} );
    v(1,1) = CreateMatrix(2,2, {11.0, 15.0, 12.0, 16.0} );
    const boost::numeric::ublas::matrix<double> w
      = SimplifyMatrixOfMatrix(v);
    assert(w.size1() == 4);
    assert(w.size2() == 4);
    const boost::numeric::ublas::matrix<double> expected
      = CreateMatrix(4,4,
      {
        1.0, 5.0,  9.0, 13.0,
        2.0, 6.0, 10.0, 14.0,
        3.0, 7.0, 11.0, 15.0,
        4.0, 8.0, 12.0, 16.0
      } );
    if (!MatricesAreAboutEqual(w,expected))
    {
      std::cerr
        << "w: " << w << '\n'
        << "e: " << expected << '\n';
    }
    assert(MatricesAreAboutEqual(w,expected));
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
  //Test VectorsAreAboutEqual
  {
    const vector<double> m = CreateVector( {1.0,3.0,2.0,4.0} );
    assert(VectorsAreAboutEqual(m,m));
    vector<double> n(m);
    n *= 3.0;
    n /= 6.0;
    n *= 2.0;
    assert(VectorsAreAboutEqual(m,n));
  }
  //Test Power
  {
    const int sz = 2;
    const matrix<double> m = CreateMatrix(sz,sz, {1.0,3.0,2.0,4.0} );
    const matrix<double> expected_0 = boost::numeric::ublas::identity_matrix<double>(sz);
    const matrix<double> expected_1 = m;
    const matrix<double> expected_2 = CreateMatrix(sz,sz, {7.0,15.0,10.0,22.0} );
    assert(ribi::Matrix::MatricesAreAboutEqual(m,m));
    assert(ribi::Matrix::MatricesAreAboutEqual(Power(m,0),expected_0));
    assert(ribi::Matrix::MatricesAreAboutEqual(Power(m,1),expected_1));
    assert(ribi::Matrix::MatricesAreAboutEqual(Power(m,2),expected_2));
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
        const matrix<double> m = ribi::Matrix::CreateRandomMatrix(n_rows,n_cols);

        //Assume it is found identical to itself
        assert(equals(m,m,epsilon,epsilon));

        //Chop and unchop the input matrix
        const matrix<double> n = ribi::Matrix::Unchop(Chop(m));

        //Assume input matrix and result are identical
        assert(equals(m,n,epsilon,epsilon));
      }
    }
  }
  //Test Inverse on 2x2 matrix
  {
    // [ 1.0 2.0 ] -1    [ -2.0   1.0 ]
    // [ 3.0 4.0 ]     = [  1.5  -0.5 ]
    const matrix<double> m = ribi::Matrix::CreateMatrix(2,2, {1.0,3.0,2.0,4.0} );
    assert(m(0,0) == 1.0);
    assert(m(1,0) == 3.0);
    assert(m(0,1) == 2.0);
    assert(m(1,1) == 4.0);
    const matrix<double> n = ribi::Matrix::Inverse(m);
    const double epsilon = 0.0000001; //Rounding error
    assert(n(0,0) > -2.0 - epsilon && n(0,0) < -2.0 + epsilon);
    assert(n(1,0) >  1.5 - epsilon && n(1,0) <  1.5 + epsilon);
    assert(n(0,1) >  1.0 - epsilon && n(0,1) <  1.0 + epsilon);
    assert(n(1,1) > -0.5 - epsilon && n(1,1) < -0.5 + epsilon);
    assert(ribi::Matrix::Prod(m,n)(0,0) > 1.0 - epsilon && ribi::Matrix::Prod(m,n)(0,0) < 1.0 + epsilon);
    assert(ribi::Matrix::Prod(m,n)(1,0) > 0.0 - epsilon && ribi::Matrix::Prod(m,n)(1,0) < 0.0 + epsilon);
    assert(ribi::Matrix::Prod(m,n)(0,1) > 0.0 - epsilon && ribi::Matrix::Prod(m,n)(0,1) < 0.0 + epsilon);
    assert(ribi::Matrix::Prod(m,n)(1,1) > 1.0 - epsilon && ribi::Matrix::Prod(m,n)(1,1) < 1.0 + epsilon);
  }


  {
    // [ 1.0 2.0 3.0] -1    [ -24.0   18.0   5.0]
    // [ 0.0 1.0 4.0]       [  20.0  -15.0  -4.0]
    // [ 5.0 6.0 0.0]     = [ - 5.0    4.0   1.0]
    const matrix<double> m = ribi::Matrix::CreateMatrix(3,3, {1.0,0.0,5.0,2.0,1.0,6.0,3.0,4.0,0.0} );
    assert(m(0,0) == 1.0); assert(m(0,1) == 2.0); assert(m(0,2) == 3.0);
    assert(m(1,0) == 0.0); assert(m(1,1) == 1.0); assert(m(1,2) == 4.0);
    assert(m(2,0) == 5.0); assert(m(2,1) == 6.0); assert(m(2,2) == 0.0);
    const matrix<double> n = ribi::Matrix::Inverse(m);
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
    const matrix<double> i = ribi::Matrix::Prod(m,n);
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
    const matrix<double> m = ribi::Matrix::CreateMatrix(3,3, {1.0,4.0,7.0,2.0,4.0,8.0,3.0,6.0,9.0} );
    assert(m(0,0) == 1.0); assert(m(0,1) == 2.0); assert(m(0,2) == 3.0);
    assert(m(1,0) == 4.0); assert(m(1,1) == 4.0); assert(m(1,2) == 6.0);
    assert(m(2,0) == 7.0); assert(m(2,1) == 8.0); assert(m(2,2) == 9.0);
    const matrix<double> n = ribi::Matrix::Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = ribi::Matrix::Prod(m,n);
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
    const matrix<double> m = ribi::Matrix::CreateRandomMatrix(4,4);
    const matrix<double> n = ribi::Matrix::Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = ribi::Matrix::Prod(m,n);
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
  //TRACE("Test Inverse on bigger matrices");
  for (std::size_t sz = 5; sz!=20; ++sz)
  {
    const matrix<double> m = ribi::Matrix::CreateRandomMatrix(sz,sz);
    const matrix<double> n = ribi::Matrix::Inverse(m);
    const double epsilon = 0.00001; //Rounding error
    const matrix<double> i = ribi::Matrix::Prod(m,n);
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
  //TRACE("Test MatricesAreEqual");
  {
    {
      const auto a = boost::numeric::ublas::zero_matrix<double>(2,3);
      const auto b = boost::numeric::ublas::zero_matrix<double>(3,2);
      const auto c = boost::numeric::ublas::zero_matrix<double>(2,2);
      const auto d = boost::numeric::ublas::zero_matrix<double>(3,3);
      assert( MatricesAreEqual(a,a));
      assert( MatricesAreEqual(b,b));
      assert( MatricesAreEqual(c,c));
      assert( MatricesAreEqual(d,d));
      assert(!MatricesAreEqual(a,b));
      assert(!MatricesAreEqual(a,c));
      assert(!MatricesAreEqual(a,d));
      assert(!MatricesAreEqual(b,c));
      assert(!MatricesAreEqual(b,d));
      assert(!MatricesAreEqual(c,d));
    }
    {
      const auto a = CreateMatrix(2,2, { 1.0,0.0,0.0,1.0 } );
      auto b = a;
      assert(MatricesAreEqual(a,b));
      assert(MatricesAreAboutEqual(a,b));
      b(1,1) = 0.0;
      assert(!MatricesAreEqual(a,b));
      assert(!MatricesAreAboutEqual(a,b));
      b(1,1) = 1.0;
      assert(MatricesAreEqual(a,b));
      assert(MatricesAreAboutEqual(a,b));
    }
  }
  //TRACE("Test VectorsAreEqual (int)");
  {
    {
      const auto a = boost::numeric::ublas::vector<int>(2,0);
      const auto b = boost::numeric::ublas::vector<int>(3,0);
      assert( VectorsIntAreEqual(a,a));
      assert( VectorsIntAreEqual(b,b));
      assert(!VectorsIntAreEqual(a,b));
      assert(!VectorsIntAreEqual(b,a));
    }
    {
      const auto a = CreateVector( { 1,2,3 } );
      auto b = a;
      assert(VectorsIntAreEqual(a,a));
      assert(VectorsIntAreEqual(a,b));
      assert(VectorsIntAreEqual(b,a));
      assert(VectorsIntAreEqual(b,b));
      b(1) = 0;
      assert( VectorsIntAreEqual(a,a));
      assert(!VectorsIntAreEqual(a,b));
      assert(!VectorsIntAreEqual(b,a));
      assert( VectorsIntAreEqual(b,b));
      b(1) = 2;
      assert(VectorsIntAreEqual(a,a));
      assert(VectorsIntAreEqual(a,b));
      assert(VectorsIntAreEqual(b,a));
      assert(VectorsIntAreEqual(b,b));
    }
  }
  //TRACE("Test VectorsAreEqual (double)");
  {
    {
      const auto a = boost::numeric::ublas::zero_vector<double>(2);
      const auto b = boost::numeric::ublas::zero_vector<double>(3);
      assert( VectorsDoubleAreEqual(a,a));
      assert( VectorsDoubleAreEqual(b,b));
      assert(!VectorsDoubleAreEqual(a,b));
      assert(!VectorsDoubleAreEqual(b,a));
    }
    {
      const auto a = CreateVector( { 1.1,2.2,3.3 } );
      auto b = a;
      assert(VectorsDoubleAreEqual(a,b));
      assert(VectorsAreAboutEqual(a,b));
      b(1) = 0.0;
      assert(!VectorsDoubleAreEqual(a,b));
      assert(!VectorsAreAboutEqual(a,b));
      b(1) = 2.2;
      assert(VectorsDoubleAreEqual(a,b));
      assert(VectorsAreAboutEqual(a,b));
    }
  }
}
#endif

const boost::numeric::ublas::matrix<double> ribi::Matrix::Unchop(
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

bool ribi::Matrix::VectorIsAboutEqual(
  const boost::numeric::ublas::vector<double>& a,
  const boost::numeric::ublas::vector<double>& b) noexcept
{
  TRACE("Deprecated naming");
  return VectorsAreAboutEqual(a,b);
}

bool ribi::Matrix::VectorsAreAboutEqual(
  const boost::numeric::ublas::vector<double>& a,
  const boost::numeric::ublas::vector<double>& b) noexcept
{
  if (a.size() != b.size()) return false;
  return std::equal(a.begin(),a.end(),b.begin(),&ribi::Matrix::IsAboutEqual);
}

bool ribi::Matrix::VectorsDoubleAreEqual(
  const boost::numeric::ublas::vector<double>& a,
  const boost::numeric::ublas::vector<double>& b) noexcept
{
  if (a.size() != b.size()) return false;
  return std::equal(a.begin(),a.end(),b.begin());
}

bool ribi::Matrix::VectorsIntAreEqual(
  const boost::numeric::ublas::vector<int>& a,
  const boost::numeric::ublas::vector<int>& b) noexcept
{
  if (a.size() != b.size()) return false;
  return std::equal(a.begin(),a.end(),b.begin());
}
