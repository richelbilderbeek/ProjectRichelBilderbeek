#ifndef ALPHABETAFILTER_H
#define ALPHABETAFILTER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "floatingpointstateobserver.h"
#pragma GCC diagnostic pop

namespace ribi {

///An alpha beta filter
struct AlphaBetaFilter : public FloatingPointStateObserver
{
  AlphaBetaFilter(
    const double alpha = 0.1 ,
    const double beta  = 0.01,
    const double dt    = 1.0
  );

  ///Get the current state estimate
  double GetEstimate() const { return m_output; }

  ///Supply a measurement, which will update the state estimate
  void Update(const double measurement);

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  const double m_alpha;
  const double m_beta;
  const double m_dt;

  double m_slope;
  double m_output;
};

} //~namespace ribi

#endif // ALPHABETAFILTER_H
