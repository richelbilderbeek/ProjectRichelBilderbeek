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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
struct Question;
struct TFormQuestion;
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel;
        TButton *Quit;
        TPanel *PanelQuestion;
        TTimer *TimerMain;
        TPanel *PanelQuit;
        void __fastcall TimerMainTimer(TObject *Sender);
        void __fastcall QuitClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
  typedef std::vector<boost::shared_ptr<Question> >::const_iterator QuestionIterator;
  boost::shared_ptr<TFormQuestion> m_child;
  std::vector<boost::shared_ptr<Question> > m_questions;
  std::vector<std::string> m_results;
  int m_n_correct;
  int m_n_incorrect;
  bool m_quit;
  QuestionIterator m_current_question;
  void PutQuestionOnScreen();
  void ShowScore();
  void SaveTestResults() const;
  const int m_key;
  const std::string m_username;
  const std::string m_filename;
  protected:
  const bool m_is_test;
public:		// User declarations
  __fastcall TFormMain(
    TComponent* Owner,
    const std::vector<boost::shared_ptr<Question> >& questions,
    const bool is_test,
    const int key,
    const std::string& username,
    const std::string& filename);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
const std::string ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void SaveContainer(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<Container::value_type>(f,"\n"));
}
//---------------------------------------------------------------------------


#endif
