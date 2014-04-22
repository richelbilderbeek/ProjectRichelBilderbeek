#include <cassert>
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
  const std::function<std::string(const U&)> tag_to_content_function
  )
{
  std::stringstream s;
  s
    << "<"  << tag_to_str_function(tag_name) << ">"
    << tag_to_content_function(content)
    << "</" << tag_to_str_function(tag_name) << ">";
  //No test here, as ToXml is used in testing FromXml
  return s.str();
}

///Convert a single-line XML to its content and its tag name
///For example, the XML line "<cat_name>Kitty</cat_name>"
///becomes a std::pair with elements {"cat_name","Kitty"}
///The data can be converted back with ToXml
template <class T, class U>
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


int main()
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
    const ContentType content  { boost::shared_ptr<const std::string>(new std::string("Kitty")) };

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
      [](const std::string& s) { return boost::shared_ptr<const std::string>(new std::string(s)); }
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
    const ContentType content  { boost::shared_ptr<const std::string>(new std::string("one-two-three")) };

    //Convert tag and content to XML
    const std::function<std::string(const TagType&)> tag_to_str_function {
      [](const TagType& t) { return boost::lexical_cast<std::string>(t); }
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
      [](const std::string& s) { return boost::lexical_cast<TagType>(s); }
    };
    const std::function<ContentType(const std::string&)> str_to_content_function {
      [](const std::string& s) { return boost::shared_ptr<const std::string>(new std::string(s)); }
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
