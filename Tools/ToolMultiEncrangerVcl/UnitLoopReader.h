//---------------------------------------------------------------------------
/*
  MultiEncranger, encryption and de-encryption tool
  Copyright (C) 2010  Richel Bilderbeek

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
#ifndef UnitLoopReaderH
#define UnitLoopReaderH
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppLoopReader.htm
//Reads a container in a loop:
//  when the end is reached, it starts
//  reading from the beginning again
template <class Iterator>
struct LoopReader
{
  LoopReader(const Iterator begin, const Iterator end)
    : begin_(begin), read_(begin), end_(end)
  {

  }
  const Iterator Read() const { return read_; }

  void Next()
  {
    ++read_;
    if (read_ == end_) read_ = begin_;
  }

  private:
  const Iterator begin_;
  const Iterator end_;
  Iterator read_;

};
//---------------------------------------------------------------------------
#endif
