//---------------------------------------------------------------------------

#ifndef UnitSpeakerH
#define UnitSpeakerH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//View
//Use
struct TwoSwitch;
struct Dial;
//Connectors
struct EuroMale;
struct InternalConnection;
struct JackFemale;
struct SpeakonFemale;
struct XlrFemale;
struct XlrMale;
//Display
struct Led;
//Forms
struct TFormRcf322A;
struct TFormRcfEvent3000;
//---------------------------------------------------------------------------
struct Speaker : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //Speakers supply power to for example a power indication LED
  virtual const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //Speakers can be daisy-chained, so a speaker can supply an audio signal
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  //Speakers never send out DMX signals
  const double DmxSignalStrength(const int ) const { return 0.0; }
  //Does the machine have power?
  virtual const bool HasPower() const = 0;

  protected:
  //Speaker can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~Speaker() {}
  friend boost::checked_delete(Speaker *);

};
//---------------------------------------------------------------------------
struct PassiveSpeaker : public Speaker
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //Speakers supply power to for example a power indication LED
  const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const { return 0.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //Speakers can be daisy-chained, so a speaker can supply an audio signal
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  const bool HasPower() const { return 0.0; }

  protected:
  //Speaker can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~PassiveSpeaker() {}
  friend boost::checked_delete(PassiveSpeaker *);

};
//---------------------------------------------------------------------------
struct Rcf322A : public Speaker
{
  Rcf322A();

  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have power?
  const bool HasPower() const;
  //What is the sound output (with the limiter acting)?
  const double GetSoundLevel() const;
  //The maximal sound level before the limiter protection kicks in
  const double mMaxSoundLevel;


  private:

  //The sound level without the limiter acting
  const double GetUnlimitedSoundLevel() const;

  //Rcf322A can only be deleted by boost::shared_ptr
  ~Rcf322A() {}
  friend boost::checked_delete(Rcf322A*);

  //View
  //Use
  boost::shared_ptr<TwoSwitch> mPowerSwitch;
  boost::shared_ptr<Dial> mVolumeDial;
  //Connect
  boost::shared_ptr<JackFemale> mJackInput;
  boost::shared_ptr<XlrMale> mXlrDaisyChain;
  boost::shared_ptr<XlrFemale> mXlrInput;
  boost::shared_ptr<EuroMale> mEuroMalePower;
  boost::shared_ptr<InternalConnection> mConnectionLedPower;
  boost::shared_ptr<InternalConnection> mConnectionLedLimProt;
  //Display
  boost::shared_ptr<Led> mLedPower;
  boost::shared_ptr<Led> mLedLimProt;

  friend TFormRcf322A;
};
//---------------------------------------------------------------------------
struct RcfEvent3000 : public PassiveSpeaker
{
  RcfEvent3000();

  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //What is the sound output?
  const double GetSoundLevel() const;

  private:

  //The sound level without the limiter acting
  const double GetUnlimitedSoundLevel() const;

  //RcfEvent3000 can only be deleted by boost::shared_ptr
  ~RcfEvent3000() {}
  friend boost::checked_delete(RcfEvent3000*);

  //View
  //Use
  //Connect
  boost::shared_ptr<SpeakonFemale> mInput;
  boost::shared_ptr<SpeakonFemale> mLink;
  //Display

  friend TFormRcfEvent3000;
};
//---------------------------------------------------------------------------

#endif
