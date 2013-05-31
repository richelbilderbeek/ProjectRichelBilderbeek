//---------------------------------------------------------------------------
/*
KTouchLectureCreator, create KTouch lecture for C++ programmers
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolKTouchLectureCreator.htm
//---------------------------------------------------------------------------
#include "ktouchlevels.h"

#include <algorithm>
#include <cassert>
#include <numeric>

#include "trace.h"

template <class T>
const T Sort(T t)
{
  std::sort(t.begin(),t.end());
  return t;
}

KTouchLevels::KTouchLevels()
  : m_v(CreateLevels())
{

}

const std::vector<KTouchLevel> KTouchLevels::CreateLevels()
{
  const std::vector<std::string> new_chars
  {
    //Cannot allow / because file will mess up
    //Cannot allow < because file will mess up
    //Cannot allow & because file will mess up
    "fj","dk","sl","a;","gh'", //Home
    "cn","vm","b,",".x","z\\", //Low
    "eu","ri","to","yp","w[","q]", //High
    "39","48","57","60","2-","1=","`", //Numbers
    "FJ","DK","SL","A:","GH\"", //Shift + Home
    "CN","VM","B",">X","Z?", //Shift + Low
    "EU","RI","TO","YP","W{","Q}", //Shift + High
    "#(","$*","%","^)","@_","!+","~|" //Shift + Numbers
  };
  #ifndef NDEBUG
  {
    const std::string all_chars = "`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./~!@#$%^*()_+QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM>?|";
    const std::string all_chars_sorted = Sort(all_chars);

    std::string new_chars_str;
    std::for_each(new_chars.begin(),new_chars.end(),
      [&new_chars_str](const std::string& s) { new_chars_str+=s; }
    );
    const std::string new_chars_str_sorted = Sort(new_chars_str);

    std::string difference;
    std::set_difference(new_chars_str_sorted.begin(),new_chars_str_sorted.end(),all_chars_sorted.begin(),all_chars_sorted.end(),std::back_inserter(difference));
    //TRACE(difference);


    assert(new_chars_str.size() == all_chars.size());
    assert(
      std::accumulate(new_chars.begin(),new_chars.end(),0,
        [](const int init, const std::string& t)
        {
          return init + static_cast<int>(t.size());
        }
      )
      == static_cast<int>(all_chars.size())
      && "All characters must be present"
    );
  }
  #endif
  std::vector<std::string> all_chars = new_chars;
  if (all_chars.size() > 1)
  {
    const int sz = static_cast<int>(all_chars.size());
    for (int from=0; from!=sz-1; ++from)
    {
      const std::string to_append = all_chars.at(from);
      for (int to=from+1; to!=sz; ++to)
      {
        all_chars.at(to)+=new_chars.at(from);
      }
    }
  }
  assert(all_chars.size() == new_chars.size());
  const int sz = all_chars.size();

  std::vector<KTouchLevel> levels;

  for (int i=0; i!=sz; ++i)
  {
    KTouchLevel level(all_chars.at(i),new_chars.at(i));
    levels.push_back(level);

  }
  return levels;
}

const std::vector<std::string> KTouchLevels::ToXml() const
{
  std::vector<std::string> v;
  v.push_back("<Levels>");
  {
    std::for_each(m_v.begin(),m_v.end(),
      [&v](const KTouchLevel& level)
      {
        const auto w = level.ToXml();
        std::transform(w.begin(),w.end(),std::back_inserter(v),
          [](const std::string& s)
          {
            return std::string("  ") + s;
          }
        );
      }
    );
  }
  v.push_back("</Levels>");
  return v;
}
