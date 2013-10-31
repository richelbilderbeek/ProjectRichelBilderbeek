#include "help.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "trace.h"

ribi::Help::Option::Option(
  const char option_short,
  const std::string& option_long,
  const std::string& option_description)
  : m_short(option_short),
    m_long(option_long),
    m_description(option_description)
{
  #ifndef NDEBUG
  const int max_chars_per_line = 80;
  const int chars_for_padding = 7;
  const int max_chars = max_chars_per_line - chars_for_padding;
  const int chars_used = static_cast<int>(1 + m_long.size() + m_description.size());
  assert(chars_used <= max_chars && "Options must be kept short to fit on a line");
  //os << "-" << p.m_short << ", --" << p.m_long << "  " << p.m_description << '\n';
  #endif
}


ribi::Help::Help(
  const std::string& program_name,
  const std::string& program_description,
  const std::vector<Option>& options,
  const std::vector<std::string> example_uses)
  : m_example_uses(example_uses),
    m_options(AddDefaultOptions(options)),
    m_program_description(program_description),
    m_program_name(program_name)
{

  #ifndef NDEBUG
  //checks if there are no short or long option occurring twice
  const std::size_t sz = m_options.size();
  for (std::size_t i=0; i!=sz-1; ++i)
  {
    const Option& a { m_options[i] };
    for (std::size_t j=i+1; j!=sz; ++j)
    {
      assert(j < m_options.size());
      const Option& b { m_options[j] };
      if (a.m_short == b.m_short
        || a.m_long == b.m_long)
      {
        TRACE(a.m_short);
        TRACE(a.m_long);
        TRACE(a.m_description);
        TRACE(b.m_short);
        TRACE(b.m_long);
        TRACE(b.m_description);
      }
      assert(a.m_short != b.m_short
        && "Every short option must be unique");
      assert(a.m_long != b.m_long
        && "Every long option must be unique");
    }
  }
  #endif
}

const std::vector<ribi::Help::Option> ribi::Help::AddDefaultOptions(const std::vector<Option>& options)
{
  //v: unpadded Options
  std::vector<Option> v { options };
  v.push_back(Option('a',"about","display about message"));
  v.push_back(Option('h',"help","display this help message"));
  v.push_back(Option('i',"history","display version history"));
  v.push_back(Option('l',"licence","display licence"));
  v.push_back(Option('v',"version","display version"));

  //Find the longest long option, for padding
  const int max_length {
    static_cast<int>(
      std::max_element(
        v.begin(), v.end(),
        [](const Option& lhs, const Option& rhs)
        {
          return lhs.m_long.size() < rhs.m_long.size();
        }
      )->m_long.size()
    )
  };
  //w: padded options
  std::vector<Option> w;
  for (Option& p: v)
  {
    const int sz = static_cast<int>(p.m_long.size());
    assert(max_length >= sz);
    const int n_spaces = max_length - sz;
    assert(n_spaces >= 0);
    const std::string s = p.m_long
      + (n_spaces > 0 ? std::string(n_spaces,' '): std::string());
    assert(max_length == static_cast<int>(s.size()));
    const Option q(p.m_short,s,p.m_description);
    w.push_back(q);
  }

  //Sorts by short option
  //Also checks if there are no short or long option occurring twice
  std::sort(
    w.begin(),w.end(),
    [](const Option& lhs, const Option& rhs)
      {
        #ifndef NDEBUG
        if (lhs.m_short == rhs.m_short
          || lhs.m_long == rhs.m_long)
        {
          TRACE(lhs.m_short);
          TRACE(lhs.m_long);
          TRACE(lhs.m_description);
          TRACE(rhs.m_short);
          TRACE(rhs.m_long);
          TRACE(rhs.m_description);
        }
        #endif
        assert(lhs.m_short != rhs.m_short
          && "Every short option must be unique");
        assert(lhs.m_long != rhs.m_long
          && "Every long option must be unique");
        return lhs.m_short < rhs.m_short;
      }
    );

  return w;
}



std::ostream& ribi::operator<<(std::ostream& os, const Help& help)
{
  os
    << help.GetProgramName() << " help menu\n"
    << "\n"
    << help.GetProgramDescription() << "\n"
    << "\n"
    << "Allowed options for " << help.GetProgramName() << ":\n";
  for (const Help::Option& p: help.GetOptions())
  {
    os << "-" << p.m_short << ", --" << p.m_long << "  " << p.m_description << '\n';
  }
  os
    << "\n"
    << "Example uses:\n";
  for (const std::string& s: help.GetExampleUses())
  {
    os << "  " << s << '\n';
  }
  return os;
}
