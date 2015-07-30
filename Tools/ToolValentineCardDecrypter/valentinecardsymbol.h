#ifndef VALENTINECARDSYMBOL_H
#define VALENTINECARDSYMBOL_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QImage>
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

  explicit ValentineCardSymbol(
    const std::array<bool,4> lines,
    const CenterSymbol center_symbol
  );

  explicit ValentineCardSymbol(
    const int value
  );
  ~ValentineCardSymbol() {}

  int CalcValue() const noexcept;
  CenterSymbol GetCenterSymbol() const noexcept { return m_center_symbol; }
  const std::array<bool,4>& GetLines() const noexcept { return m_lines; }
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  const boost::shared_ptr<QImage> ToImage() const noexcept;
  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  private:
  friend void boost::checked_delete<>(ValentineCardSymbol* x);
  friend void boost::checked_delete<>(const ValentineCardSymbol* x);

  CenterSymbol m_center_symbol;
  std::array<bool,4> m_lines;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator<(const ValentineCardSymbol& lhs, const ValentineCardSymbol& rhs) noexcept;

} //~namespace ribi

#endif // VALENTINECARDSYMBOL_H
