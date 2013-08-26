//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitDisplay.h"
#include "UnitDisplayControl.h"
#include "UnitFormSprites.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
DisplayControl::DisplayControl(Extctrls::TImage * const image)
  : mImage(image)
{
  assert(mImage!=0);
}
//---------------------------------------------------------------------------
AudioSignalControl::AudioSignalControl(
    const boost::shared_ptr<AudioSignalDisplay> audioSignalDisplay,
    Extctrls::TImage * const image)
  : DisplayControl(image), mAudioSignalDisplay(audioSignalDisplay)
{
  assert(mAudioSignalDisplay.get()!=0);
}
//---------------------------------------------------------------------------
void AudioSignalControl::Update()
{
  const double intensity = mAudioSignalDisplay->GetDisplayIntensity();
  DrawAudioSignal(mImage,intensity);
}
//---------------------------------------------------------------------------
LcdSymbolControl::LcdSymbolControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image, Extctrls::TImage * const imageLcdSymbol)
  : DisplayControl(image), mLcdSymbol(lcdSymbol), mImageLcdSymbol(imageLcdSymbol)
{
  assert(mLcdSymbol.get()!=0);
  assert(mImageLcdSymbol!=0);
}
//---------------------------------------------------------------------------
void LcdSymbolControl::Update()
{
  const double intensity = mLcdSymbol->GetDisplayIntensity();
  mImage->Picture = mImageLcdSymbol->Picture;
  Blacken(mImage,1.0-intensity);
}
//---------------------------------------------------------------------------
LcdSymbolPlayControl::LcdSymbolPlayControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image)
  : LcdSymbolControl(lcdSymbol,image,FormSprites->ImageLcdSymbolPlay)
{

}
//---------------------------------------------------------------------------
LcdSymbolRecControl::LcdSymbolRecControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image)
  : LcdSymbolControl(lcdSymbol,image,FormSprites->ImageLcdSymbolRec)
{

}
//---------------------------------------------------------------------------
LedControl::LedControl(const boost::shared_ptr<Led> led,
    Extctrls::TImage * const image)
  : DisplayControl(image), mLed(led)
{
  assert(mLed.get()!=0);
}
//---------------------------------------------------------------------------
void LedControl::Update()
{
  const double intensity = mLed->GetDisplayIntensity();
  DrawLed(mImage,intensity,mLed->mRed,mLed->mGreen,mLed->mBlue);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
