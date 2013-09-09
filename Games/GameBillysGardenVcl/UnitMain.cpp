
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <Types.hpp>
#include "UnitMovement.h"
#include "UnitMovementPattern.h"
#pragma hdrstop




void TestUnitMovement()
{
  double x = 0.0;
  double y = 0.0;
  boost::shared_ptr<Movement> m;

  {
    //Test NeverMoment
    m.reset(new NeverMovement);
    m->Move();
    assert(x == 0.0);
    assert(y == 0.0);
    assert(m->IsDone() == false);
  }

  {
    //Test WaitMovement
    const int n_wait = 100;
    m.reset(new WaitMovement(n_wait));
    for (int i=0; i!=n_wait-1; ++i)
    {
      m->Move();
      assert(m->IsDone()==false);
    }
    m->Move();
    assert(x == 0.0);
    assert(y == 0.0);
    assert(m->IsDone()==true);
  }

  {
    //Test TeleportMovement
    const double dest_x = 1.0;
    const double dest_y = 2.0;
    m.reset(new TeleportMovement(x,y,dest_x,dest_y));
    m->Move();
    assert(m->IsDone() == true);
    assert(x == dest_x);
    assert(y == dest_y);
  }

  {
    x = 0.0;
    y = 0.0;
    //Test StraightLineMovement
    const int cnt = 100;
    const double dx = 0.5;
    const double dy = 1.0;
    m.reset(new StraightLineMovement(x,y,cnt,dx,dy));
    for (int i=0; i!=cnt-1; ++i)
    {
      m->Move();
      assert(m->IsDone()==false);
    }
    m->Move();
    assert(m->IsDone()==true);
    assert( x == static_cast<double>(cnt)*dx);
    assert( y == static_cast<double>(cnt)*dy);
  }
}

void TestUnitMovementPattern()
{
  ComplexMovePattern p;
  double x = 0.0;
  double y = 0.0;
  p.AddTeleportMovement(x,y,20.0,10.0);
  p.AddStraightLineMovement(x,y,10,-2.0,-0.5);
  p.AddWaitMovement(5);

  for (int i=0; i!=20; ++i)
  {
    std::cout << x << '\t' << y << '\n';
    p.Move();
  }

}

const bool DoCollide(const Types::TRect& a, const Types::TRect& b)
{
  const int a_x1 = a.Left;
  const int a_x2 = a.Right;
  const int a_y1 = a.Top;
  const int a_y2 = a.Bottom;
  const int b_x1 = b.Left;
  const int b_x2 = b.Right;
  const int b_y1 = b.Top;
  const int b_y2 = b.Bottom;

  return (
     //Top-left of a in b?
     (a_x1 > b_x1 && a_x1 < b_x2 && a_y1 > b_y1 && a_y1 < b_y2)
     //Top-right of a in b?
  || (a_x2 > b_x1 && a_x2 < b_x2 && a_y1 > b_y1 && a_y1 < b_y2)
     //Bottom-left of a in b?
  || (a_x1 > b_x1 && a_x1 < b_x2 && a_y2 > b_y1 && a_y2 < b_y2)
     //Bottom-right of a in b?
  || (a_x2 > b_x1 && a_x2 < b_x2 && a_y2 > b_y1 && a_y2 < b_y2) );

}

int main(int argc, char* argv[])
{
  TestUnitMovement();
  TestUnitMovementPattern();

}