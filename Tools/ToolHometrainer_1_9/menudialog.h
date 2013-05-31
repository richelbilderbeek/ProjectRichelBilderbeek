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
#ifndef MENUDIALOG_H
#define MENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
struct Question;
//---------------------------------------------------------------------------
///The GUI independent part of the menu dialog
struct MenuDialog
{
  MenuDialog();

  static const About GetAbout();

  ///Get the questions
  const std::vector<boost::shared_ptr<Question> >& GetQuestions() const { return m_questions; }


  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  void OnButtonLoadClicked(const std::string& file);

  private:
  ///The obligatory first line in a hometrainer file
  static const std::string m_signature;

  ///The questions
  std::vector<boost::shared_ptr<Question> > m_questions;

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  ///Replace all occurances of a certain substring in a string
  //From http://www.richelbilderbeek.nl/CppReplaceAll.htm
  static  const std::string ReplaceAll(
    std::string s,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat);

  ///Replace all occurances of a certain substring in the strings
  ///in a container
  //From http://www.richelbilderbeek.nl/CppReplaceAll.htm
  static const std::vector<std::string> ReplaceAll(
    std::vector<std::string> v,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat);

  ///Splits a std::string
  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};
//---------------------------------------------------------------------------
#endif // MENUDIALOG_H
