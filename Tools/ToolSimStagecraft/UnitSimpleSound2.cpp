//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitSimpleSound2.h"
//---------------------------------------------------------------------------
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
SimpleSound2::SimpleSound2()
  : //View
    //Use
    mFader1(boost::shared_ptr<Fader>(new Fader)),
    mFader2(boost::shared_ptr<Fader>(new Fader)),
    mDial1(boost::shared_ptr<Dial>(new Dial)),
    mDial2(boost::shared_ptr<Dial>(new Dial)),
    mPressButton1(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButton2(boost::shared_ptr<PressButton>(new PressButton)),
    mFaderMaster(boost::shared_ptr<Fader>(new Fader)),
    //Connect
    mMic1(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMic2(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
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
const double SimpleSound2::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  assert(connector != 0);
  if (this->HasPower() == false) return 0.0;

  if (connector == mConnectionAudioSignal.get())
  {
    //Display the audio strength of mic1 and/or mic2 input
    double mic1Input = 0.0;
    {
      const Connector * const connectedTo = this->mMic1->GetConnectedTo();
      if (connectedTo != 0 && mPressButton1->IsIn()==true)
      {
        const Machine * const otherMachine = connectedTo->mBelongsTo;
        assert(otherMachine != 0);
        //Set mic1Input
        mic1Input = otherMachine->AudioSignalStrength(
          connectedTo,std::vector<const Connector*>()) //Input
          * (mDial1->GetRelPosition() * 2.0); //Gain
      }
    }
    double mic2Input = 0.0;
    {
      const Connector * const connectedTo = this->mMic2->GetConnectedTo();
      if (connectedTo != 0 && mPressButton2->IsIn()==true)
      {
        const Machine * const otherMachine = connectedTo->mBelongsTo;
        assert(otherMachine != 0);
        //Set mic2Input
        mic2Input = otherMachine->AudioSignalStrength(
          connectedTo,std::vector<const Connector*>()) //Input
          * (mDial2->GetRelPosition() * 2.0); //Gain
      }
    }
    return std::max(mic1Input,mic2Input);
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double SimpleSound2::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert (connector == mMasterL.get() || connector == mMasterR.get() );

  if (this->HasPower() == false) return 0.0;

  //Check mic1
  double mic1AudioSignalStrength = 0.0;
  {
    //Sound levels for L and R channel are equal for the SimpleSound
    //Mic1 connected to something?
    const Connector * const inputConnection = this->mMic1->GetConnectedTo();
    if (inputConnection != 0 //Must be connected
      && (std::find(prevConnectors.begin(),
      prevConnectors.end(),inputConnection) == prevConnectors.end())) //No loops
    {
      const Machine * const inputMachine = inputConnection->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      const double audioInput = inputMachine->AudioSignalStrength(
        inputConnection,prevConnectors);
      prevConnectors.pop_back(); //Undo the push_back for mic2
      const double masterThroughput = 2.0 * this->mFaderMaster->GetRelPosition();
      const double micThroughput = 2.0 * this->mFader1->GetRelPosition();
      const double gain = 2.0 * this->mDial1->GetRelPosition();
      mic1AudioSignalStrength = gain * audioInput * masterThroughput * micThroughput;
    }
  }

  //Check mic2
  double mic2AudioSignalStrength = 0.0;
  {
    //Sound levels for L and R channel are equal for the SimpleSound
    //Mic1 connected to something?
    const Connector * const inputConnection = this->mMic2->GetConnectedTo();
    if (inputConnection != 0 //Must be connected
      && (std::find(prevConnectors.begin(),
      prevConnectors.end(),inputConnection) == prevConnectors.end())) //No loops
    {
      const Machine * const inputMachine = inputConnection->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      const double audioInput = inputMachine->AudioSignalStrength(
        inputConnection,prevConnectors);
      prevConnectors.pop_back(); //Undo the push_back for mic1??
      const double masterThroughput = 2.0 * this->mFaderMaster->GetRelPosition();
      const double micThroughput = 2.0 * this->mFader2->GetRelPosition();
      const double gain = 2.0 * this->mDial2->GetRelPosition();
      mic2AudioSignalStrength = gain * audioInput * masterThroughput * micThroughput;
    }
  }
  return std::max(mic1AudioSignalStrength,mic2AudioSignalStrength);
}
//---------------------------------------------------------------------------
const bool SimpleSound2::HasPower() const
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
