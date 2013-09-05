//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "whitenoisesystemfactory.h"

#include <cassert>
#include "gapsfilledwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemfactory.h"
#include "standardwhitenoisesystemfactory.h"

const boost::shared_ptr<ribi::WhiteNoiseSystem> ribi::WhiteNoiseSystemFactory::Create(
  const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters)
{
  boost::shared_ptr<WhiteNoiseSystem> p;
  switch (parameters->GetType())
  {
    case WhiteNoiseSystemType::gaps_filled:
      p = GapsFilledWhiteNoiseSystemFactory::Create(parameters);
      break;
    case WhiteNoiseSystemType::lagged:
      p = LaggedWhiteNoiseSystemFactory::Create(parameters);
      break;
    case WhiteNoiseSystemType::standard:
      p = StandardWhiteNoiseSystemFactory::Create(parameters);
      break;
    case WhiteNoiseSystemType::n_types:
      assert(!"Unimplemented white noise system");
      throw std::logic_error(__func__);
  }
  assert(p);
  return p;
}
