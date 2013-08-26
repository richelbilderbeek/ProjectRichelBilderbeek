//---------------------------------------------------------------------------

#ifndef UnitControllerControlH
#define UnitControllerControlH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//#include "UnitEnumControllerType.h"
//struct Controller;
struct TFormMachine;

struct Dial;
struct Fader;
struct PressButton;
struct PushButton;
struct TwoSwitch;
namespace Extctrls { struct TImage; }
//---------------------------------------------------------------------------
//Handles the GUI of a Controller
//An XControl manages the GUI of an X
struct ControllerControl
{
  ControllerControl(TFormMachine * const formParent,
    Extctrls::TImage * const image);
  //The x and y are the coordinats on mImage itself,
  //independent of its TImage::Left and TImage::Top properties
  virtual void OnMouseDown(const int x, const int y) = 0;

  protected:
  Extctrls::TImage * const mImage;
  TFormMachine * const mFormParent;

  //ControllerControl can only be deleted by boost::shared_ptr
  //or descendants
  virtual ~ControllerControl() {}
  friend boost::checked_delete(ControllerControl *);

};
//---------------------------------------------------------------------------
struct DialControl : public ControllerControl
{
  DialControl(TFormMachine * const formParent,
    const boost::shared_ptr<Dial> dial,
    Extctrls::TImage * const image);

  void OnMouseDown(const int x, const int y);

  private:
  const boost::shared_ptr<Dial> mDial;

  //DialControl can only be deleted by boost::shared_ptr
  ~DialControl() {}
  friend boost::checked_delete(DialControl *);
};
//---------------------------------------------------------------------------
struct FaderControl : public ControllerControl
{
  FaderControl(TFormMachine * const formParent,
    const boost::shared_ptr<Fader> fader,
    Extctrls::TImage * const image);

  void OnMouseDown(const int x, const int y);

  private:
  const boost::shared_ptr<Fader> mFader;

  //FaderControl can only be deleted by boost::shared_ptr
  ~FaderControl() {}
  friend boost::checked_delete(FaderControl *);
};
//---------------------------------------------------------------------------
struct PressButtonControl : public ControllerControl
{
  PressButtonControl(TFormMachine * const formParent,
    const boost::shared_ptr<PressButton> pressButton,
    Extctrls::TImage * const image);

  void OnMouseDown(const int, const int);

  private:

  const boost::shared_ptr<PressButton> mPressButton;
  const Extctrls::TImage * const mImageIn;
  const Extctrls::TImage * const mImageOut;

  //PressButtonControl can only be deleted by boost::shared_ptr
  ~PressButtonControl() {}
  friend boost::checked_delete(PressButtonControl *);
};
//---------------------------------------------------------------------------
// TabButtonControl has been moved to UnitTapButtonControl.h
//---------------------------------------------------------------------------
struct TwoSwitchControl : public ControllerControl
{
  TwoSwitchControl(TFormMachine * const formParent,
    const boost::shared_ptr<TwoSwitch> twoSwitch,
    Extctrls::TImage * const image);

  void OnMouseDown(const int x, const int y);

  private:

  const boost::shared_ptr<TwoSwitch> mTwoSwitch;
  const Extctrls::TImage * const mImageOn;
  const Extctrls::TImage * const mImageOff;

  //TwoSwitchControl can only be deleted by boost::shared_ptr
  ~TwoSwitchControl() {}
  friend boost::checked_delete(TwoSwitchControl *);
};
//---------------------------------------------------------------------------

#endif
