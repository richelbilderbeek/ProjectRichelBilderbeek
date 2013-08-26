//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitController.h" //For Fader, etc..
#include "UnitConnector.h"
#include "UnitDisplay.h"
#include "UnitAmplifier.h"
//---------------------------------------------------------------------------
EasyAmp::EasyAmp()
  : //Use
    mPowerSwitch(boost::shared_ptr<TwoSwitch>(new TwoSwitch)),
    mGain(boost::shared_ptr<Dial>(new Dial)),
    //Connect
    mEuroPower(boost::shared_ptr<EuroMale>(new EuroMale(this))),
    mJackXlrL(boost::shared_ptr<JackXlrFemale>(new JackXlrFemale(this))),
    mJackXlrR(boost::shared_ptr<JackXlrFemale>(new JackXlrFemale(this))),
    mSpeakonL(boost::shared_ptr<SpeakonFemale>(new SpeakonFemale(this))),
    mSpeakonR(boost::shared_ptr<SpeakonFemale>(new SpeakonFemale(this))),
    mConnectionLedPower(boost::shared_ptr<InternalConnection>(
      new InternalConnection(this)))
{
  //Display
  mLedPower = boost::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),255,0,0));

}
//---------------------------------------------------------------------------
const double EasyAmp::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{

  if ( connector == mConnectionLedPower.get()
    && this->mPowerSwitch->IsOn() == true)
  {
    return (this->HasPower() == true ? 1.0 : 0.0);
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double EasyAmp::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  if (this->HasPower() == false) return 0.0;
  if (this->mPowerSwitch->IsOn() == false) return 0.0;

  //Only the speakon plugs will supply audio signal
  if (connector != mSpeakonL.get() && connector != mSpeakonR.get())
  {
    return 0.0;
  }

  const Connector * const inputConnection
    = (connector == mSpeakonL.get()
    ? this->mJackXlrL->GetConnectedTo()
    : this->mJackXlrR->GetConnectedTo());
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
  const double gain = 2.0 * this->mGain->GetRelPosition();
  return audioInput * gain;
}
//---------------------------------------------------------------------------
//Does the machine have access to power? Does NOT mean the machine is ON!
const bool EasyAmp::HasPower() const
{
  const Connector * const connectedTo = this->mEuroPower->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);
  return (otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>()) > 0.0 ? true : false);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
