//---------------------------------------------------------------------------

#ifndef UnitMachineH
#define UnitMachineH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/checked_delete.hpp>
//---------------------------------------------------------------------------
struct Connector;
//---------------------------------------------------------------------------
struct Machine
{
  Machine() {}
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  virtual const double PowerSupplyStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  virtual const double DmxSignalStrength(const int dmxChannel) const = 0;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  //Machine can only be deleted by boost::shared_ptr
  //or descendants
  virtual ~Machine() {}
  friend boost::checked_delete(Machine *);
};
//---------------------------------------------------------------------------
#endif
