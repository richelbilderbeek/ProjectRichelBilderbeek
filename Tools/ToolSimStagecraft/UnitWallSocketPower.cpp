//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cassert>
#include "UnitConnector.h"
#include "UnitWallSocketPower.h"
//---------------------------------------------------------------------------
WallSocketPower::WallSocketPower()
  : mSocketPower(boost::shared_ptr<SocketPowerFemale>(new SocketPowerFemale(this)))
{
  assert(mSocketPower.get() != 0);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
