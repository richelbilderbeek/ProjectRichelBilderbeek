#ifndef SIMPLELINEARREGRESSION_H
#define SIMPLELINEARREGRESSION_H

#include <cassert>
#include <numeric>
#include <string>
#include <vector>

namespace ribi {

template <typename T>
T GetZero() { return T{}; }

//template <>
//double GetZero() { return 0.0; }

//template <typename T> void GetZero(T& t) { t = T(); }
//template <> void GetZero(double& d) { d = 0.0; }


///Class to obtain the best fitting line through all (x,y) pairs
///The best fitting line has form 'y = a.x + b', where
///- a: std::pair<double,double>::first
///- b: std::pair<double,double>::second
struct SimpleLinearRegression
{
  ///Obtain the best fitting line through all (x,y) pairs
  ///The best fitting line has form 'y = a.x + b', where
  ///- a: std::pair<double,double>::first
  ///- b: std::pair<double,double>::second
  template <class X, class Y>
  static auto CalculateBestFit(
    const std::vector<X>& xs,
    const std::vector<Y>& ys) -> const std::pair<decltype(ys[0]/xs[0]),Y>;

  ///Obtain Anscombe's Quartet its x values, for index 1 to (and including) 4
  static const std::vector<double> GetAnscombesQuartetX(const int index);

  ///Obtain Anscombe's Quartet its y values, for index 1 to (and including) 4
  static const std::vector<double> GetAnscombesQuartetY(const int index);

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

private:

  ///From htpp://www.richelbilderbeek.nl/CppCalculateCovariance.htm
  static double CalculateCovariance(
    const std::vector<double>& xs,
    const std::vector<double>& ys);

  ///From htpp://www.richelbilderbeek.nl/CppGetMean.htm
  template <class T>
  static T CalculateMean(
    const std::vector<T>& v);

  template <class X, class Y>
  static auto CalculateSlope(
    const std::vector<X>& xs,
    const std::vector<Y>& ys) -> decltype(ys[0]/xs[0]);

  ///From htpp://www.richelbilderbeek.nl/CppCalculateVariance.htm
  static double CalculateVariance(
    const std::vector<double>& v);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

template <class X, class Y>
auto SimpleLinearRegression::CalculateBestFit(
  const std::vector<X>& xs,
  const std::vector<Y>& ys) -> const std::pair<decltype(ys[0]/xs[0]),Y>
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(xs.size() == ys.size()
    && "Every coordinat must have exactly one x and one y value");
  const X mean_x { CalculateMean(xs) };
  const Y mean_y { CalculateMean(ys) };
  //const double covariance_xy = CalculateCovariance(xs,ys);
  //const double variance_x = CalculateVariance(xs);
  //const double slope = covariance_xy / variance_x;
  typedef decltype(ys[0]/xs[0]) Slope;
  const Slope slope { CalculateSlope(xs,ys) };
  const Y intercept { mean_y - (slope * mean_x) };
  return std::make_pair(slope,intercept);
}

template <class T>
T SimpleLinearRegression::CalculateMean(
  const std::vector<T>& v)
{
  //static_assert(!std::is_integral<T>(),"Cannot calculate the mean of integers");
  assert(!v.empty());
  return std::accumulate(v.begin(),v.end(),T()) / static_cast<double>(v.size());
}

template <class X, class Y>
auto SimpleLinearRegression::CalculateSlope(
  const std::vector<X>& xs,
  const std::vector<Y>& ys) -> decltype(ys[0]/xs[0])
{
  assert(xs.size() == ys.size());
  typedef decltype(xs[0] * ys[0]) Numerator;
  typedef decltype(xs[0] * xs[0]) Denominator;
  Numerator numerator { GetZero<X>() * GetZero<Y>() };
  Denominator denominator { GetZero<X>() * GetZero<X>() };
  const X x_mean { CalculateMean(xs) };
  const Y y_mean { CalculateMean(ys) };
  const std::size_t sz { xs.size() };
  for (std::size_t i=0; i!=sz; ++i)
  {
    const X x { xs[i] };
    const Y y { ys[i] };
    numerator   += ((x - x_mean) * (y - y_mean));
    denominator += ((x - x_mean) * (x - x_mean));
  }
  return numerator / denominator;
}

//template <> double SimpleLinearRegression::GetZero() { return 0.0; }
//template <class T> T SimpleLinearRegression::GetZero() { return T(); }

} //~namespace ribi

#endif // SIMPLELINEARREGRESSION_H
