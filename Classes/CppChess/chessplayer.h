#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <string>
#include <vector>

namespace ribi {
namespace Chess {

///Player is a chess player
enum class Player { white, black };
const std::string PlayerToStr(const Player player);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPLAYER_H
