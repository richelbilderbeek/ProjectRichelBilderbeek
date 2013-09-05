//---------------------------------------------------------------------------
/*
Matrix, functions working on vectors and matrices
Copyright (C) 2013 Richel Bilderbeek

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
#ifndef MATRIX_H
#define MATRIX_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Helper class for matrix operations
struct Matrix
{
  ///Calculate the determinant
  //Adapted from the code Maik Beckmann posted at
  //  http://boost.2283326.n4.nabble.com/How-to-compute-determinant-td2710896.html
  static double CalcDeterminant(boost::numeric::ublas::matrix<double> m);

  ///Chop returns a std::vector of sub-matrices
  ///[ A at [0]   B at [1] ]
  ///[ C at [2]   D at [4] ]
  static const std::vector<boost::numeric::ublas::matrix<double> > Chop(
    const boost::numeric::ublas::matrix<double>& m);

  ///Create a n_rows x n_cols sized matrix from a std::vector,
  ///used for easy initialization
  static const boost::numeric::ublas::matrix<double> CreateMatrix(
    const std::size_t n_rows,
    const std::size_t n_cols,
    const std::vector<double>& v);

  ///Create a random-filled matrix
  static const boost::numeric::ublas::matrix<double> CreateRandomMatrix(
    const std::size_t n_rows, const std::size_t n_cols);

  ///Create a uBLAS vector from a std::vector,
  ///used for easy initialization
  static const boost::numeric::ublas::vector<double> CreateVector(const std::vector<double>& v);

  ///Create a uBLAS vector from a std::vector,
  ///used for easy initialization
  static const boost::numeric::ublas::vector<int> CreateVectorInt(const std::vector<int>& v);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Calculate the inverse of a matrix
  static const boost::numeric::ublas::matrix<double> Inverse(
    const boost::numeric::ublas::matrix<double>& m);

  ///Check if two doubles are about equal
  static bool IsAboutEqual(const double a, const double b);

  ///Check if two matrices are equal
  ///This is only suitable to test for exact copies.
  ///Use MatricesAreAboutEqual to allow for a
  ///small difference between the matrix elements.
  static bool MatricesAreEqual(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::matrix<double>& b);

  ///Check if two matrices are about equal
  static bool MatricesAreAboutEqual(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::matrix<double>& b);

  ///Check if two matrices are about equal
  static bool MatrixIsAboutEqual(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::matrix<double>& b);

  ///Calculates the matrix product a * b * c
  static const boost::numeric::ublas::matrix<double> MultiProd(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::matrix<double>& b,
    const boost::numeric::ublas::matrix<double>& c
    );

  ///Take the power of a square matrix
  static const boost::numeric::ublas::matrix<double> Power(
    const boost::numeric::ublas::matrix<double>& m,
    const int exponent);

  ///Calculates the matrix product a * b
  ///with checking for correct dimensions
  static const boost::numeric::ublas::matrix<double> Prod(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::matrix<double>& b
    );

  ///Calculates the matrix product a * b
  ///with checking for correct dimensions
  static const boost::numeric::ublas::vector<double> Prod(
    const boost::numeric::ublas::matrix<double>& a,
    const boost::numeric::ublas::vector<double>& b
    );

  ///Simplify a structure
  /// [ [A] ]
  /// [ [B] ]    [ A ]
  /// [     ]    [ B ]
  /// [ [C] ]    [ C ]
  /// [ [D] ] -> [ D ]
  static const boost::numeric::ublas::vector<double> SimplifyVectorOfVector(
    const boost::numeric::ublas::vector<
      boost::numeric::ublas::vector<double>
    >& m);

  ///Simplify a structure
  /// [ [A B] ]
  /// [ [C D] ]    [ A B ]
  /// [       ]    [ C D ]
  /// [ [E F] ]    [ E F ]
  /// [ [G H] ] -> [ G H ]
  static const boost::numeric::ublas::matrix<double> SimplifyVectorOfMatrix(
    const boost::numeric::ublas::vector<
      boost::numeric::ublas::matrix<double>
    >& m);

  ///Simplify a structure
  /// [ [A B]  [I J] ]
  /// [ [C D]  [K L] ]    [ A B I J]
  /// [              ]    [ C D K L]
  /// [ [E F]  [M N] ]    [ E F M N]
  /// [ [G H]  [O P] ] -> [ G H O P]
  static const boost::numeric::ublas::matrix<double> SimplifyMatrixOfMatrix(
    const boost::numeric::ublas::matrix<
      boost::numeric::ublas::matrix<double>
    >& m);

  #ifndef NDEBUG
  ///Test these functions
  static void Test();
  #endif

  ///Unchop merges the 4 std::vector of sub-matrices produced by Chop
  static const boost::numeric::ublas::matrix<double> Unchop(
    const std::vector<boost::numeric::ublas::matrix<double> >& v);

  ///Check if two vectors are about equal
  static bool VectorsAreAboutEqual(
    const boost::numeric::ublas::vector<double>& a,
    const boost::numeric::ublas::vector<double>& b);

  ///Check if two vectors are about equal
  static bool VectorIsAboutEqual(
    const boost::numeric::ublas::vector<double>& a,
    const boost::numeric::ublas::vector<double>& b);

  ///Check if two vector are equal
  ///This is only suitable to test for exact copies.
  ///Use VectorsAreAboutEqual to allow for a
  ///small difference between the vector elements.
  static bool VectorsDoubleAreEqual(
    const boost::numeric::ublas::vector<double>& a,
    const boost::numeric::ublas::vector<double>& b);

  ///Check if two vector are equal
  static bool VectorsIntAreEqual(
    const boost::numeric::ublas::vector<int>& a,
    const boost::numeric::ublas::vector<int>& b);
};

} //~namespace ribi

#endif // MATRIX_H
