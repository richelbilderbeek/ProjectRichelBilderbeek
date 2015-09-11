#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "maziakmaindialog.h"

#include <cassert>
#include <iostream>

#include "maziakkey.h"
#include "maziakmaze.h"
#include "maziakdisplay.h"
#include "maziakintmaze.h"
#include "maziakdistancesmaze.h"
#include "maziakreceiver.h"
#include "maziaksolutionmaze.h"
#include "maziaksprites.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::maziak::MainDialog::MainDialog(const int maze_size)
  : m_direction(PlayerDirection::pdDown),
    m_display{nullptr},
    m_distances{},
    m_do_show_solution{false},
    m_fighting_frame(0),
    m_has_sword(true),
    m_maze(maze_size),
    m_move_now(PlayerMove::none),
    m_solution{},
    m_state{GameState::playing},
    m_x(-1),
    m_y(-1)
{
  #ifndef NDEBUG
  Test();
  #endif

  {
    const std::pair<int,int> exit = m_maze.FindExit();
    m_distances = m_maze.GetIntMaze().GetDistancesMaze(exit.first,exit.second);
  }
  {
    const std::pair<int,int> start = m_maze.FindStart();
    m_x = start.first;
    m_y = start.second;
  }
  assert(maze_size && "Maze size must be 7 + (4 * n) for n e [0,->>");
  assert(m_maze.IsSquare());

  m_solution = CreateNewSolution();

}

void ribi::maziak::MainDialog::AnimateEnemiesAndPrisoners(
  const int view_width,
  const int view_height
) noexcept
{
  m_maze.AnimateEnemiesAndPrisoners(
    m_x,
    m_y,
    view_width,
    view_height
  );
}

void ribi::maziak::MainDialog::AnimateFighting() noexcept
{
  if (m_fighting_frame > 0)
  {
    ++m_fighting_frame;
    if (m_fighting_frame == 13)
    {
      if (!m_has_sword)
      {
        m_state = GameState::game_over;
        m_display->SetGameState(m_state);
        return;
      }
      m_fighting_frame = 0;
      m_has_sword = false;
    }
  }
}

ribi::maziak::SolutionMaze ribi::maziak::MainDialog::CreateNewSolution() noexcept
{
  SolutionMaze solution(m_distances,m_x,m_y);
  return solution;
}


void ribi::maziak::MainDialog::Execute() noexcept
{
  while (1)
  {
    m_display->DoDisplay(*this);
    if (this->GetState() == GameState::game_over) break;
    if (this->GetState() == GameState::has_won) break;

    const auto keys = m_display->RequestKeys();

    PressKeys(keys);

    m_do_show_solution = m_display->GetDoShowSolution();

    RespondToCurrentSquare();

    const int view_width  = m_display->GetViewWidth(); //Was 20
    const int view_height = m_display->GetViewHeight(); //Was 20
    if (m_display->MustAnimateEnemiesAndPrisoners())
    {
      AnimateEnemiesAndPrisoners(view_width,view_height);
    }
    if(m_fighting_frame > 0)
    {
      AnimateFighting();
    }
  }
}

ribi::maziak::Sprite ribi::maziak::MainDialog::GetSpriteFloor(
  const Maze& maze,
  const int x,
  const int y,
  const bool do_show_solution,
  const SolutionMaze& solution
) noexcept
{
  assert(do_show_solution == false || solution.GetSize() == maze.GetSize());
  if (!maze.CanGet(x,y)) { return Sprite::wall; }
  else if (do_show_solution
    && solution.Get(x,y) == 1
    && ( maze.Get(x,y) == MazeSquare::msEmpty
      || maze.Get(x,y) == MazeSquare::msEnemy1
      || maze.Get(x,y) == MazeSquare::msEnemy2)
    )
  {
    return Sprite::path;
  }
  return Sprite::empty;
}

ribi::maziak::Sprite ribi::maziak::MainDialog::GetSpriteAboveFloor(
  const int x,
  const int y,
  const Maze& maze
) noexcept
{
  if (!maze.CanGet(x,y)) { return Sprite::wall; }
  //What else here?
  switch(maze.Get(x,y))
  {
    case MazeSquare::msStart     :
    case MazeSquare::msEmpty     : return Sprite::transparent;
    case MazeSquare::msWall      : return Sprite::wall;
    case MazeSquare::msEnemy1    : return Sprite::enemy1;
    case MazeSquare::msEnemy2    : return Sprite::enemy2;
    case MazeSquare::msPrisoner1 : return Sprite::prisoner1;
    case MazeSquare::msPrisoner2 : return Sprite::prisoner2;
    case MazeSquare::msSword     : return Sprite::sword;
    case MazeSquare::msExit      : return Sprite::exit;
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unexpected MazeSquare at mMaze");
  }
}

