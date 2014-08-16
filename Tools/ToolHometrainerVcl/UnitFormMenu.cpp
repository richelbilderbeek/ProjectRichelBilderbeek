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

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <assert>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "UnitMultipleChoiceQuestion.h"
#include "UnitOpenQuestion.h"
#include "UnitQuestion.h"
#include "UnitFormMenu.h"
#include "UnitFormMain.h"
#include "UnitFormAbout.h"
#include "UnitEncranger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
//---------------------------------------------------------------------------
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
 : TForm(Owner),
   signature("Hometrainer2 (C) 2009 Richel Bilderbeek"),
   m_key(0)
{
  RandomizeTimer();

  assert(GetPath("f.txt")=="f.txt");
  assert(GetPath("C:\\f.txt")=="C:");
  assert(GetPath("C:\\games\\f.txt")=="C:\\games");

}
//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppSeperateString.htm
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
void __fastcall TFormMenu::ImageLoadExerciseClick(TObject *Sender)
{
  if (!OpenDialog->Execute()) return;

  boost::shared_ptr<TStringList> s(new TStringList);
  s->LoadFromFile(OpenDialog->FileName);

  const std::string path = GetPath(OpenDialog->FileName.c_str());

  if (s->Count == 0)
  {
    MessageDlg("File is empty and cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }
  if (s->Count == 1)
  {
    MessageDlg("File has only one line and thus cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }
  if (s->Count > 1 && s->operator [](0) != signature)
  {
    MessageDlg("The first line of the file must read\n" + signature
      + "\nTherefore the file will not be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }

  //Parsing the questions
  m_questions.clear();
  assert(m_questions.empty() == true);

  const int sz = s->Count;
  for (int i=1; i!=sz; ++i) //1, because first line is signature
  {
    //Obtain the string to split
    const std::string str_to_split_original = s->operator [](i).c_str();
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

    const std::string& filename = path + '\\' + v[0];
    const std::string& question = v[1];
    const std::string& answer   = v[2];

    if (answer.empty()) continue;

    const std::vector<std::string> false_answers(&v[3],v.end());

    if (false_answers.empty())
    {
      //Open question
      const std::vector<std::string> answers(SeperateString(answer,"/"));
      boost::shared_ptr<Question> q(
        new OpenQuestion(filename,question,answers));
      m_questions.push_back(q);
    }
    else
    {
      //Multiple choice question
      boost::shared_ptr<Question> q(
        new MultipleChoiceQuestion(filename,question,answer,false_answers));
      m_questions.push_back(q);
    }
  }

  if (m_questions.empty() == false) ImageStartExercise->Visible = true;

}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageStartExerciseClick(TObject *Sender)
{
  const std::string username = "";
  const int key = 0;
  assert(m_questions.empty() == false);
  boost::shared_ptr<TFormMain> f(new TFormMain(0,m_questions,false,key,username,"no_file.txt"));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageAboutClick(TObject *Sender)
{
  boost::shared_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageQuitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
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
void __fastcall TFormMenu::ImageStartTestClick(TObject *Sender)
{
//  //Ask name
  String username_Vcl = "";
  const bool inputGiven = InputQuery(
    "Hometrainer2",
    "Please enter your full name",
    username_Vcl);
  if (!inputGiven) return;

  const std::string username = username_Vcl.c_str();

  SaveDialog1->FileName = String(username.c_str()) + ".txt";
  if (!SaveDialog1->Execute()) return;
  const std::string path = GetPath(SaveDialog1->FileName.c_str());
  const std::string filename = path + "\\" + username + ".txt";


  assert(m_questions.empty() == false);
  boost::shared_ptr<TFormMain> f(new TFormMain(0,m_questions,true,m_key,username,filename));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMenu::ImageLoadTestClick(TObject *Sender)
{
  //Ask for file
  if (!OpenDialog->Execute()) return;

  //Ask for key
  String userInput = "0";
  const bool inputGiven = InputQuery(
    "Hometrainer 2", //The caption of the InputBox
    "What is the encryption key?",
    userInput);

  if (!inputGiven) return;

  const int key_user = userInput.ToInt();

  boost::shared_ptr<TStringList> s(new TStringList);
  s->LoadFromFile(OpenDialog->FileName);

  const std::string path = GetPath(OpenDialog->FileName.c_str());

  if (s->Count == 0)
  {
    MessageDlg("File is empty and cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }
  if (s->Count == 1)
  {
    MessageDlg("File has only one line and thus cannot be used",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }

  //Deencrypt file
  {
    //Need of new TStringList, because TStringList::operator[]()
    //does not seem to support writing, use TStringList::Add() instead
    boost::shared_ptr<TStringList> s_new(new TStringList);

    Encranger e(key_user);
    const int sz = s->Count;
    for (int i=0; i!=sz; ++i)
    {
      const String s1 = s->operator [](i).c_str();
      const String s2 = e.Deencrypt(s1.c_str()).c_str();
      s_new->Add(s2);
    }
    //Overwrite old TStringList
    s = s_new;
  }

  if (s->Count > 1 && s->operator [](0) != signature)
  {
    //ShowMessage(s->operator [](0));
    MessageDlg("Incorrect key given, therefore test is not loaded.",
      mtError,
      TMsgDlgButtons() << mbOK,
      0);
    return;
  }

  //Parsing the questions
  m_questions.clear();
  assert(m_questions.empty() == true);

  const int sz = s->Count;
  for (int i=1; i!=sz; ++i) //1, because first line is signature
  {
    const std::string str_to_split_original = s->operator [](i).c_str();
    if (str_to_split_original.empty() == true) continue;

    //Replace \, by {comma}
    const std::string str_to_split = ReplaceAll(str_to_split_original,"\\,","{comma}");

    const std::string debug_output = "MyDebug:" + str_to_split;
    OutputDebugString(debug_output.c_str());
    const std::vector<std::string> v_original = SeperateString(str_to_split,",");

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> v = ReplaceAll(v_original,"{comma}",",");

    if (v.empty()==true) continue;

    const std::string& filename = path + '\\' + v[0];
    const std::string& question = v[1];
    const std::string& answer   = v[2];
    const std::vector<std::string> false_answers(&v[3],v.end());

    if (false_answers.empty())
    {
      //Open question
      const std::vector<std::string> answers(SeperateString(answer,"/"));
      boost::shared_ptr<Question> q(
        new OpenQuestion(filename,question,answers));
      m_questions.push_back(q);
    }
    else
    {
      //Multiple choice question
      boost::shared_ptr<Question> q(
        new MultipleChoiceQuestion(filename,question,answer,false_answers));
      m_questions.push_back(q);
    }
  }


  if (m_questions.empty() == false)
  {
    m_key = key_user;
    ImageStartTest->Visible = true;
  }
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



