#include "stochasticityinspectormaindialog.h"

#include <boost/math/distributions/chi_squared.hpp>

#include "apfloat.h"

#include "brownianmotionprocess.h"
#include "brownianmotionhelper.h"
#include "ornsteinuhlenbeckprocess.h"
#include "ornsteinuhlenbeckhelper.h"
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
  m_xs.push_back(x);
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

ribi::StochasticityInspectorMainDialog::HlrtResult
  ribi::StochasticityInspectorMainDialog::DoHierarchicalLikelihoodRatioTest() const
{
  const double log_likelihood_bm = ribi::bm::Helper().CalcMaxLogLikelihood(m_xs);
  const double log_likelihood_ou = ribi::ou::Helper().CalcMaxLogLikelihood(m_xs);

  const apfloat likelihood_bm{exp(apfloat(log_likelihood_bm))};
  const apfloat likelihood_ou{exp(apfloat(log_likelihood_ou))};

  const double alpha{0.05};
  const int dof{2};
  boost::math::chi_squared_distribution<double> distribution(dof);
  const apfloat critical_value = boost::math::quantile(boost::math::complement(distribution,alpha));


  //BM is H_0, OU is H_1
  const apfloat delta = apfloat(2.0) * (likelihood_ou - likelihood_bm);

  if (delta < critical_value)
  {
    return HlrtResult::null_hypothesis_cannot_be_rejected;
  }
  else
  {
    return HlrtResult::reject_null_hypothesis;
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

  const bool verbose{false};
  //Worked example
  {
    //Start with an Brownian Motion
    StochasticityInspectorMainDialog d(
      0.0,
      10,
      ribi::bm::Parameters(
        0.5 / boost::units::si::second,
        83
      )
    );

    if (verbose)
    {
      std::copy(
        std::begin(d.GetValues()),
        std::end(d.GetValues()),
        std::ostream_iterator<double>(std::cout,"\n")
      );
    }
    const HlrtResult result{d.DoHierarchicalLikelihoodRatioTest()};
    assert(result == HlrtResult::null_hypothesis_cannot_be_rejected);
  }

}
#endif
