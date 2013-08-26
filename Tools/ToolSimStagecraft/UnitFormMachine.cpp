//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include "UnitMachine.h"
#include "UnitConnectorControl.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMachine *FormMachine;
//---------------------------------------------------------------------------
__fastcall TFormMachine::TFormMachine(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TForm(Owner),
    mFormParent(formParent),
    mDisplayMode(modeView)
{
  assert(Owner == 0 && "Deletion of TFormMachine is done by boost::shared_ptr");
  assert(mFormParent != 0 && "TFormMachine must know its parent form");
}
//---------------------------------------------------------------------------
void __fastcall TFormMachine::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;
  OnAfterResize();
}
//---------------------------------------------------------------------------
void TFormMachine::OnControllerClick()
{
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
void TFormMachine::OnConnectorClick(ConnectorControl * const connectorControl)
{
  mFormParent->OnConnectorClick(connectorControl);
}
//---------------------------------------------------------------------------
void TFormMachine::DrawOnBuffer(const TImage * const image)
{
  ImageBuffer->Canvas->Draw(image->Left, image->Top, image->Picture->Graphic);
}
//---------------------------------------------------------------------------
void TFormMachine::DrawOnBuffer(const std::vector<TImage * const>& images)
{
  typedef std::vector<TImage * const>::const_iterator Iterator;
  const Iterator j = images.end();
  for (Iterator i = images.begin(); i!=j; ++i)
  {
    ImageBuffer->Canvas->Draw((*i)->Left, (*i)->Top, (*i)->Picture->Graphic);
  }
}
//---------------------------------------------------------------------------
void TFormMachine::DrawOnBuffer(const std::vector<TImage *>& images)
{
  typedef std::vector<TImage * >::const_iterator Iterator;
  const Iterator j = images.end();
  for (Iterator i = images.begin(); i!=j; ++i)
  {
    ImageBuffer->Canvas->Draw((*i)->Left, (*i)->Top, (*i)->Picture->Graphic);
  }
}
//---------------------------------------------------------------------------
void TFormMachine::DrawBorderAroundBuffer()
{
  ImageBuffer->Canvas->Pen->Width = mBorderSize;
  ImageBuffer->Canvas->Pen->Color = clBlack;
  ImageBuffer->Canvas->MoveTo(0,0);
  ImageBuffer->Canvas->LineTo(0,ClientHeight);
  ImageBuffer->Canvas->LineTo(ClientWidth,ClientHeight);
  ImageBuffer->Canvas->LineTo(ClientWidth,0);
  ImageBuffer->Canvas->LineTo(0,0);
}
//---------------------------------------------------------------------------

