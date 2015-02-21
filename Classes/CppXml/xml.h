//---------------------------------------------------------------------------
/*
XML functions
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppXml.htm
//---------------------------------------------------------------------------
#ifndef RIBI_XML_H
#define RIBI_XML_H

#include <map>
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

std::string GetVersion() noexcept;
std::vector<std::string> GetVersionHistory() noexcept;

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
template <class T, class U>
std::string ToXml(
  const T& tag_name,
  const U& content)
{
  std::stringstream s;
  s << "<"  << tag_name << ">" << content << "</" << tag_name << ">";
  //No test here, as ToXml is used in testing FromXml
  return s.str();
}

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
template <class T, class U>
std::string ToXml(
  const T& tag_name,
  const U& content,
  const std::function<std::string(const T&)> tag_to_str_function,
  const std::function<std::string(const U&)> content_to_str_function
  )
{
  std::stringstream s;
  s
    << "<"  << tag_to_str_function(tag_name) << ">"
    << content_to_str_function(content)
    << "</" << tag_to_str_function(tag_name) << ">";
  //No test here, as ToXml is used in testing FromXml
  return s.str();
}

///Convert a container to single-line XML
///For example, a std::vector<std::string> with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with FromXml
template <class Iter>
std::string ToXml(
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

//
//
// Above: order-dependent for compiling
// Below: alphabetic ordering
//
//

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with ToXml
template <class T = std::string, class U = std::string>
std::pair<T,U> FromXml(const std::string& xml)
{
  assert(!xml.empty());
  assert(xml[0] == '<');
  assert(xml[xml.size() - 1] == '>');
  assert(xml.find('>') != std::string::npos);
  const int tag_name_sz = static_cast<int>(xml.find('>')) - 1;
  const std::string tag_name = xml.substr(1,tag_name_sz);

  assert(xml.find_last_of('/') != std::string::npos);
  const int content_sz = static_cast<int>(xml.find_last_of('/')) - tag_name_sz - 3;
  const std::string content = xml.substr(tag_name.size() + 2,content_sz);
  const std::pair<T,U> p {
    boost::lexical_cast<T>(tag_name),
    boost::lexical_cast<U>(content)
  };
  assert(ToXml(p.first,p.second) == xml);
  return p;
}

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with ToXml
template <class T, class U>
std::pair<T,U> FromXml(
  const std::string& xml,
  const std::function<T(const std::string&)> str_to_tag_function,
  const std::function<U(const std::string&)> str_to_content_function
  )
{
  assert(!xml.empty());
  assert(xml[0] == '<');
  assert(xml[xml.size() - 1] == '>');
  assert(xml.find('>') != std::string::npos);
  const int tag_name_sz = static_cast<int>(xml.find('>')) - 1;
  const std::string tag_name = xml.substr(1,tag_name_sz);

  assert(xml.find_last_of('/') != std::string::npos);
  const int content_sz = static_cast<int>(xml.find_last_of('/')) - tag_name_sz - 3;
  const std::string content = xml.substr(tag_name.size() + 2,content_sz);
  const std::pair<T,U> p {
    str_to_tag_function(tag_name),
    str_to_content_function(content)
  };
  //Cannot do this debug check anymore, as one would need
  //a tag_to_str_function and content_to_str_function:
  //assert(ToXml(p.first,p.second,tag_to_str_function,content_to_str_function) == xml);
  return p;
}

///Convert a map to single-line XML
///For example, an int-to-string map of
/// {{1,"one"}, {2,"two"}, {4,"four"}} and tag name "numbers" becomes the following XML string:
///
/// <numbers>
///   <1>one</1>
///   <2>two</2>
///   <4>four</4>
/// </numbers>
///
/// <numbers>
///   <0><key>1</key><value>one</value></0>
///   <1><key>2</key><value>two</value></1>
///   <2><key>4</key><value>four</value></2>
/// </numbers>
///
///(indentation is added for readability)
///The data can be converted back with XmlToPtrs
template <
  class TagType = std::string,
  class KeyType = std::string,
  class ValueType = std::string>
std::string MapToXml(
  const TagType& tag_name,
  const std::map<KeyType,ValueType> m
  )
{
  std::stringstream s;
  const auto end = std::end(m);
  for (/* const */ auto begin = std::begin(m); begin!=end; ++begin)
  {
    s << ToXml( (*begin).first, (*begin).second);
  }
  const std::string content { s.str() };
  return ToXml(tag_name,content);
}


///Convert a map to single-line XML
///For example, an int-to-string map of
/// {{1,"one"}, {2,"two"}, {4,"four"}} and tag name "numbers" becomes the following XML string:
///
/// <numbers>
///   <1>one</1>
///   <2>two</2>
///   <4>four</4>
/// </numbers>
///
/// <numbers>
///   <0><key>1</key><value>one</value></0>
///   <1><key>2</key><value>two</value></1>
///   <2><key>4</key><value>four</value></2>
/// </numbers>
///
///(indentation is added for readability)
///The data can be converted back with XmlToPtrs
template <class TagType, class KeyType, class ValueType>
std::string MapToXml(
  const TagType& tag_name,
  const std::map<KeyType,ValueType> m,
  const std::function<std::string(const TagType&  )> tag_to_str_function,
  const std::function<std::string(const KeyType&  )> key_to_str_function,
  const std::function<std::string(const ValueType&)> value_to_str_function
  )
{
  std::stringstream s;
  const auto end = std::end(m);
  for (/* const */ auto begin = std::begin(m); begin!=end; ++begin)
  {
    s << ToXml( (*begin).first, (*begin).second, key_to_str_function, value_to_str_function);
  }
  const std::string content { s.str() };
  return ToXml(tag_to_str_function(tag_name),content);
}

