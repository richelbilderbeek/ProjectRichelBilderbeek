//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop
//---------------------------------------------------------------------------
#include <cassert>
#include "UnitConnector.h"
#include "UnitDisplay.h"
//---------------------------------------------------------------------------
//The InternalConnection 'attachedTo' is not const, because
//here the soldering takes place: the InternalConnections
//'attachedTo' and 'mConnection' are mutually connected
Display::Display(InternalConnection * const attachedTo)
  : mConnection(boost::shared_ptr<InternalConnection>(new
      InternalConnection(this)))
{
  assert(mConnection.get() != 0);
  //Connect the Display and (an InternalConnection of) a Machine
  mConnection->Connect(attachedTo);
  attachedTo->Connect(mConnection.get());
  assert(mConnection->IsConnected() == true);
  assert(attachedTo->IsConnected() == true);
}
//---------------------------------------------------------------------------
const bool Display::HasPower() const
{
  const Connector * const otherConnector = mConnection->GetConnectedTo();
  assert(otherConnector != 0
    && "Display must be internally connected to a Machine");
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  return (otherMachine->HasPower());
}
//---------------------------------------------------------------------------
const double Display::GetDisplayIntensity() const
{
  const Connector * const otherConnector = mConnection->GetConnectedTo();
  assert(otherConnector != 0
    && "Display must be internally connected to a Machine");
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  //The display intensity is managed by the internal connector
  //in the other machine
  return (otherMachine->PowerSupplyStrength(
    otherConnector,
    std::vector<const Connector*>()));
}
//---------------------------------------------------------------------------
AudioSignalDisplay::AudioSignalDisplay(InternalConnection * const attachedTo)
  : Display(attachedTo)
{

}
//---------------------------------------------------------------------------
LcdDisplay::LcdDisplay(InternalConnection * const attachedTo)
  : Display(attachedTo)
{

}
//---------------------------------------------------------------------------
LcdSymbol::LcdSymbol(InternalConnection * const attachedTo)
  : Display(attachedTo)
{

}
//---------------------------------------------------------------------------
Led::Led(InternalConnection * const attachedTo,
  const int red, const int green, const int blue)
  : Display(attachedTo),
    mRed(red), mGreen(green), mBlue(blue)
{
  assert(mRed   >= 0); assert(mRed   < 256);
  assert(mGreen >= 0); assert(mGreen < 256);
  assert(mBlue  >= 0); assert(mBlue  < 256);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
