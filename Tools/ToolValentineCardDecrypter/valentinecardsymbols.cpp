#include "valentinecardsymbols.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include "trace.h"
#pragma GCC diagnostic pop

const std::vector<ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::CreateAll() noexcept
{
  std::vector<ValentineCardSymbol> v;
  for (int center_index = 0; center_index!=3; ++center_index)
  {
    ValentineCardSymbol::CenterSymbol center_symbol;
    switch (center_index)
    {
      case 0: center_symbol = ValentineCardSymbol::CenterSymbol::none; break;
      case 1: center_symbol = ValentineCardSymbol::CenterSymbol::dot; break;
      case 2: center_symbol = ValentineCardSymbol::CenterSymbol::cross; break;
      assert(!"Should not get here");
    }
    for (int i=0; i!=9; ++i)
    {
      // +0+
      // 3 1
      // +2+
      //
      //   + + + +
      //   | | | |
      // +-+ +-+ +-+
      //
      // +-+ +-+ +-+
      //   | | | |
      // +-+ +-+ +-+
      //
      // +-+ +-+ +-+
      //   | | | |
      //   + + + +
      //
      const bool a = i / 3 >= 1;
      const bool b = i % 3 <= 1;
      const bool c = i / 3 <= 1;
      const bool d = i % 3 >= 1;
      ValentineCardSymbol symbol(
        { a, b, c, d },
        center_symbol
      );
      v.push_back(symbol);
    }
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
