#ifndef MAZIAKDISPLAY_H
#define MAZIAKDISPLAY_H

#include "maziakgamestate.h"

namespace ribi {
namespace maziak {

struct MainDialog;

///Displays Maziak in any way
///Cannot use Boost or Qt due to NDS library
struct Display
{
  Display();

  virtual ~Display() {}

  //Put the MainDialog on screen
  virtual void DoDisplay(const MainDialog& main_dialog) = 0;

  bool GetShowSolution() const noexcept { return m_show_solution; }
  GameState GetGameState() const noexcept { return m_game_state; }

  int GetViewHeight();
  int GetViewWidth();

  void SetGameState(const GameState game_state) noexcept { m_game_state = game_state; }

  void SetShowSolution(const bool show_solution) noexcept { m_show_solution = show_solution; }

  private:
  bool m_show_solution;
  GameState m_game_state;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKDISPLAY_H
