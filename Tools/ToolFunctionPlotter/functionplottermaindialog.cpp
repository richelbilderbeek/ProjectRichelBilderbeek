#include "functionplottermaindialog.h"

#include <cassert>
#include <stdexcept>

#include "fparser.hh"

ribi::FunctionPlotterMainDialog::FunctionPlotterMainDialog(
  const std::string& formula,
  const double x_min,
  const double x_max,
  const int n_cols
) : m_x(std::vector<double>(n_cols,0.0)),
    m_y(std::vector<double>(n_cols,0.0))
{
  #ifndef NDEBUG
  assert(Rescale(2.0,1.0,5.0,0.0,100.0) >= 24.9999 && Rescale(2.0,1.0,5.0,0.0,100.0) < 25.0001);
  #endif

  FunctionParser f;

  f.Parse(formula,"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    throw std::runtime_error("Function cannot not be parsed");
  }

  if (x_min >= x_max)
  {
    throw std::runtime_error("Value of x_min must be smaller than x_max");
  }

  //Evaluate the function in a 2D std::vector
  const double n_cols_d = static_cast<double>(n_cols);

  for (int x = 0; x!=n_cols; ++x)
  {
    const double xD = static_cast<double>(x);
    const double x_scaled = Rescale(xD,0.0,n_cols_d,x_min,x_max);
    const double xs[1] = { x_scaled };
    const double y = f.Eval(xs);
    if (!f.EvalError())
    {
      m_y[x] = y;
    }
    else
    {
      m_y[x] = 0.0;
    }
    m_x[x] = x_scaled;
  }

}

double ribi::FunctionPlotterMainDialog::Rescale(
  const double value,
  const double old_min,
  const double old_max,
  const double new_min,
  const double new_max)
{
  assert(value >= old_min);
  assert(value <= old_max);
  const double old_distance = old_max - old_min;
  //At which relative distance is value on old_min to old_max ?
  const double distance = (value - old_min) / old_distance;
  assert(distance >= 0.0);
  assert(distance <= 1.0);
  const double new_distance = new_max - new_min;
  const double new_value = new_min + (distance * new_distance);
  assert(new_value >= new_min);
  assert(new_value <= new_max);
  return new_value;
}
