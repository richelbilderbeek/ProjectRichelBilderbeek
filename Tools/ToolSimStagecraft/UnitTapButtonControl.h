//---------------------------------------------------------------------------

#ifndef UnitTapButtonControlH
#define UnitTapButtonControlH
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include "UnitControllerControl.h"
#include "UnitFunctions.h"
#include "UnitTapButton.h"
//---------------------------------------------------------------------------
export template <class T>
struct TapButtonControl : public ControllerControl
{
  TapButtonControl(TFormMachine * const formParent,
    const boost::shared_ptr<TapButton<T> > tapButton,
    Extctrls::TImage * const image)
    : ControllerControl(formParent,image),
      mTapButton(tapButton),
      mImage(image)
  {
    assert(mTapButton.get() != 0);
    assert(mImage != 0);
  }

  void OnMouseDown(const int x, const int y)
  {
    const int midX = mImage->Width / 2;
    const int midY = mImage->Height / 2;
    const double angle
      = GetAngle( static_cast<double>(x - midX),
          static_cast<double>(y - midY));
    const double ray = static_cast<double>(std::min( midX, midY ));
    const double distance
      = GetDistance(
        static_cast<double>(x - midX),
        static_cast<double>(y - midY) );
    if (distance < ray )
    {
      mTapButton->Tap();
      //Notify the parent of this event
      mFormParent->OnControllerClick();
    }
  }

  private:

  const boost::shared_ptr<TapButton<T> > mTapButton;
  const Extctrls::TImage * const mImage;

  //TapButtonControl can only be deleted by boost::shared_ptr
  ~TapButtonControl() {}
  friend boost::checked_delete(TapButtonControl *);
};
//---------------------------------------------------------------------------
#endif
