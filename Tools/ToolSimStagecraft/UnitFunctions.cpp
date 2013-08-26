//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitFunctions.h"

#include <cmath>
#include <cassert>

//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppGetAngle.htm
const double GetAngle(const double dX, const double dY)
{
  //In which quadrant are we?
  if (dX > 0)
  {
    if (dY > 0)
    {
      //dX > 0 && dY > 0
      //Quadrant IV
      assert(dX > 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 0.5 * M_PI && angle < 1.0 * M_PI);
      return angle;
    }
    else if (dY < 0)
    {
      //dX > 0 && dY <= 0
      //Quadrant I
      assert(dX > 0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 0.0 * M_PI && angle < 0.5 * M_PI);
      return angle;
    }
    else
    {
      //dX > 0.0 && dY == 0.0
      //On Y-axis, right side
      assert(dX > 0.0 && dY == 0.0);
      const double angle = (0.5 * M_PI);
      return angle;
    }
  }
  else if (dX < 0.0)
  {
    if (dY > 0.0)
    {
      //dX < 0 && dY > 0
      //Quadrant III
      assert(dX < 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 1.0 * M_PI && angle < 1.5 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX < 0 && dY < 0
      //Quadrant II
      assert(dX < 0.0 && dY < 0.0);
      const double angle = (2.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 1.5 * M_PI && angle < 2.0 * M_PI);
      return angle;
    }
    else
    {
      //dX < 0 && dY == 0
      //On X-axis
      assert(dX < 0.0 && dY == 0.0);
      const double angle = (1.5 * M_PI);
      return angle;
    }
  }
  else
  {
    if (dY > 0.0)
    {
      //dX == 0 && dY > 0.0)
      //On Y-axis, right side of origin
      assert(dX==0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX == 0 && dY < 0.0)
      //On Y-axis, left side of origin
      assert(dX==0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
    else
    {
      //dX == 0 && dY == 0.0)
      //On origin
      assert(dX==0.0 && dY == 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
  }
}
//---------------------------------------------------------------------------
const double GetDistance(const double dX, const double dY)
{
  return std::sqrt((dX * dX) + (dY * dY));
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
