#include "stochasticityinspectormaindialog.h"

#include "brownianmotionprocess.h"
#include "ornsteinuhlenbeckprocess.h"

StochasticityInspectorMainDialog::StochasticityInspectorMainDialog()
  : m_ts{}, m_xs{}
{

}

StochasticityInspectorMainDialog::StochasticityInspectorMainDialog(
  const double init_x,
  const double t_end,
  const ribi::bm::Parameters& parameters
) : m_ts{}, m_xs{}
{
  if (t_end <= 0.0) return;

  ribi::bm::Process sim(parameters);

  double x = init_x;

  for (int i=0; i < t_end; ++i)
  {
    m_xs.push_back(x);
    m_ts.push_back(static_cast<double>(i));
    x = sim.CalcNext(x);
  }
}

StochasticityInspectorMainDialog::StochasticityInspectorMainDialog(
  const double init_x,
  const double dt,
  const double t_end,
  const ribi::ou::Parameters& parameters
) : m_ts{}, m_xs{}
{
  if (dt <= 0.0) return;
  if (t_end <= 0.0) return;

  ribi::ou::Process sim(parameters);

  double x = init_x;
  for (double t=0.0; t<t_end; t+=dt)
  {
    m_xs.push_back(x);
    m_ts.push_back(t);
    x = sim.CalcNext(x,dt);
  }
}

