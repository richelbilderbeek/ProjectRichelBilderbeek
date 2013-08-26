//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitSimpleSound1.h"
//---------------------------------------------------------------------------
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
SimpleSound1::SimpleSound1()
  : mFaderMaster(boost::shared_ptr<Fader>(new Fader)),
    mMic1(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMasterL(boost::shared_ptr<XlrMale>(new XlrMale(this))),
    mMasterR(boost::shared_ptr<XlrMale>(new XlrMale(this))),
    mPower(boost::shared_ptr<EuroMale>(new EuroMale(this))),
    mConnectionAudioSignal(
     boost::shared_ptr<InternalConnection>(new InternalConnection(this)))
{
  mAudioSignalDisplay = boost::shared_ptr<AudioSignalDisplay>(
    new AudioSignalDisplay(mConnectionAudioSignal.get()));

}
//---------------------------------------------------------------------------
const double SimpleSound1::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  assert(connector != 0);
  if (this->HasPower() == false) return 0.0;

  if (connector == mConnectionAudioSignal.get())
  {
    const Connector * const connectedTo = this->mMic1->GetConnectedTo();
    if (connectedTo == 0) return 0.0;
    const Machine * const otherMachine = connectedTo->mBelongsTo;
    assert(otherMachine != 0);
    const double audioInput = otherMachine->AudioSignalStrength(
      connectedTo,std::vector<const Connector*>());
    return audioInput;
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double SimpleSound1::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert (connector == mMasterL.get() || connector == mMasterR.get() );

  if (this->HasPower() == false) return 0.0;

  //Sound levels for L and R channel are equal for the SimpleSound
  //Mic1 connected to something?
  const Connector * const inputConnection = this->mMic1->GetConnectedTo();
  if (inputConnection == 0) return 0.0;
  //Prevent loops of connection
  if (std::find(prevConnectors.begin(),prevConnectors.end(),inputConnection)
    != prevConnectors.end())
  {
    return 0.0;
  }
  //Correct connection
  const Machine * const inputMachine = inputConnection->mBelongsTo;
  assert(inputMachine != 0);
  prevConnectors.push_back(connector); //We just checked connector...
  const double audioInput = inputMachine->AudioSignalStrength(
    inputConnection,prevConnectors);
  const double masterThroughput = 2.0 * this->mFaderMaster->GetRelPosition();
  return audioInput * masterThroughput;
}
//---------------------------------------------------------------------------
const bool SimpleSound1::HasPower() const
{
  assert(this->mPower.get() != 0);
  const Connector * const connectedTo = this->mPower->GetConnectedTo();
  if (connectedTo == 0)
  {
    //Power socket (euro male) not connected to anything
    return false;
  }
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);

  const double powerSupply = otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>());
  return (powerSupply > 0.0 ? true : false);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
