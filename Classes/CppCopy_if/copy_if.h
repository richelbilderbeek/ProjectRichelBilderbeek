//---------------------------------------------------------------------------
/*
Copy_if, what should have been std::copy_if
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCopy_if.htm
//---------------------------------------------------------------------------
#ifndef COPY_IF_H
#define COPY_IF_H
//---------------------------------------------------------------------------
///Copy_if was dropped from the standard library by accident.
///Note: in C++0x, std::copy_if is present in algorithm.h
//From http://richelbilderbeek.nl/CppCopy_if.htm
template<typename In, typename Out, typename Pred>
Out Copy_if(In first, In last, Out res, Pred Pr)
{
  while (first != last)
  {
    if (Pr(*first))
      *res++ = *first;
    ++first;
  }
  return res;
}
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
struct Copy_if_version
{
  static const std::string GetVersion()
  {
    return "2.0";
  }
  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2011-xx-xx: Version 1.0: initial version");
    v.push_back("2011-06-22: Version 2.0: added versioning");
    return v;
  }
};
//---------------------------------------------------------------------------
#endif // COPY_IF_H
