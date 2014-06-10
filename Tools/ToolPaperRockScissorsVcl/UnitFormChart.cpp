//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormChart *FormChart;
//---------------------------------------------------------------------------
__fastcall TFormChart::TFormChart(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormChart::Add(const double p, const double r, const double s)
{
  Chart1->Series[0]->Add(p);
  Chart1->Series[1]->Add(r);
  Chart1->Series[2]->Add(s);

}
//---------------------------------------------------------------------------
void TFormChart::Clear()
{
  Chart1->Series[0]->Clear();
  Chart1->Series[1]->Clear();
  Chart1->Series[2]->Clear();
}
//---------------------------------------------------------------------------


