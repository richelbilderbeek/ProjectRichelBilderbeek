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
  ValentineCardSymbols() {}
  const std::vector<boost::shared_ptr<ValentineCardSymbol>> CreateAll() const noexcept;
  const boost::bimap<char,boost::shared_ptr<ValentineCardSymbol>> CreateAlphabet() const noexcept;
  const std::vector<boost::shared_ptr<ValentineCardSymbol>> TextToSymbols(const std::string& s) const noexcept;

  //private:
  //~ValentineCardSymbols() {}
  //friend void boost::checked_delete<>(ValentineCardSymbols* x);
  //friend void boost::checked_delete<>(const ValentineCardSymbols* x);
};

} //~namespace ribi

#endif // VALENTINECARDSYMBOLS_H
