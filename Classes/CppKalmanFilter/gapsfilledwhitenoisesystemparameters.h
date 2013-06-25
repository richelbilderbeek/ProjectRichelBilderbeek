#ifndef GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H
#define GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H

#include <boost/shared_ptr.hpp>
#include "whitenoisesystemparameters.h"

struct GapsFilledWhiteNoiseSystemParameters : public WhiteNoiseSystemParameters
{
  GapsFilledWhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const int gap,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  ///The gap (in timesteps) is the number of measurements of which only one real measurement is acquired
  int GetGap() const { return m_gap; }

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const { return WhiteNoiseSystemType::gaps_filled; }

  private:
  ///Can only be deleted by boost::checked_delete
  ~GapsFilledWhiteNoiseSystemParameters() {}
  friend void boost::checked_delete<>(GapsFilledWhiteNoiseSystemParameters*);

  ///The gap (in timesteps) is the number of measurements of which only one real measurement is acquired
  const int m_gap;
};

#endif // GAPSFILLEDWHITENOISESYSTEMPARAMETERS_H
