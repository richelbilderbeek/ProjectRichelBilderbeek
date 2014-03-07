#ifndef REVERSIBOARD_H
#define REVERSIBOARD_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "reversisquare.h"
#include "reversiplayer.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace reversi {

///Board is a reversi board with the most level interface as possible.
///Board does not know the current player and Board cannot undo its moves
///For a higher level interface, use Widget
struct Board
{

  Board(const int size = 10);
  //Board(const Board& other);
  //Board& operator=(const Board& other);
  //~Board() noexcept {}

  bool CanDoMove(const int x, const int y, const Player player) const noexcept;

  int Count(const Square square) const noexcept;

  void DoMove(const int x, const int y, const Player player) noexcept;

  const std::vector<std::vector<Square> >& GetBoard() const noexcept { return m_board; }

  Square Get(const int x, const int y) const noexcept;

  int GetSize() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  const std::vector<std::pair<int,int>> GetValidMoves(const Player player) const noexcept;

  ///Simply sets a square, without any checking
  void Set(const int x, const int y, const Square state) noexcept;

  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  private:
  std::vector<std::vector<Square>> m_board;

  ///Create the delta-x and delta-y to search in the 8 directions
  static const std::vector<std::pair<int,int>> CreateDeltas() noexcept;

  static Player GetOtherPlayer(const Player player) noexcept;

  Square PlayerToSquare(const Player player) const noexcept;

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
