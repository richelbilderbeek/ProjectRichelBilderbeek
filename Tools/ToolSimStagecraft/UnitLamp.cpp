//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitConnector.h"
#include "UnitLamp.h"
#include <cassert>
//---------------------------------------------------------------------------
Par64::Par64()
  : mPlug220(boost::shared_ptr<Plug220>(new Plug220(this)))
{
  assert(mPlug220.get() != 0);
}
//---------------------------------------------------------------------------
const bool Par64::HasPower() const
{
  const Connector * const otherConnector = mPlug220->GetConnectedTo();
  if (otherConnector == 0) return false;
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  return (otherMachine->PowerSupplyStrength(
    otherConnector,
    std::vector<const Connector*>()) > 0.0);
}
//---------------------------------------------------------------------------
const double Par64::GetLightIntensity() const
{
  const Connector * const otherConnector = mPlug220->GetConnectedTo();
  if (otherConnector == 0) return 0.0;
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  return otherMachine->PowerSupplyStrength(
    otherConnector,
    std::vector<const Connector*>());
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
