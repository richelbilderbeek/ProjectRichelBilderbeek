#ifndef MAZIAKMAINDIALOG_H
#define MAZIAKMAINDIALOG_H

#include <set>
#include <vector>

#include "maziakfwd.h"
#include "maziakkey.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "maziakdistancesmaze.h"
#include "maziakmaze.h"
#include "maziakgamestate.h"
#include "maziaksolutionmaze.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "maziaksprite.h"
//#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

struct Display;

struct MainDialog
{
  MainDialog(const int maze_size);

  MainDialog(const MainDialog&) = delete;
  MainDialog& operator=(const MainDialog&) = delete;

  void AnimateEnemiesAndPrisoners(const int view_width, const int view_height) noexcept;

  void AnimateFighting() noexcept;


  ///Play the game
  void Execute() noexcept;

  const Maze& GetMaze() const noexcept { return m_maze; }
  bool GetDoShowSolution() const noexcept { return m_do_show_solution; }

  PlayerDirection GetPlayerDirection() const noexcept { return m_direction; }
  int GetPlayerFightingFrame() const noexcept { return m_fighting_frame; }
  bool GetPlayerHasSword() const noexcept { return m_has_sword; }
  PlayerMove GetPlayerMove() const noexcept { return m_move_now; }

  const SolutionMaze& GetSolution() const noexcept { return m_solution; }

  Sprite GetSpriteFloor(const int x,const int y) const noexcept { return GetSpriteFloor(m_maze,x,y,m_do_show_solution,m_solution); }
  Sprite GetSpriteAboveFloor(const int x,const int y) const noexcept { return GetSpriteAboveFloor(x,y,m_maze); }
  Sprite GetSpritePlayer() const noexcept { return GetSpritePlayer(m_direction,m_move_now,m_has_sword,m_fighting_frame); }

  static Sprite GetSpriteFloor(
    const Maze& maze,
    const int x,
    const int y,
    const bool show_solution,
    const SolutionMaze& solution
  ) noexcept;
  static Sprite GetSpriteAboveFloor(
    const int x,
    const int y,
    const Maze& m_maze
  ) noexcept;
  static Sprite GetSpritePlayer(
    const PlayerDirection direction,
    const PlayerMove moveNow,
    const bool m_has_sword,
    const int m_fighting_frame
  ) noexcept;

  GameState GetState() const noexcept { return m_state; }

  int GetX() const noexcept { return m_x; }
  int GetY() const noexcept { return m_y; }

  ///Press all active keys
  void PressKeys(const std::set<Key>& keys);

  void RespondToCurrentSquare() noexcept;

  ///Set how the game is displayed
  void SetDisplay(Display * const display);

  private:

  PlayerDirection m_direction;
  Display * m_display;
  DistancesMaze m_distances;

  ///Shows the solution. This really is a member variable of this class,
  ///as it determines if a player can or cannot walk upon a prisoner square
  bool m_do_show_solution;

  int m_fighting_frame;
  bool m_has_sword;
  Maze m_maze;
  PlayerMove m_move_now;


  SolutionMaze m_solution;
  GameState m_state;
  int m_x;
  int m_y;

  SolutionMaze CreateNewSolution() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace maziak
} //namespace ribi


#endif // MAZIAKMAINDIALOG_H
