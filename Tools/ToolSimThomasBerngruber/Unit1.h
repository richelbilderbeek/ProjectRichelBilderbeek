//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
//---------------------------------------------------------------------------
#include "UnitRandom.h"
//#include <richel001.h>
enum STATE {EMPTY, SUS, RES, KILL};    // Some global definitions
STATE area[400][400];
int NEmpty=0;
int NSus=0;
int NRes=0;
int NKill=0;
double deathrate=0.0;
double birthrate=0.0;
double cost_of_res=0.0;
double extra_death_kil=0.0;
double mut=0.0;
int duration=0;
int maxx=0;
int maxy=0;
double initsus=0.0;
double initres=0.0;
double initkill=0.0;
int diffusion=0;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TButton *Button1;
  TChart *Chart1;
  TLineSeries *Series1;
  TLineSeries *Series2;
  TLineSeries *Series3;
  TLineSeries *Series4;
  TValueListEditor *ValueListEditor1;
        TImage *ImageGrid;
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

 //////////////////////
/// Mobius Function///
//////////////////////
template <class T>
void Mobius(T &number,T min, T max)
  {
  if (number>max) {number-=(max+min);}
  if (number<min) {number+=(max-min);}
  }//End of: void Mobius

////////////////////////////////////////////////////////////
// Choose from a 4 neighborhood at max distance diffusion///
////////////////////////////////////////////////////////////

void FindNeighbour(int x1, int y1, int &x2, int& y2, int diffusion)
  {
   x2=x1+(random(2*diffusion+1)-diffusion);
   y2=y1+(random(2*diffusion+1)-diffusion);
   while (x2==x1 && y2==y1)
     {
      x2=x1+(random(2*diffusion+1)-diffusion);
      y2=y1+(random(2*diffusion+1)-diffusion);
     }
  /*switch(random(4))
    {
    case 0 : y2=y1-diffusion; x2=x1; break;
    case 1 : x2=x1-diffusion; y2=y1; break;
    case 2 : y2=y1+diffusion; x2=x1; break;
    case 3 : x2=x1-diffusion; y2=y1; break;
    }//End of: switch (random(4))*/
  }

/////////////////////////////////////
/// Map states to colors ////////////
/////////////////////////////////////

TColor StateToColor(STATE number)
  {
  TColor solution=clWhite;
  if (number==EMPTY) solution=clBlack;
  if (number==SUS) solution=clYellow;
  if (number==RES) solution=clLime;
  if (number==KILL) solution=clRed;
  return (solution);
  }

void ExtractRGB(const int& colorvalue, int &R, int &G, int &B)
   {
   R=GetRValue(colorvalue);
   G=GetGValue(colorvalue);
   B=GetBValue(colorvalue);
   }//End of:

void ExtractRGB(const TColor& colorvalue, int &R, int &G, int &B)
   {
   R=GetRValue(colorvalue);
   G=GetGValue(colorvalue);
   B=GetBValue(colorvalue);
   }//End of:

////////////////////////////////////////////////////////////
// EMPTY THE CHART
////////////////////////////////////////////////////////////
void EmptyChart(TChart * Chart1)
  {
  Chart1->Series[0]->Clear();
  Chart1->Series[1]->Clear();
  Chart1->Series[2]->Clear();
  Chart1->Series[3]->Clear();
  }

////////////////////////////////////////////////////////////
// INITIALIZE THE GRID
////////////////////////////////////////////////////////////
void Init_grid(void)
  {
  for (int x=0; x<maxx; x++)
    {
    for (int y=0; y<maxy; y++)
      {
      //ShowMessage(initsus);
      double ran1=rnd::uniform();
      if (ran1 < initsus) {area[x][y]=SUS;  continue; }
      if (ran1 > initsus &&  ran1 < initsus+initres) {area[x][y]=RES; continue;}
      if (ran1 > initsus+initres  && ran1 < initsus+initres+initkill) {area[x][y]=KILL; continue;}
      area[x][y]=EMPTY;
      }// next y
    }// next x
  }//End of: Init_grid


