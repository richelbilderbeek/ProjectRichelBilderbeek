//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "pvdbhelper.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <QFile>
#include <QRegExp>

#include "testtimer.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

double ribi::pvdb::GetDistance(const double delta_x, const double delta_y)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  return std::sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
}

double ribi::pvdb::GetDistance(const double x1, const double y1, const double x2, const double y2)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  return GetDistance(x1-x2,y1-y2);
}

std::vector<std::string> ribi::pvdb::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  QRegExp r(r_original);
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
}

std::vector<std::string> ribi::pvdb::SafeFileToVector(const std::string& filename)
{
  std::vector<std::string> v = ribi::fileio::FileIo().FileToVector(filename);
  if (!v.empty() && v.back().empty()) v.pop_back();
  return v;
}

std::vector<std::string> ribi::pvdb::SplitXml(const std::string& s)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  std::vector<std::string> v;
  std::string::const_iterator i = s.begin();
  std::string::const_iterator j = s.begin();
  const std::string::const_iterator end = s.end();
  while (j!=end)
  {
    ++j;
    if ((*j=='>' || *j == '<') && std::distance(i,j) > 1)
    {
      std::string t;
      std::copy(
        *i=='<' ? i   : i+1,
        *j=='>' ? j+1 : j,
        std::back_inserter(t));
      v.push_back(t);
      i = j;
    }
  }
  return v;
}


#ifndef NDEBUG
void ribi::pvdb::TestHelperFunctions()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //GetRegexMatches
  {
    const std::string s = "In the Netherlands, 1234 AB and 2345 BC are valid zip codes";
    std::vector<std::string> expected;
    expected.push_back("1234 AB");
    expected.push_back("2345 BC");
    {
      const std::string r = "(\\d{4} [A-Z]{2})";
      assert(pvdb::GetRegexMatches(s,QRegExp(r.c_str())) == expected);
    }
  }
  {
    const std::string s = "<concept><name>Concept with examples</name><example>Example 1</example><example>Example 2</example><example>Example 3</example></concept>";
    assert(std::count(s.begin(),s.end(),'\b') == 0);
    std::vector<std::string> expected;
    expected.push_back("<example>Example 1</example>");
    expected.push_back("<example>Example 2</example>");
    expected.push_back("<example>Example 3</example>");
    {
      const std::string r = "(<example>.*</example>)";
      assert(pvdb::GetRegexMatches(s,QRegExp(r.c_str())) == expected);
    }
  }
  //GetCombinations
  //Assume the number of elements is correct
  assert(GetCombinations(std::vector<int>( {         } ) ).size() ==  1);
  assert(GetCombinations(std::vector<int>( {1        } ) ).size() ==  2);
  assert(GetCombinations(std::vector<int>( {1,2      } ) ).size() ==  4);
  assert(GetCombinations(std::vector<int>( {1,2,3    } ) ).size() ==  8);
  assert(GetCombinations(std::vector<int>( {1,2,3,4  } ) ).size() == 16);
  assert(GetCombinations(std::vector<int>( {1,2,3,4,5} ) ).size() == 32);
  //Assume the elements are correct
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {1,2};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2,3 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {3};
    const std::vector<int> expected_4 = {1,2};
    const std::vector<int> expected_5 = {1,3};
    const std::vector<int> expected_6 = {2,3};
    const std::vector<int> expected_7 = {1,2,3};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
    assert(std::count(v.begin(),v.end(),expected_4));
    assert(std::count(v.begin(),v.end(),expected_5));
    assert(std::count(v.begin(),v.end(),expected_6));
    assert(std::count(v.begin(),v.end(),expected_7));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2,3,4 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {3};
    const std::vector<int> expected_4 = {4};
    const std::vector<int> expected_5 = {1,2};
    const std::vector<int> expected_6 = {1,3};
    const std::vector<int> expected_7 = {1,4};
    const std::vector<int> expected_8 = {2,3};
    const std::vector<int> expected_9 = {2,4};
    const std::vector<int> expected_10 = {3,4};
    const std::vector<int> expected_11 = {1,2,3};
    const std::vector<int> expected_12 = {1,2,4};
    const std::vector<int> expected_13 = {1,3,4};
    const std::vector<int> expected_14 = {2,3,4};
    const std::vector<int> expected_15 = {1,2,3,4};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
    assert(std::count(v.begin(),v.end(),expected_4));
    assert(std::count(v.begin(),v.end(),expected_5));
    assert(std::count(v.begin(),v.end(),expected_6));
    assert(std::count(v.begin(),v.end(),expected_7));
    assert(std::count(v.begin(),v.end(),expected_8));
    assert(std::count(v.begin(),v.end(),expected_9));
    assert(std::count(v.begin(),v.end(),expected_10));
    assert(std::count(v.begin(),v.end(),expected_11));
    assert(std::count(v.begin(),v.end(),expected_12));
    assert(std::count(v.begin(),v.end(),expected_13));
    assert(std::count(v.begin(),v.end(),expected_14));
    assert(std::count(v.begin(),v.end(),expected_15));
  }
  //Wordwrap
  {
    const auto v {
      "",
      "1",
      "12",
      "123",
      "1234",
      "12345",
      "123456",
      "1234567",
      "12345678",
      "123456789",
      "1234567890",
      "12345678901",
      "123456789012",
      "1234567890123",
      "12345678901234",
      "123456789012345",
      "1234567890123456",
      "12345678901234567",
      "123456789012345678",
      "1234567890123456789",
      "12345678901234567890",
      "123456789012345678901",
      "1234567890123456789012",
      "12345678901234567890123",
      "123456789012345678901234",
      "1234567890123456789012345",
      "12345678901234567890123456",
      "123456789012345678901234567",
      "1234567890123456789012345678",
      "12345678901234567890123456789",
      "123456789012345678901234567890",
      "1234567890123456789012345678901",
      "12345678901234567890123456789012",
      "123456789012345678901234567890123",
      "1234567890123456789012345678901234",
      "12345678901234567890123456789012345",
      "123456789012345678901234567890123456",
      "1234567890123456789012345678901234567",
      "12345678901234567890123456789012345678",
      "123456789012345678901234567890123456789",
      "1234567890123456789012345678901234567890",
      "1 1",
      "12 12",
      "123 123",
      "1234 1234",
      "12345 12345",
      "123456 123456",
      "1234567 1234567",
      "12345678 8",
      "123456789 9",
      "1234567890 0",
      "1234567890 1234567890",
      "1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      " 1",
      "  1",
      "  1 ",
      "  1  ",
      "  1 2 ",
      "  1 23 ",
      "  12 34  ",
      "  12  34  ",
      "   12   34   ",
      "   12   34   5",
      "   12   34   5 ",
      "   12   34   5 6",
      "0   12   34   5 6",
      "0   12   34   5 6  ",
      "                    ",
      "                      ",
      "                        ",
      "                            ",
      "                                    ",
      "                                                    ",
      "                                                                                     "
    };
    for (int len=1; len!=1000; ++len)
    {
      for (const std::string& s: v)
      {
        //Wordwrap calls Unwordwrap
        Wordwrap(s,len);
      }
    }
  }

}
#endif

