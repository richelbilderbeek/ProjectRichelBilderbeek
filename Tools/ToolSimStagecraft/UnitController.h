//---------------------------------------------------------------------------

#ifndef UnitControllerH
#define UnitControllerH
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
//---------------------------------------------------------------------------
struct Fader;
//---------------------------------------------------------------------------
struct Controller
{
  protected:
  virtual ~Controller() {}

  private:
  //Controller can only be deleted by boost::shared_ptr
  //or descendants
  friend boost::checked_delete(Controller *);
};
//---------------------------------------------------------------------------
struct Dial : public Controller
{
  Dial(const double position = 0.0);
  const double GetPosition() const { return mPosition; }
  const double GetRelPosition() const;
  void SetPosition(const double position);

  const double GetMinPosition() const { return 0.0; }
  const double GetMaxPosition() const { return 1.0; }

  private:

  double mPosition;

  //Dial can only be deleted by boost::shared_ptr
  virtual ~Dial() {}
  friend boost::checked_delete(Dial *);
};
//---------------------------------------------------------------------------
struct Fader : public Controller
{
  Fader(const double position = 0.0);
  const double GetPosition() const { return mPosition; }
  void SetPosition(const double position);
  const double GetMinPosition() const { return 0.0; }
  const double GetMaxPosition() const { return 1.0; }
  const double GetRelPosition() const;

  private:
  double mPosition;

  //Fader can only be deleted by boost::shared_ptr
  virtual ~Fader() {}
  friend boost::checked_delete(Fader *);
};
//---------------------------------------------------------------------------
struct PushButton : public Controller
{
  private:
  //PushButton can only be deleted by boost::shared_ptr
  virtual ~PushButton() {}
  friend boost::checked_delete(PushButton *);
};
//---------------------------------------------------------------------------
struct PressButton : public Controller
{
  PressButton() : mIn(false) {}

  const bool IsIn() const { return mIn; }
  void Press()  { mIn = !mIn; }

  private:
  bool mIn;

  //PressButton can only be deleted by boost::shared_ptr
  virtual ~PressButton() {}
  friend boost::checked_delete(PressButton *);

};
//---------------------------------------------------------------------------
//TapButton has been moved to UnitTabButton.h
//---------------------------------------------------------------------------
struct TwoSwitch : public Controller
{
  TwoSwitch() : mOn(false) {}

  const bool IsOn() const { return mOn; }
  void SwitchOn()  { mOn = true; }
  void SwitchOff() { mOn = false; }

  private:
  bool mOn;

  //TwoSwitch can only be deleted by boost::shared_ptr
  virtual ~TwoSwitch() {}
  friend boost::checked_delete(TwoSwitch *);

};
//---------------------------------------------------------------------------

#endif
