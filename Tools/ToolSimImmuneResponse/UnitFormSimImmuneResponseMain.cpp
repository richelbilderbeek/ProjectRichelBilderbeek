//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <cassert>
#include <string>
#include "UnitSprite.h"
#include "UnitEnum.h"
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSimImmuneResponseMain.h"
#include "UnitFormSimImmuneResponseLegend.h"
#include "UnitFormSimImmuneResponseFeedback.h"
#include "UnitFormSimImmuneResponseOptions.h"
#include "UnitFormSimImmuneResponseInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimImmuneResponseMain *FormSimImmuneResponseMain;
//---------------------------------------------------------------------------
__fastcall TFormSimImmuneResponseMain::TFormSimImmuneResponseMain(TComponent* Owner)
  : TForm(Owner),
    mFormFeedback(new TFormSimImmuneResponseFeedback(this)),
    mFormInfo(new TFormSimImmuneResponseInfo(this)),
    mFormLegend(new TFormSimImmuneResponseLegend(this)),
    mFormOptions(new TFormSimImmuneResponseOptions(this)),
    mMouseDown(false),
    mDraggingSomething(false),
    //mSprite(0),
    mNpaneCols(2),
    mNpaneRows(2)
{
  {
    //Arrange the forms
    mFormFeedback->Width = Width + mFormLegend->Width - mFormOptions->Width - mFormInfo->Width;
    const int totalWidth  = this->Width  + mFormLegend->Width;
    const int totalHeight = this->Height + mFormOptions->Height;
    Left = (Screen->WorkAreaWidth  / 2) - (totalWidth / 2);
    Top  = (Screen->WorkAreaHeight / 2) - (totalHeight / 2);
    mFormLegend->Left = Left + Width;
    mFormLegend->Top = Top;
    mFormOptions->Left = Left;
    mFormOptions->Top = Top + Height;
    mFormInfo->Left = mFormOptions->Left + mFormOptions->Width;
    mFormInfo->Top = Top + Height;
    mFormFeedback->Left = mFormInfo->Left + mFormInfo->Width;
    mFormFeedback->Top = Top + Height;
  }

  OnResize(0);
  TimerFeedbackTimer(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseMain::FormResize(TObject *Sender)
{
  const int clientWidth  = this->GetClientWidth();
  const int clientHeight = this->GetClientHeight();
  assert(clientWidth  % 32 == 0);
  assert(clientHeight % 32 == 0);
  //if (clientWidth  % mNpaneCols != 0) { ++ClientWidth ; return; }
  //if (clientHeight % mNpaneRows != 0) { ++ClientHeight; return; }

  ImageBuffer->Picture->Bitmap->Width  = clientWidth;
  ImageBuffer->Picture->Bitmap->Height = clientHeight;

  const int blockWidth  = clientWidth  / mNpaneCols;
  const int blockHeight = clientHeight / mNpaneRows;

  Sprite::maxx = blockWidth;
  Sprite::maxy = blockHeight;
  //Top left, bone marrow
  ImageBoneMarrow->Picture->Bitmap->Width  = blockWidth;
  ImageBoneMarrow->Picture->Bitmap->Height = blockHeight;
  ImageBoneMarrowBackground->Picture->Bitmap->Width  = blockWidth;
  ImageBoneMarrowBackground->Picture->Bitmap->Height = blockHeight;
  PaintVcl(ImageBoneMarrowBackground,255,196,255);
  ImageBoneMarrowBackground->Canvas->Font = Font;
  ImageBoneMarrowBackground->Canvas->Font->Size = 24;
  DrawTextCentered(ImageBoneMarrowBackground,"Bone marrow");
  //Top right, cell tissue
  ImageCellTissue->Picture->Bitmap->Width  = blockWidth;
  ImageCellTissue->Picture->Bitmap->Height = blockHeight;
  ImageCellTissueBackground->Picture->Bitmap->Width  = blockWidth;
  ImageCellTissueBackground->Picture->Bitmap->Height = blockHeight;
  PaintVcl(ImageCellTissueBackground,196,196,196);
  ImageCellTissueBackground->Canvas->Font = Font;
  ImageCellTissueBackground->Canvas->Font->Size = 24;
  DrawTextCentered(ImageCellTissueBackground,"Cell tissue");
  //Bottom left, bloodstream
  ImageBloodStream->Picture->Bitmap->Width  = blockWidth;
  ImageBloodStream->Picture->Bitmap->Height = blockHeight;
  ImageBloodStreamBackground->Picture->Bitmap->Width  = blockWidth;
  ImageBloodStreamBackground->Picture->Bitmap->Height = blockHeight;
  PaintVcl(ImageBloodStreamBackground,255,196,196);
  ImageBloodStreamBackground->Canvas->Font = Font;
  ImageBloodStreamBackground->Canvas->Font->Size = 24;
  DrawTextCentered(ImageBloodStreamBackground,"Blood stream");
  //Bottom right, lymph node
  ImageLymphNode->Picture->Bitmap->Width  = blockWidth;
  ImageLymphNode->Picture->Bitmap->Height = blockHeight;
  ImageLymphNodeBackground->Picture->Bitmap->Width  = blockWidth;
  ImageLymphNodeBackground->Picture->Bitmap->Height = blockHeight;
  PaintVcl(ImageLymphNodeBackground,255,255,196);
  ImageLymphNodeBackground->Canvas->Font = Font;
  ImageLymphNodeBackground->Canvas->Font->Size = 24;
  DrawTextCentered(ImageLymphNodeBackground,"Lymph node");

}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetClientWidth() const
{
  //const_cast as the VCL is not const-correct. Grumble, grumble....
  return const_cast<TFormSimImmuneResponseMain*>(this)->ClientWidth;
}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetClientHeight() const
{
  //const_cast as the VCL is not const-correct. Grumble, grumble....
  return const_cast<TFormSimImmuneResponseMain*>(this)->ClientHeight;
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseMain::TimerSpritesTimer(TObject *Sender)
{
  mSim.Tick();
  {
    //Clean the four background
    ImageBoneMarrow->Canvas->Draw(0,0,ImageBoneMarrowBackground->Picture->Graphic);
    ImageBloodStream->Canvas->Draw(0,0,ImageBloodStreamBackground->Picture->Graphic);
    ImageCellTissue->Canvas->Draw(0,0,ImageCellTissueBackground->Picture->Graphic);
    ImageLymphNode->Canvas->Draw(0,0,ImageLymphNodeBackground->Picture->Graphic);
  }

  {
    //Draw the four location's sprites
    typedef std::list<boost::shared_ptr<Sprite> >::const_iterator Iterator;
    {
      //Bone marrow
      const std::list<boost::shared_ptr<Sprite> >& v = mSim.GetSprites(boneMarrow);
      const Iterator j = v.end();
      for (Iterator i = v.begin(); i!=j; ++i)
      {
        ImageBoneMarrow->Canvas->Draw((*i)->GetX(), (*i)->GetY(), (*i)->GetImage()->Picture->Graphic);
      }
    }
    {
      //Cell Tissue
      const std::list<boost::shared_ptr<Sprite> >& v = mSim.GetSprites(cellTissue);
      const Iterator j = v.end();
      for (Iterator i = v.begin(); i!=j; ++i)
      {
        ImageCellTissue->Canvas->Draw((*i)->GetX(), (*i)->GetY(), (*i)->GetImage()->Picture->Graphic);
      }
    }
    {
      //Blood stream
      const std::list<boost::shared_ptr<Sprite> >& v = mSim.GetSprites(bloodStream);
      const Iterator j = v.end();
      for (Iterator i = v.begin(); i!=j; ++i)
      {
        ImageBloodStream->Canvas->Draw((*i)->GetX(), (*i)->GetY(), (*i)->GetImage()->Picture->Graphic);
      }
    }
    {
      //Lymph node
      const std::list<boost::shared_ptr<Sprite> >& v = mSim.GetSprites(lymphNode);
      const Iterator j = v.end();
      for (Iterator i = v.begin(); i!=j; ++i)
      {
        ImageLymphNode->Canvas->Draw((*i)->GetX(), (*i)->GetY(), (*i)->GetImage()->Picture->Graphic);
      }
    }
  }

  //Draw the four locations on the buffer
  {
    const int dx = (this->GetClientWidth()  / mNpaneCols);
    const int dy = (this->GetClientHeight() / mNpaneRows);
    ImageBuffer->Canvas->Draw(0 * dx, 0 * dy,ImageBoneMarrow->Picture->Graphic);
    ImageBuffer->Canvas->Draw(1 * dx, 0 * dy,ImageCellTissue->Picture->Graphic);
    ImageBuffer->Canvas->Draw(0 * dx, 1 * dy,ImageBloodStream->Picture->Graphic);
    ImageBuffer->Canvas->Draw(1 * dx, 1 * dy,ImageLymphNode->Picture->Graphic);
  }

  if (mDraggingSomething == true)
  {
    const TPoint pos = this->CalcCursorPos();
    //Draw the dragged cell on screen
    ImageBuffer->Canvas->Draw(
      pos.x,pos.y,
      mSprite->GetImage()->Picture->Graphic);
  }

  //Draw the buffer to screen
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

}
//---------------------------------------------------------------------------
const TImage * const TFormSimImmuneResponseMain::ToImage(
  const EnumCellType t) const
{
  return mFormLegend->ToImage(t);
}
//---------------------------------------------------------------------------
void TFormSimImmuneResponseMain::Restart()
{
  mDraggingSomething = false;
  mSim = SimImmuneResponse();

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------
const EnumLocation TFormSimImmuneResponseMain::GetLocation(
  const int x, const int y) const
{
  const int dx = (this->GetClientWidth()  / mNpaneCols);
  const int dy = (this->GetClientHeight() / mNpaneRows);
  const int locationX = x / dx;
  const int locationY = y / dy;
  if (locationY <= 0)
  {
    if (locationX <= 0)
      return boneMarrow;
    else
      return cellTissue;
  }
  else
  {
    if (locationX <= 0)
      return bloodStream;
    else
      return lymphNode;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Caption = IntToStr(X) + " , " + IntToStr(Y);
  mMouseDown = true;

  const EnumLocation location = this->GetLocation(X,Y);


  //Perhaps start dragging something
  const int dx = (this->GetClientWidth()  / mNpaneCols);
  const int dy = (this->GetClientHeight() / mNpaneRows);

  if (mSim.CanGrabSprite(location,X%dx,Y%dy) == false)
  {
    //Nothing to grab
    return;
  }

  mSprite = mSim.GrabSprite(location,X%dx,Y%dy);
  mDraggingSomething = true;

  //Draw the grabbed image on screen
  TImage * const image = mFormInfo->ImageInfo;
  PaintVcl(image,0,0,0);
  const TRect r(0,0,image->Picture->Graphic->Width, image->Picture->Graphic->Height);
  image->Canvas->StretchDraw( r, mSprite->GetImage()->Picture->Graphic);
  DrawTextCentered(image,CellTypeToString(mSprite->GetCellType()));
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseMain::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Caption = IntToStr(X) + " , " + IntToStr(Y);
  mMouseDown = false;

  if (mDraggingSomething == true)
  {
    const int maxx = 2 * (this->GetClientWidth()  / mNpaneCols);
    const int maxy = this->GetClientHeight();
    TPoint p = Mouse->CursorPos;
    if (X > maxx)
    {
      p.x -= (X - maxx);
      Mouse->CursorPos = p;
      X = maxx - 1; //Change X
    }
    else if (X < 0)
    {
      p.x += (-X) ;
      Mouse->CursorPos = p;
      X = 0; //Change X
    }
    if (Y > maxy)
    {
      p.y -= (Y - maxy);
      Mouse->CursorPos = p;
      Y = maxy - 1; //Change Y
    }
    else if (Y < 0)
    {
      p.y += (-Y) ;
      Mouse->CursorPos = p;
      Y = 0; //Change Y
    }


    const EnumLocation location = GetLocation(X,Y);
    const int blockWidth  = (this->GetClientWidth()  / mNpaneCols);
    const int blockHeight = (this->GetClientHeight() / mNpaneRows);
    mSprite->SetX(X % blockWidth);
    mSprite->SetY(Y % blockHeight);
    mSim.AddSprite(mSprite,location);
    mDraggingSomething = false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormSimImmuneResponseMain::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  //Prevent dragged stuff leaving the gaming area
  const int maxx = 2 * (this->GetClientWidth()  / mNpaneCols);
  const int maxy = this->GetClientHeight();

  if (mDraggingSomething)
  {
    TPoint p = Mouse->CursorPos;
    if (X > maxx)
    {
      p.x -= (X - maxx);
      Mouse->CursorPos = p;
    }
    else if (X < 0)
    {
      p.x += (-X) ;
      Mouse->CursorPos = p;
    }
    if (Y > maxy)
    {
      p.y -= (Y - maxy);
      Mouse->CursorPos = p;
    }
    else if (Y < 0)
    {
      p.y += (-Y) ;
      Mouse->CursorPos = p;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseMain::TimerFeedbackTimer(
      TObject *Sender)
{
  mFormFeedback->RichEditFeedback->Clear();
  mFormFeedback->RichEditFeedback->Lines->Add(
    AnsiString(mSim.GetFeedback().c_str()) );
}
//---------------------------------------------------------------------------

void TFormSimImmuneResponseMain::AddCell(const EnumCellType cellType)
{
  mSim.AddSprite(cellType,boneMarrow);
}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetLocationWidth() const
{
  return ImageBoneMarrow->Picture->Graphic->Width;
}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetLocationHeight() const
{
  return ImageBoneMarrow->Picture->Graphic->Height;
}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetSpriteWidth() const
{
  return mFormLegend->ImageBcell->Picture->Graphic->Width;
}
//---------------------------------------------------------------------------
const int TFormSimImmuneResponseMain::GetSpriteHeight() const
{
  return mFormLegend->ImageBcell->Picture->Graphic->Height;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetFontHeight.htm
const int GetFontHeight(const TImage * const image)
{
  //const_cast necessary as the VCL is not const-correct. Grumble, grumble...
  return const_cast<TImage*>(image)->Canvas->TextHeight("x");
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawTextCentered.htm
void DrawTextCentered(TImage* const image, const std::string& s)
{
  const int textWidth = image->Canvas->TextWidth(s.c_str());
  const int textHeight = GetFontHeight(image);
  assert(textHeight >= 0);
  const int midX = image->Picture->Graphic->Width / 2;
  const int midY = image->Picture->Graphic->Height / 2;
  const int x1 = midX - (textWidth  / 2);
  const int y1 = midY - (textHeight / 2);
  const int x2 = midX + (textWidth  / 2);
  const int y2 = midY + (textHeight / 2);
  image->Canvas->TextRect(
    TRect(x1,y1,x2,y2),
    x1,y1,s.c_str());
}
//---------------------------------------------------------------------------

