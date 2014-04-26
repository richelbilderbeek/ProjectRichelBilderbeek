//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <boost/scoped_ptr.hpp>
#include "UnitFormTronCollectionMenu.h"
#include "UnitFormSuperTronMenu.h"
#include "UnitFormClassicTronMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTronCollectionMenu *FormTronCollectionMenu;
//---------------------------------------------------------------------------
__fastcall TFormTronCollectionMenu::TFormTronCollectionMenu(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormTronCollectionMenu::ImageClassicTronMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  boost::scoped_ptr<TFormClassicTronMenu> f(new TFormClassicTronMenu(0));
  f->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TFormTronCollectionMenu::ImageSuperTronMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  boost::scoped_ptr<TFormSuperTronMenu> f(new TFormSuperTronMenu(0));
  f->ShowModal();

}
//---------------------------------------------------------------------------
void __fastcall TFormTronCollectionMenu::ImageUltimateTronMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  //boost::scoped_ptr<TFormUltimateTronMenu> f(new TFormUltimateTronMenu(0));
  //f->ShowModal();
}
//---------------------------------------------------------------------------

