//---------------------------------------------------------------------------

#ifndef UnitWallSocketPowerH
#define UnitWallSocketPowerH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
struct SocketPowerFemale;
struct TFormWallSocketPower;
//---------------------------------------------------------------------------
struct WallSocketPower : public Machine
{
  WallSocketPower();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(
    const Connector * const,
    std::vector<const Connector*>) const { return 1.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(
    const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const { return true; }

  private:
  //Control
  //Connect
  boost::shared_ptr<SocketPowerFemale> mSocketPower;

  friend TFormWallSocketPower;

  //WallSocketPower can only be deleted by boost::shared_ptr
  ~WallSocketPower() {}
  friend boost::checked_delete(WallSocketPower *);

};
//---------------------------------------------------------------------------

#endif
