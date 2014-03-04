#ifndef AAFFIGHTERFACTORY_H
#define AAFFIGHTERFACTORY_H

#include "aafaminoacid.h"
#include "aaffwd.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace aaf {

///Factory for Fighter
struct FighterFactory
{
  FighterFactory() noexcept;

  boost::shared_ptr<Fighter> Create(const AminoAcid a) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFFIGHTERFACTORY_H
