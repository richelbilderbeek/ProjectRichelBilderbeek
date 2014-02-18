#ifndef VALENTINECARDSYMBOL_H
#define VALENTINECARDSYMBOL_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

///A symbol on the valentine card
/*

There can be four lines in a character:

+-+ +0+
| | 3 1
+-+ +2+

There can be three sybols in the center (including none):

+-+ +-+ +-+
| | |.| |x|
+-+ +-+ +-+

*/

namespace ribi {

struct TextCanvas;

struct ValentineCardSymbol
{
  enum class CenterSymbol { none, dot, cross };

  ValentineCardSymbol(
    const std::array<bool,4> lines,
    const CenterSymbol center_symbol
  );

  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  private:
  const CenterSymbol m_center_symbol;
  const std::array<bool,4> m_lines;
};

} //~namespace ribi

#endif // VALENTINECARDSYMBOL_H
