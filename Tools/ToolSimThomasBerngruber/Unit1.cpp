//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <vector>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;



//---------------------------------------------------------------------------
// CONSTRUCTOR OF FORM
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////
//   MAIN FUNCTION ////////////////////////////////////
///////////////////////////////////////////////////////
void __fastcall TForm1::Button1Click(TObject *Sender)
{
// Read in Parameters

birthrate = ValueListEditor1->Cells[1][1].ToDouble();
deathrate =ValueListEditor1->Cells[1][2].ToDouble();
cost_of_res =ValueListEditor1->Cells[1][3].ToDouble();
extra_death_kil =ValueListEditor1->Cells[1][4].ToDouble();
mut =ValueListEditor1->Cells[1][5].ToDouble();
initsus =ValueListEditor1->Cells[1][6].ToDouble();
initres =ValueListEditor1->Cells[1][7].ToDouble();
initkill =ValueListEditor1->Cells[1][8].ToDouble();
maxx=ValueListEditor1->Cells[1][9].ToInt();
maxy=ValueListEditor1->Cells[1][10].ToInt();
duration=ValueListEditor1->Cells[1][11].ToInt();
diffusion=ValueListEditor1->Cells[1][12].ToInt();

EmptyChart(Chart1);
Init_grid(); //Initialize grid
CountValues();
DisplayValues(Chart1);
ShowArea(ImageGrid);

for (int time=0; time<duration; time++)
  {
  GridUpdate();
  CountValues();
  DisplayValues(Chart1);
  ShowArea(ImageGrid);
  this->Canvas->Draw(0,0,ImageGrid->Picture->Graphic);
  }//Next time
}
//--------------------------------------------------------------------------



