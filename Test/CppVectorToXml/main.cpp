#include <cassert>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

///Convert a std::vector to single-line XML
///For example, a std::vector with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with XmlToVector
const std::string VectorToXml(
  const std::vector<std::string>& v,
  const std::string& name)
{
  std::stringstream s;
  s << "<" << name << ">";
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    s << "<"  << i << ">" << v[i] << "</" << i << ">";

  }
  s << "</" << name << ">";
  return s.str();
}

///Convert a single-line XML to a std::vector and its name
///For example, the XML line "<animals><0>cat</0><1>dog</1></animals>"
///becomes a std::vector with elements {"cat","dog"} and the name "animals"
///The data can be converted back with VectorToXml
const std::pair<std::vector<std::string>,std::string> XmlToVector(
  const std::string& s)
{
  assert(!s.empty());
  assert(s[           0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);

  //Read the name tag
  //<name>...</name>
  const int name_sz = static_cast<int>(s.find('>')) - 1;
  const std::string name = s.substr(1,name_sz);

  std::vector<std::string> v;

  //Remove the name tags
  std::string t = s.substr(name_sz + 2,s.size() - (2 * name_sz) - 5);
  for (int i=0; !t.empty(); ++i)
  {
    //Read the index tags and item
    //<index>item</index>
    assert(!t.empty());
    assert(t[0] == '<');
    assert(t[t.size() - 1] == '>');
    assert(t.find('>') != std::string::npos);
    const int index_sz = static_cast<int>(t.find('>')) - 1;
    const std::string index = t.substr(1,index_sz);
    assert(i == boost::lexical_cast<int>(index));
    assert(t.find('/') != std::string::npos);
    const int item_sz = static_cast<int>(t.find('/')) - index_sz - 3;
    const std::string item = t.substr(index.size() + 2,item_sz);

    const int total_sz = (2 * index_sz) + item_sz + 5;
    t = t.substr(total_sz,t.size() - total_sz);

    v.push_back(item);
  }
  return std::make_pair(v,name);
}

int main()
{
  const std::vector<std::string> v { "cats", "dog", "zebrafinch" };
  const std::string name = "animals";
  const std::string s = VectorToXml(v,name);
  const std::pair<std::vector<std::string>,std::string> p { XmlToVector(s) };
  assert(p.first == v);
  assert(p.second == name);
}
