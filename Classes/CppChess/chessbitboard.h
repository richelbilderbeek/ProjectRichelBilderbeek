#ifndef CHESSBITBOARD_H
#define CHESSBITBOARD_H

#include <iosfwd>
#include <vector>

#include "chessfwd.h"

namespace Chess {

///BitBoard is an 8x8 square of bools
struct BitBoard
{
  ///Create an empty BitBoard
  BitBoard();

  ///Set a value
  void Set(const Square& s, const bool value);

  ///Get a value
  bool Get(const Square& s) const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Test the BitBoard
  static void Test();

  private:
  ///An 8x8 std::vector of bools
  std::vector<std::vector<bool> > m_v;

  friend std::ostream& operator<<(std::ostream& os, const BitBoard& b);
};

std::ostream& operator<<(std::ostream& os, const BitBoard& b);

} //~ namespace Chess

#endif // CHESSBITBOARD_H
