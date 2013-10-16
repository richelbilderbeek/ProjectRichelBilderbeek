#ifndef RIBI_XML_H
#define RIBI_XML_H

#include <set>
#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

namespace ribi {

namespace xml {

///Convert a content and a tag name to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with FromXml
template <class T>
const std::string ToXml(
  const std::string& tag_name,
  const T& content)
{
  std::stringstream s;
  s << "<"  << tag_name << ">"
    << boost::lexical_cast<std::string>(content)
    << "</" << tag_name << ">";
  //No test here, as ToXml is used in testing FromXml
  return s.str();
}

///Convert a container to single-line XML
///For example, a std::vector<std::string> with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with FromXml
template <class Iter>
const std::string ToXml(
  const std::string& tag_name,
  Iter begin,
  const Iter& end)
{
  std::stringstream s;
  int i = 0;
  for ( ; begin!=end; ++begin)
  {
    const std::string index_tag_name = boost::lexical_cast<std::string>(i);
    const std::string index_content  = boost::lexical_cast<std::string>(*begin);
    s << ToXml(index_tag_name,index_content);
    ++i;
  }
  const std::string content = s.str();
  //No test here, as this function is used in XmlToVector
  return ToXml(tag_name,content);
}

///Convert a container of pointers to single-line XML
///For example, a std::vector<std::string> with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with FromXml
template <class Iter>
const std::string PtrsToXml(
  const std::string& tag_name,
  Iter begin,
  const Iter& end)
{
  std::stringstream s;
  int i = 0;
  for ( ; begin!=end; ++begin)
  {
    const std::string index_tag_name = boost::lexical_cast<std::string>(i);
    const std::string index_content  = boost::lexical_cast<std::string>( *(*begin) );
    s << ToXml(index_tag_name,index_content);
    ++i;
  }
  const std::string content = s.str();
  //No test here, as this function is used in XmlToVector
  return ToXml(tag_name,content);
}

template <class T>
const std::string MapToXml(
  const std::string& tag_name,
  T begin,
  const T& end)
{
  std::stringstream s;
  for ( ; begin!=end; ++begin)
  {
    s << ToXml( (*begin).first, (*begin).second);
  }
  const std::string content { s.str() };
  return ToXml(tag_name,content);
}


template <class T>
const std::string SetToXml(
  const std::string& tag_name,
  const std::set<T>& content)
{
  return ToXml(tag_name,content.begin(),content.end());
}

///Split an XML std::string into its parts
//From http://www.richelbilderbeek.nl/CppSplitXml.htm
const std::vector<std::string> SplitXml(const std::string& s);

///Strip the XML tags of an XML item
///For example '<tag>text</tag>' becomes 'text'
///Note that also '<any_tag>text</other_tag>' fails
//From http://www.richelbilderbeek.nl/CppStripXmlTag.htm
const std::string StripXmlTag(const std::string& s);

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
const std::string StrToXml(
  const std::string& tag,
  const std::string& content);

#ifndef NDEBUG
void Test() noexcept;
#endif




///Convert a std::vector to single-line XML
///For example, a std::vector with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with XmlToVector
template <class T>
const std::string VectorToXml(
  const std::string& tag_name,
  const std::vector<T>& v
)
{
  //No test here, as this function is used in XmlToVector
  return ToXml(tag_name,v.begin(),v.end());
}

///Pretty-print an XML std::string by indenting its elements
//From http://www.richelbilderbeek.nl/CppXmlToPretty.htm
const std::vector<std::string> XmlToPretty(const std::string& s);

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with StrToXml
const std::pair<std::string,std::string> XmlToStr(
  const std::string& s);

///Convert a single-line XML to a std::vector and its name
///For example, the XML line "<animals><0>cat</0><1>dog</1></animals>"
///becomes a std::vector with elements {"cat","dog"} and the name "animals"
///The data can be converted back with VectorToXml
const std::pair<std::string,std::vector<std::string>> XmlToVector(
  const std::string& s);

} //~namespace xml

} //~namespace ribi

#endif // RIBI_XML_H
