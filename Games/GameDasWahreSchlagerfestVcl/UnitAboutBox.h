//---------------------------------------------------------------------------
/*
 *  Das Wahre Schlagerfest. A simple game.
 *  Copyright (C) 2003  Richel Bilderbeek
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
#ifndef UnitAboutBoxH
#define UnitAboutBoxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormAboutBox : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TRichEdit *RichEdit1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormAboutBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAboutBox *FormAboutBox;
//---------------------------------------------------------------------------
#endif
