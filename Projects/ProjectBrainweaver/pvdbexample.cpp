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

#include <boost/lexical_cast.hpp>
#include <QRegExp>

#include "pvdbexample.h"
#include "pvdbexamplefactory.h"
#include "pvdbhelper.h"
#include "trace.h"

ribi::pvdb::Example::Example(
  const std::string& text,
  const pvdb::Competency competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific
  )
  : m_competency(competency),
    m_is_complex(is_complex),
    m_is_concrete(is_concrete),
    m_is_specific(is_specific),
    m_text(text)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::string ribi::pvdb::Example::CompetencyToStr(const pvdb::Competency competency)
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
  throw std::logic_error("ribi::pvdb::Example::CompetencyToStr: unknown Competency");
}

const boost::shared_ptr<ribi::pvdb::Example> ribi::pvdb::Example::FromXml(const std::string& s)
{
  assert(s.size() >= 17);
  assert(s.substr(0,9) == std::string("<example>"));
  assert(s.substr(s.size() - 10,10) == std::string("</example>"));

  std::string text;
  pvdb::Competency competency = pvdb::Competency::uninitialized;
  bool is_complex = false;
  bool is_concrete = false;
  bool is_specific = false;

  //competency
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<competency>.*</competency>)"));
    assert(v.size() == 1);
    competency = StrToCompetency(StripXmlTag(v[0]));
  }
  //is_complex
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<is_complex>.*</is_complex>)"));
    assert(v.size() == 1);
    is_complex = boost::lexical_cast<bool>(StripXmlTag(v[0]));
  }
  //is_concrete
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<is_concrete>.*</is_concrete>)"));
    assert(v.size() == 1);
    is_concrete = boost::lexical_cast<bool>(StripXmlTag(v[0]));
  }
  //is_specific
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<is_specific>.*</is_specific>)"));
    assert(v.size() == 1);
    is_specific = boost::lexical_cast<bool>(StripXmlTag(v[0]));
  }
  //text
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<text>.*</text>)"));
    assert(v.size() == 1 && "<text>.*</text> must be present once in an Example");
    text = pvdb::StripXmlTag(v[0]);
  }

  return pvdb::ExampleFactory::Create(text,competency,is_complex,is_concrete,is_specific);
}

void ribi::pvdb::Example::SetCompetency(const pvdb::Competency competency)
{
  if (m_competency != competency)
  {
    m_competency = competency;
    m_signal_competency_changed(this);
  }
}

void ribi::pvdb::Example::SetText(const std::string& text)
{
  if (m_text != text)
  {
    m_text = text;
    m_signal_text_changed(this);
  }
}

ribi::pvdb::Competency ribi::pvdb::Example::StrToCompetency(const std::string& s)
{
  if (s == "uninitialized") return pvdb::Competency::uninitialized;
  if (s == "profession") return pvdb::Competency::profession;
  if (s == "organisations") return pvdb::Competency::organisations;
  if (s == "social_surroundings") return pvdb::Competency::social_surroundings;
  if (s == "target_audience") return pvdb::Competency::target_audience;
  if (s == "ti_knowledge") return pvdb::Competency::ti_knowledge;
  if (s == "prof_growth") return pvdb::Competency::prof_growth;
  if (s == "misc") return pvdb::Competency::misc;
  assert(!"Should not get here");
  throw std::logic_error("ribi::pvdb::Example::StrToCompetency: unknown string");
}

