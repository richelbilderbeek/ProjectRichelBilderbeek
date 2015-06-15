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

  for (int i=0; i <= t_end; ++i) //Also include t_end
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

double ribi::StochasticityInspectorMainDialog::CalcBrownianMotionMaxLogLikelihood() const noexcept
{
  return ribi::bm::Helper().CalcMaxLogLikelihood(m_xs);
}

double ribi::StochasticityInspectorMainDialog::CalcOrnsteinUhlenbeckMaxLogLikelihood() const noexcept
{
  return ribi::ou::Helper().CalcMaxLogLikelihood(m_xs);
}

ribi::StochasticityInspectorMainDialog::HlrtResult
  ribi::StochasticityInspectorMainDialog::DoHierarchicalLikelihoodRatioTest() const
{
  const bool verbose{false};

  const double log_likelihood_bm = ribi::bm::Helper().CalcMaxLogLikelihood(m_xs);
  const double log_likelihood_ou = ribi::ou::Helper().CalcMaxLogLikelihood(m_xs);

  const double alpha{0.05};
  const int dof{2};
  boost::math::chi_squared_distribution<double> distribution(dof);
  const double critical_value{boost::math::quantile(boost::math::complement(distribution,alpha))};


  //BM is H_0, OU is H_1
  const double delta{2.0 * (log_likelihood_ou - log_likelihood_bm)};

  if (verbose)
  {
    std::cout
      << "log_likelihood_bm: " << log_likelihood_bm << '\n'
      << "log_likelihood_ou: " << log_likelihood_ou << '\n'
      << "alpha: " << alpha << '\n'
      << "dof: " << dof << '\n'
      << "critical_value: " << critical_value << '\n'
      << "delta: " << delta << '\n'
    ;
  }

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
  //Brownian motion
  {
    StochasticityInspectorMainDialog d(
      0.0, //init_x
      10,  //t_end
      ribi::bm::Parameters(
        0.5 / boost::units::si::second,
        83
      )
    );
    assert(d.GetTimePoints().size() == d.GetValues().size());
  }
  //Worked example
  std::cout << "HERE:" << std::endl;
  {
    //Start with an Brownian Motion
    StochasticityInspectorMainDialog d(
      0.0, //init_x
      10,  //t_end
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
    assert(d.GetTimePoints().size() == 11);
    const double expected_bm_log_likelihood{-4.9811847};
    const double expected_ou_log_likelihood{0.0489702};
    const double found_bm_log_likelihood{d.CalcBrownianMotionMaxLogLikelihood()};
    const double found_ou_log_likelihood{d.CalcOrnsteinUhlenbeckMaxLogLikelihood()};
    std::cout
      << "found_bm_log_likelihood: " << found_bm_log_likelihood << '\n'
      << "found_ou_log_likelihood: " << found_ou_log_likelihood << '\n'
    ;

    assert(std::abs(found_bm_log_likelihood - expected_bm_log_likelihood) < 0.0001);
    assert(std::abs(found_ou_log_likelihood - expected_ou_log_likelihood) < 0.0001);

    const HlrtResult result{d.DoHierarchicalLikelihoodRatioTest()};
    assert(result == HlrtResult::reject_null_hypothesis);
  }

}
#endif
