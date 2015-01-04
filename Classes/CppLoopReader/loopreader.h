//---------------------------------------------------------------------------
/*
LoopReader, class that reads a sequence looped
Copyright (C) 2010-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppLoopReader.htm
//---------------------------------------------------------------------------
#ifndef LOOPREADER_H
#define LOOPREADER_H

#include <cassert>
#include <string>
#include <vector>

namespace ribi {

// From http://www.richelbilderbeek.nl/CppLoopReader.htm
//Reads a container in a loop:
//  when the end is reached, it starts
//  reading from the beginning again
template <class Iterator>
struct LoopReader
{
  explicit LoopReader(const Iterator begin, const Iterator end)
    : m_begin(begin),
      m_end(end),
      m_cur(begin)
  {
    assert(m_begin != m_end);
  }
  const Iterator Read() const noexcept { return m_cur; }

  void Next() noexcept
  {
    assert(m_cur != m_end);
    ++m_cur;
    if (m_cur == m_end) m_cur = m_begin;
  }

  static std::string GetVersion() noexcept
  {
    return "1.2";
  }

  static std::vector<std::string> GetVersionHistory() noexcept
  {
    return {
      "2009-08-26: Version 1.0: initial version",
      "2011-03-06: Version 1.1: added GetVersion and GetVersionHistory member functions",
      "2013-11-25: Version 1.2: added some asserts, added noexcept"
    };
  }

  private:
  const Iterator m_begin;
  const Iterator m_end;

  //The current address to read
  Iterator m_cur;
};

} //~namespace ribi

#endif // LOOPREADER_H
