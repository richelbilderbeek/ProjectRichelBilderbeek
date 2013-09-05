#ifndef GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H
#define GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H

#include <boost/shared_ptr.hpp>
#include "whitenoisesystemparameters.h"

namespace ribi {

struct GapsFilledWhiteNoiseSystemParameters : public WhiteNoiseSystemParameters
{
  explicit GapsFilledWhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<int>& measurement_frequency,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  ///The number of timesteps after which a real measurement is acquired
  const boost::numeric::ublas::vector<int>& GetMeasurementFrequency() const { return m_measurement_frequency; }

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const { return WhiteNoiseSystemType::gaps_filled; }

  private:
  ///Can only be deleted by boost::checked_delete
  ~GapsFilledWhiteNoiseSystemParameters() {}
  friend void boost::checked_delete<>(GapsFilledWhiteNoiseSystemParameters*);

  ///The gaps (in timesteps) is the number of measurements of which only one real measurement is acquired
  const boost::numeric::ublas::vector<int> m_measurement_frequency;

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace ribi

#endif // GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H
