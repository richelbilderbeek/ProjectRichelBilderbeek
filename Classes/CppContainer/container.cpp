//---------------------------------------------------------------------------
/*
Container, class with container class helper functions
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppContainer.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "container.h"

#include <boost/algorithm/string/split.hpp>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::Container::Container()
{
  #ifndef NDEBUG
  Test();
  #endif
}


std::string ribi::Container::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Container::GetVersionHistory() const noexcept
{
  return {
    "2014-xx-xx: Version 1.0: initial version",
    "2014-06-14: Version 1.1: added SeperateString"
  };
}

std::vector<std::string> ribi::Container::SeperateString(
  const std::string& input,
  const char seperator) const noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

#ifndef NDEBUG
void ribi::Container::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Container::Test");
  const Container c;
  //SeperateString
  {
    { //Single input, seperator of type char
      const auto v = c.SeperateString("a",',');
      assert(v.size() == 1);
      assert(v[0]=="a");
    }
    { //Two inputs, seperator of type char
      const auto v = c.SeperateString("a,b",',');
      assert(v.size() == 2);
      assert(v[0]=="a");
      assert(v[1]=="b");
    }
    {
      //Five inputs, seperator of type char
      const auto v = c.SeperateString("a,bb,ccc,dddd,eeeee",',');
      assert(v.size() == 5);
      assert(v[0]=="a");
      assert(v[1]=="bb");
      assert(v[2]=="ccc");
      assert(v[3]=="dddd");
      assert(v[4]=="eeeee");
    }
    { //Three inputs, of which one empty, seperator of type char
      const auto v = c.SeperateString("a, ,ccc",',');
      assert(v.size() == 3);
      assert(v[0]=="a");
      assert(v[1]==" ");
      assert(v[2]=="ccc");
    }
  }
  TRACE("Finished ribi::Container::Test successfully");
}
#endif
