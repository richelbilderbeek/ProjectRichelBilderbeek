#ifndef RUBIKSCLOCKPEGS_H
#define RUBIKSCLOCKPEGS_H

#include <iosfwd>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "rubiksclockfwd.h"
#include "rubiksclockside.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace ruco {

///The four Pegs on a Rubik's Clock
struct Pegs
{
  Pegs() noexcept;
  boost::shared_ptr<ToggleButtonWidget> m_pegs[2][2]; //Is peg pressed?
  static Pegs CreatePegsFromIndex(const int index) noexcept;
  const boost::shared_ptr<const ToggleButtonWidget> GetPeg(const Side side) const noexcept;
  std::string ToXml() const noexcept;

  private:
  ~Pegs() noexcept {}
  friend void boost::checked_delete<>(Pegs*);
  friend void boost::checked_delete<>(const Pegs*);
};

std::ostream& operator<<(std::ostream& os, const Pegs& p) noexcept;
bool operator==(const Pegs& lhs, const Pegs& rhs) noexcept;

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCKPEGS_H
