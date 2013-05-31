//---------------------------------------------------------------------------
/*
Pylos::Move, class for a Pylos/Phyraos move
Copyright (C) 2010-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pylosmove.h"

#include <iostream>
//---------------------------------------------------------------------------
#include <boost/regex.hpp>
//---------------------------------------------------------------------------
#include "pyloscoordinat.h"
#include "trace.h"
//---------------------------------------------------------------------------
namespace Pylos {
//---------------------------------------------------------------------------
Move::Move()
{
  #ifndef NDEBUG
  Test();
  #endif
}
//---------------------------------------------------------------------------
Move::Move(
  const std::vector<Coordinat>& moving,
  const std::vector<Coordinat>& removing)
{
  #ifndef NDEBUG
  Test();
  #endif

  m_move = moving;
  m_remove = removing;

  assert(!m_move.empty()
    && "In every move a marble must be placed or transferred");
  assert(m_move.size() <= 2);
  assert(m_remove.size() <= 2
    && "At most two marbles are removed in a move");
}
//---------------------------------------------------------------------------
Move::Move(const std::string& s)
{
  #ifndef NDEBUG
  Test();
  #endif

  #ifndef NDEBUG
  if (!(
       s.size() == 7
    || s.size() == 16
    || s.size() == 25
    || s.size() == 34)) TRACE(s);
  #endif

  //Read first coordinat
  assert(
       s.size() == 7
    || s.size() == 16
    || s.size() == 25
    || s.size() == 34);
  {
    const Coordinat c(s.substr(0,7));
    m_move.push_back(c);
    if (s.size() == 7) return;
  }
  //Test for transfer with/without removal '(Z,X,Y)->(Z,X,Y)'
  if (s[7] == '-' && s[8] == '>')
  {
    const Coordinat c(s.substr(9,7));
    m_move.push_back(c);
    if (s.size() == 16) return;
  }
  //Test for place and single removal '(Z,X,Y) !(Z,X,Y)'
  if (s[7] == ' ' && s[8] == '!')
  {
    const Coordinat c(s.substr(9,7));
    m_remove.push_back(c);
    if (s.size() == 16) return;
  }
  //Test for transfer with single removal '(Z,X,Y)->(Z,X,Y) !(Z,X,Y)'
  assert(s[16] == ' ' && s[17] == '!');
  {
    const Coordinat c(s.substr(18,7));
    m_remove.push_back(c);
    if (s.size() == 25) return;
  }
  //Test for transfer with double removal '(Z,X,Y)->(Z,X,Y) !(Z,X,Y) !(Z,X,Y)'
  assert(s[25] == ' ' && s[26] == '!');
  {
    const Coordinat c(s.substr(27,7));
    m_remove.push_back(c);
  }
  assert(s.size() == 34);
}
//---------------------------------------------------------------------------
const std::string Move::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> Move::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-05-05: version 2.0: initial release version");
  return v;
}
//---------------------------------------------------------------------------
bool Move::IsValid() const
{
  return
       m_move.size() >= 1
    && m_move.size() <= 2
    && m_remove.size() <= 2;
}
//---------------------------------------------------------------------------
void Move::Test()
{
  static bool tested = false;
  if (tested) return;
  tested = true;

  TRACE("Test Moves");
  {
    Pylos::Move m;
    assert(!m.IsValid() && "An empty move is invalid");
    Pylos::Move n;
    assert(m == n);
    m.m_move.push_back(Coordinat(0,0,0));
    n.m_move.push_back(Coordinat(0,0,0));
    assert(m == n);
  }
  {
    //Valid Moves
    const std::vector<std::string> v
    =
      {
        "(0,0,0)",
        "(0,0,0) !(0,0,0)",
        "(0,0,0) !(0,0,0) !(0,0,0)",
        "(0,0,0)->(0,0,0)",
        "(0,0,0)->(0,0,0) !(0,0,0)",
        "(0,0,0)->(0,0,0) !(0,0,0) !(0,0,0)",
      };
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        try
        {
          const Move m(s);
          //OK
        }
        catch (std::exception& e)
        {
          TRACE(s);
          assert(!"Should not get here");
        }
      }
    );
  }
}
//---------------------------------------------------------------------------
const std::string Move::ToStr() const
{
  #ifndef NDEBUG
  if (!(m_move.size() == 1 || m_move.size() == 2)) TRACE(m_move.size());

  #endif
  assert(m_move.size() == 1 || m_move.size() == 2);

  std::string s = m_move[0].ToStr();
  if (m_move.size() == 2)
  {
    s+="->";
    s+=m_move[1].ToStr();
  }
  if (m_remove.empty()) return s;
  assert(m_remove.size() == 1 || m_remove.size() == 2);
  s+=" !";
  s+=m_remove[0].ToStr();
  if (m_remove.size() == 2)
  {
    s+=" !";
    s+=m_remove[0].ToStr();
  }
  return s;
}
//---------------------------------------------------------------------------
bool operator==(const Move& lhs, const Move& rhs)
{
  return lhs.m_move == rhs.m_move
    && lhs.m_remove == rhs.m_remove;
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Move& m)
{
  os << m.ToStr();
  return os;
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string> GetRegexMatches(
  const std::string& s,
  const boost::regex& r)
{
  std::vector<std::string> v;

  std::string::const_iterator start = s.begin();
  const std::string::const_iterator end = s.end();
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags = boost::match_default;
  while(boost::regex_search(start, end, what, r, flags))
  {
    const std::string x = what.str();
    v.push_back(x);
    start = what[0].second;
    flags |= boost::match_prev_avail;
    flags |= boost::match_not_bob;
  }
  return v;
}
//---------------------------------------------------------------------------
} //~namespace Pylos
//---------------------------------------------------------------------------
