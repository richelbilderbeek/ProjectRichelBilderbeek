#include <cassert>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
const std::string StrToXml(
  const std::string& tag_name,
  const std::string& content)
{
  std::stringstream s;
  s << "<"  << tag_name << ">" << content << "</" << tag_name << ">";
  //No test here, as StrToXml is used in testing XmlToStr
  return s.str();
}

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with StrToXml
const std::pair<std::string,std::string> XmlToStr(const std::string& s)
{
  assert(!s.empty());
  assert(s[0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);
  const int tag_name_sz = static_cast<int>(s.find('>')) - 1;
  const std::string tag_name = s.substr(1,tag_name_sz);

  assert(s.find_last_of('/') != std::string::npos);
  const int content_sz = static_cast<int>(s.find_last_of('/')) - tag_name_sz - 3;
  const std::string content = s.substr(tag_name.size() + 2,content_sz);
  const std::pair<std::string,std::string> p { tag_name, content };
  assert(StrToXml(p.first,p.second) == s);
  return p;
}


int main()
{
  const std::vector<std::string> v { "a", "ab", "abc", " ", "" };
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    const std::string tag_name = v[i];
    for (std::size_t j=0; j!=sz; ++j)
    {
      const std::string content = v[j];
      const std::string xml = StrToXml(tag_name,content);
      assert(XmlToStr(xml).first  == tag_name);
      assert(XmlToStr(xml).second == content);
    }
  }
}
