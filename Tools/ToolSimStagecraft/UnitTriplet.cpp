//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitController.h"
#include "UnitConnector.h"

#include "UnitTriplet.h"
//---------------------------------------------------------------------------
Triplet::Triplet()
  : mPlug(boost::shared_ptr<Plug220>(new Plug220(this))),
    mSocket220_1(boost::shared_ptr<Socket220>(new Socket220(this))),
    mSocket220_2(boost::shared_ptr<Socket220>(new Socket220(this))),
    mSocket220_3(boost::shared_ptr<Socket220>(new Socket220(this)))
{

}
//---------------------------------------------------------------------------
const double Triplet::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  //The power of the Machine the plug is connected to
  const Connector * const inputConnection = mPlug->GetConnectedTo();
  //Connected to something?
  if (inputConnection == 0) return 0.0;
  //Prevent loops of connection
  if (std::find(prevConnectors.begin(),prevConnectors.end(),inputConnection)
    != prevConnectors.end())
  {
    return 0.0;
  }
  const Machine * const inputMachine = inputConnection->mBelongsTo;
  assert(inputMachine != 0);
  //Everything okay...
  prevConnectors.push_back(connector); //We just checked connector...
  return inputMachine->PowerSupplyStrength(inputConnection,prevConnectors);
}
//---------------------------------------------------------------------------
const bool Triplet::HasPower() const
{
  //The power of the Machine the plug is connected to
  const Connector * const connectedTo = mPlug->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);
  //if (otherMachine == this) return 0.0; //Triplet is connected to itself
  return (otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>()) > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
