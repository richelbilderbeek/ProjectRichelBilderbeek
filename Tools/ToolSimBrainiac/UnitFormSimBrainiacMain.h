/*
  SimBrainiac, a simulation of Brainiacs interacting
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
#ifndef UnitFormSimBrainiacMainH
#define UnitFormSimBrainiacMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include "UnitBrainiac.h"
#include "UnitSimBrainiac.h"
class TFormSimBrainiacGraph;
//---------------------------------------------------------------------------
class TFormSimBrainiacMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImageBrainiac;
        TTimer *TimerMain;
        void __fastcall TimerMainTimer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  SimBrainiac mSim;
  bool mUseGrey;
  bool mDrawBrainiacs;
  void DrawBrainiac(const Brainiac& b) const;
  std::auto_ptr<TFormSimBrainiacGraph> mFormGraph;
  int mNcols, mNrows;

public:		// User declarations
  __fastcall TFormSimBrainiacMain(TComponent* Owner,
    const int nBrainiacs,
    const int nCorrectAnswerLevels,
    const int nHasQuestionLevels);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimBrainiacMain *FormSimBrainiacMain;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
void DrawGlobe(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax);
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//Set a line of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//Set a square of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
void Rainbow(
  const double x,
  unsigned char& r,
  unsigned char& g,
  unsigned char& b);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetRed(const double x);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetGreen(const double x);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetBlue(const double x);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
//---------------------------------------------------------------------------

#endif
