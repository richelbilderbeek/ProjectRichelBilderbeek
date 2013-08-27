#include "tooltestsimplelinearregressionmaindialog.h"

#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <sstream>

#include "trace.h"

double ToolTestSimpleLinearRegressionMainDialog::CalculateCovariance(
  const std::vector<double>& xs,
  const std::vector<double>& ys)
{
  assert(xs.size() == ys.size());
  const std::size_t sz = xs.size();
  std::vector<double> ps(sz);
  for (std::size_t i=0; i!=sz; ++i)
  {
    ps[i] = xs[i] * ys[i];
  }

  const double mean_x = CalculateMean(xs);
  const double mean_y = CalculateMean(ys);
  const double mean_p = CalculateMean(ps);
  return mean_p - (mean_x * mean_y);
}

double ToolTestSimpleLinearRegressionMainDialog::CalculateMean(
  const std::vector<double>& v)
{
  assert(!v.empty());
  return std::accumulate(v.begin(),v.end(),0.0) / static_cast<double>(v.size());
}

const std::pair<double,double>
  ToolTestSimpleLinearRegressionMainDialog::CalculateSimpleLinearRegression(
    const std::vector<double>& xs,
    const std::vector<double>& ys)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(xs.size() == ys.size()
    && "Every coordinat must have exactly one x and one y value");
  const double mean_x = CalculateMean(xs);
  const double mean_y = CalculateMean(ys);
  //const double covariance_xy = CalculateCovariance(xs,ys);
  //const double variance_x = CalculateVariance(xs);
  //const double slope = covariance_xy / variance_x;
  const double slope = CalculateSlope(xs,ys);
  const double intercept = mean_y - (slope * mean_x);
  return std::make_pair(slope,intercept);
}

double ToolTestSimpleLinearRegressionMainDialog::CalculateSlope(
  const std::vector<double>& xs,
  const std::vector<double>& ys)
{
  assert(xs.size() == ys.size());
  double numerator = 0.0;
  double denominator = 0.0;
  const double x_mean = CalculateMean(xs);
  const double y_mean = CalculateMean(ys);
  const std::size_t sz = xs.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    const double x = xs[i];
    const double y = ys[i];
    numerator   += ((x - x_mean) * (y - y_mean));
    denominator += ((x - x_mean) * (x - x_mean));
  }
  return numerator / denominator;
}

double ToolTestSimpleLinearRegressionMainDialog::CalculateVariance(
  const std::vector<double>& v)
{
  assert(!v.empty());
  const double mean = CalculateMean(v);


  const double mean_of_squares
    = std::accumulate(v.begin(),v.end(),0.0,
      [](const double init, const double x)
      {
        return init + (x * x);
      }
    ) / static_cast<double>(v.size());

  return mean_of_squares - (mean * mean);
}

const std::vector<double>
  ToolTestSimpleLinearRegressionMainDialog::GetAnscombesQuartetX(const int index)
{
  switch (index)
  {
    case 1:
    case 2:
    case 3:
      return { 10.0,8.0,13.0,9.0,11.0,14.0,6.0,4.0,12.0,7.0,5.0 };
    case 4:
      return { 8.0,8.0,8.0,8.0,8.0,8.0,8.0,19.0,8.0,8.0,8.0 };
    default:
    {
      std::stringstream s;
      s << "ERROR ("
        << __func__
        << "): Anscombe's Quartet has index 1 to and including 4, given index is: "
        << index;
      std::cerr << s << std::endl;
      assert(!"Should not get here: ");
      throw std::logic_error(s.str());
    }
  }
}

const std::vector<double>
  ToolTestSimpleLinearRegressionMainDialog::GetAnscombesQuartetY(const int index)
{
  switch (index)
  {
    case 1:
      return { 8.04,6.95,7.58,8.81,8.33,9.96,7.24,4.26,10.84,4.82,5.68 };
    case 2:
      return { 9.14,8.14,8.74,8.77,9.26,8.1,6.13,3.1,9.13,7.26,4.74 };
    case 3:
      return { 7.46,6.77,12.74,7.11,7.81,8.84,6.08,5.39,8.15,6.42,5.73 };
    case 4:
      return { 6.58,5.76,7.71,8.84,8.47,7.04,5.25,12.5,5.56,7.91,6.89 };
    default:
    {
      std::stringstream s;
      s << "ERROR ("
        << __func__
        << "): Anscombe's Quartet has index 1 to and including 4, given index is: "
        << index;
      std::cerr << s << std::endl;
      assert(!"Should not get here: ");
      throw std::logic_error(s.str());
    }
  }
}

#ifndef NDEBUG
void ToolTestSimpleLinearRegressionMainDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ToolTestSimpleLinearRegressionMainDialog::Test");
  {
    const std::vector<double> v { 75.0, 83.0, 96.0, 100.0, 121.0, 125.0 };
    const double variance = CalculateVariance(v);
    const double expected = 332.666667;
    assert(std::abs(variance - expected) < 0.0001);
  }
  {
    const std::vector<double> v { 0.23, 0.37, 0.45, 0.49, 0.56, 0.63, 0.63, 0.70, 0.72, 0.82 };
    const double variance = CalculateVariance(v);
    const double expected = 0.02846;
    assert(std::abs(variance - expected) < 0.0001);
  }
  for (int i=1; i!=5; ++i) //Human-based counting, following the Ansombe's Quartet indices
  {
    const std::vector<double> xs = GetAnscombesQuartetX(i);
    const std::vector<double> ys = GetAnscombesQuartetY(i);
    const std::pair<double,double> p = CalculateSimpleLinearRegression(xs,ys);

    const double mean_x = CalculateMean(xs);
    const double mean_y = CalculateMean(ys);
    const double slope = p.first;
    const double intercept = p.second;

    //const double variance_x = CalculateVariance(xs);
    //const double variance_y = CalculateVariance(ys);


    const double expected_mean_x = 9.0;
    const double expected_mean_y = 7.5;              //to 2 decimal places
    const double expected_slope = 0.500; //to 3 decimal places
    const double expected_intercept = 3.00;  //to 2 decimal places

    const double e = 0.01;
    assert(std::abs(expected_mean_x - mean_x) < e);
    assert(std::abs(expected_mean_y - mean_y) < e);

    //const double expected_variance_x = 11.0;
    //const double expected_variance_y = 4.125;        //4.122 or 4.127 (to 3 decimal places)
    //const double expected_correlation = 0.816;       //to 3 decimal places)
    //assert(std::abs(expected_variance_x - variance_x) < e);
    //assert(std::abs(expected_variance_y - variance_y) < e);
    assert(std::abs(expected_slope - slope) < e);
    assert(std::abs(expected_intercept - intercept) < e);
  }
  TRACE("Finished ToolTestSimpleLinearRegressionMainDialog::Test successfully");
}
#endif
