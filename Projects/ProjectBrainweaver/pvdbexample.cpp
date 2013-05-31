#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbexample.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <QRegExp>

#include "pvdbexample.h"
#include "pvdbexamplefactory.h"
#include "pvdbhelper.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Example::Example(const std::string& text, const pvdb::Competency competency)
  : m_competency(competency),
    m_is_complex(true),  //Often, an example is assessed to be complex
    m_is_concrete(true), //Often, an example is assessed to be concrete
    m_is_specific(true), //Often, an example is assessed to be specific
    m_text(text)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::string pvdb::Example::CompetencyToStr(const pvdb::Competency competency)
{
  switch (competency)
  {
    case pvdb::Competency::uninitialized: return "uninitialized";
    case pvdb::Competency::profession: return "profession";
    case pvdb::Competency::organisations: return "organisations";
    case pvdb::Competency::social_surroundings: return "social_surroundings";
    case pvdb::Competency::target_audience: return "target_audience";
    case pvdb::Competency::ti_knowledge: return "ti_knowledge";
    case pvdb::Competency::prof_growth: return "prof_growth";
    case pvdb::Competency::misc: return "misc";
  }
  assert(!"Should not get here");
  throw std::logic_error("pvdb::Example::CompetencyToStr: unknown Competency");
}

const boost::shared_ptr<pvdb::Example> pvdb::Example::FromXml(const std::string& s)
{
  assert(s.size() >= 17);
  assert(s.substr(0,9) == std::string("<example>"));
  assert(s.substr(s.size() - 10,10) == std::string("</example>"));

  std::string text;
  pvdb::Competency competency = pvdb::Competency::uninitialized;

  //text
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<text>.*</text>)"));
    assert(v.size() == 1 && "<text>.*</text> must be present once in an Example");
    text = pvdb::StripXmlTag(v[0]);
  }
  //competency
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<competency>.*</competency>)"));
    assert(v.size() == 1);
    competency = StrToCompetency(StripXmlTag(v[0]));
  }

  return pvdb::ExampleFactory::Create(text,competency);
}

void pvdb::Example::SetCompetency(const pvdb::Competency competency)
{
  if (m_competency != competency)
  {
    m_competency = competency;
    m_signal_competency_changed(this);
  }
}

void pvdb::Example::SetText(const std::string& text)
{
  if (m_text != text)
  {
    m_text = text;
    m_signal_text_changed(this);
  }
}

pvdb::Competency pvdb::Example::StrToCompetency(const std::string& s)
{
  if (s == "uninitialized") return pvdb::Competency::uninitialized;
  if (s == "profession") return pvdb::Competency::profession;
  if (s == "organisations") return pvdb::Competency::organisations;
  if (s == "social_surroundings") return pvdb::Competency::social_surroundings;
  if (s == "target_audience") return pvdb::Competency::target_audience;
  if (s == "ti_knowledge") return pvdb::Competency::ti_knowledge;
  if (s == "prof_growth") return pvdb::Competency::prof_growth;
  if (s == "misc") return pvdb::Competency::misc;
  TRACE(s);
  assert(!"Should not get here");
  throw std::logic_error("pvdb::Example::StrToCompetency: unknown string");
}

void pvdb::Example::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif

  TRACE("Starting pvdb::Example::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(pvdb::ExampleFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const pvdb::Example> a = pvdb::ExampleFactory::GetTests().at(i);
      boost::shared_ptr<      Example> b = pvdb::ExampleFactory::GetTests().at(i);
      assert(a==a); assert(a==b); assert(b==a); assert(b==b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const pvdb::Example> c = pvdb::ExampleFactory::GetTests().at(j);
        boost::shared_ptr<      Example> d = pvdb::ExampleFactory::GetTests().at(j);
        assert(c==c); assert(c==d); assert(d==c); assert(d==d);
        if (i==j)
        {
          assert(a==c); assert(a==d);
          assert(b==c); assert(b==d);
          assert(c==a); assert(c==b);
          assert(d==a); assert(d==b);
        }
        else
        {
          assert(a!=c); assert(a!=d);
          assert(b!=c); assert(b!=d);
          assert(c!=a); assert(c!=b);
          assert(d!=a); assert(d!=b);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<pvdb::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert(a == a); assert(a == b); assert(a != c);
    assert(b == a); assert(b == b); assert(b != c);
    assert(c != a); assert(c != b); assert(c == c);
  }
  //Conversion between std::string and competency
  {
    const std::vector<Competency> v
      =
      {
        pvdb::Competency::uninitialized,
        pvdb::Competency::profession,
        pvdb::Competency::organisations,
        pvdb::Competency::social_surroundings,
        pvdb::Competency::target_audience,
        pvdb::Competency::ti_knowledge,
        pvdb::Competency::prof_growth,
        pvdb::Competency::misc
      };
    std::vector<std::string> w;
    std::transform(v.begin(),v.end(),std::back_inserter(w),
      [](const pvdb::Competency& c)
      {
        return pvdb::Example::CompetencyToStr(c);
      }
    );
    std::vector<Competency> x;
    std::transform(w.begin(),w.end(),std::back_inserter(x),
      [](const std::string& s)
      {
        return pvdb::Example::StrToCompetency(s);
      }
    );
    assert(v == x);
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst( ::pvdb::ExampleFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::Example>& e)
      {
        assert(e);
        const std::string s = pvdb::Example::ToXml(e);
        const boost::shared_ptr<const pvdb::Example> f(Example::FromXml(s));
        assert(e == f);
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst( ::pvdb::ExampleFactory::GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const pvdb::Example>& e = v[i];
      const std::string s = pvdb::Example::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const pvdb::Example>& f = v[j];
        const std::string t = pvdb::Example::ToXml(f);
        if (i == j)
        {
          assert(e == f);
          assert(s == t);
        }
        else
        {
          assert(e != f);
          assert(s != t);
        }
      }
    }
  }
  TRACE("Example::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

const std::string pvdb::Example::ToXml(const boost::shared_ptr<const pvdb::Example>& c)
{
  assert(c);
  std::stringstream s;
  s << "<example>";
  s <<   "<text>";
  s <<     c->GetText();
  s <<   "</text>";
  s <<   "<competency>";
  s <<     CompetencyToStr(c->GetCompetency());
  s <<   "</competency>";
  s << "</example>";

  const std::string r = s.str();
  assert(r.size() >= 17);
  assert(r.substr(0,9) == std::string("<example>"));
  assert(r.substr(r.size() - 10,10) == std::string("</example>"));
  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool operator==(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  assert(lhs && rhs);
  return
       lhs->GetText() == rhs->GetText()
    && lhs->GetCompetency() == rhs->GetCompetency();
}

bool operator==(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) == boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) == boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) == boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) != boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) != boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs)
{
  return boost::shared_ptr<const pvdb::Example>(lhs) != boost::shared_ptr<const pvdb::Example>(rhs);
}

bool operator<(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() < rhs->GetText()) return true;
  if (lhs->GetText() > rhs->GetText()) return false;
  return lhs->GetCompetency() < rhs->GetCompetency();
}

bool operator>(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() > rhs->GetText()) return true;
  if (lhs->GetText() < rhs->GetText()) return false;
  return lhs->GetCompetency() > rhs->GetCompetency();
}

} //~namespace pvdb
