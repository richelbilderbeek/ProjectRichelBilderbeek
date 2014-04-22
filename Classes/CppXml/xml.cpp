//---------------------------------------------------------------------------
/*
XML functions
Copyright (C) 2014-2014 Richel Bilderbeek

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
#include "xml.h"

#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include "trace.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppCanLexicalCast.htm
template <class TargetType, class SourceType>
bool CanLexicalCast(const SourceType& from)
{
  try
  {
    boost::lexical_cast<TargetType>(from);
  }
  catch (boost::bad_lexical_cast)
  {
    return false;
  }
  catch (...)
  {
    assert(!"Something unexpected happened");
    throw;
  }
  return true;
}

std::string ribi::xml::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::xml::GetVersionHistory() noexcept
{
  return {
    "201x-xx-xx: Version 1.0: initial version",
    "2014-02-27: Version 1.1: started versioning"
  };
}

std::vector<std::string> ribi::xml::SplitXml(const std::string& s)
{
  std::vector<std::string> v;
  std::string::const_iterator i = s.begin();
  std::string::const_iterator j = s.begin();
  const std::string::const_iterator end = s.end();
  while (j!=end)
  {
    ++j;
    if ((*j=='>' || *j == '<') && std::distance(i,j) > 1)
    {
      std::string t;
      std::copy(
        *i=='<' ? i   : i+1,
        *j=='>' ? j+1 : j,
        std::back_inserter(t));
      v.push_back(t);
      i = j;
    }
  }
  return v;
}

std::string ribi::xml::StripXmlTag(const std::string& s)
{
  if (s.empty()) return "";
  if (s[0]!='<') return "";
  if (s[s.size() - 1]!='>') return "";
  const int begin = s.find_first_of('>');
  if (begin == static_cast<int>(std::string::npos)) return "";
  const int end = s.find_last_of('<');
  if (end == static_cast<int>(std::string::npos)) return "";
  if (begin > end) return "";
  assert(begin < end);
  const std::string tag_left = s.substr(0,begin+1);
  assert(!tag_left.empty());
  assert(tag_left[0] == '<');
  assert(tag_left[tag_left.size() - 1] == '>');
  const std::string tag_left_text = tag_left.substr(1,tag_left.size() - 2);
  if (tag_left_text.empty()) return "";
  const std::string tag_right = s.substr(end,s.size() - end);
  if (tag_right.size() < 2) return "";
  assert(!tag_right.empty());
  assert(tag_right[0] == '<');
  assert(tag_right[tag_right.size() - 1] == '>');
  const std::string tag_right_text = tag_right.substr(2,tag_right.size() - 3);
  if (tag_right_text.empty()) return "";
  if (tag_left_text != tag_right_text) return "";
  const std::string text = s.substr(begin + 1,end - begin - 1);
  return text;
}

#ifndef NDEBUG
void ribi::xml::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //StripXmlTag
  {
    assert(StripXmlTag("<my_tag>text</my_tag>") == "text");
    assert(StripXmlTag("<mytag>text</mytag>") == "text");
    assert(StripXmlTag("<tags>text</tags>") == "text");
    assert(StripXmlTag("<tag>text</tag>") == "text");
    assert(StripXmlTag("<tg>text</tg>") == "text");
    assert(StripXmlTag("<t>text</t>") == "text");
    assert(StripXmlTag("<x>y</x>") == "y");
    assert(StripXmlTag("<x>y</x></x>") == "y</x>");
    assert(StripXmlTag("<x><x>y</x>") == "<x>y");
    assert(StripXmlTag("<x><x>y</x></x>") == "<x>y</x>");
    assert(StripXmlTag("<x>y</z>") == "");
    assert(StripXmlTag("<x>y<x>") == "");
    assert(StripXmlTag("<>y<>") == "");
    assert(StripXmlTag("<>y</>") == "");
    assert(StripXmlTag("<x>y") == "");
    assert(StripXmlTag("<x></x>") == "");
  }
  //StrToXml and XmlToStr
  {
    const std::vector<std::string> v { "a", "ab", "abc", " ", "" };
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const std::string tag_name = v[i];
      for (std::size_t j=0; j!=sz; ++j)
      {
        const std::string content = v[j];
        const std::string xml = ToXml(tag_name,content);
        assert(FromXml(xml).first  == tag_name);
        assert(FromXml(xml).second == content);
      }
    }
  }
  //MapToXml
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
      const std::string xml = MapToXml(tag_name,m);

      //Convert XML back to map
      const std::function<KeyType(const std::string&)>& str_to_key_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<KeyType>(s));
          return boost::lexical_cast<KeyType>(s);
        }
      };
      const std::function<ValueType(const std::string&)>& str_to_value_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<ValueType>(s));
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
      std::stringstream s;
      s << MapToXml(p.first,p.second);
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
      const std::string xml = MapToXml(tag_name,m);

      //Convert XML back to map
      const std::function<KeyType(const std::string&)>& str_to_key_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<KeyType>(s));
          return boost::lexical_cast<KeyType>(s);
        }
      };
      const std::function<ValueType(const std::string&)>& str_to_value_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<ValueType>(s));
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
      std::stringstream s;
      s << MapToXml(p.first,p.second) << '\n';
    }

    //Use int to boost::shared_ptr<const std::string> map
    {
      //Create a map
      typedef std::string TagType;
      typedef int KeyType;
      typedef boost::shared_ptr<const std::string> ValueType;
      const TagType tag_name { "integers again" };
      std::map<KeyType,ValueType> m;
      m.insert(
        std::make_pair(
          1,
          boost::make_shared<const std::string>("one" )
        )
      );
      m.insert( std::make_pair(4,boost::make_shared<const std::string>("four")) );
      m.insert( std::make_pair(9,boost::make_shared<const std::string>("nine")) );

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
          assert(CanLexicalCast<std::string>(key));
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
      //const std::function<TagType(const std::string&)>& str_to_tag_function {
      //  [](const std::string& s)
      //  {
      //    return s;
      //  }
      //};
      const std::function<KeyType(const std::string&)>& str_to_key_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<KeyType>(s));
          return boost::lexical_cast<KeyType>(s);
        }
      };
      const std::function<ValueType(const std::string&)>& str_to_value_function {
        [](const std::string& s)
        {
          return boost::make_shared<const std::string>(s);
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
      std::stringstream s;
      s << MapToXml(tag_name,m,tag_to_str_function,key_to_str_function,value_to_str_function);
    }

  }

  //SetToXml and XmlToSet
  {
    const std::set<std::string> content { "cats", "dog", "zebrafinch" };
    const std::string tag_name = "animals";
    const std::string xml = ToXml(tag_name,content.begin(),content.begin());
    //const std::pair<std::string,std::set<std::string>> p { XmlToSet(xml) };
    //assert(p.first == tag_name);
    //assert(p.second == content);
  }
  //ToXml and FromXml
  {
    //tag: std::string, content: std::string
    {
      typedef std::string TagType;
      typedef std::string ContentType;
      const TagType     tag_name { "name"  };
      const ContentType content  { "Kitty" };
      const std::string xml { ToXml(tag_name,content) };
      const std::pair<TagType,ContentType> p { FromXml<TagType,ContentType>(xml) };
      assert(p.first  == tag_name);
      assert(p.second == content);
    }
    //tag: int, content: std::string
    {
      typedef int TagType;
      typedef std::string ContentType;
      const TagType     tag_name { 42  };
      const ContentType content  { "The answer" };
      const std::string xml { ToXml(tag_name,content) };
      const std::pair<TagType,ContentType> p { FromXml<TagType,ContentType>(xml) };
      assert(p.first  == tag_name);
      assert(p.second == content);
    }
    //tag: int, content: std::string
    {
      typedef int ContentType;
      typedef std::string TagType;
      const TagType     tag_name { "The answer" };
      const ContentType content  { 42 };
      const std::string xml { ToXml(tag_name,content) };
      const std::pair<TagType,ContentType> p { FromXml<TagType,ContentType>(xml) };
      assert(p.first  == tag_name);
      assert(p.second == content);
    }
    //tag: int, content: int
    {
      typedef std::string TagType;
      typedef int ContentType;
      const TagType     tag_name { 123 };
      const ContentType content  { 456 };
      const std::string xml { ToXml(tag_name,content) };
      const std::pair<TagType,ContentType> p { FromXml<TagType,ContentType>(xml) };
      assert(p.first  == tag_name);
      assert(p.second == content);
    }
    //tag: std::string, content: boost::shared_ptr<const std::string>
    {
      typedef std::string TagType;
      typedef boost::shared_ptr<const std::string> ContentType;
      const TagType     tag_name { "name" };
      const ContentType content  { boost::make_shared<const std::string>("Kitty") };

      //Convert tag and content to XML
      const std::function<std::string(const TagType&)> tag_to_str_function {
        [](const TagType& t) { return t; }
      };
      const std::function<std::string(const ContentType&)> content_to_str_function {
        [](const ContentType& c) { return *c; }
      };

      const std::string xml {
        ToXml(tag_name,content,tag_to_str_function,content_to_str_function)
      };

      //Convert XML back to its tag and content
      //with custom functions
      const std::function<TagType(const std::string&)> str_to_tag_function {
        [](const std::string& s) { return s; }
      };
      const std::function<ContentType(const std::string&)> str_to_content_function {
        [](const std::string& s) { return boost::make_shared<const std::string>(s); }
      };

      //Check both conversion functions
      //Cannot simply compare to tag_name and content, as these may be of any type
      assert(tag_to_str_function(str_to_tag_function(tag_to_str_function(tag_name)))
        ==   tag_to_str_function(                                        tag_name));
      assert(content_to_str_function(str_to_content_function(content_to_str_function(content)))
        ==   content_to_str_function(                                                content));

      const std::pair<TagType,ContentType> p {
        FromXml<TagType,ContentType>(
          xml,
          str_to_tag_function,
          str_to_content_function
        )
      };

      //Cannot simply compare to tag_name and content, as these may be of any type
      assert(tag_to_str_function(    p.first ) == tag_to_str_function(    tag_name));
      assert(content_to_str_function(p.second) == content_to_str_function(content ));
    }

    //tag: int, content: boost::shared_ptr<const std::string>
    {
      typedef int TagType;
      typedef boost::shared_ptr<const std::string> ContentType;
      const TagType     tag_name { 123 };
      const ContentType content  { boost::make_shared<const std::string>("one-two-three") };

      //Convert tag and content to XML
      const std::function<std::string(const TagType&)> tag_to_str_function {
        [](const TagType& t)
        {
          assert(CanLexicalCast<std::string>(t));
          return boost::lexical_cast<std::string>(t);
        }
      };
      const std::function<std::string(const ContentType&)> content_to_str_function {
        [](const ContentType& c) { return *c; }
      };

      const std::string xml {
        ToXml(tag_name,content,tag_to_str_function,content_to_str_function)
      };

      //Convert XML back to its tag and content
      //with custom functions
      const std::function<TagType(const std::string&)> str_to_tag_function {
        [](const std::string& s)
        {
          assert(CanLexicalCast<TagType>(s));
          return boost::lexical_cast<TagType>(s);
        }
      };
      const std::function<ContentType(const std::string&)> str_to_content_function {
        [](const std::string& s) { return boost::make_shared<const std::string>(s); }
      };

      //Check both conversion functions
      //Cannot simply compare to tag_name and content, as these may be of any type
      assert(tag_to_str_function(str_to_tag_function(tag_to_str_function(tag_name)))
        ==   tag_to_str_function(                                        tag_name));
      assert(content_to_str_function(str_to_content_function(content_to_str_function(content)))
        ==   content_to_str_function(                                                content));

      const std::pair<TagType,ContentType> p {
        FromXml<TagType,ContentType>(
          xml,
          str_to_tag_function,
          str_to_content_function
        )
      };

      //Cannot simply compare to tag_name and content, as these may be of any type
      assert(tag_to_str_function(    p.first ) == tag_to_str_function(    tag_name));
      assert(content_to_str_function(p.second) == content_to_str_function(content ));
    }
  }
  //VectorToXml and XmlToVector
  {
    const std::vector<std::string> content { "cats", "dog", "zebrafinch" };
    const std::string tag_name = "animals";
    const std::string xml = VectorToXml(tag_name,content);
    assert(xml == "<animals><0>cats</0><1>dog</1><2>zebrafinch</2></animals>");
    assert(xml == ToXml(tag_name,content.begin(),content.end()));
    const std::pair<std::string,std::vector<std::string>> p { XmlToVector(xml) };
    assert(p.first == tag_name);
    assert(p.second == content);
  }
  //XmlToPretty
  {
    {
      const std::vector<std::string> result {
        XmlToPretty("<a>test</a>")
      };
      const std::vector<std::string> expected {
        "<a>",
        "test",
        "</a>"
      };
      //std::copy(result.begin(),result.end(),std::ostream_iterator<std::string>(std::cerr,"\n"));
      assert(result == expected);
    }
    {
      const std::vector<std::string> result {
        XmlToPretty("<a><b>test</b></a>")
      };
      const std::vector<std::string> expected {
        "<a>",
        "  <b>",
        "  test",
        "  </b>",
        "</a>"
      };
      //std::copy(result.begin(),result.end(),std::ostream_iterator<std::string>(std::cerr,"\n"));
      assert(result == expected);
    }
    {
      const std::vector<std::string> result {
        XmlToPretty("<a><b>this is</b><c>a test</c></a>")
      };
      const std::vector<std::string> expected {
        "<a>",
        "  <b>",
        "  this is",
        "  </b>",
        "  <c>",
        "  a test",
        "  </c>",
        "</a>"
      };
      //std::copy(result.begin(),result.end(),std::ostream_iterator<std::string>(std::cerr,"\n"));
      assert(result == expected);
    }
  {
    const std::string s = "<a>A</a>";
    const std::vector<std::string> split = SplitXml(s);
    const std::vector<std::string> split_expected
      =
      {
        "<a>",
        "A",
        "</a>"
      };
    assert(split == split_expected);
    const std::vector<std::string> pretty = XmlToPretty(s);
    const std::vector<std::string> pretty_expected
      =
      {
        "<a>",
        "A",
        "</a>"
      };
    assert(pretty == pretty_expected);
  }
  {
    const std::string s = "<a>A<b>B</b></a>";
    const std::vector<std::string> split = SplitXml(s);
    const std::vector<std::string> split_expected
      =
      {
        "<a>",
        "A",
        "<b>",
        "B",
        "</b>",
        "</a>"
      };
    assert(split == split_expected);
    const std::vector<std::string> pretty = XmlToPretty(s);
    const std::vector<std::string> pretty_expected
      =
      {
        "<a>",
        "A",
        "  <b>",
        "  B",
        "  </b>",
        "</a>"
      };
    assert(pretty == pretty_expected);
  }
  {
    const std::string s = "<a>A<b>B1</b><b>B2</b></a>";
    const std::vector<std::string> split = SplitXml(s);
    const std::vector<std::string> split_expected
      =
      {
        "<a>",
        "A",
        "<b>",
        "B1",
        "</b>",
        "<b>",
        "B2",
        "</b>",
        "</a>"
      };
    assert(split == split_expected);
    const std::vector<std::string> pretty = XmlToPretty(s);
    const std::vector<std::string> pretty_expected
      =
      {
        "<a>",
        "A",
        "  <b>",
        "  B1",
        "  </b>",
        "  <b>",
        "  B2",
        "  </b>",
        "</a>"
      };
    assert(pretty == pretty_expected);
  }
  }
}
#endif


std::vector<std::string> ribi::xml::XmlToPretty(const std::string& s) noexcept
{
  std::vector<std::string> v = SplitXml(s);
  int n = -2;
  for (std::string& s: v)
  {
    assert(!s.empty());
    if (s[0] == '<' && s[1] != '/')
    {
      n+=2;
    }
    assert(n >= 0);
    s = std::string(n,' ') + s;
    if (s[n+0] == '<' && s[n+1] == '/')
    {
      n-=2;
    }
  }
  return v;
}

/*
const std::pair<std::string,std::string> ribi::xml::XmlToStr(const std::string& s)
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
  assert(ToXml(p.first,p.second) == s);
  return p;
}
*/

