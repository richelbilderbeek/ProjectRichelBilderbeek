//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitGameMain.h"
//---------------------------------------------------------------------------
#include <Assert.hpp>
#include "UnitConstants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGameMain *FormGameMain;
//---------------------------------------------------------------------------
__fastcall TFormGameMain::TFormGameMain(TComponent* Owner)
  : TForm(Owner),
  mPlayerX(0),
  mPlayerY(0),
  mSpriteX(100),
  mSpriteY(100),
  mSpriteWidth(34),
  mSpriteHeight(34),
  mSpriteIndex(TPS::mainCharRocketLeft1),
  mSpeedX(0.0),
  mSpeedY(0.0),
  mPlayerStep(5),
  //mPlayerAccel(0.1),
  mPlayerJumpAccel(3.5)
{
  ImageBackground->Picture->LoadFromFile("BackGround.bmp");
  ImageSprites->Picture->LoadFromFile("Sprites.bmp");
  resizeImage(ImagePlayer,mSpriteWidth,mSpriteHeight);
  //Fill ImageList with all images

  const int width = 34;
  const int height = 34;
  for (int y=0; y<11; ++y)
  {
    for(int x=0; x<18; ++x)
    {
      mSpriteX = width * x;
      mSpriteY = height * y;
      mPlayerX = mSpriteX;
      mPlayerY = mSpriteY;
      for(int readY=mSpriteY,writeY=0; readY<mSpriteY+mSpriteHeight;++readY,++writeY)
      {
        const unsigned char * lineRead = static_cast<const char*>(ImageSprites->Picture->Bitmap->ScanLine[readY]);
        unsigned char * lineWrite = static_cast<char*>(ImagePlayer->Picture->Bitmap->ScanLine[writeY]);
        for(int readX=mSpriteX,writeX=0; readX<mSpriteX+mSpriteWidth;++readX,++writeX)
        {
          lineWrite[writeX*3+0] = lineRead[readX*3+0];
          lineWrite[writeX*3+1] = lineRead[readX*3+1];
          lineWrite[writeX*3+2] = lineRead[readX*3+2];
        }
      }
      ImageList1->AddMasked(ImagePlayer->Picture->Bitmap,clBlack);
    }
  }
  FormResize(0);


}
//---------------------------------------------------------------------------
void __fastcall TFormGameMain::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
  //Draw everything
  const std::vector<EnumKey> keys = mKeyList.GetKeys();
  for(std::vector<EnumKey>::const_iterator i = keys.begin(); i!=keys.end(); ++i)
  {
    mSpriteIndex = mSpriteIndexChanger.Move(*i,mSpriteIndex);
    switch (*i)
    {
      case keyLeft : mPlayerX-=mPlayerStep; break;
      case keyRight: mPlayerX+=mPlayerStep; break;
    }
  }
  //Image
  //ImageSprites->Canvas->Draw()

  mPlayerX+=mSpeedX;
  mPlayerY+=mSpeedY;
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  //ImageBuffer->Canvas->Draw(mPlayerX,mPlayerY,ImagePlayer->Picture->Graphic);
  ImageList1->Draw(ImageBuffer->Canvas,mPlayerX,mPlayerY,mSpriteIndex);

  Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
  Done = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormGameMain::FormResize(TObject *Sender)
{
  resizeImage(ImageBuffer,ClientWidth,ClientHeight);

}
//---------------------------------------------------------------------------
void TFormGameMain::resizeImage(const TImage* image, const int& width,const int& height)
{
  image->Picture->Graphic->Width  = width;
  image->Picture->Graphic->Height = height;
}
//---------------------------------------------------------------------------
void __fastcall TFormGameMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key)
  {
    case VK_UP:
      mSpriteIndex = mSpriteIndexChanger.MoveUp(mSpriteIndex); break;
      //mKeyList.AddKey(keyUp)   ; break;
    case VK_RIGHT: mKeyList.AddKey(keyRight); break;
    case VK_DOWN:
      //mKeyList.AddKey(keyDown) ;
      mSpriteIndex = mSpriteIndexChanger.MoveDown(mSpriteIndex); break;
    case VK_LEFT:  mKeyList.AddKey(keyLeft) ; break;
    default: Caption = Key;
  }

  const String text =
    IntToStr(mSpriteX) + " "
    + IntToStr(mSpriteY) + " "
    + IntToStr(mSpriteWidth) + " "
    + IntToStr(mSpriteHeight);
  StatusBar1->Panels->Items[0]->Text = text;
}
//---------------------------------------------------------------------------
void TFormGameMain::setSpriteIndex(const int& index)
{
  mSpriteIndex = index;
  ImageList1->Draw(ImagePlayer->Canvas,0,0,index);
}
//---------------------------------------------------------------------------
void TFormGameMain::jump()
{
  mSpeedY = -mPlayerJumpAccel;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFormGameMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key)
  {
    case VK_UP:    mKeyList.RemoveKey(keyUp)   ; break;
    case VK_RIGHT: mKeyList.RemoveKey(keyRight); break;
    case VK_DOWN:  mKeyList.RemoveKey(keyDown) ; break;
    case VK_LEFT:  mKeyList.RemoveKey(keyLeft) ; break;
    default: Caption = Key;
  }

}
//---------------------------------------------------------------------------

