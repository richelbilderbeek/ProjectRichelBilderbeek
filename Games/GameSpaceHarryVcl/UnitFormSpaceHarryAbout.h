//---------------------------------------------------------------------------
/*
  Space Harry, a simple 'Space Harrier' clone
<<<<<<< HEAD
  Copyright (C) 2007  Richèl Bilderbeek
=======
  Copyright (C) 2007  Richel Bilderbeek
>>>>>>> develop

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
#ifndef UnitFormSpaceHarryAboutH
#define UnitFormSpaceHarryAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSpaceHarryAbout : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TPanel *Panel1;
        TPanel *Panel2;
        TRichEdit *RichEdit1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSpaceHarryAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSpaceHarryAbout *FormSpaceHarryAbout;
//---------------------------------------------------------------------------
#endif
