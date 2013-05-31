#ifndef MULTIALPHAFILTER_H
#define MULTIALPHAFILTER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "alphafilter.h"

struct MultiAlphaFilter
{
  MultiAlphaFilter(
    const std::vector<double> alphas,
    const double dt = 1.0
  );

  double Estimate(const double measurement);

  private:
  std::vector<boost::shared_ptr<AlphaFilter> > m_filters;

  static const std::vector<boost::shared_ptr<AlphaFilter> > CreateFilters(
    const std::vector<double> alphas,
    const double dt);
};

#endif // MULTIALPHAFILTER_H
