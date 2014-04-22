#ifndef WORLDTYPE_H
#define WORLDTYPE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace tron {

struct WorldType
{
  protected:
  WorldType(const int width, const int height)
    : m_width(width), m_height(height) {}

  const int m_width;
  const int m_height;
  virtual ~WorldType() {}

  public:
  virtual void RespondToPlayer(double& x, double& y, bool& dead) const = 0;
};

struct WorldTypeDonut : public WorldType
{
  WorldTypeDonut(const int width, const int height)
    : WorldType(width,height) {}

  void RespondToPlayer(double& x, double& y, bool&) const
  {
    if (x <        0) x+=m_width;
    if (x >= m_width) x-=m_width;
    if (y <         0) y+=m_height;
    if (y >= m_height) y-=m_height;
  }
};

struct WorldTypeSquare : public WorldType
{
  WorldTypeSquare(const int width, const int height)
    : WorldType(width,height) {}

  void RespondToPlayer(double& x, double& y, bool& dead) const
  {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) dead = true;
  }
};

} //~namespace tron
} //~namespace ribi

#endif // WORLDTYPE_H
