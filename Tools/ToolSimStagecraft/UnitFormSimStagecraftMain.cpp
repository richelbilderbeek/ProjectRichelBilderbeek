//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <algorithm>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "UnitCreateMachines.h"
#include "UnitConnectorControl.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimStagecraftMain *FormSimStagecraftMain;
//---------------------------------------------------------------------------
//The constructor a TForm-derived class cannot take a TComponent* and
//int, because this will result in a Stack Overflow. Instead of passing an
//int, a String is passed.
__fastcall TFormSimStagecraftMain::TFormSimStagecraftMain(TComponent* Owner,
  const String selectedLevel)
  : TForm(Owner),
    mMachines(CreateMachines(this,StrToInt(selectedLevel))),
    mConnector1(0), mConnector2(0), //Human, 1-based counting :-)
    mDragMachine(0),
    mDragX(0),
    mDragY(0)
{
  //Set the Tag of the three TSpeedButtons
  //These are used in the OnButtonClick method
  ButtonView->Tag    = 1;
  ButtonConnect->Tag = 2;
  ButtonUse->Tag     = 3;

  OnResize(0);

  SetDisplayModes(modeView);

  UpdateBuffers();

  DrawScreen();
}
//---------------------------------------------------------------------------
const int TFormSimStagecraftMain::GetDrawingSurfaceHeight() const
{
  //Need to remove const of TFormStagecraftMain,
  //because the VCL is not const-correct. Grumble, grumble...
  TFormSimStagecraftMain * const form = const_cast<TFormSimStagecraftMain*>(this);
  return form->ClientHeight - form->PanelBottom->Height;
}
//---------------------------------------------------------------------------
const int TFormSimStagecraftMain::GetDrawingSurfaceWidth() const
{
  //Need to remove const of TFormStagecraftMain,
  //because the VCL is not const-correct. Grumble, grumble...
  TFormSimStagecraftMain * const form = const_cast<TFormSimStagecraftMain*>(this);
  return form->ClientWidth;
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::DrawScreen()
{
  //Draw background on buffer (or clear buffer otherwise)
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  {
    
    //Draw all Machines
    const ConstMachineIterator j = mMachines.end();
    for (ConstMachineIterator i = mMachines.begin();
      i!=j;
      ++i)
    {
      const int x = (*i)->Left;
      const int y = (*i)->Top;
      ImageBuffer->Canvas->Draw(x,y,(*i)->ImageBuffer->Picture->Graphic);
    }
  }

  //Draw wires on buffer
  //??

  //Draw buffer to screen
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::SetDisplayModes(const EnumDisplayMode mode)
{
  mDisplayMode = mode;
  //Set the DisplayMode of all TFormMachines
  const MachineIterator j = mMachines.end();
  for (MachineIterator i = mMachines.begin(); i!=j; ++i)
  {
    (*i)->SetDisplayMode(mode);
  }
  UpdateBuffers(); //Needed for non-active machines (e.g. Par64 and WallSocket220)
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::UpdateBuffers()
{
  //Set the DisplayMode of all TFormMachines
  const MachineIterator j = mMachines.end();
  for (MachineIterator i = mMachines.begin(); i!=j; ++i)
  {
    (*i)->UpdateBuffer();
  }
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::PaintBackground()
{
  TImage * const image = ImageBackground;

  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);

    for (int x = 0; x != maxx; ++x)
    {
      const double xD = static_cast<double>(x);
      //Range z: -3 , +3
      const double zD
        = std::cos(xD / 30.0)
        + std::sin(yD / 45.0)
        - std::sin( (xD + yD) / 60.0);
      const int grey = static_cast<int>( (zD + 3.0) * (256.0 / 6.0) );
      assert(grey >=   0);
      assert(grey <  256);
      myLine[x*3+2] = grey; //Red
      myLine[x*3+1] = grey; //Green
      myLine[x*3+0] = grey; //Blue
    }
  }
}
//---------------------------------------------------------------------------}
void TFormSimStagecraftMain::TickBackground()
{
  TImage * const image = ImageBackground;

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
      ++myLine[x*3+2]; //Red
      ++myLine[x*3+1]; //Green
      ++myLine[x*3+0]; //Blue
    }
  }
}
//---------------------------------------------------------------------------}

void __fastcall TFormSimStagecraftMain::TimerMainTimer(TObject *Sender)
{
  //TickBackground();

  if (CheckBoxAutoMove->Checked == true) AutoMove();

  DrawScreen();

}
//---------------------------------------------------------------------------

