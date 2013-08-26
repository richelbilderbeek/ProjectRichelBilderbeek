//---------------------------------------------------------------------------

#ifndef UnitWallSocket220H
#define UnitWallSocket220H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
struct Socket220;
struct TFormWallSocket220;
//---------------------------------------------------------------------------
struct WallSocket220 : public Machine
{
  WallSocket220();

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
  boost::shared_ptr<Socket220> mSocket220;

  friend TFormWallSocket220;

  //WallSocket220 can only be deleted by boost::shared_ptr
  ~WallSocket220() {}
  friend boost::checked_delete(WallSocket220 *);

};
//---------------------------------------------------------------------------

#endif
