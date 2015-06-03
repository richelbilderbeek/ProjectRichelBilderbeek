#ifndef STOCHASTICITYINSPECTORMAINDIALOG_H
#define STOCHASTICITYINSPECTORMAINDIALOG_H

#include <vector>

namespace ribi { namespace ou { struct Parameters; } }

struct StochasticityInspectorMainDialog
{
  //Start with an Ornstein-Uhlenbeck process
  StochasticityInspectorMainDialog(
    const double init_x,
    const double dt,
    const double t_end,
    const ribi::ou::Parameters& parameters
  );


  private:
  std::vector<double> m_ts;
  std::vector<double> m_xs;
};

#endif // STOCHASTICITYINSPECTORMAINDIALOG_H
