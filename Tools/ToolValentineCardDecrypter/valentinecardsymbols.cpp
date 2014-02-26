#include "valentinecardsymbols.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include "trace.h"
#include "valentinecardsymbol.h"
#pragma GCC diagnostic pop

const std::vector<boost::shared_ptr<ribi::ValentineCardSymbol>> ribi::ValentineCardSymbols::CreateAll() const noexcept
{
  std::vector<boost::shared_ptr<ValentineCardSymbol>> v;
  for (int i=0; i!=27; ++i)
  {
    const boost::shared_ptr<ValentineCardSymbol> symbol {
      new ValentineCardSymbol(i)
    };
    assert(symbol);
    v.push_back(symbol);
  }
  //TRACE(v.size());
  return v;
}

const boost::bimap<char,boost::shared_ptr<ribi::ValentineCardSymbol>> ribi::ValentineCardSymbols::CreateAlphabet() const noexcept
{
  const std::vector<boost::shared_ptr<ValentineCardSymbol>> v { CreateAll() };
  typedef char Left;
  typedef boost::shared_ptr<ribi::ValentineCardSymbol> Right;
  boost::bimap<Left,Right> m;

  for (int i=0; i!=26; ++i)
  {
    const char my_char = 'a' + i;
    assert(i < static_cast<int>(v.size()));
    m.insert(boost::bimap<Left,Right>::value_type(
      my_char,v[i]));
  }
  return m;
}

const std::vector<boost::shared_ptr<ribi::ValentineCardSymbol>> ribi::ValentineCardSymbols::TextToSymbols(const std::string& s) const noexcept
{
  typedef char Left;
  typedef boost::shared_ptr<ribi::ValentineCardSymbol> Right;
  boost::bimap<Left,Right> alphabet {
    ValentineCardSymbols().CreateAlphabet()
  };
  {
    assert(alphabet.left.find('?') == alphabet.left.end());
    const char my_char = '?';
    assert(26 < CreateAll().size());
    alphabet.insert(boost::bimap<Left,Right>::value_type(
      my_char,CreateAll()[26])
    );
    assert(alphabet.left.find('?') != alphabet.left.end());
  }
  {
    assert(alphabet.left.find(' ') == alphabet.left.end()
      && "alphabet must not yet contain a space"
    );
    const char my_char = ' ';
    const boost::shared_ptr<ValentineCardSymbol> s {
      new ValentineCardSymbol(
      {false,false,false,false},
      ValentineCardSymbol::CenterSymbol::none
      )
    };
    assert(s);
    alphabet.insert(boost::bimap<Left,Right>::value_type(
      my_char,s)
    );
    assert(alphabet.left.find(my_char) != alphabet.left.end()
      && "my_char should be in the alphabet now");
    assert(alphabet.left.find(' ') != alphabet.left.end()
      && "a space should be in the alphabet now");
  }

  std::vector<boost::shared_ptr<ValentineCardSymbol>> v;
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