std::string ribi::pvdb::Unwordwrap(
  const std::vector<std::string>& v) noexcept
{
  //Simply concatenate
  std::string t;
  for (const std::string& s: v) { t += s; }
  return t;
}

std::vector<std::string> ribi::pvdb::Wordwrap(
  const std::string& s_original, const std::size_t max_len) noexcept
{
  if (max_len == 0)
  {
    throw std::logic_error("Cannot wordwrap for a max_len of zero");
  }
  //std::clog << "Wordwrap \'" << s_original << '\'' << std::endl;
  std::string s{s_original};
  assert(s.size() == s_original.size());

  ///Replace multiple spaces with '\b ', where x is a char not in the string
  std::string::value_type x = '\b'; //Bell
  {
    const std::size_t sz = s.size();

    ///Replace spaces at beginning
    for (std::size_t i=0; i!=sz; ++i)
    {
      if (s[i] == ' ')
        s[i] = x;
      else
        break;
    }
    //Replace spaces at end
    if (sz > 0)
    {
      //i!=0, because if s[0] is a space, it is already converted to bell
      for (std::size_t i=sz-1; i!=0; ++i)
      {
        if (s[i] == ' ')
          s[i] = x;
        else
          break;
      }
    }
    ///Replace "  " by "\b "
    for (std::size_t i=0; i!=sz-1; ++i)
    {
      if (s[i] == ' ' && s[i+1] == ' ')
        s[i] = x;
      else
        break;
    }
  }

  std::vector<std::string> v;

  //Start the actual wordwrapping
  while (!s.empty())
  {
    //TRACE(s);
    //Is the word short enough?
    if (s.size() < max_len)
    {
      //Copy entire word
      v.push_back(s);
      s = {};
      assert(s.empty());
      continue;
    }
    //No spaces, or space beyond max_len: cut word
    if (s.find(' ') == std::string::npos || s.find(' ') > max_len)
    {
      v.push_back(s.substr(0,max_len));
      s = s.substr(max_len,s.size() - max_len);
      continue;
    }
    //Find last space before max_len
    std::size_t len = s.find(' ');
    assert(len != std::string::npos);
    assert(len < s.size());
    while (1)
    {
      const std::size_t new_len = s.find(' ',len + 1);
      if (new_len > max_len || new_len == std::string::npos) break;
      len = new_len;
    }
    assert(len + 0 < s.size());
    assert(len + 1 < s.size());
    //cut s, put cut part in vector
    const std::string line = s.substr(0,len+1); //Keep space
    assert(!line.empty());
    v.push_back(line);
    const std::size_t new_index = len+1; //After the space found
    assert(new_index < s.size());
    const std::string new_s = s.substr(new_index,s.size() - new_index);
    assert(s != new_s);
    s = new_s;
  }

  ///Replace bell characters by spaces again
  for (std::string& s: v)
  {
    assert(x != ' ');
    std::size_t pos = s.find(x);
    while (pos != std::string::npos)
    {
      assert(pos != std::string::npos);
      assert(pos < s.size());
      assert(pos == s.find(x)); //To prevent infinite while loop
      s[pos] = ' ';
      assert(s[pos] == ' ');
      assert(pos != s.find(x)); //To prevent infinite while loop
      pos = s.find(x);
    }
    assert(s.find(x) == std::string::npos);
  }

  #ifndef NDEBUG
  //Test if Unwordwrap the result produces the original input
  if (Unwordwrap(v) != s_original)
  {
    std::cerr << v.size() << '\n';
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cerr,"\n"));
    std::cerr << Unwordwrap(v) << '\n';
    std::cerr << s_original << std::endl;

  }
  #endif
  assert(Unwordwrap(v) == s_original);
  return v;
}

std::vector<std::string> ribi::pvdb::XmlToPretty(const std::string& s)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  std::vector<std::string> v = pvdb::SplitXml(s);
  int n = -2;
  std::for_each(v.begin(),v.end(),
    [&n](std::string& s)
    {
      assert(!s.empty());
      if (s[0] == '<' && s[1] != '/')
      {
        n+=2;
      }
      s = std::string(n,' ') + s;
      if (s[n+0] == '<' && s[n+1] == '/')
      {
        n-=2;
      }
    }
  );
  return v;
}
