//---------------------------------------------------------------------------

#ifndef UnitAmplifierH
#define UnitAmplifierH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//Use
struct Dial;
struct TwoSwitch;
//Connect
struct EuroMale;
struct InternalConnection;
struct JackXlrFemale;
struct SpeakonFemale;
//Display
struct Led;
//Misc
struct TFormEasyAmp;
//---------------------------------------------------------------------------
struct Amplifier : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  virtual const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const = 0;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  //Amplifiers do not use DMX
  const double DmxSignalStrength(const int dmxChannel) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  //Amplifier can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~Amplifier() {}
  friend boost::checked_delete(Amplifier *);

  //Misc
  const std::vector<boost::shared_ptr<Fader> > CreateFaders(const int n) const;
};
//---------------------------------------------------------------------------
struct EasyAmp : public Amplifier
{
  EasyAmp();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  //Amplifier can only be deleted by boost::shared_ptr
  ~EasyAmp() {}
  friend boost::checked_delete(EasyAmp*);

  //View
  //Use
  boost::shared_ptr<TwoSwitch> mPowerSwitch;
  boost::shared_ptr<Dial> mGain;
  //Connect
  boost::shared_ptr<EuroMale> mEuroPower;
  boost::shared_ptr<JackXlrFemale> mJackXlrL;
  boost::shared_ptr<JackXlrFemale> mJackXlrR;
  boost::shared_ptr<SpeakonFemale> mSpeakonL;
  boost::shared_ptr<SpeakonFemale> mSpeakonR;
  boost::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  boost::shared_ptr<Led> mLedPower;


  friend TFormEasyAmp;
};
//---------------------------------------------------------------------------

#endif
