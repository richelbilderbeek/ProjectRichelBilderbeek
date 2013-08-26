//---------------------------------------------------------------------------

#ifndef UnitDisplayH
#define UnitDisplayH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
struct InternalConnection;
struct LcdSymbolControl;
struct LedControl;
struct AudioSignalControl;
//---------------------------------------------------------------------------
//A Display is a Machine that does not supply anything
//and is connected to another Machine by an InternalConnection
struct Display : public Machine
{
  Display(InternalConnection * const attachedTo);

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
  const bool HasPower() const;
  //Get the intensity the Display displays something
  //For example, an LED will shine brighter
  //and a BarDisplay (e.g. the PFL bars) wil display more bars 
  const double GetDisplayIntensity() const;

  protected:
  boost::shared_ptr<InternalConnection> mConnection;

  //Display can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~Display() {}
  friend boost::checked_delete(Display*);
};
//---------------------------------------------------------------------------
struct AudioSignalDisplay : public Display
{
  AudioSignalDisplay(InternalConnection * const attachedTo);

  private:

  friend struct AudioSignalControl;

  //AudioSignalDisplay can only be deleted by boost::shared_ptr
  ~AudioSignalDisplay() {}
  friend boost::checked_delete(AudioSignalDisplay*);
};
//---------------------------------------------------------------------------
struct LcdDisplay : public Display
{
  LcdDisplay(InternalConnection * const attachedTo);

  protected:
  //LcdDisplay can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~LcdDisplay() {}
  friend boost::checked_delete(LcdDisplay*);
};
//---------------------------------------------------------------------------
struct LcdSymbol : public Display
{
  LcdSymbol(InternalConnection * const attachedTo);

  private:

  friend struct LcdSymbolControl;

  //LcdSymbol can only be deleted by boost::shared_ptr
  ~LcdSymbol() {}
  friend boost::checked_delete(LcdSymbol*);
};
//---------------------------------------------------------------------------
struct Led : public Display
{
  Led(InternalConnection * const attachedTo,
    const int red, const int green, const int blue);

  private:

  const int mRed;
  const int mGreen;
  const int mBlue;

  friend struct LedControl;

  //Led can only be deleted by boost::shared_ptr
  ~Led() {}
  friend boost::checked_delete(Led*);
};
//---------------------------------------------------------------------------
#endif
