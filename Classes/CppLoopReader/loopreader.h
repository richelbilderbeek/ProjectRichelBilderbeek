//---------------------------------------------------------------------------
/*
LoopReader, class that reads a sequence looped
Copyright (C) 2010-2011 Richel Bilderbeek

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
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppLoopReader.htm
//Reads a container in a loop:
//  when the end is reached, it starts
//  reading from the beginning again
template <class Iterator>
struct LoopReader
{
  explicit LoopReader(const Iterator begin, const Iterator end)
    : begin_(begin),
      end_(end),
      read_(begin)
  {

  }
  const Iterator Read() const { return read_; }

  void Next()
  {
    ++read_;
    if (read_ == end_) read_ = begin_;
  }

  static const std::string GetVersion()
  {
    return "1.1";
  }

  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2009-08-26: Version 1.0: initial version");
    v.push_back("2011-03-06: Version 1.1: added GetVersion and GetVersionHistory methods");
    return v;
  }

  private:
  const Iterator begin_;
  const Iterator end_;
  Iterator read_;
};
//---------------------------------------------------------------------------
#endif // LOOPREADER_H
