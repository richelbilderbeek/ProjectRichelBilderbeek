#include <cassert>
#include <functional>
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

///Convert a container of pointers to single-line XML
///For example, a std::vector<boost::shared_ptr<std::string>>
///dynamically allocated std::strings {"cat","dog"} and tag name "animals" becomes
/// <animals><0>cat</0><1>dog</1></animals>
///The data can be converted back with XmlToPtrs
template <class Iter>
const std::string PtrsToXml(
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
    s << StrToXml(index_tag_name,index_content);
    ++i;
  }
  const std::string content = s.str();
  //No test here, as this function is used in XmlToPtrs
  return StrToXml(tag_name,content);
}

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
///     return boost::shared_ptr<std::string>(new std::string(s));
///   }
/// };
///
///The data can be converted back with PtrsToXml
template <class T>
const std::pair<
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

int main()
{
  //Use int
  {
    //Create data consisting of pointers
    std::vector<boost::shared_ptr<int> > v;
    { const boost::shared_ptr<int> p { new int(1) }; v.push_back(p); }
    { const boost::shared_ptr<int> p { new int(4) }; v.push_back(p); }
    { const boost::shared_ptr<int> p { new int(9) }; v.push_back(p); }
    const std::string tag_name = "integers";

    //Convert pointers to XML
    const std::string xml = PtrsToXml(tag_name,v.begin(),v.end());

    //Convert XML back to pointers again
    const std::function<const boost::shared_ptr<int>(const std::string&)> str_to_ptr_function {
      [](const std::string& s)
      {
        return boost::shared_ptr<int>(
          new int(
            boost::lexical_cast<int>(s)
          )
        );
      }
    };
    const std::pair<std::string,std::vector<boost::shared_ptr<int>>> p {
      XmlToPtrs(xml,str_to_ptr_function)
    };
    assert(p.first == tag_name);
    assert(p.second.size() == v.size());
    assert(
      std::equal(v.begin(),v.end(),p.second.begin(),
        [](const boost::shared_ptr<int> a, const boost::shared_ptr<int> b)
        {
          return *a == *b;
        }
      )
    );
    //Again convert pointers to XML
    std::cout << PtrsToXml(p.first,p.second.begin(),p.second.end()) << '\n';
  }

  //Use std::string
  {
    //Create data consisting of pointers
    std::vector<boost::shared_ptr<std::string> > v;
    { const boost::shared_ptr<std::string> p { new std::string("cats") }; v.push_back(p); }
    { const boost::shared_ptr<std::string> p { new std::string("dogs") }; v.push_back(p); }
    { const boost::shared_ptr<std::string> p { new std::string("cows") }; v.push_back(p); }
    const std::string tag_name = "animals";

    //Convert pointers to XML
    const std::string xml = PtrsToXml(tag_name,v.begin(),v.end());

    //Convert XML back to pointers again
    const std::function<const boost::shared_ptr<std::string>(const std::string&)> str_to_ptr_function {
      [](const std::string& s)
      {
        return boost::shared_ptr<std::string>(new std::string(s));
      }
    };
    const std::pair<std::string,std::vector<boost::shared_ptr<std::string>>> p {
      XmlToPtrs(xml,str_to_ptr_function)
    };
    assert(p.first == tag_name);
    assert(p.second.size() == v.size());
    assert(
      std::equal(v.begin(),v.end(),p.second.begin(),
        [](const boost::shared_ptr<std::string> a, const boost::shared_ptr<std::string> b)
        {
          return *a == *b;
        }
      )
    );
    //Again convert pointers to XML
    std::cout << PtrsToXml(p.first,p.second.begin(),p.second.end()) << '\n';
  }
}

/* Screen output:

<integers><0>1</0><1>4</1><2>9</2></integers>
<animals><0>cats</0><1>dogs</1><2>cows</2></animals>
Press <RETURN> to close this window...

*/
