//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitController.h"
#include "UnitConnector.h"

#include "UnitOctlet.h"
//---------------------------------------------------------------------------
Octlet::Octlet()
  : mPowerSwitch(boost::shared_ptr<TwoSwitch>(new TwoSwitch)),
    mPlug(boost::shared_ptr<Plug220>(new Plug220(this))),
    mSockets220(CreateSockets220())
{

}
//---------------------------------------------------------------------------
const double Octlet::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  if (mPowerSwitch->IsOn() == false) return 0.0;
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
  prevConnectors.push_back(inputConnection);
  return inputMachine->PowerSupplyStrength(inputConnection,prevConnectors);
}
//---------------------------------------------------------------------------
const bool Octlet::HasPower() const
{
  //The power of the Machine the plug is connected to
  const Connector * const connectedTo = mPlug->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);
  if (otherMachine == this) return 0.0; //Octlet is connected to itself
  return (otherMachine->PowerSupplyStrength(connectedTo,
    std::vector<const Connector*>()) > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
const std::vector<boost::shared_ptr<Socket220> > Octlet::CreateSockets220() const
{
  std::vector<boost::shared_ptr<Socket220> > sockets;
  const int nSockets = 8; //An octlet has 8 sockets per definition

  for (int i=0; i!=nSockets; ++i)
  {
    boost::shared_ptr<Socket220> socket(new Socket220(this));
    sockets.push_back(socket);
  }
  return sockets;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
