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
#ifndef UnitFormScoreTestsH
#define UnitFormScoreTestsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <string>
//---------------------------------------------------------------------------
class TFormScoreTests : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TButton *ButtonLoad;
        TLabel *LabelKey;
        TEdit *EditKey;
        TButton *ButtonSave;
        TButton *ButtonAbout;
        TOpenDialog *OpenDialog1;
        TEdit *EditPenalty;
        TLabel *LabelPenalty;
        TButton *ButtonScore;
        TSaveDialog *SaveDialog1;
        TPageControl *PageControl1;
        TTabSheet *TabSheetStudents;
        TTabSheet *TabSheetQuestions;
        TStringGrid *StringGridStudents;
        TStringGrid *StringGridQuestions;
        TLabel *LabelNquestions;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ButtonScoreClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
private:	// User declarations
  void ReadFile(const String& filename);
  void ScoreQuestion(const std::string& s, const bool is_correct);
  void CalculateQuestionScores();
public:		// User declarations
        __fastcall TFormScoreTests(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormScoreTests *FormScoreTests;
//---------------------------------------------------------------------------
const std::string FindUserName(const std::vector<std::string>& v);
//---------------------------------------------------------------------------
const int CountQuestions(const std::vector<std::string>& v);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName);
//---------------------------------------------------------------------------
//From //From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> SeperateString(
  const std::string& input,
  const std::string& seperator);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppReplaceString.htm
const std::string ReplaceOnce(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppReplaceString.htm
const std::string ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat);
//---------------------------------------------------------------------------
const std::vector<std::string> ReplaceAll(
  std::vector<std::string> v,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRemovePath.htm
const std::string RemovePath(const std::string& fileName);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRemoveExtension.htm
const std::string RemoveExtension(const std::string& fileName);
//---------------------------------------------------------------------------




#endif
