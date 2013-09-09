#ifndef QTMATRIX_H
#define QTMATRIX_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

struct QTableWidget;

namespace ribi {

///Helper class for matrix operations
struct QtMatrix
{
  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Write a uBLAS matrix of doubles to a QTableWidget
  static void MatrixToTable(const boost::numeric::ublas::matrix<double>& m, QTableWidget * const table);

  ///Write a vector of doubles to a QTableWidget
  static void StdVectorDoubleToTable(const std::vector<double>& v, QTableWidget * const table);

  ///Write a vector of strings to a QTableWidget
  static void StrVectorToTable(const std::vector<std::string>& v, QTableWidget * const table);

  ///Test these functions
  static void Test();

  ///Convert a QTableWidget to a uBLAS matrix of doubles
  static const boost::numeric::ublas::matrix<double> ToMatrix(const QTableWidget * const table);

  ///Convert a QTableWidget to a vector of strings
  static const std::vector<std::string> ToStrVector(const QTableWidget * const table);

  ///Convert a QTableWidget to a uBLAS vector of doubles
  static const boost::numeric::ublas::vector<double> ToVector(const QTableWidget * const table);

  ///Write a uBLAS vector of doubles to a QTableWidget
  static void UblasVectorDoubleToTable(const boost::numeric::ublas::vector<double>& v, QTableWidget * const table);
};

} //~namespace ribi

#endif // QTMATRIX_H
