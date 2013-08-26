//---------------------------------------------------------------------------

#ifndef UnitDimmerpackH
#define UnitDimmerpackH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
struct TFormDimblockV3;
struct SocketPowerMale;
struct DmxMale;
struct DmxFemale;
struct LcdDisplay;
struct Led;
struct InternalConnection;
//---------------------------------------------------------------------------
struct Dimmerpack : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  virtual const double PowerSupplyStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  //Dimmerpacks never supply audio
  const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  virtual const double DmxSignalStrength(const int dmxChannel) const = 0;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  //Dimmerpack can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~Dimmerpack() {}
  friend boost::checked_delete(Dimmerpack *);


};
//---------------------------------------------------------------------------
struct DimblockV3 : public Dimmerpack
{
  DimblockV3();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(const Connector * const  connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  //DimblockV3 can only be deleted by boost::shared_ptr
  ~DimblockV3() {}
  friend boost::checked_delete(DimblockV3*);

  //View
  //Use
  //Connect
  boost::shared_ptr<DmxMale> mDmxMaleInput;
  boost::shared_ptr<DmxFemale> mDmxFemaleOutput;
  boost::shared_ptr<SocketPowerMale> mPowerMale;
  std::vector<boost::shared_ptr<Socket220> > mSockets;

  boost::shared_ptr<InternalConnection> mConnectionLedMainsPower;
  boost::shared_ptr<InternalConnection> mConnectionLedNondimSet;
  boost::shared_ptr<InternalConnection> mConnectionLedPresetSet;
  boost::shared_ptr<InternalConnection> mConnectionLedDmxPresent;
  boost::shared_ptr<InternalConnection> mConnectionLedWarning;
  //Display
  boost::shared_ptr<Led> mLedMainsPower;
  boost::shared_ptr<Led> mLedNondimSet;
  boost::shared_ptr<Led> mLedPresetSet;
  boost::shared_ptr<Led> mLedDmxPresent;
  boost::shared_ptr<Led> mLedWarning;


  friend TFormDimblockV3;

};
//---------------------------------------------------------------------------
const std::vector<boost::shared_ptr<Socket220> > CreateSockets(
  const Machine * const belongTo,
  const int nSockets);
//---------------------------------------------------------------------------
#endif
