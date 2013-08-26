//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitSimpleSound4.h"
//---------------------------------------------------------------------------
#include <stdexcept>
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
SimpleSound4::SimpleSound4()
  : //View
    //Use
    mFader1(boost::shared_ptr<Fader>(new Fader)),
    mFader2(boost::shared_ptr<Fader>(new Fader)),
    mFader3(boost::shared_ptr<Fader>(new Fader)),
    mFader4(boost::shared_ptr<Fader>(new Fader)),
    mDialGain1(boost::shared_ptr<Dial>(new Dial)),
    mDialGain2(boost::shared_ptr<Dial>(new Dial)),
    mDialGain3(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_1(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_2(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_3(boost::shared_ptr<Dial>(new Dial)),
    mDialAux1_4(boost::shared_ptr<Dial>(new Dial)),
    mDialAux2_1(boost::shared_ptr<Dial>(new Dial)),
    mDialAux2_2(boost::shared_ptr<Dial>(new Dial)),
    mDialAux2_3(boost::shared_ptr<Dial>(new Dial)),
    mDialAux2_4(boost::shared_ptr<Dial>(new Dial)),
    mPressButtonPfl1(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButtonPfl2(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButtonPfl3(boost::shared_ptr<PressButton>(new PressButton)),
    mPressButtonPfl4(boost::shared_ptr<PressButton>(new PressButton)),
    mDialSendAux1(boost::shared_ptr<Dial>(new Dial)),
    mDialSendAux2(boost::shared_ptr<Dial>(new Dial)),
    mFaderMaster(boost::shared_ptr<Fader>(new Fader)),
    //Connect
    mMic1(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMic2(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mMic3(boost::shared_ptr<XlrFemale>(new XlrFemale(this))),
    mCinchFemaleL4(boost::shared_ptr<CinchWhiteFemale>(new CinchWhiteFemale(this))),
    mCinchFemaleR4(boost::shared_ptr<CinchRedFemale>(new CinchRedFemale(this))),
    mAux1(boost::shared_ptr<JackFemale>(new JackFemale(this))),
    mAux2(boost::shared_ptr<JackFemale>(new JackFemale(this))),
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
const double SimpleSound4::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector != 0);
  if (this->HasPower() == false) return 0.0;

  if (connector == mConnectionAudioSignal.get())
  {
    assert( static_cast<Channel>(0) == channel1);
    const int nInputs = 4;
    std::vector<double> inputs;
    for (int i=0; i!=nInputs; ++i)
    {
      inputs.push_back(this->AudioSignalInputStrength(connector,prevConnectors,
        static_cast<Channel>(i)));
    }
    inputs[0] *= (this->mPressButtonPfl1->IsIn() ? 1.0 : 0.0);
    inputs[1] *= (this->mPressButtonPfl2->IsIn() ? 1.0 : 0.0);
    inputs[2] *= (this->mPressButtonPfl3->IsIn() ? 1.0 : 0.0);
    inputs[3] *= (this->mPressButtonPfl4->IsIn() ? 1.0 : 0.0);

    return *(std::max_element(inputs.begin(),inputs.end()));
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double SimpleSound4::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert (connector == mMasterL.get()
       || connector == mMasterR.get()
       || connector == mAux1.get()
       || connector == mAux2.get());

  if (this->HasPower() == false) return 0.0;

  if (connector == mMasterL.get() || connector == mMasterR.get())
  {
    assert( static_cast<Channel>(0) == channel1);
    const int nInputs = 4;
    std::vector<double> outputs;
    for (int i=0; i!=nInputs; ++i)
    {
      outputs.push_back(this->AudioSignalMasterOutputStrength(connector,prevConnectors,
        static_cast<Channel>(i)));
    }
    return *(std::max_element(outputs.begin(),outputs.end()));
  }
  else if (connector == mAux1.get())
  {
    assert( static_cast<Channel>(0) == channel1);
    const int nInputs = 4;
    std::vector<double> outputs;
    for (int i=0; i!=nInputs; ++i)
    {
      outputs.push_back(
        this->AudioSignalAuxOutputStrength(connector,prevConnectors,
          static_cast<Channel>(i),aux1));
    }
    return *(std::max_element(outputs.begin(),outputs.end()));
  }
  else if (connector == mAux2.get())
  {
    assert( static_cast<Channel>(0) == channel1);
    const int nInputs = 4;
    std::vector<double> outputs;
    for (int i=0; i!=nInputs; ++i)
    {
      outputs.push_back(
        this->AudioSignalAuxOutputStrength(connector,prevConnectors,
          static_cast<Channel>(i),aux2));
    }
    return *(std::max_element(outputs.begin(),outputs.end()));
  }
  assert(!"Should not get here");
  throw std::logic_error(
    "Unknown output connector in SimpleSound4::AudioSignalStrength");
}
//---------------------------------------------------------------------------
//What is the input strength of a certain channel after GAIN?
const double SimpleSound4::AudioSignalInputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const Channel channel) const
{
  assert(channel == channel1
      || channel == channel2
      || channel == channel3
      || channel == channel4);

  double audioInput = 0.0;

  //Calculate the audio input
  if (channel == channel1 || channel == channel2 || channel == channel3)
  {
    //Calculate the audio input of the single input channels
    boost::shared_ptr<Connector> channelConnector;
    switch (channel)
    {
      case channel1: channelConnector = this->mMic1; break;
      case channel2: channelConnector = this->mMic2; break;
      case channel3: channelConnector = this->mMic3; break;
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
    /*const double*/ audioInput = inputMachine->AudioSignalStrength(
      inputConnection,prevConnectors);
  }
  else
  {
    //Calculate the audio input of the dual input channels
    assert(channel == channel4);
    boost::shared_ptr<Connector> channelConnectorL;
    boost::shared_ptr<Connector> channelConnectorR;
    switch (channel)
    {
      case channel4:
        channelConnectorL = this->mCinchFemaleL4;
        channelConnectorR = this->mCinchFemaleR4;
        break;
      default: assert(!"Should not get here");
    }

    //Sound levels for L and R channel are equal for the SimpleSound
    //Connected to something?
    const Connector * const inputConnectionL = channelConnectorL->GetConnectedTo();
    const Connector * const inputConnectionR = channelConnectorR->GetConnectedTo();

    double audioInputL = 0.0;
    double audioInputR = 0.0;

    if(   inputConnectionL != 0 //Connected to something
      && (std::find(prevConnectors.begin(),prevConnectors.end(),
            inputConnectionL) == prevConnectors.end()) //Not in loop
      )
    {
      const Machine * const inputMachine = inputConnectionL->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      audioInputL = inputMachine->AudioSignalStrength(
        inputConnectionL,prevConnectors);

    }

    if(   inputConnectionR != 0 //Connected to something
      && (std::find(prevConnectors.begin(),prevConnectors.end(),
            inputConnectionR) == prevConnectors.end()) //Not in loop
      )
    {
      const Machine * const inputMachine = inputConnectionR->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      audioInputL = inputMachine->AudioSignalStrength(
        inputConnectionR,prevConnectors);
    }
    audioInput = std::max(audioInputL, audioInputR);
  }

  boost::shared_ptr<Dial> dialGain;
  switch (channel)
  {
    case channel1: dialGain = this->mDialGain1; break;
    case channel2: dialGain = this->mDialGain2; break;
    case channel3: dialGain = this->mDialGain3; break;
    case channel4: break; //Channel 4 does not have a gain
    default:
      assert(!"Should not get here");
      break;
  }

  const double gain = 2.0
    * (dialGain.get() != 0 ? dialGain->GetRelPosition() : 1.0);

  return gain * audioInput;
}
//---------------------------------------------------------------------------
//What is the output strength to MASTER of a certain channel?
const double SimpleSound4::AudioSignalMasterOutputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const Channel channel) const
{
  assert(channel == channel1
      || channel == channel2
      || channel == channel3
      || channel == channel4);

  const double audioInput
    = AudioSignalInputStrength(connector,prevConnectors,channel);

  const double masterThroughput = 2.0 * this->mFaderMaster->GetRelPosition();

  boost::shared_ptr<Fader> fader;
  switch (channel)
  {
    case channel1: fader = this->mFader1; break;
    case channel2: fader = this->mFader2; break;
    case channel3: fader = this->mFader3; break;
    case channel4: fader = this->mFader4; break;
    default: assert(!"Should not get here");
  }

  const double micThroughput = 2.0 * fader->GetRelPosition();

  const double audioOut = audioInput * masterThroughput * micThroughput;
  return audioOut;
}
//---------------------------------------------------------------------------
//What is the output strength to AUX of a certain channel?
const double SimpleSound4::AudioSignalAuxOutputStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors,
  const Channel channel,
  const Aux aux) const
{
  assert(channel == channel1
      || channel == channel2
      || channel == channel3
      || channel == channel4);
  assert(aux == aux1 || aux == aux2);

  boost::shared_ptr<Dial> dialSendAux;
  switch(aux)
  {
    case aux1 : dialSendAux = mDialSendAux1; break;
    case aux2 : dialSendAux = mDialSendAux2; break;
    default: assert(!"Should not get here");
  }

  assert(dialSendAux.get() != 0);

  const double audioInput
    = AudioSignalInputStrength(connector,prevConnectors,channel);

  const double sendAuxThroughput = 2.0 * dialSendAux->GetRelPosition();

  boost::shared_ptr<Dial> dial;

  switch (aux)
  {
    case aux1:
      switch (channel)
      {
        case channel1: dial = this->mDialAux1_1; break;
        case channel2: dial = this->mDialAux1_2; break;
        case channel3: dial = this->mDialAux1_3; break;
        case channel4: dial = this->mDialAux1_4; break;
        default: assert(!"Should not get here");
      }
    break;
    case aux2:
      switch (channel)
      {
        case channel1: dial = this->mDialAux2_1; break;
        case channel2: dial = this->mDialAux2_2; break;
        case channel3: dial = this->mDialAux2_3; break;
        case channel4: dial = this->mDialAux2_4; break;
        default: assert(!"Should not get here");
      }
    break;
  }

  const double dialThroughput = 2.0 * dial->GetRelPosition();

  const double audioOut = audioInput * sendAuxThroughput * dialThroughput;
  return audioOut;
}
//---------------------------------------------------------------------------
const bool SimpleSound4::HasPower() const
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
