#ifndef VALENTINECARDSYMBOLS_H
#define VALENTINECARDSYMBOLS_H

#include <vector>
#include "valentinecardsymbol.h"

namespace ribi {

struct ValentineCardSymbols
{
  static const std::vector<ValentineCardSymbol> CreateAll() noexcept;
};

} //~namespace ribi

#endif // VALENTINECARDSYMBOLS_H
