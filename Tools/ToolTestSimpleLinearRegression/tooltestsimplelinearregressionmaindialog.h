#ifndef TOOLTESTAPPROXIMATORMAINDIALOG_H
#define TOOLTESTAPPROXIMATORMAINDIALOG_H

#include <vector>

struct ToolTestSimpleLinearRegressionMainDialog
{
  ///Obtain the best fitting line through all (x,y) pairs
  ///The best fitting line has form 'y = a.x + b', where
  ///- a: std::pair<double,double>::first
  ///- b: std::pair<double,double>::second
  static const std::pair<double,double> CalculateSimpleLinearRegression(
    const std::vector<double>& xs,
    const std::vector<double>& ys);

  ///Obtain Anscombe's Quartet its x values, for index 1 to (and including) 4
  static const std::vector<double> GetAnscombesQuartetX(const int index);

  ///Obtain Anscombe's Quartet its y values, for index 1 to (and including) 4
  static const std::vector<double> GetAnscombesQuartetY(const int index);

private:

  ///From htpp://www.richelbilderbeek.nl/CppCalculateCovariance.htm
  static double CalculateCovariance(
    const std::vector<double>& xs,
    const std::vector<double>& ys);

  ///From htpp://www.richelbilderbeek.nl/CppGetMean.htm
  static double CalculateMean(
    const std::vector<double>& v);

  static double CalculateSlope(
    const std::vector<double>& xs,
    const std::vector<double>& ys);

  ///From htpp://www.richelbilderbeek.nl/CppCalculateVariance.htm
  static double CalculateVariance(
    const std::vector<double>& v);

  #ifndef NDEBUG
  static void Test();
  #endif
};

#endif // TOOLTESTAPPROXIMATORMAINDIALOG_H
