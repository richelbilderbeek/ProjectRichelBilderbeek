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
#include <boost/shared_ptr.hpp>
#include <jpeg.hpp>

#include "UnitFormMultipleChoiceQuestion.h"
#include "UnitFormImage.h"
#include "UnitFormCorrect.h"
#include "UnitFormIncorrect.h"
#include "UnitDotMatrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormQuestion"
#pragma resource "*.dfm"
TFormMultipleChoiceQuestion *FormMultipleChoiceQuestion;
//---------------------------------------------------------------------------
__fastcall TFormMultipleChoiceQuestion::TFormMultipleChoiceQuestion(
  TComponent* Owner,
  const boost::shared_ptr<Question>& question,
  const bool is_test)
  : TFormQuestion(Owner,question,is_test),
    m_mcquestion(dynamic_cast<MultipleChoiceQuestion*>(question.get()))
{
  assert(m_mcquestion && "Cast to MultipleChoiceQuestion has failed");
  assert(m_mcquestion->m_answers.size() == 1
    && "A multiple choice question only has one correct answer");

  if (FileExists(m_mcquestion->m_filename.c_str()))
  {
    try
    {
      Image->Picture->LoadFromFile(m_mcquestion->m_filename.c_str());
    }
    catch (...)
    {
      //Just continue...
    }
  }
  else
  {
    //Write a message
    std::vector<std::string> v;
    v.push_back(" "); //First empty line
    const int font_width  = 6;
    const int font_height = 8;
    //Valid filename?
    //Does it contain a dot?
    if (std::find(
         m_mcquestion->m_filename.begin(),
         m_mcquestion->m_filename.end(),
         '.')
      != m_mcquestion->m_filename.end())
    {
      v.push_back(" File not found: ");
      const std::string filename = " " + m_mcquestion->m_filename + " ";
      v.push_back(filename);
    }
    else
    {
      v.push_back(" (No image) ");
    }
    v.push_back(" "); //Last empty line
    const int width  = GetMaxStringLength(v) * font_width;
    const int height = v.size() * font_height;
    Image->Picture->Graphic->Width  = width;
    Image->Picture->Graphic->Height = height;
    DotMatrix(Image,0,0,v);
  }


  RichEdit->Text = m_mcquestion->m_question.c_str();

  {
    std::vector<std::string> answers(m_mcquestion->mWrongAnswers);
    answers.push_back(m_mcquestion->m_answers[0]);
    random_shuffle(answers.begin(), answers.end() );
    const int n_answers = answers.size();

    RadioGroup->Items->Clear();
    for (int i=0; i!=n_answers; ++i)
    {
      RadioGroup->Items->Add(answers[i].c_str());
    }
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMultipleChoiceQuestion::ImageClick(TObject *Sender)
{
  //Show image full screen
  boost::shared_ptr<TFormImage> f(new TFormImage(0,Image));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMultipleChoiceQuestion::RadioGroupClick(TObject *Sender)
{
  assert(RadioGroup->ItemIndex != -1);
  if (RadioGroup->Items->operator [](RadioGroup->ItemIndex)
    == m_mcquestion->m_answers[0].c_str())
  {
    //Correct
    if (!m_is_test)
    {
      //Reward user when not test
      boost::shared_ptr<TFormCorrect> f(new TFormCorrect(0));
      f->ShowModal();
    }
    m_state = correct;
    Close();
  }
  else
  {
    //Incorrect
    if (!m_is_test)
    {
      //Show correct answer when not test
      boost::shared_ptr<TFormIncorrect> f(
        new TFormIncorrect(0,m_mcquestion->m_answers[0]));
      f->ShowModal();
    }
    m_state = incorrect;
    Close();
  }

}
//---------------------------------------------------------------------------
const int GetMaxStringLength(const std::vector<std::string>& v)
{
  typedef std::vector<std::string>::const_iterator Iter;
  Iter i = v.begin();
  const Iter j = v.end();
  int max = (*i).size();
  ++i;
  for ( ; i!=j; ++i)
  {
    const int sz = (*i).size();
    if  (sz > max) max = sz;
  }
  return max;
}
//---------------------------------------------------------------------------

