

#ifndef UnitMovementPatternH
#define UnitMovementPatternH

#include <vector>
#include <boost/shared_ptr.hpp>
#include "athleticlandfwd.h"

namespace ribi {
namespace athl {

struct Movement;

struct MovementPattern
{
  virtual void Move() = 0;
  virtual ~MovementPattern() {}
  virtual void Restart() = 0;
};

struct NoMovePattern : public MovementPattern
{
  void Tick() {}
  void Restart() {}
};

struct ComplexMovePattern : public MovementPattern
{
  ComplexMovePattern()
  :
    m_cur_index(0),
    m_movements{}
  {

  }

  void AddStraightLineMovement(double& x,double& y,const int cnt,const double dx, const double dy);
  void AddTeleportMovement(double& x,double& y,const double dest_x, const double dest_y);
  void AddWaitMovement(const int cnt);

  void Move();
  void Restart() { m_cur_index = 0; }

  private:
  int m_cur_index;
  std::vector<boost::shared_ptr<Movement> > m_movements;
};

} //~namespace ribi
} //~namespace athl

#endif
