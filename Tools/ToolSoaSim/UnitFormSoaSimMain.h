//---------------------------------------------------------------------------
/*
  SoaSim, a simulator of sexually transmitted diseases
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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormSoaSimMainH
#define UnitFormSoaSimMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
struct Person;
#include "UnitInteraction.h"
//struct Interaction;
//---------------------------------------------------------------------------
class TFormSoaSimMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageSafeSex;
        TImage *ImageUnsafeSex;
        TImage *ImageProposeSafe;
        TImage *ImageProposeUnsafe;
        TImage *ImageNo;
        TImage *ImageYes;
        TImage *ImageBuffer;
        TImage *ImagePersonRed;
        TImage *ImagePersonGreen;
        TImage *ImagePersonBlue;
        TImage *ImageShadow;
        TImage *ImageBackground;
        TImage *ImageBlaRight;
        TImage *ImageBlaLeft;
        TTimer *TimerMove;
        TTimer *TimerInteraction;
        TImage *ImagePersonCustom;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall TimerMoveTimer(TObject *Sender);
        void __fastcall TimerInteractionTimer(TObject *Sender);
private:	// User declarations
  std::list<boost::shared_ptr<Person > > mPersons;
  std::list< Interaction > mInteractions;
  void DrawScreen();
public:		// User declarations
  __fastcall TFormSoaSimMain(TComponent* Owner);
  double GetPercentageInfected() const;
  void ClearPersons();
  void AddBadBoy(const bool isInfected);
  void AddPartyAnimal(const bool isInfected);
  void AddWiseGuy(const bool isInfected);
  void AddCustomPerson(
    const double pProposeSafe,
    const double pAgreeSafe,
    const double pAgreeUnsafe,
    const bool isInfected);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormSoaSimMain *FormSoaSimMain;
//---------------------------------------------------------------------------
void DrawGlobe(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax);
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
const double GetRandomUniform();
const double GetDistance(const double dX, const double dY);

#endif
