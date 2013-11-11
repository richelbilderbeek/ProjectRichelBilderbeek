#ifndef NSANABROSPLAYER_H
#define NSANABROSPLAYER_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "nsanabrosstlfwdheader.h"
#pragma GCC diagnostic pop

namespace ribi {

///NsanaBrosPlayer is the main player.
struct NsanaBrosPlayer
{
  NsanaBrosPlayer();
  NsanaBrosPlayer(const NsanaBrosPlayer&) = delete;
  NsanaBrosPlayer& operator=(const NsanaBrosPlayer&) = delete;

  double GetDx() const noexcept { return m_dx; }
  double GetDy() const noexcept { return m_dy; }
  double GetHeight() const;
  boost::shared_ptr<const NsanaBrosSprite> GetSprite() const;
  double GetWidth() const;
  double GetX() const;
  double GetY() const;
  void Move();
  void RespondToKeys(const boost::shared_ptr<const NsanaBrosKeys> keys);
  void SetDx(const double dx);
  void SetDy(const double dy);
  void Translate(const double dx, const double dy);

  private:
  ~NsanaBrosPlayer() {}
  friend void boost::checked_delete<>(NsanaBrosPlayer *);

  boost::shared_ptr<NsanaBrosSprite> m_sprite;
  double m_dx;
  double m_dy;

  static const double m_dy_jump;
  static const double m_dx_walk;
};

std::ostream& operator<<(std::ostream& os, const NsanaBrosPlayer& p);

} //~namespace ribi

#endif // NSANABROSPLAYER_H
