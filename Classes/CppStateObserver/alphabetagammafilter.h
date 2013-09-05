#ifndef ALPHABETAGAMMAFILTER_H
#define ALPHABETAGAMMAFILTER_H

#include <string>
#include <vector>

#include "floatingpointstateobserver.h"

namespace ribi {

///An alpha beta gamma filter
struct AlphaBetaGammaFilter : public FloatingPointStateObserver
{
  AlphaBetaGammaFilter(
    const double alpha = 0.1 ,
    const double beta  = 0.01,
    const double gamma = 0.001,
    const double dt    = 1.0
  );

  ///Get the current state estimate
  double GetEstimate() const { return m_position; }

  ///Supply a measurement, which will update the state estimate
  void Update(const double measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  double m_acceleration;
  const double m_alpha;
  const double m_beta;
  const double m_dt;
  const double m_gamma;
  double m_position;
  double m_velocity;
};

} //~namespace ribi

#endif // ALPHABETAGAMMAFILTER_H
