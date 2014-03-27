//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Richèl Bilderbeek

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
#ifndef UnitFormTrackBarH
#define UnitFormTrackBarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
struct TFormImage;
//---------------------------------------------------------------------------
class TFormTrackBar : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *TrackBar;
        void __fastcall TrackBarChange(TObject *Sender);
private:	// User declarations
  const TImage * const mSource;
  TFormImage * const mTarget;
  void(* const mFunction)(const TImage * const, const int, TImage * const);

public:		// User declarations
  __fastcall TFormTrackBar(TComponent* Owner,
    const TImage * const source,
    TFormImage * const target,
    void(*anyFunction)(const TImage * const, const int, TImage * const));

};
//---------------------------------------------------------------------------
extern PACKAGE TFormTrackBar *FormTrackBar;
//---------------------------------------------------------------------------
#endif
