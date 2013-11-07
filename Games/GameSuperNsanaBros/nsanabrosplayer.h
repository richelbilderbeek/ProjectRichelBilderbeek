#ifndef NSANABROSPLAYER_H
#define NSANABROSPLAYER_H

#include <iosfwd>

#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "nsanabrosstlfwdheader.h"

namespace ribi {

///NsanaBrosPlayer is the main player.
struct NsanaBrosPlayer : public boost::noncopyable
{
  NsanaBrosPlayer();
  double GetDx() const { return m_dx; }
  double GetDy() const { return m_dy; }
  double GetHeight() const;
  const NsanaBrosSprite * GetSprite() const;
  double GetWidth() const;
  double GetX() const;
  double GetY() const;
  void Move();
  void RespondToKeys(const NsanaBrosKeys * const keys);
  void SetDx(const double dx);
  void SetDy(const double dy);
  void Translate(const double dx, const double dy);

  private:
  ~NsanaBrosPlayer() {}
  friend void boost::checked_delete<>(NsanaBrosPlayer *);

  boost::scoped_ptr<NsanaBrosSprite> m_sprite;
  double m_dx;
  double m_dy;

  static const double m_dy_jump;
  static const double m_dx_walk;
};

std::ostream& operator<<(std::ostream& os, const NsanaBrosPlayer * const p);

} //~namespace ribi

#endif // NSANABROSPLAYER_H
