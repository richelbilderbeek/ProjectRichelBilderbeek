//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitMovement.h"
#include "UnitMovementPattern.h"

//---------------------------------------------------------------------------
void ComplexMovePattern::Move()
{
  const int n_movements = static_cast<int>(m_movements.size());

  assert(m_cur_index < n_movements);
  assert(m_movements[m_cur_index]);

  m_movements[m_cur_index]->Move();

  if (m_movements[m_cur_index]->IsDone())
  {
    //Reset old move
    m_movements[m_cur_index]->Restart();
    //Go to next move
    m_cur_index = (m_cur_index + 1) % n_movements;
  }
}
//---------------------------------------------------------------------------
void ComplexMovePattern::AddStraightLineMovement(double& x,double& y,const int cnt,const double dx, const double dy)
{
  assert(cnt > 0);
  boost::shared_ptr<Movement> m(new StraightLineMovement(x,y,cnt,dx,dy));
  m_movements.push_back(m);
}
//---------------------------------------------------------------------------
void ComplexMovePattern::AddTeleportMovement(double& x,double& y,const double dest_x, const double dest_y)
{
  boost::shared_ptr<Movement> m(new TeleportMovement(x,y,dest_x,dest_y));
  m_movements.push_back(m);
}
//---------------------------------------------------------------------------
void ComplexMovePattern::AddWaitMovement(const int cnt)
{
  assert(cnt > 0);
  boost::shared_ptr<Movement> m(new WaitMovement(cnt));
  m_movements.push_back(m);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
