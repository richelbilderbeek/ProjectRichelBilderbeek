//---------------------------------------------------------------------------

#ifndef UnitSoundTableH
#define UnitSoundTableH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//#include "UnitEnumMachineType.h"
struct Fader;
struct PressButton;
struct Dial;
//struct Connector;
struct EuroMale;
struct XlrMale;
struct XlrFemale;
struct InternalConnection;
struct AudioSignalDisplay;
struct TFormSimpleSound1;
struct TFormSimpleSound2;
//---------------------------------------------------------------------------
struct SoundTable : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //Sound tables supply power to their displays
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int) const { return 0.0; };
  //Does the machine have power?
  virtual const bool HasPower() const = 0;

  protected:
  //SoundTable can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~SoundTable() {}
  friend boost::checked_delete(SoundTable *);
};
//---------------------------------------------------------------------------
#endif
