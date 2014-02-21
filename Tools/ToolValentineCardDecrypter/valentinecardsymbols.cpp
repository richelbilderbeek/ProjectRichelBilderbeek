#include "valentinecardsymbols.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include "trace.h"
#include "valentinecardsymbol.h"
#pragma GCC diagnostic pop

const std::vector<ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::CreateAll() noexcept
{
  std::vector<ValentineCardSymbol> v;
  for (int i=0; i!=27; ++i)
  {
    ValentineCardSymbol symbol(i);
    v.push_back(symbol);
  }
  TRACE(v.size());
  return v;
}

const boost::bimap<char,ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::CreateAlphabet() noexcept
{
  const std::vector<ValentineCardSymbol> v { CreateAll() };
  boost::bimap<char,ribi::ValentineCardSymbol> m;

  for (int i=0; i!=26; ++i)
  {
    const char my_char = 'a' + i;
    m.insert(boost::bimap<char,ribi::ValentineCardSymbol>::value_type(
      my_char,v[i]));
  }
  return m;
}
