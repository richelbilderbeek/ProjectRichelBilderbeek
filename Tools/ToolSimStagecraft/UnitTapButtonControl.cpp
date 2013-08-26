//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitTapButtonControl.h"
//---------------------------------------------------------------------------
/*
export template <class T>
TapButtonControl<T>::TapButtonControl(TFormMachine * const formParent,
  const boost::shared_ptr<TapButton<T> > tapButton,
  Extctrls::TImage * const image)
  : ControllerControl(formParent,image),
    mTapButton(tapButton),
    mImage(image)
{
  assert(mTapButton.get() != 0);
  assert(mImage != 0);
}
//---------------------------------------------------------------------------
export template <class T>
void TapButtonControl<T>::OnMouseDown(const int, const int y)
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
  if (distance > 0.25 * ray && (angle < 0.75 * M_PI || angle > 1.25 * M_PI ) )
  {
    mTapButton->Tap();
    //Notify the parent of this event
    mFormParent->OnControllerClick();
  }
}
//---------------------------------------------------------------------------
*/
#pragma package(smart_init)
