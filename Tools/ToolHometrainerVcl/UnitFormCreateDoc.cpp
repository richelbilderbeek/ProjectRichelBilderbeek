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
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "UnitEncranger.h"
#include "UnitFormCreateDoc.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCreateDoc *FormCreateDoc;
//---------------------------------------------------------------------------
__fastcall TFormCreateDoc::TFormCreateDoc(TComponent* Owner)
 : TForm(Owner)
{
  RandomizeTimer();
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::ButtonCreateDocClick(TObject *Sender)
{
  assert(m_plaintext.size() > 1);

  //Start at index one, because index zero is the copyright line
  std::random_shuffle(&m_plaintext[1],m_plaintext.end());

  if (CheckBoxUseCode->Checked)
  {
    m_doctext = CreateDoc(
      m_plaintext,
      EditNquestions->Text.ToInt(),
      StrToUpper(EditCode->Text.c_str()));
  }
  else
  {
    m_doctext = CreateDoc(m_plaintext,EditNquestions->Text.ToInt());
  }

  VectorToStringList(m_doctext,RichEdit2->Lines);

  ++PageControl1->ActivePageIndex;
}
//---------------------------------------------------------------------------
//Assumes v is shuffled and v[0] is the copyright line
const std::vector<std::string> CreateDoc(
  const std::vector<std::string> text_in,
  const int n_questions_desired)
{
  std::vector<std::string> text_out;

  text_out.push_back("<head>");
  text_out.push_back("<title>Hometrainer 2 test</title>");
  text_out.push_back("</head>");
  text_out.push_back("<html>");
  text_out.push_back("<body>");
  text_out.push_back("<font size=\"4\" face=\"Courier New\" >");

  //Parsing the questions
  const int sz
    = std::min(static_cast<int>(text_in.size()),
        n_questions_desired + 1);

  for (int i=1; i!=sz; ++i) //1, because first line is signature
  {
    //Obtain the string to split
    const std::string str_to_split_original = text_in[i];
    if (str_to_split_original.empty() == true) continue;

    //Replace \, by {comma}
    const std::string str_to_split = ReplaceAll(str_to_split_original,"\\,","{comma}");

    //Write string to split to debug
    const std::string debug_output = "MyDebug:" + str_to_split;
    OutputDebugString(debug_output.c_str());
    const std::vector<std::string> v_original = SeperateString(str_to_split,",");

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> v = ReplaceAll(v_original,"{comma}",",");

    if (v.empty()==true) continue;

    const std::string filename = v[0];
    //const std::string filename = m_path + '\\' + v[0];

    const std::string& question = v[1];
    const std::string& answer   = v[2];

    if (answer.empty()) continue;

    if (!filename.empty())
    {
      text_out.push_back("<img src = \"" + filename + "\" />");
      //text_out.push_back("<img src = \"" + filename + "\" alt = \"My Image\" />");
    }

    const std::vector<std::string> false_answers(&v[3],v.end());

    if (false_answers.empty())
    {
      //Open question
      //Create the doc
      const std::string question_line
        = "<p>"
        + boost::lexical_cast<std::string>(i)
        + ". "
        + question
        + "</p>";
      text_out.push_back(question_line);
      const std::string line_to_write_on
        = "<p>"
        + std::string("_",40)
        + "</p>";
      text_out.push_back(line_to_write_on);
    }
    else
    {
      //Multiple choice question

      //Prepare the answers
      std::vector<std::string> answers;
      answers.push_back(answer);
      std::copy(false_answers.begin(),false_answers.end(),std::back_inserter(answers));
      std::sort(answers.begin(),answers.end());

      //Create the doc
      const std::string question_line
        = "<p>"
        + boost::lexical_cast<std::string>(i)
        + ". "
        + question
        + "</p>";
      text_out.push_back(question_line);

      text_out.push_back("<ul  type=\"disc\" >");

      const int n_answers = answers.size();
      for (int i=0; i!=n_answers; ++i)
      {
        const std::string s = "<li> " + answers[i] + "</li>";
        text_out.push_back(s);
      }

      text_out.push_back("</ul>");

      text_out.push_back("<p></p>"); //Empty line
    }
  }

  text_out.push_back("</font>");
  text_out.push_back("</body>");
  text_out.push_back("</html>");

  return text_out;
}
//---------------------------------------------------------------------------
//Assumes v is shuffled and v[0] is the copyright line
const std::vector<std::string> CreateDoc(
  const std::vector<std::string> text_in,
  const int n_questions_desired,
  const std::string& code)
{
  std::vector<std::string> text_out;
  text_out.push_back("<head>");
  text_out.push_back("<title>Hometrainer 2 test</title>");
  text_out.push_back("</head>");
  text_out.push_back("<html>");
  text_out.push_back("<body>");
  text_out.push_back("<font size=\"4\" face=\"Courier New\" >");

  //Parsing the questions
  const int sz
    = std::min(static_cast<int>(text_in.size()),
        n_questions_desired + 1);

  for (int i=1; i!=sz; ++i) //1, because first line is signature
  {
    //Obtain the string to split
    const std::string str_to_split_original = text_in[i];
    if (str_to_split_original.empty() == true) continue;

    //Replace \, by {comma}
    const std::string str_to_split = ReplaceAll(str_to_split_original,"\\,","{comma}");

    //Write string to split to debug
    const std::string debug_output = "MyDebug:" + str_to_split;
    OutputDebugString(debug_output.c_str());
    const std::vector<std::string> v_original = SeperateString(str_to_split,",");

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> v = ReplaceAll(v_original,"{comma}",",");

    if (v.empty()==true) continue;

    const std::string filename = v[0];
    //const std::string filename = m_path + '\\' + v[0];
    const std::string& question = v[1];
    const char answer_char = code[ (i - 1)% code.size() ]; //-1 because v[0] is copyright line
    const std::string answer = boost::lexical_cast<std::string>(answer_char) + ") " + v[2];

    if (answer.empty()) continue;

    if (!filename.empty())
    {
      text_out.push_back("<img src = \"" + filename + "\" />");
      //text_out.push_back("<img src = \"" + filename + "\" alt = \"My Image\" />");
    }

    const std::vector<std::string> false_answers_no_char(&v[3],v.end());

    const std::vector<std::string> false_answers = AddChar(false_answers_no_char,answer_char,code);

    if (false_answers.empty())
    {
      //Open question
      //Create the doc
      const std::string question_line
        = "<p>"
        + boost::lexical_cast<std::string>(i)
        + ". "
        + question
        + "</p>";
      text_out.push_back(question_line);
      const std::string line_to_write_on
        = "<p>"
        + std::string("_",40)
        + "</p>";
      text_out.push_back(line_to_write_on);
    }
    else
    {
      //Multiple choice question

      //Prepare the answers
      std::vector<std::string> answers;
      answers.push_back(answer);
      std::copy(false_answers.begin(),false_answers.end(),std::back_inserter(answers));
      std::sort(answers.begin(),answers.end());

      //Create the doc
      const std::string question_line
        = "<p>"
        + boost::lexical_cast<std::string>(i)
        + ". "
        + question
        + "</p>";
      text_out.push_back(question_line);

      text_out.push_back("<ul  type=\"disc\" >");

      const int n_answers = answers.size();
      for (int i=0; i!=n_answers; ++i)
      {
        const std::string s = "<li>" + answers[i] + "</li>";
        text_out.push_back(s);
      }

      text_out.push_back("</ul>");
      text_out.push_back("<p></p>"); //Empty line
    }
  }

  text_out.push_back("</font>");
  text_out.push_back("</body>");
  text_out.push_back("</html>");
  return text_out;
}
//---------------------------------------------------------------------------
const std::vector<std::string> AddChar(
  const std::vector<std::string>& v_original,
  const char not,
  const std::string& s)
{
  std::vector<std::string> v;

  std::vector<char> nots;
  nots.push_back(not);

  const int sz = v_original.size();
  for (int i=0; i!=sz; ++i)
  {
    const char c = GetRandomFromButNot(s,nots);
    nots.push_back(c);
    const std::string line
    //  = boost::lexical_cast<std::string>(std::toupper(c))
      = std::string(1,std::toupper(c))
      + ") " + v_original[i];
    v.push_back(line);
  }
  return v;
}
//---------------------------------------------------------------------------
const char GetRandomFromButNot(
  const std::string& s,
  const std::vector<char>& not)
{
  const int sz = static_cast<int>(s.size());
  while (1)
  {
    const int i = std::rand() % sz;
    const char c = s[i];
    if (std::find(not.begin(),not.end(),c)==not.end()) //c is not in 'not'
      return c;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::FormResize(TObject *Sender)
{
  RichEdit1->Width = ClientWidth / 2;
  RichEdit2->Width = ClientWidth - RichEdit1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::ButtonLoadClick(TObject *Sender)
{
  if (!OpenDialog1->Execute()) return;
  m_plaintext = FileToVector(OpenDialog1->FileName.c_str());
  VectorToStringList(m_plaintext,RichEdit1->Lines);
  EditNquestions->Text = m_plaintext.size() - 1;

  ButtonCreateDoc->Enabled = (m_plaintext.size() > 1);
  m_path = GetPath(OpenDialog1->FileName.c_str());

}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::ButtonSaveClick(TObject *Sender)
{
  if (!SaveDialog1->Execute()) return;
  SaveContainer(m_doctext,SaveDialog1->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
{
  assert(FileExists(fileName)==true);
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
void VectorToStringList(const std::vector<std::string>& v,TStrings * const l)
{
  l->Clear();
  typedef std::vector<std::string>::const_iterator Iterator;
  const Iterator j = v.end();
  for (Iterator i = v.begin(); i!=j; ++i)
  {
    l->Add((*i).c_str());
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName)
{
  std::fstream fin;
  fin.open(fileName.c_str(),std::ios::in);
  if( fin.is_open() )
  {
    fin.close();
    return true;
  }
  fin.close();
  return false;
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
//From //From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> SeperateString(
  const std::string& input,
  const std::string& seperator)
{
  std::vector<std::string> v;
  typedef std::string::const_iterator Iterator;
  const Iterator end = input.end();
  Iterator i1 = input.begin();
  {
    //Copy until first comma
    Iterator i2 = std::search(i1,end,seperator.begin(), seperator.end());
    assert(i1!=i2);
    std::string s;
    std::copy(i1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  while (i1!=end)
  {
    //Copy from comma to (comma || end)
    Iterator i2 = std::search(i1 + 1,end,seperator.begin(), seperator.end());
    assert(i1!=i2);
    assert(i2 == end || std::equal(seperator.begin(),seperator.end(),i2));
    std::string s;
    std::copy(i1+1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  return v;
}
//---------------------------------------------------------------------------
const std::vector<std::string> ReplaceAll(
  std::vector<std::string> v,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  typedef std::vector<std::string>::iterator Iterator;
  const Iterator j = v.end();

  for (Iterator i = v.begin(); i!=j; ++i)
  {
    *i = ReplaceAll(*i,replaceWhat,replaceWithWhat);
  }
  return v;
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
void __fastcall TFormCreateDoc::ButtonAdvancedClick(TObject *Sender)
{
  PanelAdvanced->Visible = !PanelAdvanced->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateDoc::CheckBoxUseCodeClick(TObject *Sender)
{
  EditCode->Enabled = CheckBoxUseCode->Checked;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStrToUpper.htm
const std::string StrToUpper(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),std::ptr_fun(std::toupper));
  return s;
}
//---------------------------------------------------------------------------

