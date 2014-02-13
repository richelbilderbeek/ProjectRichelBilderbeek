#ifndef CONNECTTHREEPLAYER_H
#define CONNECTTHREEPLAYER_H

namespace ribi {
namespace con3 {

enum class Player { player1, player2, player3 };

Player GetNextPlayer(const Player player) noexcept;

} //~namespace con3
} //~namespace ribi

#endif // CONNECTTHREEPLAYER_H
