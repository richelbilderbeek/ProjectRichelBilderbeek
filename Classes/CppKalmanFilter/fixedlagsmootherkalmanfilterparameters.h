#ifndef FIXEDLAGSMOOTHERKALMANFILTERPARAMETERS_H
#define FIXEDLAGSMOOTHERKALMANFILTERPARAMETERS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "kalmanfilterparameters.h"
#include "kalmanfiltertype.h"
#include "standardkalmanfilterparameters.h"

namespace ribi {
namespace kalman {

struct FixedLagSmootherKalmanFilterParameters : public KalmanFilterParameters
{
  explicit FixedLagSmootherKalmanFilterParameters(
    const boost::shared_ptr<StandardKalmanFilterParameters>& standard_parameters,
    const int lag);

  ///Obtain the lag in timesteps
  int GetLag() const { return m_lag; }

  ///The parameters from a standard Kalman filter
  boost::shared_ptr<const StandardKalmanFilterParameters> GetStandardParameters() const
    { return m_standard_parameters; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::fixed_lag_smoother; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Check if this parameter set has a certain type of KalmanFilterParameter
  static bool HasParameterType(const KalmanFilterParameterType type);

  private:
  ///Can only be deleted by boost::checked_delete
  ~FixedLagSmootherKalmanFilterParameters() noexcept {}
  friend void boost::checked_delete<>(FixedLagSmootherKalmanFilterParameters*);

  ///The lag in timesteps
  const int m_lag;

  ///The parameters from a standard Kalman filter
  const boost::shared_ptr<const StandardKalmanFilterParameters> m_standard_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // FIXEDLAGSMOOTHERKALMANFILTERPARAMETERS_H
