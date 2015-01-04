//---------------------------------------------------------------------------
/*
QtScopedDisable, Qt class that disables something up until it is destroyed
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtScopedDisable.htm
//---------------------------------------------------------------------------
#ifndef CPPQTSCOPEDDISABLE_H
#define CPPQTSCOPEDDISABLE_H

#include <cassert>
#include <string>
#include <vector>

///QtScopedDisable is a template class that
///disables something upon construction, and enables it
///again when it goes out of scope.
///From http://www.richelbilderbeek.nl/CppQtScopedDisable.htm
template <class T>
struct QtScopedDisable
{
  QtScopedDisable(T * const t)
    : m_t(t)
  {
    assert(m_t);
    m_t->setEnabled(false);
  }
  ~QtScopedDisable()
  {
    m_t->setEnabled(true);
  }

  ///Obtain the version of this class
  static std::string GetVersion()
  {
    return "1.2";
  }

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2012-11-22: version 1.0: initial version");
    return v;
  }


  private:
  T * const m_t;
};

#endif // CPPQTSCOPEDDISABLE_H
