//---------------------------------------------------------------------------
#ifndef UnitMovementH
#define UnitMovementH
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
// A Movement changes the x and y coordinat or the client
// * NeverMovement: the client never changes its coordinats
// * StraightLineMovement: the client moves in a straight line for some time
// * TeleportMovement: the client teleports once
// * WaitMovement: the client waits (it does not change its coordinats)
//     for some time
//---------------------------------------------------------------------------
struct Movement
{
  virtual ~Movement() {}
  virtual void Move() = 0;
  virtual const bool IsDone() const = 0;
  virtual void Restart() = 0;
};
//---------------------------------------------------------------------------
struct NeverMovement : public Movement
{
  void Move() {}
  const bool IsDone() const { return false; }
  void Restart();
};
//---------------------------------------------------------------------------
struct StraightLineMovement : public Movement
{
  StraightLineMovement(
    double& x,
    double& y,
    const int max_cnt,
    const double dx,
    const double dy)
    : m_x(x),
      m_y(y),
      m_cnt(0),
      m_max_cnt(max_cnt),
      m_dx(dx),
      m_dy(dy)
  {
    assert(max_cnt > 0);
  }
  void Move()
  {
    //Perform move
    m_x+=m_dx;
    m_y+=m_dy;
    //Make move end
    ++m_cnt;
    if (m_cnt == m_max_cnt) m_cnt = 0; //Movement has ended, prepare for next time
  }
  const bool IsDone() const
  {
    return (m_cnt == 0);
  }
  void Restart()
  {
    m_cnt = 0;
  }

  double& m_x;         //x-coordinat of sprite
  double& m_y;         //y-coordinat of sprite
  int m_cnt;           //count of move
  const int m_max_cnt; //maximal count of move
  const double m_dx;   //change in x-coordinat of sprite
  const double m_dy;   //change in y-coordinat of sprite

};
//---------------------------------------------------------------------------
struct TeleportMovement : public Movement
{
  TeleportMovement(
    double& x,
    double& y,
    const double target_x,
    const double target_y)
    : m_x(x),
      m_y(y),
      m_target_x(target_x),
      m_target_y(target_y)
  {

  }
  void Move()
  {
    //Perform move
    m_x=m_target_x;
    m_y=m_target_y;
  }
  const bool IsDone() const
  {
    return true; //Assume only one teleport, so after each Move IsDone returns true
  }
  void Restart() {}

  double& m_x;         //x-coordinat of sprite
  double& m_y;         //y-coordinat of sprite
  const double m_target_x;
  const double m_target_y;
};
//---------------------------------------------------------------------------
struct WaitMovement : public Movement
{
  WaitMovement(const int max_cnt)
    : m_max_cnt(max_cnt),
      m_cnt(0)
  {
    assert(max_cnt > 0);
  }
  void Move() //Assumes Move is called before IsDone
  {
    //Make move end
    ++m_cnt;
    if (m_cnt == m_max_cnt) m_cnt = 0; //Movement has ended, prepare for next time
  }
  const bool IsDone() const //Assumes Move is called before IsDone
  {
    return (m_cnt == 0);
  }
  void Restart()
  {
    m_cnt = 0;
  }

  private:
  const int m_max_cnt;
  int m_cnt;

};
//---------------------------------------------------------------------------
#endif
