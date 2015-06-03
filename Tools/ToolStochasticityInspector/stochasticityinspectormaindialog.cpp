#include "stochasticityinspectormaindialog.h"

#include "ornsteinuhlenbeckprocess.h"

StochasticityInspectorMainDialog::StochasticityInspectorMainDialog(
  const double init_x,
  const double dt,
  const double t_end,
  const ribi::ou::Parameters& parameters
) : m_ts{}, m_xs{}
{
  if (dt <= 0.0) return;

  ribi::ou::Process sim(parameters);

  double x = init_x;
  for (double t=0.0; t<t_end; t+=dt)
  {
    m_xs.push_back(x);
    m_ts.push_back(t);
    x = sim.CalcNext(x,dt);
  }
}
