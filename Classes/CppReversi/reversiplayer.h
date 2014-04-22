#ifndef REVERSIPLAYER_H
#define REVERSIPLAYER_H

#include <string>

namespace ribi {
namespace reversi {

enum class Player { player1, player2 };

std::string PlayerToStr(const Player player) noexcept;

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIPLAYER_H
