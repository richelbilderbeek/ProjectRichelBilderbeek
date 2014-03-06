#ifndef MULTIALPHAFILTER_H
#define MULTIALPHAFILTER_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "alphafilter.h"
#include "floatingpointstateobserver.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MultiAlphaFilter : public FloatingPointStateObserver
{
  MultiAlphaFilter(
    const std::vector<double> alphas,
    const double dt = 1.0
  );

  ///Get the current state estimate
  double GetEstimate() const;

  ///Supply a measurement, which will update the state estimate
  void Update(const double measurement);

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  std::vector<boost::shared_ptr<AlphaFilter> > m_filters;

  static const std::vector<boost::shared_ptr<AlphaFilter> > CreateFilters(
    const std::vector<double> alphas,
    const double dt);
};

} //~namespace ribi

#endif // MULTIALPHAFILTER_H