///Convert a container of pointers to single-line XML
///For example, a std::vector<boost::shared_ptr<std::string>>
///dynamically allocated std::strings {"cat","dog"} and tag name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with XmlToPtrs
template <class Iter>
std::string PtrsToXml(
  const std::string& tag_name,
  Iter begin,
  const Iter& end
)
{
  std::stringstream s;
  int i = 0;
  for ( ; begin!=end; ++begin)
  {
    const std::string index_tag_name = boost::lexical_cast<std::string>(i);
    const std::string index_content  = boost::lexical_cast<std::string>( *(*begin) );
    s << ToXml(index_tag_name,index_content); //StrToXml
    ++i;
  }
  const std::string content = s.str();
  //No test here, as this function is used in XmlToPtrs
  return ToXml(tag_name,content); //StrToXml
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
std::vector<std::string> SplitXml(const std::string& s);

///Strip the XML tags of an XML item
///For example '<tag>text</tag>' becomes 'text'
///Note that also '<any_tag>text</other_tag>' fails
//From http://www.richelbilderbeek.nl/CppStripXmlTag.htm
std::string StripXmlTag(const std::string& s);

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
//const std::string StrToXml(
//  const std::string& tag_name,
//  const std::string& content)
//{
//  return ToXml(tag_name,content);
//}


#ifndef NDEBUG
void Test() noexcept;
#endif

///Convert a std::vector to single-line XML
///For example, a std::vector with elements {"cat","dog"} and name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with XmlToVector
template <class T>
std::string VectorToXml(
  const std::string& tag_name,
  const std::vector<T>& v
)
{
  //No test here, as this function is used in XmlToVector
  return ToXml(tag_name,v.begin(),v.end());
}

///Convert a single-line XML to a map
///The data can be converted back with MapToXml
template <class KeyType, class ValueType>
std::pair<std::string,std::map<KeyType,ValueType>> XmlToMap(
    const std::string& s,
    const std::function<KeyType(const std::string&)> str_to_key_function,
    const std::function<ValueType(const std::string&)> str_to_value_function
  )
{
  assert(!s.empty());
  assert(s[           0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);

  //Read the name tag
  //<name>...</name>
  const int tag_name_sz = static_cast<int>(s.find('>')) - 1;
  const std::string tag_name = s.substr(1,tag_name_sz);

  std::map<KeyType,ValueType> map;

  //Remove the name tags
  std::string t = s.substr(tag_name_sz + 2,s.size() - (2 * tag_name_sz) - 5);
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
    //assert(i == boost::lexical_cast<int>(index));
    assert(t.find('/') != std::string::npos);
    const int item_sz = static_cast<int>(t.find('/')) - index_sz - 3;
    const std::string item_str = t.substr(index.size() + 2,item_sz);
    const int total_sz = (2 * index_sz) + item_sz + 5;
    t = t.substr(total_sz,t.size() - total_sz);

    map.insert(
      std::make_pair(
        str_to_key_function(index),
        str_to_value_function(item_str)
      )
    );
  }
  //Cannot do the test below, as one would need a key_to_str_function and content_to_str_function
  //assert(MapToXml(tag_name,map.begin(),map.end(),key_to_str_function,content_to_str_function) == s);
  return std::make_pair(tag_name,map);
}

///Pretty-print an XML std::string by indenting its elements
//From http://www.richelbilderbeek.nl/CppXmlToPretty.htm
std::vector<std::string> XmlToPretty(const std::string& s) noexcept;

///Convert a single-line XML to a std::vector of smart pointers and its name
///For example, the XML line "<animals><0>cat</0><1>dog</1></animals>"
///becomes a std::vector of smart pointers of dynamically allocated strings
///with values {"cat","dog"} and the tag name "animals"
///The conversion from std::string to smart pointer needs to be supplied, for example
///a conversion from string to a smart pointer of a dynamically allocated string:
///
/// const std::function<const boost::shared_ptr<std::string>(const std::string&)> str_to_ptr_function {
///   [](const std::string& s)
///   {
///     return boost::make_shared<std::string>(s);
///   }
/// };
///
///The data can be converted back with PtrsToXml
template <class T>
std::pair<
    std::string,
    std::vector<boost::shared_ptr<T>>
  >
  XmlToPtrs(
    const std::string& s,
    const std::function<const boost::shared_ptr<T>(const std::string&)> str_to_ptr_function
  )
{
  assert(!s.empty());
  assert(s[           0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);

  //Read the name tag
  //<name>...</name>
  const int name_sz = static_cast<int>(s.find('>')) - 1;
  const std::string name = s.substr(1,name_sz);

  std::vector<boost::shared_ptr<T>> v;

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
    const std::string item_str = t.substr(index.size() + 2,item_sz);
    const int total_sz = (2 * index_sz) + item_sz + 5;
    t = t.substr(total_sz,t.size() - total_sz);

    const boost::shared_ptr<T> item { str_to_ptr_function(item_str) };
    v.push_back(item);
  }
  assert(PtrsToXml(name,v.begin(),v.end()) == s);
  return std::make_pair(name,v);
}

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with StrToXml
//const std::pair<std::string,std::string> XmlToStr(
//  const std::string& s);

///Convert a single-line XML to a std::vector and its name
///For example, the XML line "<animals><0>cat</0><1>dog</1></animals>"
///becomes a std::vector with elements {"cat","dog"} and the name "animals"
///The data can be converted back with VectorToXml
std::pair<std::string,std::vector<std::string>> XmlToVector(const std::string& s);

} //~namespace xml

} //~namespace ribi

#endif // RIBI_XML_H
