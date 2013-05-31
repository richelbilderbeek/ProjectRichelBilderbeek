//---------------------------------------------------------------------------
/*
Hometrainer, tool to make exercises and tests
Copyright (C) 2009-2011  Richl Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolHometrainer
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include "encranger.h"
#include "loopreader.h"
#include "menudialog.h"
#include "multiplechoicequestion.h"
#include "openquestion.h"
#include "question.h"
#include "trace.h"
//---------------------------------------------------------------------------
const std::string MenuDialog::m_signature("Hometrainer (C) 2009-2011 Richel Bilderbeek");
//---------------------------------------------------------------------------
MenuDialog::MenuDialog()
{

}
//---------------------------------------------------------------------------
///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> MenuDialog::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}
//---------------------------------------------------------------------------
const About MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "Hometrainer",
    "tool to make exercises and tests",
    "the 27th of June 2011",
    "2009-2011",
    "http://www.richelbilderbeek.nl/ToolHometrainer.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<char>::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string MenuDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-04-28: Version 1.0: initial C++ Builder version");
  v.push_back("2009-05-09: Version 1.1: added support for open questions, added support for questions without pictures, added support for JPEG picture, added help at creating new Hometrainer 2 text files");
  v.push_back("2009-08-23: Version 1.2: added support for examination, added program to create tests, added program to score tests");
  v.push_back("2009-08-29: Version 1.3: no need to enter number of questions in ScoreTests, added support of question analysis, added warning in FormSaveResults, added privacy disclaimer in FormSaveResults, changed feedback in ScoreTest, fixed bug in ReplaceOnce', fixed bug in ReplaceAll'");
  v.push_back("2009-09-20: Version 1.4: used MVC model in FormCreateTest, fixed assertion error when user supplies questions file with a comma after the question, but without any answers");
  v.push_back("2009-10-29: Version 1.5: allow the use of comma's in question text, added support to generate a test of a smaller size than the exercise in thet test creater, fixed bug: test key is only modified when test is correct");
  v.push_back("2009-03-11: Version 1.6: fixed bug detected by ScoreTest, CreateTest and ScoreTest are compiled to standalone executables");
  v.push_back("2010-01-07: Version 1.7: results are saved after every answered question, keep \'Encrypt\' disabled in CreateTest until actual test is loaded");
  v.push_back("2010-01-28: Version 1.8: added CreateDoc to suite, renamed CreateDoc to CreateRtf");
  v.push_back("2011-06-27: Version 2.0: port to Qt Creator");
  return v;
}
//---------------------------------------------------------------------------
void MenuDialog::OnButtonLoadClicked(const std::string& file)
{
  const std::vector<std::string> v = FileToVector(file);

  const std::string path = boost::filesystem::path(file).parent_path().string();

  if (v.empty())
  {
    throw std::runtime_error("File is empty and cannot be used");
  }
  if (v.size() == 1)
  {
    throw std::runtime_error("File has only one line and thus cannot be used");
  }
  if (v.size() > 1 && v[0] != m_signature)
  {
    throw std::runtime_error(
      "The first line of the file must read \'"
      + m_signature
      + "\'");
    return;
  }

  //Parsing the questions
  m_questions.clear();
  assert(m_questions.empty());

  BOOST_FOREACH(const std::string& s,v)
  {
    if (s == m_signature) continue;
    if (s.empty()) continue;

    //Replace \, by {comma}
    const std::string str_to_split = ReplaceAll(s,"\\,","{comma}");

    //Write string to split to debug
    TRACE(str_to_split);

    const std::vector<std::string> v_original = SeperateString(str_to_split,',');

    //Replace {comma} by a comma for each std::string in v
    const std::vector<std::string> v = ReplaceAll(v_original,"{comma}",",");

    if (v.empty()) continue;

    const std::string filename = path + '\\' + v[0];
    const std::string& question = v[1];
    const std::string& answer   = v[2];

    if (answer.empty()) continue;

    const std::vector<std::string> false_answers(v.begin() + 3,v.end());

    if (false_answers.empty())
    {
      //Open question
      const std::vector<std::string> answers(SeperateString(answer,'/'));
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
}
//---------------------------------------------------------------------------
///Replace all occurances of a certain substring in a string
//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
const std::string MenuDialog::ReplaceAll(
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
///Replace all occurances of a certain substring in the strings
///in a container
//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
const std::vector<std::string> MenuDialog::ReplaceAll(
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
///Splits a std::string
//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> MenuDialog::SeperateString(
  const std::string& input,
  const char seperator)
{
 std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}
//---------------------------------------------------------------------------
