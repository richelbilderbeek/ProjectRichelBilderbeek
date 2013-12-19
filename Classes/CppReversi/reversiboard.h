#ifndef REVERSIBOARD_H
#define REVERSIBOARD_H

#include <string>
#include <vector>

namespace ribi {
namespace reversi {

///Board is a reversi board with the most level interface as possible.
///Board does not know the current player and Board cannot undo its moves
///For a higher level interface, use Widget
struct Board
{
  enum { empty   = 0};
  enum { player1 = 1};
  enum { player2 = 2};

  Board(const int size = 10);

  bool CanDoMove(const int x, const int y, const int player) const noexcept;

  int Count(const int player) const noexcept;

  void DoMove(const int x, const int y, const int player) noexcept;

  const std::vector<std::vector<int> >& GetBoard() const noexcept { return m_board; }

  int Get(const int x, const int y) const noexcept;

  int GetSize() const noexcept;

  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

  const std::vector< std::pair<int,int> > GetValidMoves(const int player) const noexcept;

  ///Simply sets a square, without any checking
  void Set(const int x, const int y, const int state) noexcept;

  private:
  std::vector<std::vector<int> > m_board;

  ///Create the delta-x and delta-y to search in the 8 directions
  static const std::vector<std::pair<int,int>> CreateDeltas() noexcept;

  static int GetOtherPlayer(const int player) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Board& r);
};

bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);
std::ostream& operator<<(std::ostream& os, const Board& r);
std::istream& operator>>(std::istream& is, Board& r);

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIBOARD_H
