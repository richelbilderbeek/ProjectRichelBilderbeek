#include "valentinecardsymbols.h"

#include <cassert>

#include "trace.h"

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
    for (int line_index=1; line_index!=16; ++line_index)
    {
      const bool a = (line_index >> 0) % 2;
      const bool b = (line_index >> 1) % 2;
      const bool c = (line_index >> 2) % 2;
      const bool d = (line_index >> 3) % 2;
      const int sum = a + b + c + d;
      if (sum < 2) continue;
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
