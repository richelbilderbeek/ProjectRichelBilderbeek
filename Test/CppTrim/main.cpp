#include <string>

///Trim leading and trailing whitespace
//From http://www.richelbilderbeek.nl/CppTrim.htm
std::string TrimStl(const std::string& s)
{
  const int size{static_cast<int>(s.size())};
  int pos_begin = -1;
  int pos_end = size-1;
  for (int i=0; i!=size; ++i)
  {
    if (s[i]!=' ' && s[i]!='\n' && s[i]!='\t')
    {
      pos_begin = i; break;
    }
  }
  if (pos_begin == -1) return "";
  for (int i=size-1; i!=-1; --i)
  {
    if (s[i]!=' ' && s[i]!='\n' && s[i]!='\t')
    {
      pos_end = i; break;
    }
  }
  return s.substr(pos_begin,pos_end-pos_begin+1);
}

#include <string>
#include <boost/algorithm/string/trim.hpp>

///Trim leading and trailing whitespace
//From http://www.richelbilderbeek.nl/CppTrim.htm
const std::string TrimBoost(const std::string& s)
{
  return boost::algorithm::trim_copy(s);
}

int main()
{
  assert(TrimStl(" abc ") == "abc");
  assert(TrimStl(" ab c ") != "abc");

  assert(TrimBoost(" abc ") == "abc");
  assert(TrimBoost(" ab c ") != "abc");
}
