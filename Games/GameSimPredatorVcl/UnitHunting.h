//---------------------------------------------------------------------------
/*
 *  SimPredator. A simple game to demonstrate selection and mutation
 *  Copyright (C) 2006  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// The program was developed from 19-05-2006 to 18-07-2006
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitHuntingH
#define UnitHuntingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
struct Prey
{
  int mX, mY, mIndex;
};
//---------------------------------------------------------------------------
class TFormHunting : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImageBackground;
        TPanel *Panel1;
        TTimer *TimerStart;
        TTimer *TimerGameDraw;
        TTimer *TimerReproduce;
        TImage *ImagePrey;
        TTimer *TimerGameTime;
        void __fastcall TimerStartTimer(TObject *Sender);
        void __fastcall TimerGameDrawTimer(TObject *Sender);
        void __fastcall TimerGameTimeTimer(TObject *Sender);
        void __fastcall TimerReproduceTimer(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  std::vector<Prey> mPrey;
  void drawScreen();
  void scorePrey();
  int mRound;
  int mClientWidth;
  int mClientHeight;
public:		// User declarations
  __fastcall TFormHunting(
    TComponent* Owner,
    const int& backgroundColor,
    const double& mutationRate);
  const int mHuntingTime;
  const int mPreyMax;
  const double mMutationRate;


};
//---------------------------------------------------------------------------
extern PACKAGE TFormHunting *FormHunting;
//---------------------------------------------------------------------------
void fillImage(TImage * image, const int& color);
double uniform();

#endif