ribi::maziak::Sprite ribi::maziak::MainDialog::GetSpritePlayer(
  const PlayerDirection direction,
  const PlayerMove move,
  const bool has_sword,
  const int fighting_frame
) noexcept
{
  switch (fighting_frame)
  {
    case  0: break;
    case  1: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  2: return Sprite::fight2;
    case  3: return Sprite::fight3;
    case  4: return Sprite::fight4;
    case  5: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  6: return Sprite::fight2;
    case  7: return Sprite::fight3;
    case  8: return Sprite::fight4;
    case  9: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 10: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
    case 11: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 12: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
  }

  switch (direction)
  {
    case PlayerDirection::pdUp:
    {
      switch (move)
      {
      case PlayerMove::none: return has_sword ? Sprite::player_look_up_sword : Sprite::player_look_up;
      case PlayerMove::up1:  return has_sword ? Sprite::player_walk_up_sword1 : Sprite::player_walk_up1;
      case PlayerMove::up2:  return has_sword ? Sprite::player_walk_up_sword2 : Sprite::player_walk_up2;
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == up");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdRight:
    {
      switch (move)
      {
        case PlayerMove::none:   return has_sword ? Sprite::player_look_right_sword : Sprite::player_look_right;
        case PlayerMove::right1: return has_sword ? Sprite::player_walk_right_sword1 : Sprite::player_walk_right1;
        case PlayerMove::right2: return has_sword ? Sprite::player_walk_right_sword2 : Sprite::player_walk_right2;
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == right");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdDown:
    {
      switch (move)
      {
      case PlayerMove::none:  return has_sword ? Sprite::player_look_down_sword : Sprite::player_look_down;
      case PlayerMove::down1: return has_sword ? Sprite::player_walk_down_sword1 : Sprite::player_walk_down1;
      case PlayerMove::down2: return has_sword ? Sprite::player_walk_down_sword2 : Sprite::player_walk_down2;
      default:
        assert("!Should not get here");
        throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == down");
      }
    }
    //break; Unreachable
    case PlayerDirection::pdLeft:
    {
      switch (move)
      {
        case PlayerMove::none:  return (has_sword ? Sprite::player_look_left_sword : Sprite::player_look_left);
        case PlayerMove::left1: return (has_sword ? Sprite::player_walk_left_sword1 : Sprite::player_walk_left1);
        case PlayerMove::left2: return (has_sword ? Sprite::player_walk_left_sword2 : Sprite::player_walk_left2);
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == left");
      }
    }
      //break; Unreachable
    default:
      assert("!Should not get here");
    throw std::logic_error("Unsupported PlayerDirection");
  }
  //Unreachable
}

void ribi::maziak::MainDialog::PressKeys(const std::set<Key>& keys)
{
  if (m_fighting_frame > 0) return;
  if (keys.empty()) { m_move_now = PlayerMove::none; return; }

  for(const Key key: keys)
  {
    //Check the keys pressed
    switch (key)
    {
      case Key::left:
        m_direction = PlayerDirection::pdLeft;
        if (!m_maze.CanMoveTo(m_x-1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::left1 ? PlayerMove::left2 : PlayerMove::left1);
        --m_x;
        break;
      case Key::right:
        m_direction = PlayerDirection::pdRight;
        if (!m_maze.CanMoveTo(m_x+1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::right1 ? PlayerMove::right2 : PlayerMove::right1);
        ++m_x;
        break;
      case Key::up:
        m_direction = PlayerDirection::pdUp;
        if (!m_maze.CanMoveTo(m_x,m_y-1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::up1 ? PlayerMove::up2 : PlayerMove::up1);
        --m_y;
        break;
      case Key::down:
        m_direction = PlayerDirection::pdDown;
        if (!m_maze.CanMoveTo(m_x,m_y+1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::down1 ? PlayerMove::down2 : PlayerMove::down1);
        ++m_y;
        break;
      default:
        m_move_now = PlayerMove::none;
        continue;
    }
  }
}

void ribi::maziak::MainDialog::SetDisplay(Display * const display)
{

  m_display = display;
}

void ribi::maziak::MainDialog::RespondToCurrentSquare() noexcept
{
  assert(m_maze.CanGet(m_x,m_y));
  switch (m_maze.Get(m_x,m_y))
  {
    case MazeSquare::msStart:
    case MazeSquare::msEmpty:
      break;
    case MazeSquare::msWall:
      assert(!"Should not get here");
      throw std::logic_error("Player cannot be in wall");
    case MazeSquare::msEnemy1: case MazeSquare::msEnemy2:
      m_fighting_frame = 1;
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      break;
    case MazeSquare::msPrisoner1: case MazeSquare::msPrisoner2:
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      m_solution = CreateNewSolution();
      assert(m_solution.IsSquare());
      this->m_display->StartShowSolution();
      m_do_show_solution = true;
      m_display->StartShowSolution();
      break;
    case MazeSquare::msSword:
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      m_has_sword = true;
      break;
    case MazeSquare::msExit:
    {
      m_state = GameState::has_won;
      m_display->SetGameState(GameState::has_won);
      break;
    }
    default:
      assert(!"Should not get here");
      break;
  }
}

#ifndef NDEBUG
void ribi::maziak::MainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
