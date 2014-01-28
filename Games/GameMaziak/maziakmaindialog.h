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
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "maziaksprite.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace maziak {

struct MainDialog
{
  MainDialog(const int maze_size);

  void AnimateEnemiesAndPrisoners(const int view_width, const int view_height) noexcept;

  void AnimateFighting() noexcept;

  bool GetDoShowSolution() const noexcept { return m_do_show_solution; }

  ///Play the game
  void Execute() noexcept;

  const boost::shared_ptr<const Maze> GetMaze() const noexcept { return m_maze; }

  PlayerDirection GetPlayerDirection() const noexcept { return m_direction; }
  int GetPlayerFightingFrame() const noexcept { return m_fighting_frame; }
  bool GetPlayerHasSword() const noexcept { return m_has_sword; }
  PlayerMove GetPlayerMove() const noexcept { return m_move_now; }

  const boost::shared_ptr<const SolutionMaze> GetSolution() const noexcept { return m_solution; }

  Sprite GetSpriteFloor(const int x,const int y) const noexcept { return GetSpriteFloor(m_maze,x,y,m_do_show_solution,m_solution); }
  Sprite GetSpriteAboveFloor(const int x,const int y) const noexcept { return GetSpriteAboveFloor(x,y,m_maze); }
  Sprite GetSpritePlayer() const noexcept { return GetSpritePlayer(m_direction,m_move_now,m_has_sword,m_fighting_frame); }

  int GetX() const noexcept { return m_x; }
  int GetY() const noexcept { return m_y; }

  ///Add a key
  void OnKeyPress(const Key key);

  ///Press all active keys
  void OnTimerPressKeys();

  ///Remove a key
  void OnKeyRelease(const Key key);

  void RespondToCurrentSquare() noexcept;

  void SetShowSolution(const bool do_show_solution) noexcept { m_do_show_solution = do_show_solution; }

  const boost::shared_ptr<const TextCanvas> ToTextCanvas(
    const int view_height,
    const int view_width
  ) const noexcept;

  boost::signals2::signal<void()> m_signal_game_over;
  boost::signals2::signal<void()> m_signal_game_won;
  boost::signals2::signal<void()> m_signal_start_showing_solution;
  private:


  PlayerDirection m_direction;
  boost::shared_ptr<const DistancesMaze> m_distances;
  bool m_do_show_solution;
  int m_fighting_frame;
  bool m_has_sword;
  std::set<Key> m_keys;
  const boost::shared_ptr<Maze> m_maze;
  PlayerMove m_move_now;
  boost::shared_ptr<const SolutionMaze> m_solution;
  int m_x;
  int m_y;

  const boost::shared_ptr<const SolutionMaze> CreateNewSolution() noexcept;

  static Sprite GetSpriteFloor(
    const boost::shared_ptr<const Maze> maze,
    const int x,
    const int y,
    const bool show_solution,
    const boost::shared_ptr<const SolutionMaze> solution
  ) noexcept;
  static Sprite GetSpriteAboveFloor(
    const int x,
    const int y,
    const boost::shared_ptr<const Maze> m_maze
  ) noexcept;
  static Sprite GetSpritePlayer(
    const PlayerDirection direction,
    const PlayerMove moveNow,
    const bool m_has_sword,
    const int m_fighting_frame
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace maziak
} //namespace ribi


#endif // MAZIAKMAINDIALOG_H
