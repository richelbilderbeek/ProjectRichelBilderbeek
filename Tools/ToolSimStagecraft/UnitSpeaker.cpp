//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cassert>
#include "UnitController.h"
#include "UnitConnector.h"
#include "UnitSpeaker.h"
#include "UnitDisplay.h"
//---------------------------------------------------------------------------
Rcf322A::Rcf322A()
  : mPowerSwitch(boost::shared_ptr<TwoSwitch>(new TwoSwitch)),
    mVolumeDial(boost::shared_ptr<Dial>(new Dial)),
    mJackInput(boost::shared_ptr<JackFemale>(new JackFemale(this))),
    mXlrDaisyChain(boost::shared_ptr<XlrMale>(new XlrMale(this))),
    mXlrInput(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mEuroMalePower(boost::shared_ptr<EuroMale>(new EuroMale(this))),
    mConnectionLedPower(boost::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedLimProt(boost::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mMaxSoundLevel(1.5)
{
  //mLedPower is green
  mLedPower = boost::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),0,255,0));
  //mLedLimProt is red
  mLedLimProt = boost::shared_ptr<Led>(
    new Led(mConnectionLedLimProt.get(),255,0,0));
}
//---------------------------------------------------------------------------
const bool Rcf322A::HasPower() const
{
  const Connector * const connectedTo = this->mEuroMalePower->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const belongsTo = connectedTo->mBelongsTo;
  assert(belongsTo != 0);
  if (belongsTo->PowerSupplyStrength(connectedTo,
    std::vector<const Connector*>()) > 0.0) return true;
  return false;
}
//---------------------------------------------------------------------------
const double Rcf322A::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  if (connector == mConnectionLedPower.get() )
  {
    //The LED has power if the speaker is connected to something that can
    //supply power
    //AND its power is on
    if( this->mPowerSwitch->IsOn() == false) return 0.0;
    const Connector * const connectedTo = this->mEuroMalePower->GetConnectedTo();
    if (connectedTo == 0) return 0.0; //Connected to nothing
    const Machine * const belongsTo = connectedTo->mBelongsTo;
    assert(belongsTo != 0);
    if (belongsTo->PowerSupplyStrength(
      connectedTo,std::vector<const Connector*>()) > 0.0) return 1.0;
  }
  else if (connector == mConnectionLedLimProt.get() )
  {
    //The Limiter protection LED indicates if unlimited sound level is above 1.5
    if (this->GetUnlimitedSoundLevel() > mMaxSoundLevel) return 1.0;
  }
  return 0.0;
}
//---------------------------------------------------------------------------
//The sound level without the limiter acting
const double Rcf322A::GetUnlimitedSoundLevel() const
{
  const double soundLevel = 2.0 * this->mVolumeDial->GetRelPosition()
    * std::max(this->AudioSignalStrength(mJackInput.get(),
        std::vector<const Connector*>()),
      this->AudioSignalStrength(mXlrInput.get(),
        std::vector<const Connector*>()) );
  return soundLevel;
}
//---------------------------------------------------------------------------
//The sound level with the limiter acting
const double Rcf322A::GetSoundLevel() const
{
  const double soundLevel = GetUnlimitedSoundLevel();
  return std::min(soundLevel,mMaxSoundLevel);
}
//---------------------------------------------------------------------------
const double Rcf322A::AudioSignalStrength(const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector != 0);
  //Must have power
  if (this->HasPower() == false) return 0.0;
  //Must have power switch on
  if (this->mPowerSwitch->IsOn() == false) return 0.0;
  //'Forward' the audio signal received
  //No enhancement by volume dial!
  const Connector * const inputConnectionXlr  = this->mXlrInput->GetConnectedTo();
  const Connector * const inputConnectionJack = this->mJackInput->GetConnectedTo();
  if (inputConnectionXlr == 0 && inputConnectionJack == 0) return 0.0;
  //Prevent loops of connection
  if ( (std::find(
       prevConnectors.begin(),prevConnectors.end(),inputConnectionXlr)
       != prevConnectors.end())
    || (std::find(prevConnectors.begin(),prevConnectors.end(),inputConnectionJack)
       != prevConnectors.end()))
  {
    return 0.0;
  }

  prevConnectors.push_back(connector); //We just checked connector...

  assert(inputConnectionXlr  == 0 || inputConnectionXlr->mBelongsTo  != 0);
  assert(inputConnectionJack == 0 || inputConnectionJack->mBelongsTo != 0);

  const double audioSignalStrengthXlr  = (inputConnectionXlr  != 0
    ? inputConnectionXlr->mBelongsTo->AudioSignalStrength(inputConnectionXlr,prevConnectors)
    : 0.0);
  const double audioSignalStrengthJack = (inputConnectionJack != 0
    ? inputConnectionJack->mBelongsTo->AudioSignalStrength(inputConnectionJack,prevConnectors)
    : 0.0);
  return std::max(audioSignalStrengthJack,audioSignalStrengthXlr);
}
//---------------------------------------------------------------------------
RcfEvent3000::RcfEvent3000()
  : mInput(boost::shared_ptr<SpeakonFemale>(new SpeakonFemale(this))),
    mLink(boost::shared_ptr<SpeakonFemale>(new SpeakonFemale(this)))
{

}
//---------------------------------------------------------------------------
const double RcfEvent3000::GetSoundLevel() const
{
  return this->AudioSignalStrength(mLink.get(),
    std::vector<const Connector*>());
}
//---------------------------------------------------------------------------
const double RcfEvent3000::AudioSignalStrength(const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector != 0);

  //Only the Link speakon female will supply audio
  if (connector != mLink.get() ) return 0.0;

  //'Forward' the audio signal received
  //No enhancement by volume dial!
  const Connector * const inputConnection  = this->mInput->GetConnectedTo();
  if (inputConnection == 0) return 0.0;
  //Prevent loops of connection
  if ( std::find(prevConnectors.begin(),prevConnectors.end(),inputConnection)
       != prevConnectors.end() )
  {
    return 0.0;
  }

  prevConnectors.push_back(connector); //We just checked connector...

  const double audioSignalStrength
    = inputConnection->mBelongsTo->AudioSignalStrength(
      inputConnection,prevConnectors);

  return audioSignalStrength;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
