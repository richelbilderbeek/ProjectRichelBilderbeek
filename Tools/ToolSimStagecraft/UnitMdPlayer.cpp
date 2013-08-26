//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitMdPlayer.h"
//---------------------------------------------------------------------------
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
MdPlayer::MdPlayer()
  :
  //Use
  mButtonPower(boost::shared_ptr<TapButton<MdPlayer> >(
    new TapButton<MdPlayer>(this,&MdPlayer::PressPower))),
  mButtonRecord(boost::shared_ptr<TapButton<MdPlayer> >(
    new TapButton<MdPlayer>(this,&MdPlayer::PressRecord))),
  mButtonStop(boost::shared_ptr<TapButton<MdPlayer> >(
    new TapButton<MdPlayer>(this,&MdPlayer::PressStop))),
  mButtonPlay(boost::shared_ptr<TapButton<MdPlayer> >(
    new TapButton<MdPlayer>(this,&MdPlayer::PressPlay))),
  //Connect
  mCinchFemaleInL(boost::shared_ptr<CinchWhiteFemale>(new CinchWhiteFemale(this))),
  mCinchFemaleInR(boost::shared_ptr<CinchRedFemale>(new CinchRedFemale(this))),
  mCinchFemaleOutL(boost::shared_ptr<CinchWhiteFemale>(new CinchWhiteFemale(this))),
  mCinchFemaleOutR(boost::shared_ptr<CinchRedFemale>(new CinchRedFemale(this))),
  mPlug220Power(boost::shared_ptr<Plug220>(new Plug220(this))),
  mConnectionAudioSignalL(boost::shared_ptr<InternalConnection>(
    new InternalConnection(this))),
  mConnectionAudioSignalR(boost::shared_ptr<InternalConnection>(
    new InternalConnection(this))),
  mConnectionLcdSymbolRecord(boost::shared_ptr<InternalConnection> (
    new InternalConnection(this))),
  mConnectionLcdSymbolPlay(boost::shared_ptr<InternalConnection> (
    new InternalConnection(this))),
  mConnectionLedPower(boost::shared_ptr<InternalConnection> (
    new InternalConnection(this))),
  mState(mdOff),
  mAudioRecordedL(std::vector<double>(100,0.0)),
  mAudioRecordedR(std::vector<double>(100,0.0)),
  mPlayPos(0)
{
  //Display
  mAudioSignalDisplayL = boost::shared_ptr<AudioSignalDisplay>(
    new AudioSignalDisplay(mConnectionAudioSignalL.get()));
  mAudioSignalDisplayR = boost::shared_ptr<AudioSignalDisplay>(
    new AudioSignalDisplay(mConnectionAudioSignalR.get()));
  mLcdSymbolRecord = boost::shared_ptr<LcdSymbol>(
    new LcdSymbol(mConnectionLcdSymbolRecord.get()));
  mLcdSymbolPlay = boost::shared_ptr<LcdSymbol>(
    new LcdSymbol(mConnectionLcdSymbolPlay.get()));
  mLedPower = boost::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),0,255,0));

  assert(mLcdSymbolRecord.get()!=0);

}
//---------------------------------------------------------------------------
const double MdPlayer::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  assert(connector != 0);
  if (this->HasPower() == false)
  {
    return 0.0;
  }

  if (connector == mConnectionAudioSignalL.get())
  {
    return this->AudioSignalStrength(mCinchFemaleInL.get(),
      std::vector<const Connector*>());
  }
  else if (connector == mConnectionAudioSignalR.get())
  {
    return this->AudioSignalStrength(mCinchFemaleInR.get(),
      std::vector<const Connector*>());
  }
  else if (connector == mConnectionLcdSymbolRecord.get())
  {
    return (mState == mdRec ? 1.0 : 0.0);
  }
  else if (connector == mConnectionLcdSymbolPlay.get())
  {
    return (mState == mdPlay ? 1.0 : 0.0);
  }
  else if (connector == mConnectionLedPower.get())
  {
    return (mState != mdOff ? 1.0 : 0.0);
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double MdPlayer::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector == mCinchFemaleInL.get()
      || connector == mCinchFemaleInR.get()
      || connector == mCinchFemaleOutL.get()
      || connector == mCinchFemaleOutR.get() );

  if (this->HasPower() == false) return 0.0;

  if (mState == mdPlay)
  {
    //Playing from MD disc, return MD disc signal ONLY
    //-> that is, input to MD player is discarded
    if (connector == mCinchFemaleOutL.get())
    {
      assert(mPlayPos >= 0);
      assert(mPlayPos < static_cast<int>(mAudioRecordedL.size()));
      return mAudioRecordedL[mPlayPos];
    }
    else if (connector == mCinchFemaleOutR.get())
    {
      assert(mPlayPos >= 0);
      assert(mPlayPos < static_cast<int>(mAudioRecordedR.size()));
      return mAudioRecordedR[mPlayPos];
    }

  }
  else
  {
    //Not playing from MD disc
    assert(mState != mdPlay);
    //mCinchFemaleInL is asked for recording
    //mCinchFemaleOutL is asked for input by other machines
    if (connector == mCinchFemaleInL.get() || connector == mCinchFemaleOutL.get())
    {
      const Connector * const inputConnection = this->mCinchFemaleInL->GetConnectedTo();
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
      return audioInput;
    }
    //mCinchFemaleInR is asked for recording
    //mCinchFemaleOutR is asked for input by other machines
    else if (connector == mCinchFemaleInR.get() || connector == mCinchFemaleOutR.get())
    {
      const Connector * const inputConnection = this->mCinchFemaleInR->GetConnectedTo();
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
      return audioInput;
    }

  }
  return 0.0;
}
//---------------------------------------------------------------------------
const bool MdPlayer::HasPower() const
{
  assert(this->mPlug220Power.get() != 0);
  const Connector * const connectedTo = this->mPlug220Power->GetConnectedTo();
  if (connectedTo == 0)
  {
    //Power plug (220V) not connected to anything
    return false;
  }
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);

  const double powerSupply = otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>());
  return (powerSupply > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
void MdPlayer::PressPower()
{
  if (mState != mdOff) { mState = mdOff; }
  else if (this->HasPower() == true) mState = mdOn;
}
//---------------------------------------------------------------------------
void MdPlayer::PressRecord()
{
  if (this->HasPower() == true)
  {
    mState = mdRec;
    mPlayPos = 0;
  }
  else
  {
    mState = mdOff;
  }
}
//---------------------------------------------------------------------------
void MdPlayer::PressStop()
{
  if (this->HasPower() == true)
  {
    mState = mdOn;
    mPlayPos = 0;
  }
  else
  {
    mState = mdOff;
  }
}
//---------------------------------------------------------------------------
void MdPlayer::PressPlay()
{
  if (this->HasPower() == true)
  {
    mState = mdPlay;
    mPlayPos = 0;
  }
  else
  {
    mState = mdOff;
  }
}
//---------------------------------------------------------------------------
//Must be called every time cycle for recording and playing
void MdPlayer::Tick()
{
  if (this->HasPower() == false)
  {
    mState = mdOff;
    return;
  }
  else if (mState == mdRec || mState == mdPlay)
  {
    assert(this->HasPower() == true);
    ++mPlayPos;
    assert(mAudioRecordedL.size() == mAudioRecordedR.size());
    if (mPlayPos == static_cast<int>(mAudioRecordedL.size()))
    {
      //Stop recording
      mPlayPos = 0;
      mState = mdOn;
      return;
    }
    if (mState == mdRec)
    {
      const double audioSignalInL = this->AudioSignalStrength(
        mCinchFemaleInL.get(), std::vector<const Connector*>() );
      mAudioRecordedL[mPlayPos] = audioSignalInL;

      const double audioSignalInR = this->AudioSignalStrength(
        mCinchFemaleInR.get(), std::vector<const Connector*>() );
      mAudioRecordedR[mPlayPos] = audioSignalInR;
    }
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
