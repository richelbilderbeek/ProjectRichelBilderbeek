#ifndef WHITENOISESYSTEMFACTORY_H
#define WHITENOISESYSTEMFACTORY_H

#include <boost/shared_ptr.hpp>
#include "whitenoisesystem.h"
#include "whitenoisesystemparameters.h"

struct WhiteNoiseSystemFactory
{
  static const boost::shared_ptr<WhiteNoiseSystem> Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters);
};

#endif // WHITENOISESYSTEMFACTORY_H
