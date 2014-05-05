#ifndef RIBI_CHESSPLAYER_H
#define RIBI_CHESSPLAYER_H

#include <string>
#include <vector>

namespace ribi {
namespace Chess {

///Player is a chess player
enum class Player { white, black };
std::string PlayerToStr(const Player player) noexcept;

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSPLAYER_H
