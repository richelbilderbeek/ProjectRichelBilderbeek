#ifndef LAGGEDWHITENOISESYSTEMFACTORY_H
#define LAGGEDWHITENOISESYSTEMFACTORY_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>
#include "laggedwhitenoisesystem.h"

///Factory for LaggedWhiteNoiseSystem
struct LaggedWhiteNoiseSystemFactory
{
  ///Create a LaggedWhiteNoiseSystem from the loose parameters
  static const boost::shared_ptr<LaggedWhiteNoiseSystem> Create(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const int lag,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  ///Create a LaggedWhiteNoiseSystem from the parameters
  static const boost::shared_ptr<LaggedWhiteNoiseSystem> Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters);
};

#endif // LAGGEDWHITENOISESYSTEMFACTORY_H
