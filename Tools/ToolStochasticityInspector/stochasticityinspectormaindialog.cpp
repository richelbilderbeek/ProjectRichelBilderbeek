#include "stochasticityinspectormaindialog.h"

#include "brownianmotionprocess.h"
#include "ornsteinuhlenbeckprocess.h"
#include "testtimer.h"

ribi::StochasticityInspectorMainDialog::StochasticityInspectorMainDialog()
  : m_ts{}, m_xs{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::StochasticityInspectorMainDialog::StochasticityInspectorMainDialog(
  const double init_x,
  const int t_end,
  const ribi::bm::Parameters& parameters
) : m_ts{}, m_xs{}
{
  if (t_end <= 0) return;

  ribi::bm::Process sim(parameters);

  double x = init_x;

  for (int i=0; i < t_end; ++i)
  {
    m_xs.push_back(x);
    m_ts.push_back(static_cast<double>(i) * boost::units::si::second);
    x = sim.CalcNext(x);
  }
}

ribi::StochasticityInspectorMainDialog::StochasticityInspectorMainDialog(
  const double init_x,
  const Time dt,
  const Time t_end,
  const ribi::ou::Parameters& parameters
) : m_ts{}, m_xs{}
{
  if (dt <= 0.0 * boost::units::si::second) return;
  if (t_end <= 0.0 * boost::units::si::second) return;

  ribi::ou::Process sim(parameters);

  double x = init_x;
  for (Time t=0.0 * boost::units::si::second; t<t_end; t+=dt)
  {
    m_xs.push_back(x);
    m_ts.push_back(t);
    x = sim.CalcNext(x,dt);
  }
}


#ifndef NDEBUG
void ribi::StochasticityInspectorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::bm::Process::Test();
    ribi::ou::Process::Test();
    StochasticityInspectorMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Worked example

}
#endif
