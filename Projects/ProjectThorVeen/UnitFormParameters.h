//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

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
#ifndef UnitFormParametersH
#define UnitFormParametersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
class SimulationParameters;
class BirdGeneralParameters;
class BirdHawkDoveParameters;
class BreedingParameters;
class InitialBirdNumbers;
//---------------------------------------------------------------------------
class TFormParameters : public TForm
{
__published:	// IDE-managed Components
  TRadioGroup *RadioGroupSimulationType;
  TValueListEditor *ValueListGeneral;
  TRadioGroup *RadioGroupFemaleChoice;
  TRadioGroup *RadioGroupMaleCompetition;
  TRadioGroup *RadioGroupNextGenerationSize;
  TPanel *PanelBirdType;
  TValueListEditor *ValueListEditorBirdHawkDove;
  TValueListEditor *ValueListBirdNumbers;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TPageControl *PageControlBirdType;
  TTabSheet *TabSheet3;
  TTabSheet *TabSheet6;
  TTabSheet *TabSheet4;
  TPanel *Panel1;
  TTabSheet *TabSheet5;
  TRadioGroup *RadioGroupPedigree;
        TRadioGroup *RadioGroupMigration;
        TPanel *Panel2;
        TPanel *Panel3;
  TPanel *PanelRearingCaption;
        TPageControl *PageControlRearing;
        TTabSheet *TabSheet7;
        TTabSheet *TabSheet8;
        TValueListEditor *ValueListRearingRandom;
        TValueListEditor *ValueListBirdGeneral;
        TPanel *Panel5;
        TRadioGroup *RadioGroupMatingSystem;
  TTabSheet *TabSheet9;
  TValueListEditor *ValueListBreeding;
  TPanel *PanelRearingLeft;
private:	// User declarations
public:		// User declarations
  __fastcall TFormParameters(TComponent* Owner);
  boost::shared_ptr<SimulationParameters> getSimulationParameters() const;
  boost::shared_ptr<BirdHawkDoveParameters> getHawkDoveParameters() const;
  boost::shared_ptr<BirdGeneralParameters> getBirdGeneralParameters() const;
  boost::shared_ptr<InitialBirdNumbers> getInitialBirdNumbers() const;
  boost::shared_ptr<BreedingParameters> getBreedingParameters() const;

};
//---------------------------------------------------------------------------
extern PACKAGE TFormParameters *FormParameters;
//---------------------------------------------------------------------------
#endif
