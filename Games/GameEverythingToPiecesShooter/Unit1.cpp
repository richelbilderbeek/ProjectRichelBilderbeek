//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner),
  mPlayerX(0),
  mPlayerY(0),
  mSpriteX(100),
  mSpriteY(100),
  mSpriteWidth(34),
  mSpriteHeight(34),
  mSpriteIndex(29),
  mSpeedX(0.0),
  mSpeedY(0.0),
  mPlayerAccel(0.1),
  mPlayerJumpAccel(3.5)
{
  ImageBackground->Picture->LoadFromFile("BackGround.bmp");
  ImageSprites->Picture->LoadFromFile("Sprites.bmp");
  resizeImage(ImagePlayer,mSpriteWidth,mSpriteHeight);
  //Fill ImageList

  const int width = 34;
  const int height = 34;
  for(int i=0; i<18; ++i)
  {
    for (int j=0; j<11; ++j)
    {
      if ((i+j)%2==0) continue;
      mSpriteX = width * i;
      mSpriteY = height * j;
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
void __fastcall TForm1::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
  //Draw everything
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

void __fastcall TForm1::FormResize(TObject *Sender)
{
  resizeImage(ImageBuffer,ClientWidth,ClientHeight);

}
//---------------------------------------------------------------------------
void TForm1::resizeImage(const TImage* image, const int& width,const int& height)
{
  image->Picture->Graphic->Width  = width;
  image->Picture->Graphic->Height = height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key)
  {
    case VK_LEFT:  turnLeft();break;
    case VK_RIGHT: turnRight(); break;
    case VK_UP:    pressUp();break;
    case VK_DOWN:  pressDown(); break;
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
void TForm1::turnLeft()
{
  mSpeedX-=mPlayerAccel;
  if (mSpriteIndex==29) setSpriteIndex(13);
  else if (mSpriteIndex==18) setSpriteIndex(40);
  else if (mSpriteIndex==24) setSpriteIndex(35);

}
//---------------------------------------------------------------------------
void TForm1::turnRight()
{
  mSpeedX+=mPlayerAccel;
  if (mSpriteIndex==13) setSpriteIndex(29);
  else if (mSpriteIndex==40) setSpriteIndex(18);
  else if (mSpriteIndex==35) setSpriteIndex(24);
}
//---------------------------------------------------------------------------
void TForm1::pressUp()
{
  if (mSpriteIndex==24) setSpriteIndex(29);
  else if (mSpriteIndex==29) setSpriteIndex(18);
  else if (mSpriteIndex==35) setSpriteIndex(13);
  else if (mSpriteIndex==13) setSpriteIndex(40);
  //if (mSpriteIndex==35) setSpriteIndex(24);
}
//---------------------------------------------------------------------------
void TForm1::pressDown()
{
  if (mSpriteIndex==18) setSpriteIndex(29);
  else if (mSpriteIndex==29) setSpriteIndex(24);
  else if (mSpriteIndex==40) setSpriteIndex(13);
  else if (mSpriteIndex==13) setSpriteIndex(35);
}
//---------------------------------------------------------------------------
void TForm1::setSpriteIndex(const int& index)
{
  mSpriteIndex = index;
  ImageList1->Draw(ImagePlayer->Canvas,0,0,index);
}
//---------------------------------------------------------------------------
void TForm1::jump()
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

