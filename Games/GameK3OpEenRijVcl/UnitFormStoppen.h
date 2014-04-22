//---------------------------------------------------------------------------
/*
    K3-Op-Een-Rij. A simple game.
    Copyright (C) 2007  Richel Bilderbeek

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
#ifndef UnitFormStoppenH
#define UnitFormStoppenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormStoppen : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *ImageHeart;
        TImage *ImageHeartGrey;
        TImage *Image4;
        TImage *Image5;
        void __fastcall OnAgainClick(TObject *Sender);
        void __fastcall OnQuitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormStoppen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStoppen *FormStoppen;
//---------------------------------------------------------------------------
#endif
