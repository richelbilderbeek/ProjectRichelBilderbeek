#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbhelper.h"

#include <cassert>
#include <fstream>
#include <QFile>
#include <QRegExp>
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const std::vector<std::string> pvdb::FileToVector(const std::string& filename)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif

  assert(QFile::exists(filename.c_str()));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

double pvdb::GetDistance(const double delta_x, const double delta_y)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  return std::sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
}

double pvdb::GetDistance(const double x1, const double y1, const double x2, const double y2)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  return GetDistance(x1-x2,y1-y2);
}

const std::vector<std::string> pvdb::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  QRegExp r(r_original);
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
}

const std::vector<std::string> pvdb::SafeFileToVector(const std::string& filename)
{
  std::vector<std::string> v = pvdb::FileToVector(filename);
  if (!v.empty() && v.back().empty()) v.pop_back();
  return v;
}

const std::vector<std::string> pvdb::SplitXml(const std::string& s)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
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

const std::string pvdb::StripXmlTag(const std::string& s)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
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

void pvdb::TestHelperFunctions()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started TestHelperFunctions");
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
  //GetRegexMatches
  {
    const std::string s = "In the Netherlands, 1234 AB and 2345 BC are valid zip codes";
    std::vector<std::string> expected;
    expected.push_back("1234 AB");
    expected.push_back("2345 BC");
    {
      const std::string r = "(\\d{4} [A-Z]{2})";
      assert(pvdb::GetRegexMatches(s,QRegExp(r.c_str())) == expected);
    }
  }
  {
    const std::string s = "<concept><name>Concept with examples</name><example>Example 1</example><example>Example 2</example><example>Example 3</example></concept>";
    assert(std::count(s.begin(),s.end(),'\b') == 0);
    std::vector<std::string> expected;
    expected.push_back("<example>Example 1</example>");
    expected.push_back("<example>Example 2</example>");
    expected.push_back("<example>Example 3</example>");
    {
      const std::string r = "(<example>.*</example>)";
      assert(pvdb::GetRegexMatches(s,QRegExp(r.c_str())) == expected);
    }
  }
  //GetCombinations
  //Assume the number of elements is correct
  assert(GetCombinations(std::vector<int>( {         } ) ).size() ==  1);
  assert(GetCombinations(std::vector<int>( {1        } ) ).size() ==  2);
  assert(GetCombinations(std::vector<int>( {1,2      } ) ).size() ==  4);
  assert(GetCombinations(std::vector<int>( {1,2,3    } ) ).size() ==  8);
  assert(GetCombinations(std::vector<int>( {1,2,3,4  } ) ).size() == 16);
  assert(GetCombinations(std::vector<int>( {1,2,3,4,5} ) ).size() == 32);
  //Assume the elements are correct
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {1,2};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2,3 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {3};
    const std::vector<int> expected_4 = {1,2};
    const std::vector<int> expected_5 = {1,3};
    const std::vector<int> expected_6 = {2,3};
    const std::vector<int> expected_7 = {1,2,3};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
    assert(std::count(v.begin(),v.end(),expected_4));
    assert(std::count(v.begin(),v.end(),expected_5));
    assert(std::count(v.begin(),v.end(),expected_6));
    assert(std::count(v.begin(),v.end(),expected_7));
  }
  {
    const std::vector<std::vector<int> > v = GetCombinations(std::vector<int>( { 1,2,3,4 } ) );
    const std::vector<int> expected_0 = {};
    const std::vector<int> expected_1 = {1};
    const std::vector<int> expected_2 = {2};
    const std::vector<int> expected_3 = {3};
    const std::vector<int> expected_4 = {4};
    const std::vector<int> expected_5 = {1,2};
    const std::vector<int> expected_6 = {1,3};
    const std::vector<int> expected_7 = {1,4};
    const std::vector<int> expected_8 = {2,3};
    const std::vector<int> expected_9 = {2,4};
    const std::vector<int> expected_10 = {3,4};
    const std::vector<int> expected_11 = {1,2,3};
    const std::vector<int> expected_12 = {1,2,4};
    const std::vector<int> expected_13 = {1,3,4};
    const std::vector<int> expected_14 = {2,3,4};
    const std::vector<int> expected_15 = {1,2,3,4};
    assert(std::count(v.begin(),v.end(),expected_0));
    assert(std::count(v.begin(),v.end(),expected_1));
    assert(std::count(v.begin(),v.end(),expected_2));
    assert(std::count(v.begin(),v.end(),expected_3));
    assert(std::count(v.begin(),v.end(),expected_4));
    assert(std::count(v.begin(),v.end(),expected_5));
    assert(std::count(v.begin(),v.end(),expected_6));
    assert(std::count(v.begin(),v.end(),expected_7));
    assert(std::count(v.begin(),v.end(),expected_8));
    assert(std::count(v.begin(),v.end(),expected_9));
    assert(std::count(v.begin(),v.end(),expected_10));
    assert(std::count(v.begin(),v.end(),expected_11));
    assert(std::count(v.begin(),v.end(),expected_12));
    assert(std::count(v.begin(),v.end(),expected_13));
    assert(std::count(v.begin(),v.end(),expected_14));
    assert(std::count(v.begin(),v.end(),expected_15));
  }
  {
    const std::string s = "<a>A</a>";
    const std::vector<std::string> split = pvdb::SplitXml(s);
    const std::vector<std::string> split_expected
      =
      {
        "<a>",
        "A",
        "</a>"
      };
    assert(split == split_expected);
    const std::vector<std::string> pretty = pvdb::XmlToPretty(s);
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
    const std::vector<std::string> split = pvdb::SplitXml(s);
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
    const std::vector<std::string> pretty = pvdb::XmlToPretty(s);
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
    const std::vector<std::string> split = pvdb::SplitXml(s);
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
    const std::vector<std::string> pretty = pvdb::XmlToPretty(s);
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
  TRACE("TestHelperFunctions finished successfully");

}

const std::vector<std::string> pvdb::XmlToPretty(const std::string& s)
{
  #ifndef NDEBUG
  pvdb::TestHelperFunctions();
  #endif
  std::vector<std::string> v = pvdb::SplitXml(s);
  int n = -2;
  std::for_each(v.begin(),v.end(),
    [&n](std::string& s)
    {
      assert(!s.empty());
      if (s[0] == '<' && s[1] != '/')
      {
        n+=2;
      }
      s = std::string(n,' ') + s;
      if (s[n+0] == '<' && s[n+1] == '/')
      {
        n-=2;
      }
    }
  );
  return v;
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