////////////////////////////////////////////////////////////
// UPDATE THE GRID
////////////////////////////////////////////////////////////
void GridUpdate(void)
  {
  int x1,y1,x2,y2;
  for (y1=0; y1<maxy; y1++)
    {
    for (x1=0; x1<maxx; x1++)
      {
      FindNeighbour(x1,y1,x2,y2,diffusion);
      Mobius(x2,0,maxx-1);
      Mobius(y2,0,maxy-1);
      //Update rule
      STATE Here=area[x1][y1];
      STATE Neighbour=area[x2][y2];
      double ran1=rnd::uniform();
      double ran2=rnd::uniform();
      switch (Here)
        {
        case EMPTY : if ((ran1 < birthrate) && (Neighbour==SUS))
                       {
                        area[x1][y1]=SUS; //Birth: If res/sus are neighbor
                       }

                     else if ((ran2 < birthrate-cost_of_res) && (Neighbour==RES))
                       {
                        area[x1][y1]=RES;
                       }
                     break;

        case SUS   : if (ran2 < deathrate  || Neighbour==KILL)
                       {
                        area[x1][y1]=EMPTY; //Mortality of Sus
                       }
                     break;

        case RES   : if (ran2 < deathrate)
                       {
                       area[x1][y1]=EMPTY; // Mortality of Res
                       }
                     else if (ran1 < mut) //Mutation: Res becomes Kil
                       {
                       area[x1][y1]=KILL;
                       }
                     break;

        case KILL  : if (ran1 < deathrate + extra_death_kil)
                       {
                       area[x1][y1]=EMPTY; //Mortality of Kil
                       }
                     break;
        }//End of: switch(Here)
      }//Next x
    }//Next y
  }//End of: void Update(void)

////////////////////////////////////////////////////////////
// EXAMINE THE GRID
////////////////////////////////////////////////////////////
void CountValues(void)
  {
  //Reset values
  NEmpty=0; NSus=0; NRes=0; NKill=0;
  //Count total grid
  for (int y=0; y<maxy; y++)
    {
    for (int x=0; x<maxx; x++)
      {
      if (area[x][y]==EMPTY) NEmpty++;
      if (area[x][y]==SUS) NSus++;
      if (area[x][y]==RES) NRes++;
      if (area[x][y]==KILL) NKill++;
      }//Next x
    }//Next y
  }//End of: void CountValues(void)

////////////////////////////////////////////////////////////
// DISPLAY THE VALUES IN THE CHART
////////////////////////////////////////////////////////////
void DisplayValues(TChart * Chart1)
  {
  /// Graphical Output timeseries
  Chart1->Series[0]->Add(NEmpty);
  Chart1->Series[1]->Add(NSus);
  Chart1->Series[2]->Add(NRes);
  Chart1->Series[3]->Add(NKill);
  Chart1->Refresh();
  }

///////////////////////////////////////////////////////
//   SHOW AREA
///////////////////////////////////////////////////////
void ShowArea(TPaintBox * PaintBox1)
  {
  int x,y;
  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      PaintBox1->Canvas->Pixels[x][y]=StateToColor(area[x][y]);
      }//Next x
    }//Next y
  }//End of: void ShowArea(..)

///////////////////////////////////////////////////////
//   SHOW AREA
///////////////////////////////////////////////////////
void ShowArea(TImage * pImage)
{
  int red, green, blue;
  unsigned char * pLine;
  for (int y=0; y<pImage->Height; ++y)
  {
    pLine=(unsigned char *) pImage->Picture->Bitmap->ScanLine[y];
    for (int x=0; x<pImage->Width; ++x)
    {
      ExtractRGB(StateToColor(area[x][y]),red,green,blue);
      pLine[x*3]  = blue;
      pLine[x*3+1]= green;
      pLine[x*3+2]= red;
    }
  }

}



