//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cassert>
#include <cmath>
#include "UnitController.h"
#include "UnitControllerControl.h"
#include "UnitFunctions.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
ControllerControl::ControllerControl(
  TFormMachine * const formParent,
  Extctrls::TImage * const image)
  : mFormParent(formParent),
    mImage(image)
{
  assert(formParent!=0);
  assert(mImage!=0);
}
//---------------------------------------------------------------------------
DialControl::DialControl(TFormMachine * const formParent,
  const boost::shared_ptr<Dial> dial,
  Extctrls::TImage * const image)
  : ControllerControl(formParent,image),mDial(dial)
{
  assert(mDial.get()!=0);
}
//---------------------------------------------------------------------------
void DialControl::OnMouseDown(const int x, const int y)
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
    DrawDial(mImage, x, y, clWhite);
    const double position =
      ( angle < 0.75 * M_PI
        ? 0.5 + (0.5 * (angle / (0.75 * M_PI))) //Topright
        : 0.5 * (angle - (1.25 * M_PI)) / (0.75 * M_PI) //Topleft
      );
    assert(position >= 0.0);
    assert(position <= 1.0);
    mDial->SetPosition(position);
    //Notify the parent of this event
    mFormParent->OnControllerClick();
  }
}
//---------------------------------------------------------------------------
FaderControl::FaderControl(TFormMachine * const formParent,
  const boost::shared_ptr<Fader> fader,
  Extctrls::TImage * const image)
  : ControllerControl(formParent,image), mFader(fader)
{
  assert(mFader.get()!=0);
}
//---------------------------------------------------------------------------
void FaderControl::OnMouseDown(const int, const int y)
{
  DrawFader(mImage,y);
  //Top of fader is position 1.0,
  //Bottom of fader is position 0.0
  const double position = 1.0 - static_cast<double>(y)
    / static_cast<double>(mImage->Height);
  assert(position >= 0.0);
  assert(position <= 1.0);
  mFader->SetPosition(position);
  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
PressButtonControl::PressButtonControl(TFormMachine * const formParent,
  const boost::shared_ptr<PressButton> pressButton,
  Extctrls::TImage * const image)
  : ControllerControl(formParent,image),
    mPressButton(pressButton),
    mImageIn(FormSprites->ImagePressButtonIn),
    mImageOut(FormSprites->ImagePressButtonOut)
{
  assert(mPressButton.get() != 0);
  assert(mImage != 0);
  assert(mImageIn != 0);
  assert(mImageOut != 0);
  assert(mImageIn->Height == mImageOut->Height);
  assert(mImageIn->Picture->Bitmap->Height == mImageOut->Picture->Bitmap->Height);
}
//---------------------------------------------------------------------------
void PressButtonControl::OnMouseDown(const int, const int y)
{
  assert(mImage->Height == mImageOut->Height);
  assert(mImageIn->Height == mImageOut->Height);
  assert(mImageIn->Picture->Bitmap->Height == mImageOut->Picture->Bitmap->Height);

  mPressButton->Press();

  if (mPressButton->IsIn() == true)
  {
    mImage->Picture = mImageIn->Picture;
  }
  else
  {
    mImage->Picture = mImageOut->Picture;
  }

  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
TwoSwitchControl::TwoSwitchControl(TFormMachine * const formParent,
  const boost::shared_ptr<TwoSwitch> twoSwitch,
  Extctrls::TImage * const image)
  : ControllerControl(formParent,image),
    mTwoSwitch(twoSwitch),
    mImageOn(FormSprites->ImageTwoSwitchOn),
    mImageOff(FormSprites->ImageTwoSwitchOff)
{
  assert(mTwoSwitch.get() != 0);
  assert(mImage != 0);
  assert(mImageOn != 0);
  assert(mImageOff != 0);
  assert(mImageOn->Height == mImageOff->Height);
  assert(mImageOn->Picture->Bitmap->Height == mImageOff->Picture->Bitmap->Height);
}
//---------------------------------------------------------------------------
void TwoSwitchControl::OnMouseDown(const int, const int y)
{
  assert(mImage->Height == mImageOff->Height);
  assert(mImageOn->Height == mImageOff->Height);
  assert(mImageOn->Picture->Bitmap->Height == mImageOff->Picture->Bitmap->Height);
  const int height = mImage->Height;

  //Lower half of image, turn two-switch to on
  if (y > height / 2)
  {
    mImage->Picture = mImageOn->Picture;
    mTwoSwitch->SwitchOn();
  }
  else if (y < height / 2)
  {
    //Turn two-switch to off
    mImage->Picture = mImageOff->Picture;
    mTwoSwitch->SwitchOff();
  }
  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)






