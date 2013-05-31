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
#include "ktouchlevel.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>

template <class T>
const T Sort(T t)
{
  std::sort(t.begin(),t.end());
  return t;
}

KTouchLevel::KTouchLevel(const std::string& chars, const std::string& new_chars)
  : m_lines(CreateLines(chars)),
    m_new_chars(new_chars)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::string KTouchLevel::CreateLine(const std::string& chars)
{
  const std::vector<std::string> v
  {
    " ",
    "&&",
    "||",
//    "//",
//    "/* */",
    "++a",
    "++b",
    "a!=b",
    "a==b",
    "alignas",
    "alignof",
    "asm",
    "auto",
    "bool",
    "boost::any",
    "boost::array",
    "boost::compressed_pair",
    "boost::dynamic_bitset",
    "boost::multi_array",
    "boost::ptr_array",
    "boost::ptr_deque",
    "boost::ptr_list",
    "boost::ptr_map",
    "boost::ptr_multimap",
    "boost::ptr_multiset",
    "boost::ptr_set",
    "boost::ptr_vector",
    "boost::shared_array",
    "boost::tuple",
    "boost::variant",
    "break;",
    "break",
    "C++11",
    "C++11",
    "C++98",
    "C++98",
    "case:",
    "case",
    "catch",
    "char",
    "char16_t",
    "char32_t",
    "class",
    "const",
    "const_cast",
    "const_cast<const double>",
    "const_cast<const int>",
    "const_cast<const std::string>",
    "const_cast<double>",
    "const_cast<int>",
    "const_cast<std::string>",
    "constexpr",
    "continue;",
    "continue",
    "decltype",
    "default:",
    "default",
    "#define",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "dynamic_cast<const T*>",
    "dynamic_cast<const T*>",
    "dynamic_cast<const T* const>",
    "dynamic_cast<T*>",
    "dynamic_cast<T* const>",
    "#elif",
    "#else",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "final",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "++i",
    "++j",
    "i!=j",
    "i==j",
    "#ifdef",
    "#ifndef",
    "#include",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "nullptr",
    "operator==",
    "operator-=",
    "operator--",
//    "operator/=",
    "operator",
    "operator*=",
    "operator+=",
    "operator++",
    "private:",
    "private",
    "protected:",
    "protected",
    "public:",
    "public",
    "register",
    "reinterpret_cast",
    "reinterpret_cast<T*>",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "static_cast<double>",
    "static_cast<int>",
    "std::accumulate",
    "std::adjacent_find",
    "std::all_of",
    "std::any_of",
    "std::binary_search",
    "std::bitset",
    "std::bit_vector",
    "std::copy",
    "std::copy_backward",
    "std::copy_if",
    "std::copy_n",
    "std::count",
    "std::count_if",
    "std::deque",
    "std::deque<int>",
    "std::deque<double>",
    "std::deque<std::string>",
    "std::equal",
    "std::equal_range",
    "std::fill",
    "std::find",
    "std::find_end",
    "std::find_first_of",
    "std::find_if",
    "std::find_if_not",
    "std::for_each",
    "std::generate",
    "std::generate_n",
    "std::hash",
    "std::hash_map",
    "std::hash_multimap",
    "std::hash_multiset",
    "std::hash_set",
    "std::includes",
    "std::inplace_merge",
    "std::iota",
    "std::is_heap",
    "std::is_heap_until",
    "std::is_sorted",
    "std::is_sorted_until",
    "std::iter_swap",
    "std::lexicographical_compare",
    "std::list",
    "std::list<int>",
    "std::list<double>",
    "std::list<std::string>",
    "std::lower_bound",
    "std::make_heap",
    "std::map",
    "std::map<int,int>",
    "std::map<double,double>",
    "std::map<std::string,std::string>",
    "std::max",
    "std::max_element",
    "std::merge",
    "std::min",
    "std::min_element",
    "std::minmax",
    "std::minmax_element",
    "std::mismatch",
    "std::move",
    "std::move_backward",
    "std::multimap",
    "std::multiset",
    "std::next_permutation",
    "std::none_of",
    "std::nth_element",
    "std::pair",
    "std::pair<int,int>",
    "std::pair<double,double>",
    "std::pair<std::string,std::string>",
    "std::partial_sort",
    "std::partial_sort_copy",
    "std::partition",
    "std::partition_copy",
    "std::partition_point",
    "std::pop_heap",
    "std::prev_permutation",
    "std::priority_queue",
    "std::push_heap",
    "std::queue",
    "std::queue<int>",
    "std::queue<double>",
    "std::queue<std::string>",
    "std::random_shuffle",
    "std::random_shuffle(v.begin(),v.end())",
    "std::remove",
    "std::remove_copy",
    "std::remove_copy_if",
    "std::remove_if",
    "std::replace",
    "std::replace_copy",
    "std::replace_copy_if",
    "std::replace_if",
    "std::reverse",
    "std::reverse_copy",
    "std::rope",
    "std::rotate",
    "std::rotate_copy",
    "std::search",
    "std::search_n",
    "std::set",
    "std::set<int>",
    "std::set<std::string>",
    "std::set_difference",
    "std::set_intersection",
    "std::set_symmetric_difference",
    "std::set_union",
    "std::slist",
    "std::sort",
    "std::sort(v.begin(),v.end())",
    "std::sort_heap",
    "std::stable_partition",
    "std::stable_sort",
    "std::stack",
    "std::stack<int>",
    "std::stack<double>",
    "std::stack<std::string>",
    "std::string",
    "std::swap",
    "std::swap_ranges",
    "std::transform",
    "std::unique",
    "std::unique_copy",
    "std::upper_bound",
    "std::valarray",
    "std::vector",
    "std::vector<int>",
    "std::vector<double>",
    "std::vector<std::string>",
    "std::vector<std::vector<int>>",
    "std::vector<std::vector<double>>",
    "std::vector<std::vector<std::string>>",
    "s.empty()",
    "s.size()",
    "s.at(0)",
    "s[0]",
    "struct",
    "switch",
    "t.empty()",
    "t.size()",
    "t.at(0)",
    "t[0]",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "v.empty()",
    "v.size()",
    "v.at(0)",
    "v[0]",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while"
  };
  //Collect all fitting words
  std::vector<std::string> w;
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [chars](const std::string& s)
    {
      return DoesFit(s,chars);
    }
  );
  std::random_shuffle(w.begin(),w.end());

  //Keep the first 30 chars of words
  {
    const int sz = static_cast<int>(w.size());
    int sum = 0;
    for (int i=0; i!=sz; ++i)
    {
      sum += static_cast<int>(w.at(i).size());
      if (sum > 30)
      {
        w.resize(i);
       break;
      }
    }
  }
  //Create histogram of used chars
  //const std::vector<std::pair<char,int> > histogram = Tally(w,chars);

  //Add words until 60 chars is reached
  const int n_chars_used = std::accumulate(w.begin(),w.end(),0,
    [](int& init, const std::string& s)
    {
      return init + static_cast<int>(s.size());
    }
  );
  // - a line must have about 60 chars
  const int n_chars_extra = 60 - n_chars_used;
  // - level = number_of_chars / 2
  const int level = static_cast<int>(chars.size());
  for (int i=0; i!=n_chars_extra; ++i)
  {
    // - word length = 2 + (level / 3)
    const int word_length = 2 + (level / 3);
    if (i % word_length == 0) { w.push_back(""); }
    const int index = std::rand() % static_cast<int>(chars.size());
    w.back()+=chars[index];
  }

  std::random_shuffle(w.begin(),w.end());

  std::string result;
  std::for_each(w.begin(),w.end(),
    [&result](const std::string& s)
    {
      result += (s + std::string(" "));
    }
  );
  //Remove trailing whitespace
  result.resize(result.size()-1);
  return result;
}

