//---------------------------------------------------------------------------

#ifndef UnitLampH
#define UnitLampH
//---------------------------------------------------------------------------
#include "UnitMachine.h"
struct InternalConnection;
struct TFormPar64;
//---------------------------------------------------------------------------
//A Lamp is a Machine that does not supply anything
struct Lamp : public Machine
{
  //virtual const EnumMachineType GetType() const = 0;
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  //Lamps never supply power
  const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  //Lamps never supply audio
  const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  //Lamps never send DMX signals
  const double DmxSignalStrength(const int) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;


  protected:
  //Lamp can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~Lamp() {}
  friend boost::checked_delete(Lamp*);

};
//---------------------------------------------------------------------------
struct Par64 : public Lamp
{
  Par64();
  const bool HasPower() const;
  const double GetLightIntensity() const;

  private:

  //Control
  //Connect
  boost::shared_ptr<Plug220> mPlug220;
  friend TFormPar64;

  //Par64 can only be deleted by boost::shared_ptr
  ~Par64() {}
  friend boost::checked_delete(Par64*);
};
//---------------------------------------------------------------------------
#endif
