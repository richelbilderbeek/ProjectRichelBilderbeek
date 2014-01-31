#ifndef MAZIAKRECEIVER_H
#define MAZIAKRECEIVER_H

namespace ribi {
namespace maziak {

///Class used by MainDialog to receive its own signals
struct Receiver
{
  Receiver();

  ///Has the game been lost?
  bool IsGameOver() const noexcept { return m_is_game_over; }

  ///Has the game been won?
  bool IsGameWon() const noexcept { return m_is_game_won; }

  void OnGameOver() noexcept { m_is_game_over = true; }
  void OnGameWon()  noexcept { m_is_game_won = true;  }
  void OnStartShowingSolution() noexcept { m_show_solution = true; }
  void OnStopShowingSolution()  noexcept { m_show_solution = false; }

  ///Should the solution stop being shown
  bool StopShowingSolution() const noexcept { return m_stop_showing_solution; }

  ///Indicate the solution has already stopped being shown
  void StoppedShowingSolution() noexcept { m_stop_showing_solution = false; }

  private:

  bool m_is_game_over;
  bool m_is_game_won;
  bool m_show_solution;
  bool m_stop_showing_solution;

};

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKRECEIVER_H