const std::vector<std::string> KTouchLevel::CreateLines(const std::string& chars)
{
  std::vector<std::string> v;
  const int n_lines = 10;
  for (int i=0; i!=n_lines; ++i) { v.push_back(CreateLine(chars)); }
  return v;
}

bool KTouchLevel::DoesFit(const std::string& s, const std::string all)
{
  const std::string t = Sort(s);
  const std::string u = Sort(all);
  //const std::set<char> a(s.begin(),s.end());
  //const std::set<char> b(all.begin(),all.end());
  std::string overlap;
  std::set_intersection(t.begin(),t.end(),u.begin(),u.end(),std::back_inserter(overlap));
  return overlap.size() == s.size();
}

const std::vector<std::string> KTouchLevel::ToXml() const
{
  std::vector<std::string> v;
  v.push_back("<Level>");
  {
    const std::string s = "<NewCharacters>" + m_new_chars + "</NewCharacters>";
    v.push_back(s);
  }
  std::transform(m_lines.begin(),m_lines.end(),std::back_inserter(v),
    [](const std::string& s)
    {
      return std::string("  <Line>") + s + std::string("</Line>");
    }
  );
  v.push_back("</Level>");
  return v;
}

void KTouchLevel::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //DoesFit
  {
    assert( DoesFit("a","a"));
    assert(!DoesFit("b","a"));
    assert( DoesFit("a","ab"));
    assert( DoesFit("b","ab"));
    assert( DoesFit("a","ba"));
    assert( DoesFit("b","ba"));
  }
}
