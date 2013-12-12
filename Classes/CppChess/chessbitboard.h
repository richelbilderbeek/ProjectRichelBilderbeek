#ifndef CHESSBITBOARD_H
#define CHESSBITBOARD_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///BitBoard is an 8x8 square of bools
struct BitBoard
{
  ///Create an empty BitBoard
  BitBoard();

  ///Set a value
  void Set(const boost::shared_ptr<const Square> s, const bool value);

  ///Get a value
  bool Get(const boost::shared_ptr<const Square> s) const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Test the BitBoard
  static void Test() noexcept;

  private:
  ///An 8x8 std::vector of bools
  std::vector<std::vector<bool> > m_v;

  friend std::ostream& operator<<(std::ostream& os, const BitBoard& b);
};

std::ostream& operator<<(std::ostream& os, const BitBoard& b);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSBITBOARD_H
