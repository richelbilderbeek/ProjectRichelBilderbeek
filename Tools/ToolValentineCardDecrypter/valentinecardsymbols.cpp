#include "valentinecardsymbols.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include "trace.h"
#include "valentinecardsymbol.h"
#pragma GCC diagnostic pop

const std::vector<ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::CreateAll() const noexcept
{
  std::vector<ValentineCardSymbol> v;
  for (int i=0; i!=27; ++i)
  {
    ValentineCardSymbol symbol(i);
    v.push_back(symbol);
  }
  TRACE(v.size());
  return v;
}

const boost::bimap<char,ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::CreateAlphabet() const noexcept
{
  const std::vector<ValentineCardSymbol> v { CreateAll() };
  boost::bimap<char,ribi::ValentineCardSymbol> m;

  for (int i=0; i!=26; ++i)
  {
    const char my_char = 'a' + i;
    m.insert(boost::bimap<char,ribi::ValentineCardSymbol>::value_type(
      my_char,v[i]));
  }
  return m;
}

const std::vector<ribi::ValentineCardSymbol> ribi::ValentineCardSymbols::TextToSymbols(const std::string& s) const noexcept
{
  boost::bimap<char,ValentineCardSymbol> alphabet {
    ValentineCardSymbols::CreateAlphabet()
  };
  {
    assert(alphabet.left.find('?') == alphabet.left.end());
    const char my_char = '?';
    assert(26 < CreateAll().size());
    alphabet.insert(boost::bimap<char,ValentineCardSymbol>::value_type(
      my_char,CreateAll()[26])
    );
    assert(alphabet.left.find('?') != alphabet.left.end());
  }
  {
    assert(alphabet.left.find(' ') == alphabet.left.end());
    const char my_char = ' ';
    ribi::ValentineCardSymbol s( {false,false,false,false},ValentineCardSymbol::CenterSymbol::none );
    alphabet.insert(boost::bimap<char,ValentineCardSymbol>::value_type(
      my_char,s)
    );
    assert(alphabet.left.find(' ') != alphabet.left.end());
  }

  std::vector<ValentineCardSymbol> v;
  for (char c: s)
  {
    if (c == ' ')
    {
      assert(alphabet.left.find(' ') != alphabet.left.end());
      v.push_back( (*alphabet.left.find(' ')).second);
      continue;
    }
    const char d = std::tolower(c);
    if (d < 'a' || d > 'z')
    {
      assert(alphabet.left.find('?') != alphabet.left.end());
      v.push_back( (*alphabet.left.find('?')).second);
      continue;
    }
    assert(alphabet.left.find(d) != alphabet.left.end());
    v.push_back( (*alphabet.left.find(d)).second);
  }

  return v;
}