void ribi::pvdb::Example::Test()
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

  TRACE("Starting ribi::pvdb::Example::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(pvdb::ExampleFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const pvdb::Example> a = pvdb::ExampleFactory::GetTests().at(i);
      boost::shared_ptr<      Example> b = pvdb::ExampleFactory::GetTests().at(i);
      assert(IsEqual(*a,*a));
      assert(IsEqual(*a,*b));
      assert(IsEqual(*b,*a));
      assert(IsEqual(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const pvdb::Example> c = pvdb::ExampleFactory::GetTests().at(j);
        boost::shared_ptr<      Example> d = pvdb::ExampleFactory::GetTests().at(j);
        assert(IsEqual(*c,*c));
        assert(IsEqual(*c,*d));
        assert(IsEqual(*d,*c));
        assert(IsEqual(*d,*d));
        if (i==j)
        {
          assert(IsEqual(*a,*c)); assert(IsEqual(*a,*d));
          assert(IsEqual(*b,*c)); assert(IsEqual(*b,*d));
          assert(IsEqual(*c,*a)); assert(IsEqual(*c,*b));
          assert(IsEqual(*d,*a)); assert(IsEqual(*d,*b));
        }
        else
        {
          assert(!IsEqual(*a,*c)); assert(!IsEqual(*a,*d));
          assert(!IsEqual(*b,*c)); assert(!IsEqual(*b,*d));
          assert(!IsEqual(*c,*a)); assert(!IsEqual(*c,*b));
          assert(!IsEqual(*d,*a)); assert(!IsEqual(*d,*b));
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<pvdb::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert( IsEqual(*a,*a)); assert( IsEqual(*a,*b)); assert(!IsEqual(*a,*c));
    assert( IsEqual(*b,*a)); assert( IsEqual(*b,*b)); assert(!IsEqual(*b,*c));
    assert(!IsEqual(*c,*a)); assert(!IsEqual(*c,*b)); assert( IsEqual(*c,*c));
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
        return ribi::pvdb::Example::CompetencyToStr(c);
      }
    );
    std::vector<Competency> x;
    std::transform(w.begin(),w.end(),std::back_inserter(x),
      [](const std::string& s)
      {
        return ribi::pvdb::Example::StrToCompetency(s);
      }
    );
    assert(v == x);
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst(ribi::pvdb::ExampleFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::Example>& e)
      {
        assert(e);
        const std::string s = ribi::pvdb::Example::ToXml(e);
        const boost::shared_ptr<const pvdb::Example> f(Example::FromXml(s));
        assert(IsEqual(*e,*f));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst(ribi::pvdb::ExampleFactory::GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const pvdb::Example>& e = v[i];
      const std::string s = ribi::pvdb::Example::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const pvdb::Example>& f = v[j];
        const std::string t = ribi::pvdb::Example::ToXml(f);
        if (i == j)
        {
          assert(IsEqual(*e,*f));
          assert(s == t);
        }
        else
        {
          assert(!IsEqual(*e,*f));
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

const std::string ribi::pvdb::Example::ToXml(const boost::shared_ptr<const pvdb::Example>& c)
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
  s <<   "<is_complex>";
  s <<     c->GetIsComplex();
  s <<   "</is_complex>";
  s <<   "<is_concrete>";
  s <<     c->GetIsConcrete();
  s <<   "</is_concrete>";
  s <<   "<is_specific>";
  s <<     c->GetIsSpecific();
  s <<   "</is_specific>";
  s << "</example>";

  const std::string r = s.str();
  assert(r.size() >= 17);
  assert(r.substr(0,9) == std::string("<example>"));
  assert(r.substr(r.size() - 10,10) == std::string("</example>"));
  return r;
}

bool ribi::pvdb::IsEqual(const pvdb::Example& lhs, const pvdb::Example& rhs)
{
  return
       lhs.GetText() == rhs.GetText()
    && lhs.GetCompetency() == rhs.GetCompetency();
}

bool ribi::pvdb::operator<(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() < rhs->GetText()) return true;
  if (lhs->GetText() > rhs->GetText()) return false;
  return lhs->GetCompetency() < rhs->GetCompetency();
}

bool ribi::pvdb::operator>(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() > rhs->GetText()) return true;
  if (lhs->GetText() < rhs->GetText()) return false;
  return lhs->GetCompetency() > rhs->GetCompetency();
}
