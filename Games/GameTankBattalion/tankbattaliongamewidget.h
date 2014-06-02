#ifndef TANKBATTALIONGAMEWIDGET_H
#define TANKBATTALIONGAMEWIDGET_H

#include <array>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "tankbattaliondirection.h"
#include "tankbattalionfwd.h"
#include "tankbattalionkey.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace taba {

struct GameWidget
{
  GameWidget();
  boost::shared_ptr<const Arena> GetArena() const { return m_arena; }
  Direction GetDirection() const noexcept { return m_direction; }

  int GetPlayerX() const noexcept { return m_x; }
  int GetPlayerY() const noexcept { return m_y; }

  void OnTimer() noexcept;

  ///Responds to a key press
  void PressKey(const Key key);

  ///Responds to a key release
  void ReleaseKey(const Key key);

  private:

  const boost::shared_ptr<Arena> m_arena;

  Direction m_direction;

  ///The primary key, if any, is at index 0
  ///The secondary key, if any, is at index 1
  std::vector<Key> m_keys;
  int m_x;
  int m_y;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONGAMEWIDGET_H
