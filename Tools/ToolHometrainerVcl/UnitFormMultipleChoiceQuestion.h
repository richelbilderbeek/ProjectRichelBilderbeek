//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
  Copyright (C) 2009  Richel Bilderbeek

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
#ifndef UnitFormMultipleChoiceQuestionH
#define UnitFormMultipleChoiceQuestionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "UnitFormQuestion.h"
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include "UnitMultipleChoiceQuestion.h"
#include "UnitFormQuestion.h"
//---------------------------------------------------------------------------
class TFormMultipleChoiceQuestion : public TFormQuestion
{
__published:	// IDE-managed Components
        TImage *Image;
        TRadioGroup *RadioGroup;
        TRichEdit *RichEdit;
        void __fastcall ImageClick(TObject *Sender);
        void __fastcall RadioGroupClick(TObject *Sender);

private:	// User declarations
  const MultipleChoiceQuestion * m_mcquestion;
public:		// User declarations
  __fastcall TFormMultipleChoiceQuestion(
    TComponent* Owner,
    const boost::shared_ptr<Question>& question,
    const bool is_test);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMultipleChoiceQuestion *FormMultipleChoiceQuestion;
//---------------------------------------------------------------------------
const int GetMaxStringLength(const std::vector<std::string>& v);
//---------------------------------------------------------------------------

#endif