std::pair<std::string,std::vector<std::string>> ribi::xml::XmlToVector(
  const std::string& s)
{
  assert(!s.empty());
  assert(s[           0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);

  //Read the name tag
  //<tag_name>...</tag_name>
  const std::pair<std::string,std::string> p = FromXml(s);
  const std::string tag_name = p.first;
  std::vector<std::string> content;

  //Remove the name tags
  //std::string t = s.substr(tag_name_sz + 2,s.size() - (2 * tag_name_sz) - 5);
  std::string t = p.second;
  for (int i=0; !t.empty(); ++i)
  {
    //Read the index tags and item
    //<index>item</index>
    assert(!t.empty());
    assert(t[0] == '<');
    assert(t[t.size() - 1] == '>');
    assert(t.find('>') != std::string::npos);
    const int index_tag_sz = static_cast<int>(t.find('>')) - 1;
    const std::string index_tag = t.substr(1,index_tag_sz);
    #ifndef NDEBUG
    if (!CanLexicalCast<int>(index_tag))
    {
      TRACE("ERROR");
      TRACE(t);
      TRACE(index_tag);
    }
    #endif
    assert(CanLexicalCast<int>(index_tag));
    assert(i == boost::lexical_cast<int>(index_tag));
    assert(t.find('/') != std::string::npos);
    const int item_sz = static_cast<int>(t.find('/')) - index_tag_sz - 3;
    const std::string item = t.substr(index_tag.size() + 2,item_sz);

    const int total_sz = (2 * index_tag_sz) + item_sz + 5;
    t = t.substr(total_sz,t.size() - total_sz);

    content.push_back(item);
  }
  assert(VectorToXml(tag_name,content) == s);
  return std::make_pair(tag_name,content);
}

