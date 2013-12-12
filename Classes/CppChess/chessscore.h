#ifndef CHESSSCORE_H
#define CHESSSCORE_H

#include <iosfwd>
#include <string>
#include <vector>

namespace ribi {
namespace Chess {

///Score contains the score that ends a chess match
struct Score
{
  Score(const std::string& s);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  bool IsBlackWinner() const { return m_is_black_winner; }
  bool IsDraw() const { return m_is_draw; }
  bool IsWhiteWinner() const { return m_is_white_winner; }

  #ifndef NDEBUG
  ///Test if Score is working correctly
  static void Test() noexcept;
  #endif

  ///Convert a Score to string
  const std::string ToStr() const;

  private:

  const bool m_is_black_winner;
  const bool m_is_draw;
  const bool m_is_white_winner;
};

std::ostream& operator<<(std::ostream& os, const Score& s);
bool operator==(const Score& lhs, const Score& rhs);
bool operator!=(const Score& lhs, const Score& rhs);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSSCORE_H
