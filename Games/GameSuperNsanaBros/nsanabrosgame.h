#ifndef NSANABROSGAME_H
#define NSANABROSGAME_H

#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>
#include <boost/timer.hpp>

//#include "nsanabroskeys.h"
//#include "nsanabrosplayer.h"
//#include "nsanabrosscreen.h"

#include "nsanabrosstlfwdheader.h"
#pragma GCC diagnostic pop

struct NsanaBrosGame : public boost::noncopyable
{
  NsanaBrosGame();
  const NsanaBrosKeys * GetKeys() const;
  const NsanaBrosPlayer * GetPlayer() const;
  const std::vector<const NsanaBrosSprite*> GetSprites() const;

  static int GetHeight();
  static int GetWidth();
  void KeyPress(const int key);
  void KeyRelease(const int key);
  void OnTimer();

  mutable boost::signals2::signal<void()> m_signal_repaint;

  private:
  ~NsanaBrosGame() {}
  friend void boost::checked_delete<>(NsanaBrosGame *);

  boost::scoped_ptr<NsanaBrosKeys> m_keys;
  boost::scoped_ptr<NsanaBrosPlayer> m_player;
  std::vector<boost::shared_ptr<NsanaBrosSprite> > m_sprites;

  static const double m_height;
  static const double m_width;
  static const double m_dy_gravity;

  static const std::vector<boost::shared_ptr<NsanaBrosSprite> > CreateTestSprites();
};
//---------------------------------------------------------------------------

#endif // NSANABROSGAME_H
