#ifndef VALENTINECARDSYMBOLS_H
#define VALENTINECARDSYMBOLS_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "valentinecardsymbol.h"

#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct ValentineCardSymbols
{
  static const std::vector<ValentineCardSymbol> CreateAll() noexcept;
  static const boost::bimap<char,ValentineCardSymbol> CreateAlphabet() noexcept;
};

} //~namespace ribi

#endif // VALENTINECARDSYMBOLS_H
