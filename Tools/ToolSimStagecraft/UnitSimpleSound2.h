//---------------------------------------------------------------------------

#ifndef UnitSimpleSound2H
#define UnitSimpleSound2H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitSoundTable.h"
struct Fader;
struct PressButton;
struct Dial;
struct Connector;
struct EuroMale;
struct XlrMale;
struct XlrFemale;
struct InternalConnection;
struct AudioSignalDisplay;
struct TFormSimpleSound2;
//---------------------------------------------------------------------------
struct SimpleSound2 : public SoundTable
{
  SimpleSound2();

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

  ~SimpleSound2() {}
  //SimpleSound2 can only be deleted by boost::shared_ptr
  friend boost::checked_delete(SimpleSound2 *);

  //View
  //Use
  boost::shared_ptr<Fader> mFader1;
  boost::shared_ptr<Fader> mFader2;
  boost::shared_ptr<Dial> mDial1; //Gain dial
  boost::shared_ptr<Dial> mDial2; //Gain dial
  boost::shared_ptr<PressButton> mPressButton1; //PFL button
  boost::shared_ptr<PressButton> mPressButton2; //PFL button
  boost::shared_ptr<Fader> mFaderMaster;
  //Connect
  boost::shared_ptr<XlrFemale> mMic1;
  boost::shared_ptr<XlrFemale> mMic2;
  boost::shared_ptr<XlrMale> mMasterL;
  boost::shared_ptr<XlrMale> mMasterR;
  boost::shared_ptr<EuroMale> mPower;
  boost::shared_ptr<InternalConnection> mConnectionAudioSignal;
  //Display
  boost::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;
  //Misc

  friend TFormSimpleSound2;
};
//---------------------------------------------------------------------------
#endif