void __fastcall TFormSimStagecraftMain::OnButtonClick(TObject *Sender)
{
  //Only SpeedButtons are allowed to call this method
  //button is not const,
  //because the VCL is not const-correct. Grumble, grumble...
  TSpeedButton * const button = dynamic_cast<TSpeedButton*>(Sender);
  assert(button!=0);
  switch (button->Tag)
  {
    case 1: this->SetDisplayModes(modeView   ); break;
    case 2: this->SetDisplayModes(modeConnect);break;
    case 3: this->SetDisplayModes(modeUse    ); break;
    default:
      OutputDebugString(IntToStr(button->Tag).c_str());
      assert(!"Should not get here: Unknown TSpeedButton::Tag");
  }

  DrawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMain::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  switch (Key)
  {
    case 'A': case 'a':
      CheckBoxAutoMove->Checked = !CheckBoxAutoMove->Checked; 
      break;
    case 'V': case 'v': case '1': case VK_F1:
      ButtonView->Down = true;
      OnButtonClick(ButtonView);
      break;
    case 'C': case 'c': case '2': case VK_F2:
      ButtonConnect->Down = true;
      OnButtonClick(ButtonConnect);
      break;
    case 'U': case 'u': case '3': case VK_F3:
      ButtonUse->Down = true;
      OnButtonClick(ButtonUse);
      break;
    case 'Q': /*case 'q':*/ case '0': case VK_F10:
      Close();
      break;
  }
}
//---------------------------------------------------------------------------
//Children forms will call this method if a connector is clicked.
//This method return if the connector is selected or not
//The child forms know if the connector is connected or not
void TFormSimStagecraftMain::OnConnectorClick(
  ConnectorControl * const connector)
{
  assert(connector != 0);

  if (mConnector1 == connector)
  {
    //Unselect
    mConnector1->Unselect();
    mConnector1= 0;
  }
  else if (mConnector2 == connector)
  {
    //Disconnect
    mConnector2->Unselect();
    mConnector2= 0;
  }
  else if ( mConnector1 && mConnector2 != 0)
  {
    assert(mConnector2 != connector); //Assume no self-connection
    mConnector1 = connector;
    mConnector1->Select();
    if ( mConnector1->IsConnected() == false
      && mConnector2->IsConnected() == false)
    {
      //A connection!
      // (Note: if connection is invalid, no actual connection takes place)
      mConnector1->Connect(mConnector2);
      mConnector2->Connect(mConnector1);
      mConnector1->Unselect();
      mConnector2->Unselect();
      mConnector1= 0;
      mConnector2= 0;
    }
    else if ( mConnector1->IsConnectedTo(mConnector2) == true
           && mConnector2->IsConnectedTo(mConnector2) == true)
    {
      //Unconnection
      mConnector1->Disconnect();
      mConnector2->Disconnect();
      mConnector1->Unselect();
      mConnector2->Unselect();
      mConnector1= 0;
      mConnector2= 0;
    }
    else
    {
      //Use selected two different things
      //Leave both selected
    }
  }
  else if ( mConnector1 != 0 && mConnector2 == 0)
  {
    assert(mConnector2 != connector); //Assume no self-connection
    mConnector2 = connector;
    mConnector2->Select();
    if ( mConnector1->IsConnected() == false
      && mConnector2->IsConnected() == false)
    {
      assert( mConnector1->CanConnect(mConnector2)
        == mConnector2->CanConnect(mConnector1)
        && "If A fits (not) in B, B fits (not) into A");
      if (mConnector1->CanConnect(mConnector2)==true)
      {
        //A connection!
        mConnector1->Connect(mConnector2);
        assert(mConnector1->IsConnected()==true);
        assert(mConnector2->IsConnected()==true);
        mConnector2->Connect(mConnector1);
        assert(mConnector1->IsConnectedTo(mConnector2)==true);
        assert(mConnector2->IsConnectedTo(mConnector1)==true);
      }
    }
    else if ( mConnector1->IsConnectedTo(mConnector2) == true
           && mConnector2->IsConnectedTo(mConnector1) == true)
    {
      //Unconnection
      mConnector1->Disconnect();
      mConnector2->Disconnect();
      assert(mConnector1->IsConnected()==false);
      assert(mConnector2->IsConnected()==false);
    }
    else
    {
      //Use selected two different things
      //Leave both selected
    }
    mConnector1->Unselect();
    mConnector2->Unselect();
    mConnector1 = 0;
    mConnector2 = 0;
  }
  else
  {
    assert(mConnector1 == 0 && mConnector2 == 0);
    mConnector1 = connector;
    mConnector1->Select();
  }
  //Update the buffers to show the new state
  UpdateBuffers();
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::OnControllerClick()
{
  UpdateBuffers(); //Refreshes all TFormMachines
}
//---------------------------------------------------------------------------

void __fastcall TFormSimStagecraftMain::ImageQuitMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Close();  
}
//---------------------------------------------------------------------------
const bool TFormSimStagecraftMain::OnFormMachine(const int x, const int y,
  const TFormMachine * const formReal) const
{
  //Const_cast because the VCL is not const-correct. Grumble, grumble...
  TFormMachine * const form = const_cast<TFormMachine*>(formReal);
  return (
       x >= form->Left
    && x  < form->Left + form->ClientWidth
    && y >= form->Top
    && y  < form->Top + form->ClientHeight);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  //
  const int nFormMachines = mMachines.size();
  for (int i=nFormMachines-1; i!=-1; --i)
  {
    if (OnFormMachine(X,Y,mMachines[i].get())==true)
    {
      //Cursor is on the top window
      const int formX = X - mMachines[i]->Left;
      const int formY = Y - mMachines[i]->Top;
      const int borderSize = TFormMachine::mBorderSize;
      //Dragging?
      if ( formX < borderSize
        || formX > mMachines[i]->ClientWidth - borderSize
        || formY < borderSize
        || formY > mMachines[i]->ClientHeight - borderSize)
      {
        //Start dragging
        mDragMachine = mMachines[i].get();
        mDragX = X;
        mDragY = Y;
        //Make dragged machine appear on top
        //by swapping it to the end of the std::vector
        //(no lust to use std::vector::remove and so...)
        for (int j = i; j != nFormMachines - 1; ++j)
        {
          assert(j + 1 < static_cast<int>(mMachines.size()));
          std::swap(mMachines[j],mMachines[j+1]);
        }
        this->Cursor = crDrag;
        return;
      }
      else
      {
        mMachines[i]->OnMouseDown(formX,formY);
        return;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMain::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (mDragMachine != 0)
  {
    const int dX = X - mDragX;
    const int dY = Y - mDragY;
    mDragMachine->Left += dX;
    mDragMachine->Top  += dY;
    mDragX = X;
    mDragY = Y;
    this->Cursor = crDrag;
  }
  else
  {
    //Can drag?
    const int nFormMachines = mMachines.size();
    for (int i=nFormMachines-1; i!=-1; --i)
    {
      if (OnFormMachine(X,Y,mMachines[i].get())==true)
      {
        //We are on the top windows
        const int formX = X - mMachines[i]->Left;
        const int formY = Y - mMachines[i]->Top;
        const int borderSize = TFormMachine::mBorderSize;
        //Dragging?
        if ( formX < borderSize
          || formX > mMachines[i]->ClientWidth - borderSize
          || formY < borderSize
          || formY > mMachines[i]->ClientHeight - borderSize)
        {
          this->Cursor = crDrag;
          return;
        }
        else
        {
          this->Cursor = crArrow;
          return;
        }
      }
    }
    this->Cursor = crArrow;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormSimStagecraftMain::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  mDragMachine = 0;
  this->Cursor = crArrow;
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMain::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width      = this->GetDrawingSurfaceWidth();
  ImageBuffer->Picture->Bitmap->Height     = this->GetDrawingSurfaceHeight();
  ImageBackground->Picture->Bitmap->Width  = this->GetDrawingSurfaceWidth();
  ImageBackground->Picture->Bitmap->Height = this->GetDrawingSurfaceHeight();
  //Resize SpeedButtons
  const int spacing = 4; //The number of pixels from button to edge of TPanel
  const int buttonWidth
    = (PanelBottom->ClientWidth / 3)
    - (4 * spacing)
    - (ImageQuit->Width / 3)
    - (CheckBoxAutoMove->Width / 3);
  const int buttonHeight = PanelBottom->ClientHeight  - ( 2 * spacing);
  CheckBoxAutoMove->Left = (1 * spacing);
  ButtonView->Left       = (2 * spacing) + (0 * buttonWidth);
  ButtonConnect->Left    = (3 * spacing) + (1 * buttonWidth);
  ButtonUse->Left        = (4 * spacing) + (2 * buttonWidth);
  ButtonView->Left       += (CheckBoxAutoMove->Left + CheckBoxAutoMove->Width);
  ButtonConnect->Left    += (CheckBoxAutoMove->Left + CheckBoxAutoMove->Width);
  ButtonUse->Left        += (CheckBoxAutoMove->Left + CheckBoxAutoMove->Width);
  CheckBoxAutoMove->Top
    = (PanelBottom->ClientHeight / 2)
    - (CheckBoxAutoMove->Height / 2);
  ButtonView->Top     = spacing;
  ButtonUse->Top      = spacing;
  ButtonConnect->Top  = spacing;
  ButtonView->Width    = buttonWidth;
  ButtonUse->Width     = buttonWidth;
  ButtonConnect->Width = buttonWidth;
  ButtonView->Height    = buttonHeight;
  ButtonUse->Height     = buttonHeight;
  ButtonConnect->Height = buttonHeight;
  //Repaint the screen at its new size
  PaintBackground();

  TileMachines();

}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::TileMachines()
{
  if (mMachines.empty() == true) return;

  const int nMachines = mMachines.size();
  const int nCols = 1 + static_cast<int>(
    std::sqrt( static_cast<double>(nMachines - 1) ) );
  const int nRows = static_cast<int>(std::sqrt(
    static_cast<double>(nMachines)
    + std::sqrt( static_cast<double>(nMachines) ) ) );
  const int dx = this->GetDrawingSurfaceWidth()  / nCols;
  const int dy = this->GetDrawingSurfaceHeight() / nRows;
  int count = 0;
  const MachineIterator j = mMachines.end();
  for (MachineIterator i = mMachines.begin();
    i!=j;
    ++i)
  {
    const int x = (count % nCols) * dx;
    const int y = (count / nCols) * dy;
    assert( x >= 0);
    assert( y >= 0);
    assert( x <= this->GetDrawingSurfaceWidth());
    assert( y <= this->GetDrawingSurfaceHeight());
    TRect rect;
    rect.Left = x;
    rect.Top  = y;
    rect.Right  = x + dx;
    rect.Bottom = y  + dy;
    PlaceInCenter( (*i).get(), rect);
    ++count;
  }
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::AutoMove()
{
  const int nForms = mMachines.size();
  for (int i=0; i!=nForms; ++i)
  {
    for (int j=0; j!=i; ++j)
    {
      TRect r1;
      r1.Left   = mMachines[i]->Left;
      r1.Top    = mMachines[i]->Top;
      r1.Right  = r1.Left + mMachines[i]->ClientWidth;
      r1.Bottom = r1.Top  + mMachines[i]->ClientHeight;
      TRect r2;
      r2.Left   = mMachines[j]->Left;
      r2.Top    = mMachines[j]->Top;
      r2.Right  = r2.Left + mMachines[j]->ClientWidth;
      r2.Bottom = r2.Top  + mMachines[j]->ClientHeight;
      MoveAway(r1,r2);
      mMachines[i]->Left = r1.Left;
      mMachines[i]->Top  = r1.Top;
      mMachines[j]->Left = r2.Left;
      mMachines[j]->Top  = r2.Top;
    }
  }
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMain::MoveAway(TRect& r1, TRect& r2)
{
  int dx1 = 0;
  int dy1 = 0;
  int dx2 = 0;
  int dy2 = 0;

  //No collision
  if (r1.Left   < 0) ++dx1;
  if (r1.Top    < 0) ++dy1;
  if (r1.Right  > this->GetDrawingSurfaceWidth() ) --dx1;
  if (r1.Bottom > this->GetDrawingSurfaceHeight()) --dy1;
  if (r2.Left   < 0) ++dx2;
  if (r2.Top    < 0) ++dy2;
  if (r2.Right  > this->GetDrawingSurfaceWidth() ) --dx2;
  if (r2.Bottom > this->GetDrawingSurfaceHeight()) --dy2;

  if (!( r1.Right  < r2.Left || r1.Left > r2.Right
    || r1.Bottom < r2.Top  || r1.Top  > r2.Bottom))
  {
    if (InRect(r1.Left ,r1.Top   ,r2)==true) { ++dx1; ++dy1; --dx2; --dy2;}
    if (InRect(r1.Right,r1.Top   ,r2)==true) { --dx1; ++dy1; ++dx2; --dy2;}
    if (InRect(r1.Left ,r1.Bottom,r2)==true) { ++dx1; --dy1; --dx2; ++dy2;}
    if (InRect(r1.Right,r1.Bottom,r2)==true) { --dx1; --dy1; ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx1 == 0 && dy1 == 0)
    {
      ++dx1;
      ++dy1;
      --dx2;
      --dy2;
    }
  }
  r1.Left   += dx1;
  r1.Right  += dx1;
  r1.Top    += dy1;
  r1.Bottom += dy1;
  r2.Left   += dx2;
  r2.Right  += dx2;
  r2.Top    += dy2;
  r2.Bottom += dy2;
}
//---------------------------------------------------------------------------
const bool InRect(const int x, const int y, const TRect& r)
{
  return (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom);
}
//---------------------------------------------------------------------------


