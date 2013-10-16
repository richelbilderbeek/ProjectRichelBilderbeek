#include "xml.h"

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include "trace.h"
#pragma GCC diagnostic pop

const std::vector<std::string> ribi::xml::SplitXml(const std::string& s)
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

const std::string ribi::xml::StripXmlTag(const std::string& s)
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

const std::string ribi::xml::StrToXml(
  const std::string& tag_name,
  const std::string& content)
{
  std::stringstream s;
  s << "<"  << tag_name << ">" << content << "</" << tag_name << ">";
  //No test here, as StrToXml is used in testing XmlToStr
  return s.str();
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
    const std::string tag_name { "cat_name" };
    const std::string content  { "Kitty" };
    const std::string xml = StrToXml(tag_name,content);
    const std::pair<std::string,std::string> p = XmlToStr(xml);
    assert(p.first == tag_name);
    assert(p.second == content);
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

  //VectorToXml and XmlToVector
  {
    const std::vector<std::string> content { "cats", "dog", "zebrafinch" };
    const std::string tag_name = "animals";
    const std::string xml = VectorToXml(tag_name,content);
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
  //assert(1==2);
}
#endif


const std::vector<std::string> ribi::xml::XmlToPretty(const std::string& s)
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
  assert(StrToXml(p.first,p.second) == s);
  return p;
}


const std::pair<std::string,std::vector<std::string>> ribi::xml::XmlToVector(
  const std::string& s)
{
  assert(!s.empty());
  assert(s[           0] == '<');
  assert(s[s.size() - 1] == '>');
  assert(s.find('>') != std::string::npos);

  //Read the name tag
  //<tag_name>...</tag_name>
  const std::pair<std::string,std::string> p = XmlToStr(s);
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

