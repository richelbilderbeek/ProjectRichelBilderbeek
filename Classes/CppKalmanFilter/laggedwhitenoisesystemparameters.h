#ifndef LAGGEDWHITENOISESYSTEMPARAMETERS_H
#define LAGGEDWHITENOISESYSTEMPARAMETERS_H

#include <boost/shared_ptr.hpp>
#include "whitenoisesystemparameters.h"
#include "standardwhitenoisesystemparameters.h"

namespace ribi {

struct LaggedWhiteNoiseSystemParameters : public WhiteNoiseSystemParameters
{
  explicit LaggedWhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const int lag,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  ///The lag (in timesteps) the lagged white noise system has
  int GetLag() const { return m_lag; }

  ///The white noise system parameters of unlagged behavior
  //const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& GetStandardWhiteNoiseSystemParameters() const
  //  { return m_standard_parameters; }

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const { return WhiteNoiseSystemType::lagged; }

  private:
  ///Can only be deleted by boost::checked_delete
  ~LaggedWhiteNoiseSystemParameters() {}
  friend void boost::checked_delete<>(LaggedWhiteNoiseSystemParameters*);

  ///The lag (in timesteps) the lagged white noise system has
  const int m_lag;
};

} //~namespace ribi

#endif // LAGGEDWHITENOISESYSTEMPARAMETERS_H
