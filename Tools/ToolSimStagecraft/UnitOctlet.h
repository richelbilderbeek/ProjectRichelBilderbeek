//---------------------------------------------------------------------------

#ifndef UnitOctletH
#define UnitOctletH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//---------------------------------------------------------------------------
struct TwoSwitch;
struct Connector;
struct Plug220;
struct Socket220;
struct TFormOctlet;
//---------------------------------------------------------------------------
struct Octlet : public Machine
{
  Octlet();
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:
  //View
  //Use
  boost::shared_ptr<TwoSwitch> mPowerSwitch;
  //Connect
  boost::shared_ptr<Plug220> mPlug;
  std::vector<boost::shared_ptr<Socket220> > mSockets220;


  friend TFormOctlet;

  const std::vector<boost::shared_ptr<Socket220> > CreateSockets220() const;

  //Octlet can only be deleted by boost::shared_ptr
  ~Octlet() {}
  friend boost::checked_delete(Octlet *);

};
//---------------------------------------------------------------------------

#endif
