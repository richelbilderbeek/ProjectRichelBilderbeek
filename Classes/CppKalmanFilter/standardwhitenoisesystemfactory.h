#ifndef STANDARDWHITENOISESYSTEMFACTORY_H
#define STANDARDWHITENOISESYSTEMFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "standardwhitenoisesystem.h"
#pragma GCC diagnostic pop

struct StandardWhiteNoiseSystemFactory
{
  static const boost::shared_ptr<StandardWhiteNoiseSystem> Create(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  static const boost::shared_ptr<StandardWhiteNoiseSystem> Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters);

};

#endif // STANDARDWHITENOISESYSTEMFACTORY_H
