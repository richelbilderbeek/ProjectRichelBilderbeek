#ifndef RIBI_CHESSBOARDFACTORY_H
#define RIBI_CHESSBOARDFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chessboard.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///Factory for creating a Chess::Board
struct BoardFactory
{
  BoardFactory();

  boost::shared_ptr<Chess::Board> Create(
    const Chess::Board::Pieces& pieces = Chess::Board::GetInitialSetup()
  ) const;


  boost::shared_ptr<Chess::Board> DeepCopy(const Board& board) const;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSBOARDFACTORY_H
