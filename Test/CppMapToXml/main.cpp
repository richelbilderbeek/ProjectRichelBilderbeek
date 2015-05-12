#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

///Convert a std::string to single-line XML
///For example, a std::string with tag name "cat_name" and content "Kitty" becomes
/// <cat_name>Kitty</cat_name>
///The data can be converted back with XmlToStr
template <class T, class U>
const std::string ToXml(
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
const std::string ToXml(
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

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with ToXml
template <class T = std::string, class U = std::string>
const std::pair<T,U> FromXml(const std::string& xml)
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
const std::pair<T,U> FromXml(
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
const std::string MapToXml(
  const TagType& tag_name,
  const std::map<KeyType,ValueType> m,
  const std::function<std::string(const TagType&  )> tag_to_str_function,
  const std::function<std::string(const KeyType&  )> key_to_str_function,
  const std::function<std::string(const ValueType&)> value_to_str_function
  )
{
  std::stringstream s;
  const auto end = std::end(m);
  for (auto begin = std::begin(m); begin!=end; ++begin)
  {
    s << ToXml( (*begin).first, (*begin).second, key_to_str_function, value_to_str_function);
  }
  const std::string content { s.str() };
  return ToXml(tag_to_str_function(tag_name),content);
}

///Convert a single-line XML to a map
///The data can be converted back with MapToXml
template <class KeyType, class ValueType>
const std::pair<std::string,std::map<KeyType,ValueType>> XmlToMap(
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

int main()
{
  //Use int to std::string map
  {
    //Create a map
    typedef int KeyType;
    typedef std::string ValueType;
    std::map<KeyType,ValueType> m;
    m.insert( std::make_pair(1,"one") );
    m.insert( std::make_pair(2,"two") );
    m.insert( std::make_pair(4,"four") );

    const std::string tag_name = "integers";

    //Convert map to XML
    const std::string xml = MapToXml(tag_name,m.begin(),m.end());

    //Convert XML back to map
    const std::function<KeyType(const std::string&)>& str_to_key_function {
      [](const std::string& s)
      {
        return boost::lexical_cast<KeyType>(s);
      }
    };
    const std::function<ValueType(const std::string&)>& str_to_value_function {
      [](const std::string& s)
      {
        return boost::lexical_cast<ValueType>(s);
      }
    };
    const std::pair<std::string,std::map<KeyType,ValueType>> p {
      XmlToMap<KeyType,ValueType>(xml,str_to_key_function,str_to_value_function)
    };
    assert(p.first == tag_name);
    assert(p.second.size() == m.size());
    assert(std::equal(m.begin(),m.end(),p.second.begin()));
    //Again convert pointers to XML
    std::cout << MapToXml(p.first,p.second.begin(),p.second.end()) << '\n';
  }
  //Use std::string to int map
  {
    //Create a map
    typedef std::string KeyType;
    typedef int ValueType;
    std::map<KeyType,ValueType> m;
    m.insert( std::make_pair("one",1) );
    m.insert( std::make_pair("two",2) );
    m.insert( std::make_pair("four",4) );

    const std::string tag_name = "integers";

    //Convert map to XML
    const std::string xml = MapToXml(tag_name,m.begin(),m.end());

    //Convert XML back to map
    const std::function<KeyType(const std::string&)>& str_to_key_function {
      [](const std::string& s)
      {
        return boost::lexical_cast<KeyType>(s);
      }
    };
    const std::function<ValueType(const std::string&)>& str_to_value_function {
      [](const std::string& s)
      {
        return boost::lexical_cast<ValueType>(s);
      }
    };
    const std::pair<std::string,std::map<KeyType,ValueType>> p {
      XmlToMap<KeyType,ValueType>(xml,str_to_key_function,str_to_value_function)
    };
    assert(p.first == tag_name);
    assert(p.second.size() == m.size());
    assert(std::equal(m.begin(),m.end(),p.second.begin()));
    //Again convert pointers to XML
    std::cout << MapToXml(p.first,p.second.begin(),p.second.end()) << '\n';
  }

  //Use int to boost::shared_ptr<const std::string> map
  {
    //Create a map
    typedef std::string TagType;
    typedef int KeyType;
    typedef boost::shared_ptr<const std::string> ValueType;
    const TagType tag_name { "integers again" };
    std::map<KeyType,ValueType> m;
    m.insert( std::make_pair(1,boost::shared_ptr<const std::string>(new std::string("one" )) ));
    m.insert( std::make_pair(4,boost::shared_ptr<const std::string>(new std::string("four")) ));
    m.insert( std::make_pair(9,boost::shared_ptr<const std::string>(new std::string("nine")) ));

    //Convert map to XML
    const std::function<std::string(const TagType&)> tag_to_str_function {
      [](const TagType& tag)
      {
        return tag;
      }
    };
    const std::function<std::string(const KeyType&  )> key_to_str_function {
      [](const KeyType& key)
      {
        return boost::lexical_cast<std::string>(key);
      }
    };
    const std::function<std::string(const ValueType&)> value_to_str_function {
      [](const ValueType& value)
      {
        return *value;
      }
    };

    const std::string xml {
      MapToXml(tag_name,m,tag_to_str_function,key_to_str_function,value_to_str_function)
    };

    //Convert XML back to map
    const std::function<TagType(const std::string&)>& str_to_tag_function {
      [](const std::string& s)
      {
        return s;
      }
    };
    const std::function<KeyType(const std::string&)>& str_to_key_function {
      [](const std::string& s)
      {
        return boost::lexical_cast<KeyType>(s);
      }
    };
    const std::function<ValueType(const std::string&)>& str_to_value_function {
      [](const std::string& s)
      {
        return boost::shared_ptr<const std::string>(new std::string(s));
      }
    };
    const std::pair<std::string,std::map<KeyType,ValueType>> p {
      XmlToMap<KeyType,ValueType>(xml,str_to_key_function,str_to_value_function)
    };
    assert(p.first == tag_name);
    assert(p.second.size() == m.size());
    assert(
      std::equal(m.begin(),m.end(),p.second.begin(),
        [key_to_str_function,value_to_str_function](
          const std::pair<KeyType,ValueType>& lhs, const std::pair<KeyType,ValueType>& rhs)
        {
          return key_to_str_function(lhs.first) == key_to_str_function(rhs.first)
            && value_to_str_function(lhs.second) == value_to_str_function(rhs.second);
        }
      )
    );
    //Again convert pointers to XML
    std::cout
      << MapToXml(tag_name,m,tag_to_str_function,key_to_str_function,value_to_str_function)
      << '\n';
  }

}

/* Screen output

<integers><1>one</1><2>two</2><4>four</4></integers>
<integers><four>4</four><one>1</one><two>2</two></integers>
<integers again><1>one</1><4>four</4><9>nine</9></integers again>
Press <RETURN> to close this window...

*/
