//---------------------------------------------------------------------------

#ifndef UnitSimpleSound4H
#define UnitSimpleSound4H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitAux.h"
#include "UnitChannel.h"
#include "UnitSoundTable.h"
//Control
struct Dial;
struct Fader;
struct PressButton;
//Connect
struct CinchRedFemale;
struct CinchWhiteFemale;
struct Connector;
struct EuroMale;
struct InternalConnection;
struct JackFemale;
struct XlrFemale;
struct XlrMale;
//Display
struct AudioSignalDisplay;
//GUI friend
struct TFormSimpleSound4;
//---------------------------------------------------------------------------
struct SimpleSound4 : public SoundTable
{
  SimpleSound4();

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

  ~SimpleSound4() {}
  //SimpleSound4 can only be deleted by boost::shared_ptr
  friend boost::checked_delete(SimpleSound4 *);

  //View
  //Use
  boost::shared_ptr<Fader> mFader1;
  boost::shared_ptr<Fader> mFader2;
  boost::shared_ptr<Fader> mFader3;
  boost::shared_ptr<Fader> mFader4;
  boost::shared_ptr<Dial> mDialGain1;
  boost::shared_ptr<Dial> mDialGain2;
  boost::shared_ptr<Dial> mDialGain3;
  boost::shared_ptr<Dial> mDialAux1_1;
  boost::shared_ptr<Dial> mDialAux1_2;
  boost::shared_ptr<Dial> mDialAux1_3;
  boost::shared_ptr<Dial> mDialAux1_4;
  boost::shared_ptr<Dial> mDialAux2_1;
  boost::shared_ptr<Dial> mDialAux2_2;
  boost::shared_ptr<Dial> mDialAux2_3;
  boost::shared_ptr<Dial> mDialAux2_4;
  boost::shared_ptr<PressButton> mPressButtonPfl1;
  boost::shared_ptr<PressButton> mPressButtonPfl2;
  boost::shared_ptr<PressButton> mPressButtonPfl3;
  boost::shared_ptr<PressButton> mPressButtonPfl4;
  boost::shared_ptr<Dial> mDialSendAux1;
  boost::shared_ptr<Dial> mDialSendAux2;
  boost::shared_ptr<Fader> mFaderMaster;
  //Connect
  boost::shared_ptr<XlrFemale> mMic1;
  boost::shared_ptr<XlrFemale> mMic2;
  boost::shared_ptr<XlrFemale> mMic3;
  boost::shared_ptr<CinchWhiteFemale> mCinchFemaleL4;
  boost::shared_ptr<CinchRedFemale> mCinchFemaleR4;
  boost::shared_ptr<JackFemale> mAux1;
  boost::shared_ptr<JackFemale> mAux2;
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
    const Channel channel) const;
  const double AudioSignalMasterOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const Channel channel) const;
  const double AudioSignalAuxOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const Channel channel, const Aux aux) const;


  friend TFormSimpleSound4;
};
//---------------------------------------------------------------------------
#endif
