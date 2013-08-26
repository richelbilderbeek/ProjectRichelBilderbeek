//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitSimpleSound3.h"
//---------------------------------------------------------------------------
#include <stdexcept>
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
SimpleSound3::SimpleSound3()
  : //View
    //Use
    mFader1(boost::shared_ptr<Fader>(new Fader)),
    mFader2(boost::shared_ptr<Fader>(new Fader)),
    mFader3(boost::shared_ptr<Fader>(new Fader)),
    mDialGain1(boost::shared_ptr<Dial>(new Dial)),
    mDialGain2(boost::shared_ptr<Dial>(new Dial)),
    mDialGain3(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_1(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_2(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_3(boost::shared_ptr<Dial>(new Dial)),
    mPressButtonPfl1(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButtonPfl2(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButtonPfl3(boost::shared_ptr<PressButton>(new PressButton)),
    mDialSendAux1(boost::shared_ptr<Dial>(new Dial)),
    mFaderMaster(boost::shared_ptr<Fader>(new Fader)),
    //Connect
    mMic1(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMic2(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMic3(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mAux1(boost::shared_ptr<JackFemale>(new JackFemale(this))),
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
const double SimpleSound3::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector != 0);
  if (this->HasPower() == false) return 0.0;

  if (connector == mConnectionAudioSignal.get())
  {
    const int nInputs = 3;
    std::vector<double> inputs;
    for (int i=0; i!=nInputs; ++i)
    {
      inputs.push_back(this->AudioSignalInputStrength(connector,prevConnectors,i+1));
    }
    inputs[0] *= (this->mPressButtonPfl1->IsIn() ? 1.0 : 0.0);
    inputs[1] *= (this->mPressButtonPfl2->IsIn() ? 1.0 : 0.0);
    inputs[2] *= (this->mPressButtonPfl3->IsIn() ? 1.0 : 0.0);

    return *(std::max_element(inputs.begin(),inputs.end()));
    /*
    //Display the audio strength of mic1 and/or mic2 input
    double mic1Input = 0.0;
    {
      const Connector * const connectedTo = this->mMic1->GetConnectedTo();
      if (connectedTo != 0 && mPressButtonPfl1->IsIn()==true)
      {
        const Machine * const otherMachine = connectedTo->mBelongsTo;
        assert(otherMachine != 0);
        //Set mic1Input
        mic1Input = otherMachine->AudioSignalStrength(
          connectedTo,std::vector<const Connector*>()) //Input
          * (mDialGain1->GetRelPosition() * 2.0); //Gain
      }
    }
    double mic2Input = 0.0;
    {
      const Connector * const connectedTo = this->mMic2->GetConnectedTo();
      if (connectedTo != 0 && mPressButtonPfl2->IsIn()==true)
      {
        const Machine * const otherMachine = connectedTo->mBelongsTo;
        assert(otherMachine != 0);
        //Set mic2Input
        mic2Input = otherMachine->AudioSignalStrength(
          connectedTo,std::vector<const Connector*>()) //Input
          * (mDialGain2->GetRelPosition() * 2.0); //Gain
      }
    }
    return std::max(mic1Input,mic2Input);
    */
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double SimpleSound3::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert (connector == mMasterL.get()
       || connector == mMasterR.get()
       || connector == mAux1.get());

  if (this->HasPower() == false) return 0.0;

  if (connector == mMasterL.get() || connector == mMasterR.get())
  {
    const int nInputs = 3;
    std::vector<double> outputs;
    for (int i=0; i!=nInputs; ++i)
    {
      outputs.push_back(this->AudioSignalMasterOutputStrength(connector,prevConnectors,i+1));
    }
    return *(std::max_element(outputs.begin(),outputs.end()));
  }
  else if (connector == mAux1.get())
  {
    const int nInputs = 3;
    std::vector<double> outputs;
    for (int i=0; i!=nInputs; ++i)
    {
      outputs.push_back(this->AudioSignalAuxOutputStrength(connector,prevConnectors,i+1));
    }
    return *(std::max_element(outputs.begin(),outputs.end()));
  }
  assert(!"Should not get here");
  //Check mic1
  /*
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
      const double gain = 2.0 * this->mDialGain1->GetRelPosition();
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
      const double gain = 2.0 * this->mDialGain2->GetRelPosition();
      mic2AudioSignalStrength = gain * audioInput * masterThroughput * micThroughput;
    }
  }
  return std::max(mic1AudioSignalStrength,mic2AudioSignalStrength);
  */
  throw std::logic_error(
    "Unknown output connector in SimpleSound3::AudioSignalStrength");
}
//---------------------------------------------------------------------------
//What is the input strength of a certain channel after GAIN?
const double SimpleSound3::AudioSignalInputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const int channel) const
{
  boost::shared_ptr<Connector> channelConnector;
  switch (channel)
  {
    case 1: channelConnector = this->mMic1; break;
    case 2: channelConnector = this->mMic2; break;
    case 3: channelConnector = this->mMic3; break;
    default: assert(!"Should not get here");
  }

  //Sound levels for L and R channel are equal for the SimpleSound
  //Mic1 connected to something?
  const Connector * const inputConnection = channelConnector->GetConnectedTo();
  if (inputConnection == 0)
  {
    //Not connected to anything
    return 0.0;
  }
  if (std::find(prevConnectors.begin(),
    prevConnectors.end(),inputConnection) != prevConnectors.end())
  {
    //Loop!
    return 0.0;
  }

  const Machine * const inputMachine = inputConnection->mBelongsTo;
  assert(inputMachine != 0);
  prevConnectors.push_back(connector); //We just checked connector...
  const double audioInput = inputMachine->AudioSignalStrength(
    inputConnection,prevConnectors);

  boost::shared_ptr<Dial> dialGain;
  switch (channel)
  {
    case 1: dialGain = this->mDialGain1; break;
    case 2: dialGain = this->mDialGain2; break;
    case 3: dialGain = this->mDialGain3; break;
    default: assert(!"Should not get here");
  }

  const double gain = 2.0 * dialGain->GetRelPosition();

  return gain * audioInput;
}
//---------------------------------------------------------------------------
//What is the output strength to MASTER of a certain channel?
const double SimpleSound3::AudioSignalMasterOutputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const int channel) const
{
  const double audioInput
    = AudioSignalInputStrength(connector,prevConnectors,channel);

  const double masterThroughput = 2.0 * this->mFaderMaster->GetRelPosition();

  boost::shared_ptr<Fader> fader;
  switch (channel)
  {
    case 1: fader = this->mFader1; break;
    case 2: fader = this->mFader2; break;
    case 3: fader = this->mFader3; break;
    default: assert(!"Should not get here");
  }

  const double micThroughput = 2.0 * fader->GetRelPosition();

  const double audioOut = audioInput * masterThroughput * micThroughput;
  return audioOut;
}
//---------------------------------------------------------------------------
//What is the output strength to AUX of a certain channel?
const double SimpleSound3::AudioSignalAuxOutputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const int channel) const
{
  const double audioInput
    = AudioSignalInputStrength(connector,prevConnectors,channel);

  const double sendAux1throughput = 2.0 * this->mDialSendAux1->GetRelPosition();

  boost::shared_ptr<Dial> dial;
  switch (channel)
  {
    case 1: dial = this->mDialAux1_1; break;
    case 2: dial = this->mDialAux1_2; break;
    case 3: dial = this->mDialAux1_3; break;
    default: assert(!"Should not get here");
  }

  const double dialThroughput = 2.0 * dial->GetRelPosition();

  const double audioOut = audioInput * sendAux1throughput * dialThroughput;
  return audioOut;
}
//---------------------------------------------------------------------------
const bool SimpleSound3::HasPower() const
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
