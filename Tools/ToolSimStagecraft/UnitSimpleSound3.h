//---------------------------------------------------------------------------

#ifndef UnitSimpleSound3H
#define UnitSimpleSound3H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitSoundTable.h"
struct Fader;
struct PressButton;
struct Dial;
struct Connector;
struct EuroMale;
struct JackFemale;
struct XlrMale;
struct XlrFemale;
struct InternalConnection;
struct AudioSignalDisplay;
struct TFormSimpleSound3;
//---------------------------------------------------------------------------
struct SimpleSound3 : public SoundTable
{
  SimpleSound3();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have power?
  const bool HasPower() const;

  private:

  ~SimpleSound3() {}
  //SimpleSound3 can only be deleted by boost::shared_ptr
  friend boost::checked_delete(SimpleSound3 *);

  //View
  //Use
  boost::shared_ptr<Fader> mFader1;
  boost::shared_ptr<Fader> mFader2;
  boost::shared_ptr<Fader> mFader3;
  boost::shared_ptr<Dial> mDialGain1;
  boost::shared_ptr<Dial> mDialGain2;
  boost::shared_ptr<Dial> mDialGain3;
  boost::shared_ptr<Dial> mDialAux1_1;
  boost::shared_ptr<Dial> mDialAux1_2;
  boost::shared_ptr<Dial> mDialAux1_3;
  boost::shared_ptr<PressButton> mPressButtonPfl1;
  boost::shared_ptr<PressButton> mPressButtonPfl2;
  boost::shared_ptr<PressButton> mPressButtonPfl3;
  boost::shared_ptr<Dial> mDialSendAux1;
  boost::shared_ptr<Fader> mFaderMaster;
  //Connect
  boost::shared_ptr<XlrFemale> mMic1;
  boost::shared_ptr<XlrFemale> mMic2;
  boost::shared_ptr<XlrFemale> mMic3;
  boost::shared_ptr<JackFemale> mAux1;
  boost::shared_ptr<XlrMale> mMasterL;
  boost::shared_ptr<XlrMale> mMasterR;
  boost::shared_ptr<EuroMale> mPower;
  boost::shared_ptr<InternalConnection> mConnectionAudioSignal;
  //Display
  boost::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;
  //Misc
  const double AudioSignalInputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;
  const double AudioSignalMasterOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;
  const double AudioSignalAuxOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;


  friend TFormSimpleSound3;
};
//---------------------------------------------------------------------------
#endif
