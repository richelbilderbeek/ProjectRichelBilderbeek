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
#ifndef UnitQuestionH
#define UnitQuestionH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <boost/checked_delete.hpp>
//---------------------------------------------------------------------------
struct Question
{
  const bool IsCorrect(const std::string& s) const;

  const std::string m_filename;
  const std::string m_question;
  const std::vector<std::string> m_answers;

  protected:
  //Made constructor private, because one cannot make a Question, only
  //derived classes of Question
  Question(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers);

  virtual ~Question() {}
  friend boost::checked_delete(Question *);
};
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName);
//---------------------------------------------------------------------------
//export template <class T> std::vector<T> CreateVector(
//  const T& t0,
//  const T& t1);
//---------------------------------------------------------------------------
template <class T> const std::vector<T> CreateVector(
  const T& t0,
  const T& t1)
{
  std::vector<T> v(2);
  v[0] = t0;
  v[1] = t1;
  return v;
}
//---------------------------------------------------------------------------
template <class T> const std::vector<T> CreateVector(
  const T& t0,
  const T& t1,
  const T& t2)
{
  std::vector<T> v(3);
  v[0] = t0;
  v[1] = t1;
  v[2] = t2;
  return v;
}
//---------------------------------------------------------------------------



#endif
