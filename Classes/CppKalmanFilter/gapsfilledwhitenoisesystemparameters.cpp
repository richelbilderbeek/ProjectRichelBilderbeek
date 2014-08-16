#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "gapsfilledwhitenoisesystemparameters.h"

#include <cassert>

#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::kalman::GapsFilledWhiteNoiseSystemParameters::GapsFilledWhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<int>& measurement_frequency,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition)
  : WhiteNoiseSystemParameters(
      control,
      initial_state,
      real_measurement_noise,
      real_process_noise,
      state_transition
    ),
    m_measurement_frequency{measurement_frequency}
{
  #ifndef NDEBUG
  Test();
  assert(m_measurement_frequency.size() == initial_state.size());
  //Check measuring frequecies
  {
    const auto v = m_measurement_frequency;
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const int x = v[i];
      if (x < 1)
      {
        TRACE(x);
        TRACE("BREAK");
      }
      assert(x >= 1 && "At least one out of one measurements is a real measurement");
    }
  }
  #endif
}

#ifndef NDEBUG
void ribi::kalman::GapsFilledWhiteNoiseSystemParameters::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {

  }
}
#endif
