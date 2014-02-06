#ifndef FUNCTIONPLOTTERMAINDIALOG_H
#define FUNCTIONPLOTTERMAINDIALOG_H

#include <string>
#include <vector>

namespace ribi {

struct FunctionPlotterMainDialog
{
  FunctionPlotterMainDialog(
    const std::string& formula,
    const double x_min,
    const double x_max,
    const int n_cols
  );

  const std::vector<double>& GetXs() const noexcept { return m_x; }
  const std::vector<double>& GetYs() const noexcept { return m_y; }

private:
  std::vector<double> m_x;
  std::vector<double> m_y;

  ///Rescale calculates a value between old_min and old_max its relative place and transforms
  ///this relative position to a new_min and new_max
  ///For example: for the old range [1,5], the value 2 is at 25% of this range. Transforming this
  ///to the new range range [0,100] results in a 25
  static double Rescale(
    const double value,
    const double oldMin,
    const double oldMax,
    const double newMin,
    const double newMax);
};

} //~namespace ribi

#endif // FUNCTIONPLOTTERMAINDIALOG_H
