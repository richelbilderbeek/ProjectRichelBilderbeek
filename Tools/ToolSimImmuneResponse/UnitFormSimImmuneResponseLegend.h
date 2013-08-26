//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
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
#ifndef UnitFormSimImmuneResponseLegendH
#define UnitFormSimImmuneResponseLegendH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitEnums.h"
//---------------------------------------------------------------------------
class TFormSimImmuneResponseLegend : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox1;
        TPanel *PanelVirus;
        TImage *ImageVirus;
        TPanel *PanelCellInfected;
        TImage *ImageCellInfected;
        TPanel *PanelCellHealthy;
        TImage *ImageCellHealthy;
        TPanel *PanelCytotoxicTcell;
        TImage *ImageCytotoxicTcell;
        TPanel *PanelActivatedThelperCell;
        TImage *ImageActivatedThelperCell;
        TPanel *PanelThelperCell;
        TImage *ImageThelperCell;
        TPanel *PanelMacrophageWithVirusParticles;
        TImage *ImageMacrophageWithVirusParticles;
        TPanel *PanelMacrophageWithoutVirusParticles;
        TImage *ImageMacrophageWithoutVirusParticles;
        TPanel *PanelCytokine;
        TImage *ImageCytokine;
        TImage *ImageActivatedBcell;
        TImage *ImageBcell;
        TPanel *PanelActivatedCytotoxicTcell;
        TImage *ImageActivatedCytotoxicTcell;
        TPanel *PanelActivatedBcell;
        TPanel *Panel2;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *PanelBcell;
        TPanel *Panel4;
        TLabel *Label3;
        TLabel *Label4;
        TPanel *Panel1;
        TLabel *Label9;
        TLabel *Label10;
        TPanel *Panel3;
        TLabel *Label5;
        TLabel *Label6;
        TPanel *Panel5;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *Panel6;
        TLabel *Label11;
        TLabel *Label12;
        TPanel *Panel7;
        TLabel *Label13;
        TLabel *Label14;
        TPanel *Panel8;
        TLabel *Label15;
        TLabel *Label16;
        TPanel *Panel9;
        TLabel *Label17;
        TLabel *Label18;
        TPanel *Panel10;
        TLabel *Label19;
        TLabel *Label20;
        TPanel *Panel11;
        TLabel *Label21;
        TLabel *Label22;
        TPanel *Panel12;
        TLabel *Label23;
        TLabel *Label24;
        TPanel *PanelAntibody;
        TImage *ImageAntibody;
        TPanel *Panel14;
        TLabel *Label25;
        TLabel *Label26;
private:	// User declarations
public:		// User declarations
  __fastcall TFormSimImmuneResponseLegend(
    TComponent* Owner);
  const TImage * const ToImage(const EnumCellType t) const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimImmuneResponseLegend *FormSimImmuneResponseLegend;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawLymphocyte.htm
void DrawLymphocyte(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax);

//template <class T>
//const std::vector<T> CreateVector

#endif
