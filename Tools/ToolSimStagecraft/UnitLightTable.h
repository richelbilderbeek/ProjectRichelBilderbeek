//---------------------------------------------------------------------------

#ifndef UnitLightTableH
#define UnitLightTableH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//Use
struct Fader;
//Connect
struct Connector;
struct InternalConnection;
struct EuroMale;
struct DmxFemale;
//Display
struct Led;
//Misc
struct TFormSimpleShine1;
struct TFormSimpleShine2;
//---------------------------------------------------------------------------
struct LightTable : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  //Light tables NEVER supply audio
  const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  virtual const double DmxSignalStrength(const int dmxChannel) const = 0;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  //LightTable can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~LightTable() {}
  friend boost::checked_delete(LightTable *);

  //Misc
  const std::vector<boost::shared_ptr<Fader> > CreateFaders(const int n) const;
};
//---------------------------------------------------------------------------
struct SimpleShine1 : public LightTable
{
  SimpleShine1();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  //LightTable can only be deleted by boost::shared_ptr
  ~SimpleShine1() {}
  friend boost::checked_delete(SimpleShine1*);

  //View
  //Use
  std::vector<boost::shared_ptr<Fader> > mFaders;
  boost::shared_ptr<Fader> mFaderMaster;
  //Connect
  boost::shared_ptr<EuroMale> mEuroMalePower;
  boost::shared_ptr<DmxFemale> mDmxFemaleOut;
  boost::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  boost::shared_ptr<Led> mLedPower;


  friend TFormSimpleShine1;
};
//---------------------------------------------------------------------------
struct SimpleShine2 : public LightTable
{
  SimpleShine2();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  //LightTable can only be deleted by boost::shared_ptr
  ~SimpleShine2() {}
  friend boost::checked_delete(SimpleShine2*);

  //View
  //Use
  std::vector<boost::shared_ptr<Fader> > mFaders;
  boost::shared_ptr<Fader> mFaderMaster;
  boost::shared_ptr<Fader> mCrossfaderA;
  boost::shared_ptr<Fader> mCrossfaderB;
  //Connect
  boost::shared_ptr<EuroMale> mEuroMalePower;
  boost::shared_ptr<DmxFemale> mDmxFemaleOut;
  boost::shared_ptr<InternalConnection> mConnectionLedPower;
  boost::shared_ptr<InternalConnection> mConnectionLedA;
  boost::shared_ptr<InternalConnection> mConnectionLedB;
  //Display
  boost::shared_ptr<Led> mLedPower;
  boost::shared_ptr<Led> mLedA;
  boost::shared_ptr<Led> mLedB;


  friend TFormSimpleShine2;
};
//---------------------------------------------------------------------------

#endif
