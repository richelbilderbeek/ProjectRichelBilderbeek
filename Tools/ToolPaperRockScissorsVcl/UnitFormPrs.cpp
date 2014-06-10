//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormPrs.h"
#include "UnitFormAbout.h"
#include "UnitFormChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrs *FormPrs;
//---------------------------------------------------------------------------
#include <memory>
#include <cassert>
//---------------------------------------------------------------------------
__fastcall TFormPrs::TFormPrs(TComponent* Owner)
        : TForm(Owner), mFormChart(new TFormChart(0))
{
  EditChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrs::EditChange(TObject *Sender)
{
  const int width  = EditWidth->Text.ToIntDef(-1);
  const int height = EditHeight->Text.ToIntDef(-1);
  if (width < 4) return;
  if (height < 4) return;

  const bool oldEnabled = Timer1->Enabled;
  Timer1->Enabled = false;

  //Resize area
  //mV.resize(width, std::vector<EnumPrs>(height) );
  mV = std::vector<std::vector<EnumPrs> >(width, std::vector<EnumPrs>(height) );

  assert(width == static_cast<int>(mV.size()));
  assert(height == static_cast<int>(mV[0].size()));

  ImageArea->Picture->Bitmap->Width  = width;
  ImageArea->Picture->Bitmap->Height = height;

  assert(ImageArea->Picture->Bitmap->Width == static_cast<int>(mV.size()));
  assert(ImageArea->Picture->Bitmap->Height == static_cast<int>(mV[0].size()));

  DrawInitialArea();
  Timer1->Enabled = oldEnabled;

}
//---------------------------------------------------------------------------
void __fastcall TFormPrs::ButtonResetClick(TObject *Sender)
{
  DrawInitialArea();
}
//---------------------------------------------------------------------------
void __fastcall TFormPrs::ButtonPlayPauseClick(TObject *Sender)
{
  if (ButtonPlayPause->Caption == "Play")
  {
    Timer1->Enabled = true;
    ButtonPlayPause->Caption = "Pause";
  }
  else
  {
    Timer1->Enabled = false;
    ButtonPlayPause->Caption = "Play";
  }
}
//---------------------------------------------------------------------------
void TFormPrs::DrawInitialArea()
{
  mFormChart->Clear();

  assert(ImageArea->Picture->Bitmap->Width == static_cast<int>(mV.size()));
  assert(ImageArea->Picture->Bitmap->Height == static_cast<int>(mV[0].size()));

  const int maxx = mV.size();
  const int maxy = mV[0].size();

  const int thirdWidth = maxx / 3;

  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      mV[x][y] = static_cast<EnumPrs>((x / thirdWidth));
    }
  }
  DrawArea();
}
//---------------------------------------------------------------------------
void TFormPrs::DrawArea()
{
  assert(ImageArea->Picture->Bitmap->Width == static_cast<int>(mV.size()));
  assert(ImageArea->Picture->Bitmap->Height == static_cast<int>(mV[0].size()));

  const int width = ImageArea->Picture->Bitmap->Width;
  const int height = ImageArea->Picture->Bitmap->Height;
  for (int y=0; y!=height; ++y)
  {
    unsigned char * line=static_cast<unsigned char *>(ImageArea->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      switch(mV[x][y])
      {
        case paper:
          line[x*3+0]= 0 ; //Blue
          line[x*3+1]= 0 ; //Green
          line[x*3+2]= 255 ; //Red
          break;
        case rock:
          line[x*3+0]= 0 ; //Blue
          line[x*3+1]= 255 ; //Green
          line[x*3+2]= 0 ; //Red
          break;
        case scissors:
          line[x*3+0]= 255 ; //Blue
          line[x*3+1]= 0 ; //Green
          line[x*3+2]= 0 ; //Red
          break;
      }
    }
  }
  ImageArea->Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TFormPrs::Timer1Timer(TObject *Sender)
{
  //Play PRS
  const int maxx = mV.size();
  const int maxy = mV[0].size();
  const int area = maxx * maxy;

  for (int i=0; i!=area; ++i)
  {
    const int x1 = std::rand() % maxx;
    const int y1 = std::rand() % maxy;

    int x2 = x1;
    int y2 = y1;
    switch (std::rand() % 4)
    {
      case 0: y2 = ((y2 - 1) + maxy) % maxy; break;
      case 1: x2 = ((x2 + 1) + 0   ) % maxx; break;
      case 2: y2 = ((y2 + 1) + 0   ) % maxy; break;
      case 3: x2 = ((x2 - 1) + maxy) % maxx; break;
    }
    const EnumPrs s1 = mV[x1][y1];
    const EnumPrs s2 = mV[x2][y2];
    const int diff = (static_cast<int>(s1) - static_cast<int>(s2) + 3) % 3;
    switch(diff)
    {
      case 0: break;
      case 1: mV[x1][y1] = s2; break;
      case 2: mV[x2][y2] = s1; break;
    }
  }

  CountPopulation();

  DrawArea();
}
//---------------------------------------------------------------------------
void TFormPrs::CountPopulation() const
{
  typedef std::vector<std::vector<EnumPrs> >::const_iterator RowIter;
  typedef std::vector<EnumPrs>::const_iterator ColIter;
  int nR = 0;
  int nG = 0;
  int nB = 0;

  const RowIter endRow = mV.end();
  for (RowIter y = mV.begin(); y!=endRow; ++y)
  {
    const ColIter endCol = (*y).end();
    for (ColIter x = (*y).begin(); x!=endCol; ++x)
    {
      switch (*x)
      {
        case paper   : ++nR; break;
        case rock    : ++nG; break;
        case scissors: ++nB; break;
      }
    }
  }
  const int sum = nR + nG + nB;
  const double sumD = static_cast<double>(sum);
  mFormChart->Add(
    static_cast<double>(nR) / sumD,
    static_cast<double>(nG) / sumD,
    static_cast<double>(nB) / sumD);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrs::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrs::CheckBoxShowClick(TObject *Sender)
{
  if (CheckBoxShow->Checked == true)
  {
    mFormChart->Show();
  }
  else
  {
    mFormChart->Hide();
  }
}
//---------------------------------------------------------------------------

