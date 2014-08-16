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
#ifndef UnitFormMenuH
#define UnitFormMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
struct Question;
//---------------------------------------------------------------------------
class TFormMenu : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog;
        TImage *ImageLoadExercise;
        TImage *ImageStartExercise;
        TImage *ImageTitle;
        TImage *ImageLoadTest;
        TImage *ImageStartTest;
        TPanel *PanelBottom;
        TImage *ImageAbout;
        TImage *ImageQuit;
        TPanel *PanelTest;
        TPanel *PanelExercise;
        TSaveDialog *SaveDialog1;
        void __fastcall ImageLoadExerciseClick(TObject *Sender);
        void __fastcall ImageStartExerciseClick(TObject *Sender);
        void __fastcall ImageQuitClick(TObject *Sender);
        void __fastcall ImageAboutClick(TObject *Sender);
        void __fastcall ImageStartTestClick(TObject *Sender);
        void __fastcall ImageLoadTestClick(TObject *Sender);
private:	// User declarations
    std::vector<boost::shared_ptr<Question> > m_questions;
    const String signature;
    int m_key;
public:		// User declarations
        __fastcall TFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenu *FormMenu;
//---------------------------------------------------------------------------
//From //From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> SeperateString(
  const std::string& input,
  const std::string& seperator);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPath.htm
const std::string GetPath(const std::string& fileName);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
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




#endif
