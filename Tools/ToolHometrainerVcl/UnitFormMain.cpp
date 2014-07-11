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
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "UnitEncranger.h"
#include "UnitFormMain.h"
#include "UnitFormMultipleChoiceQuestion.h"
#include "UnitFormOpenQuestion.h"
#include "UnitFormQuestion.h"
#include "UnitMultipleChoiceQuestion.h"
#include "UnitOpenQuestion.h"
#include "UnitQuestion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(
  TComponent* Owner,
  const std::vector<boost::shared_ptr<Question> >& questions,
  const bool is_test,
  const int key,
  const std::string& username,
  const std::string& filename)
 : TForm(Owner),
   m_questions(questions),
   m_n_correct(0),
   m_n_incorrect(0),
   m_quit(false),
   m_is_test(is_test),
   m_key(key),
   m_username(username),
   m_filename(filename)
{

  m_results.push_back("NAME," + m_username);

  //Reset question order
  RandomizeTimer();
  std::random_shuffle(m_questions.begin(), m_questions.end() );
  m_current_question = m_questions.begin();

  ShowScore();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TimerMainTimer(TObject *Sender)
{
  //Main loop

  //Disable multiple entries in loop
  TimerMain->Enabled = false;

  //Put the first question on screen
  PutQuestionOnScreen();

  while (m_quit == false) //Allow quitting
  {
    //Prevent freezing
    Application->ProcessMessages();

    //Check if answer is already given
    if (m_child->Get_state() != TFormQuestion::unanswered)
    {
      //Keep track of the score
      if (m_child->Get_state() == TFormQuestion::correct)
      {
        ++m_n_correct;
        if (m_is_test)
        {
          const std::string s
            = ReplaceAll(m_child->Get_question_string(),",","{comma}")
            + ",Y";
          assert(std::count(s.begin(),s.end(),',')==1);
          m_results.push_back(s);

          //Save
          SaveTestResults();
        }
      }
      else
      {
        ++m_n_incorrect;
        if (m_is_test)
        {
          const std::string s
            = ReplaceAll(m_child->Get_question_string(),",","{comma}")
            + ",N";
          assert(std::count(s.begin(),s.end(),',')==1);
          m_results.push_back(s);

          //Save
          SaveTestResults();
        }
      }

      //Put score on screen
      ShowScore();

      ++m_current_question;

      if (m_current_question == m_questions.end())
      {
        if (m_is_test)
        {
          SaveTestResults();
          ShowMessage("Test done. File is saved.");
          m_quit = true;
        }
        else
        {
          //Reset question order
          std::random_shuffle(m_questions.begin(), m_questions.end() );
          m_current_question = m_questions.begin();
        }
      }

      if (!m_quit)
      {
        //Put new question on screen
        PutQuestionOnScreen();
      }
    }
  }

  //Quit
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::QuitClick(TObject *Sender)
{
  m_quit = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormResize(TObject *Sender)
{
  if (m_child)
  {
    m_child->Left   = PanelQuestion->Left;
    m_child->Top    = PanelQuestion->Top;
    m_child->Width  = PanelQuestion->Width;
    m_child->Height = PanelQuestion->Height;
  }
}
//---------------------------------------------------------------------------
void TFormMain::PutQuestionOnScreen()
{
  Question * q = (*m_current_question).get();

  if (dynamic_cast<OpenQuestion*>(q))
  {
    //Open Question
    m_child = boost::shared_ptr<TFormQuestion>(new TFormOpenQuestion(
      this,*m_current_question,m_is_test));
    //Failed try to set the Edit's focus,
    //TFormOpenQuestion * f = dynamic_cast<TFormOpenQuestion*>(m_child.get());
    //assert(f);
    //f->Edit->SetFocus();
  }
  else
  {
    //Multiple choice question
    m_child = boost::shared_ptr<TFormQuestion>(new TFormMultipleChoiceQuestion(
      this,*m_current_question,m_is_test));
  }

  //m_child = boost::shared_ptr<TFormQuestion>(new TFormQuestion(
  //  this,m_current_question);
  m_child->Parent = PanelQuestion;
  m_child->Left   = PanelQuestion->Left;
  m_child->Top    = PanelQuestion->Top;
  m_child->Width  = PanelQuestion->Width;
  m_child->Height = PanelQuestion->Height;
}
//---------------------------------------------------------------------------
void TFormMain::ShowScore()
{
  if (m_is_test)
  {
    const int n_questions = static_cast<int>(m_questions.size());
    const int n_answered = m_n_correct + m_n_incorrect;
    Panel->Caption
    = "Answered " + IntToStr(n_answered)
    + " of " + IntToStr(n_questions)
    + " questions.";
  }
  else if (m_n_correct + m_n_incorrect != 0)
  {
    Panel->Caption
    = "Correct: " + IntToStr(m_n_correct)
    + ", incorrect: " + IntToStr(m_n_incorrect)
    + ", Score: "
    + FloatToStr(100.0
       * static_cast<double>(m_n_correct)
       / static_cast<double>(m_n_correct + m_n_incorrect))
    + "%";
  }
  else
  {
    Panel->Caption
    = "Correct: " + IntToStr(0)
    + ", incorrect: " + IntToStr(0)
    + ", Score: "
    + FloatToStr(100.0
       * static_cast<double>(0)
       / static_cast<double>(1))
    + "%";
  }
}
//---------------------------------------------------------------------------
void TFormMain::SaveTestResults() const
{
  std::vector<std::string> v(m_results);
  
  const int sz = static_cast<int>(v.size());

  //Obscure all v by 7 asterisks
  for (int i=0; i!=sz; ++i)
  {
    const int n_ast = std::rand() % 7;
    v[i]
      = std::string(1 + n_ast,'*')
      + v[i]
      + std::string(8 - n_ast,'*');
  }

  //Shuffle the obscured std::strings at random
  RandomizeTimer();
  std::random_shuffle(v.begin(),v.end());

  //Encode strings
  const Encranger e(m_key);
  for (int i=0; i!=sz; ++i)
  {
    v[i] = e.Encrypt(v[i]);
  }

  //Always ignore if the use has changed his/her filename
  SaveContainer(v,m_filename);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPath.htm
//Returns the path, without a trailing backslash '\'
const std::string GetPath(const std::string& fileName)
{
  const int endOfPathIndex = fileName.rfind("\\",fileName.size());
  assert(endOfPathIndex < static_cast<int>(fileName.size()));
  return fileName.substr(0,endOfPathIndex);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
const std::string ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  while(1)
  {
    const int pos = s.find(replaceWhat);
    if (pos==-1) break;
    s.replace(pos,replaceWhat.size(),replaceWithWhat);
  }
  return s;
}
//---------------------------------------------------------------------------







