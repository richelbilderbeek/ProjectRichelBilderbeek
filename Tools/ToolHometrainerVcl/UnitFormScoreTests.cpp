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
#include <fstream>
#include <boost/scoped_ptr.hpp>
#include "UnitEncranger.h"
#include "UnitFormScoreTests.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormScoreTests *FormScoreTests;
//---------------------------------------------------------------------------
__fastcall TFormScoreTests::TFormScoreTests(TComponent* Owner)
        : TForm(Owner)
{
  StringGridStudents->Cells[0][0] = "#";
  StringGridStudents->Cells[1][0] = "Name";
  StringGridStudents->Cells[2][0] = "Score";
  StringGridStudents->Cells[3][0] = "Comment";

  StringGridQuestions->Cells[0][0] = "#";
  StringGridQuestions->Cells[1][0] = "f";
  StringGridQuestions->Cells[2][0] = "Question";

  assert(RemovePath("Test.txt")=="Test.txt");
  assert(RemovePath("C:\\Test.txt")=="Test.txt");
  assert(RemovePath("C:\\Test\\Test.txt")=="Test.txt");
  assert(RemovePath("C:\\Test\\Test\\Test.txt")=="Test.txt");

  assert(RemoveExtension("Test.txt")=="Test");
  assert(RemoveExtension("C:\\Test.txt")=="C:\\Test");
  assert(RemoveExtension("C:\\Test\\Test.txt")=="C:\\Test\\Test");
  assert(RemoveExtension("C:\\Test\\Test\\Test.txt")=="C:\\Test\\Test\\Test");

}
//---------------------------------------------------------------------------
void __fastcall TFormScoreTests::ButtonLoadClick(TObject *Sender)
{
  if (!OpenDialog1->Execute()) return;
  ButtonScore->Enabled = true;
}
//---------------------------------------------------------------------------
void TFormScoreTests::ReadFile(const String& filename)
{
  const int row = StringGridStudents->RowCount - 1;
  const std::string file_stripped = RemoveExtension(RemovePath(filename.c_str()));
  ++StringGridStudents->RowCount;
  StringGridStudents->Cells[0][row] = row;
  StringGridStudents->Cells[1][row] = file_stripped.c_str();
  StringGridStudents->Cells[2][row] = "";
  StringGridStudents->Cells[3][row] = "";

  const int key = EditKey->Text.ToInt();
  const int penalty = EditPenalty->Text.ToInt();
  const Encranger e(key);


  //Load file
  std::vector<std::string> v = FileToVector(filename.c_str());

  const int sz = v.size();
  for (int i=0; i!=sz; ++i)
  {
    //Deencrypt file
    v[i] = e.Deencrypt(v[i]);
    //Remove asterisks
    v[i] = ReplaceAll(v[i],"*","");
  }

  const std::string username = FindUserName(v);

  if (username.empty())
  {
    StringGridStudents->Cells[3][row] = "Username not found";
    StringGridStudents->Cells[2][row] = "1.0 or 1.1";
    return;
  }

  if (username != file_stripped)
  {
    StringGridStudents->Cells[3][row] = "Filename differs from username";
    StringGridStudents->Cells[2][row] = "1.1";
    return;
  }


  int n_correct = 0;
  const int n_questions = CountQuestions(v);
  LabelNquestions->Caption = "#questions: " + IntToStr(n_questions);

  for (int i=0; i!=sz; ++i)
  {
    if (v[i].empty()) continue;

    const std::vector<std::string> line_markup = SeperateString(v[i],",");

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> line = ReplaceAll(line_markup,"{comma}",",");

    OutputDebugString(line.size() >= 1 ? line[0].c_str() : "line[0] = {}");
    OutputDebugString(line.size() >= 2 ? line[1].c_str() : "line[1] = {}");
    OutputDebugString(line.size() >= 3 ? line[2].c_str() : "line[2] = {}");
    OutputDebugString(line.size() >= 4 ? line[3].c_str() : "line[3] = {}");

    //assert(line.size() == 2); WORKAROUND



    if (line[0]=="NAME") continue;
    const bool is_correct = (line[line.size()-1]=="Y"); //WORKAROUND
    assert(line[line.size()-1]=="Y" || line[line.size()-1]=="N"); //WORKAROUND 
    if (is_correct) ++n_correct;
    ScoreQuestion(line[0],is_correct);
  }

  //Calculate student's score
  assert(n_questions - penalty > 0);
  const double fraction
      = static_cast<double>(n_correct - penalty)
      / static_cast<double>(n_questions - penalty);
  const double init_score = 1.0 + (9.0 * fraction);
  const double score_above_one = (init_score < 1.0 ? 1.0 : init_score);
  const double score_below_ten = (score_above_one > 10.0 ? 10.0 : score_above_one);
  const double score = score_below_ten;

  StringGridStudents->Cells[2][row] = score;
}
//---------------------------------------------------------------------------
void TFormScoreTests::ScoreQuestion(const std::string& s, const bool is_correct)
{
  if (s.empty()) return;

  //Search for s manually
  const int n_rows = StringGridQuestions->RowCount - 1; //-1 because of fixed row
  for (int i=0; i!=n_rows; ++i)
  {
    if (s == std::string(StringGridQuestions->Cells[2][i+1].c_str())) //+1 because of fixed row
    {
      StringGridQuestions->Cells[0][i+1]
        = (is_correct ? 1 : 0)
        + StringGridQuestions->Cells[0][i+1].ToInt();
      return;
    }
  }
  ++StringGridQuestions->RowCount;
  StringGridQuestions->Cells[0][n_rows] = (is_correct ? "1" : "0");
  StringGridQuestions->Cells[2][n_rows] = s.c_str();
}
//---------------------------------------------------------------------------
void TFormScoreTests::CalculateQuestionScores()
{
  const int n_tests = OpenDialog1->Files->Count;

  const int n_rows = StringGridQuestions->RowCount - 1; //-1 because of 1 fixed cell
  for (int i=0; i!=n_rows; ++i)
  {
    if (StringGridQuestions->Cells[0][i+1].IsEmpty()) continue;
    const int n_correct = StringGridQuestions->Cells[0][i+1].ToInt();
    const double fraction_correct
      = static_cast<double>(n_correct)
      / static_cast<double>(n_tests);
    StringGridQuestions->Cells[1][i+1] = fraction_correct;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormScoreTests::FormResize(TObject *Sender)
{
  //Students
  {
    const int index_width = 32;
    const int score_width = 64;
    StringGridStudents->ColWidths[0] = index_width;
    StringGridStudents->ColWidths[2] = score_width;
    const int width_left = StringGridStudents->ClientWidth - index_width - score_width;
    StringGridStudents->ColWidths[1] = (width_left / 2) - 1; //-1 just to be sure
    StringGridStudents->ColWidths[3] = (width_left / 2) - 1; //-1 just to be sure
  }
  //Questions
  {
    const int score_width = 64;
    StringGridQuestions->ColWidths[0] = score_width;
    StringGridQuestions->ColWidths[1] = score_width;
    const int width_left = StringGridQuestions->ClientWidth - score_width - score_width - 1;
    StringGridQuestions->ColWidths[2] = width_left;

  }
}
//---------------------------------------------------------------------------

void __fastcall TFormScoreTests::ButtonScoreClick(TObject *Sender)
{
  StringGridStudents->RowCount = 2;
  StringGridQuestions->RowCount = 2;

  //Read files one at a time
  const int n_files = OpenDialog1->Files->Count;
  for (int i=0; i!=n_files; ++i)
  {
    const String filename = OpenDialog1->Files->operator[](i);
    ReadFile(filename);
  }

  CalculateQuestionScores();

  ButtonSave->Enabled = true;
  LabelNquestions->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormScoreTests::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormScoreTests::ButtonSaveClick(TObject *Sender)
{
  if (!SaveDialog1->Execute()) return;

  boost::scoped_ptr<TStringList> v(new TStringList);

  const int n_rows = StringGridStudents->RowCount;
  const int n_cols = StringGridStudents->ColCount;
  for (int i=0; i!=n_rows; ++i)
  {
    String s = StringGridStudents->Cells[0][i];
    for (int j=1; j!=n_cols; ++j)
    {
      s+=","+StringGridStudents->Cells[j][i];
    }
    v->Add(s);
  }
  v->SaveToFile(SaveDialog1->FileName);

  ShowMessage("Results saved to file " + SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
const std::string FindUserName(const std::vector<std::string>& v)
{
  typedef std::vector<std::string>::const_iterator Iterator;
  const Iterator j = v.end();
  for (Iterator i = v.begin(); i!=j; ++i)
  {
    if( (*i).size() > 5 && (*i).substr(0,5)=="NAME,")
    {
      return (*i).substr(5, (*i).size() - 5);
    }
  }
  return std::string();
}
//---------------------------------------------------------------------------
const int CountQuestions(const std::vector<std::string>& v)
{
  typedef std::vector<std::string>::const_iterator Iterator;
  int n_questions = 0;
  const Iterator j = v.end();
  for (Iterator i = v.begin(); i!=j; ++i)
  {
    if( (*i).empty()
      || ( (*i).size() > 5 && (*i).substr(0,5)=="NAME," ) )
    {
      continue;
    }
    ++n_questions;
  }
  return n_questions;
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
//From http://www.richelbilderbeek.nl/CppReplaceOnce.htm
const std::string ReplaceOnce(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  const int pos = s.find(replaceWhat);
  if (pos==-1) return s;
  s.replace(pos,replaceWhat.size(),replaceWithWhat);
  return s;
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
//From http://www.richelbilderbeek.nl/CppRemovePath.htm
//Returns the filename without path
const std::string RemovePath(const std::string& filename)
{
  const int sz = static_cast<int>(filename.size());
  const int path_sz = filename.rfind("\\",filename.size());
  if (path_sz == sz) return filename;
  return filename.substr(path_sz + 1,sz - 1 - path_sz);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRemoveExtension.htm
const std::string RemoveExtension(const std::string& filename)
{
  const int dot_index = filename.rfind(".",filename.size());
  assert(dot_index != -1 && "No dot found in filename");
  return filename.substr(0,dot_index);
}
//---------------------------------------------------------------------------

