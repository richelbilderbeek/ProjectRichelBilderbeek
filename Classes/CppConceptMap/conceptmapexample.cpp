#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapexample.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <QRegExp>

#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::Example::Example(
  const std::string& text,
  const cmap::Competency competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific
  )
  : m_signal_competency_changed{},
    m_signal_text_changed{},
    m_competency(competency),
    m_is_complex(is_complex),
    m_is_concrete(is_concrete),
    m_is_specific(is_specific),
    m_text(text)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::string ribi::cmap::Example::CompetencyToStr(const cmap::Competency competency)
{
  switch (competency)
  {
    case cmap::Competency::uninitialized: return "uninitialized";
    case cmap::Competency::profession: return "profession";
    case cmap::Competency::organisations: return "organisations";
    case cmap::Competency::social_surroundings: return "social_surroundings";
    case cmap::Competency::target_audience: return "target_audience";
    case cmap::Competency::ti_knowledge: return "ti_knowledge";
    case cmap::Competency::prof_growth: return "prof_growth";
    case cmap::Competency::misc: return "misc";
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::cmap::Example::CompetencyToStr: unknown Competency");
}

const boost::shared_ptr<ribi::cmap::Example> ribi::cmap::Example::FromXml(const std::string& s)
{
  assert(s.size() >= 17);
  assert(s.substr(0,9) == std::string("<example>"));
  assert(s.substr(s.size() - 10,10) == std::string("</example>"));

  std::string text;
  cmap::Competency competency = cmap::Competency::uninitialized;
  bool is_complex = false;
  bool is_concrete = false;
  bool is_specific = false;

  //competency
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<competency>.*</competency>)"));
    assert(v.size() == 1);
    competency = StrToCompetency(ribi::xml::StripXmlTag(v[0]));
  }
  //is_complex
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<is_complex>.*</is_complex>)"));
    assert(v.size() == 1);
    is_complex = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_concrete
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<is_concrete>.*</is_concrete>)"));
    assert(v.size() == 1);
    is_concrete = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_specific
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<is_specific>.*</is_specific>)"));
    assert(v.size() == 1);
    is_specific = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //text
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<text>.*</text>)"));
    assert(v.size() == 1 && "<text>.*</text> must be present once in an Example");
    text = ribi::xml::StripXmlTag(v[0]);
  }

  return cmap::ExampleFactory::Create(text,competency,is_complex,is_concrete,is_specific);
}

void ribi::cmap::Example::SetCompetency(const cmap::Competency competency)
{
  if (m_competency != competency)
  {
    m_competency = competency;
    m_signal_competency_changed(this);
  }
}

void ribi::cmap::Example::SetText(const std::string& text)
{
  if (m_text != text)
  {
    m_text = text;
    m_signal_text_changed(this);
  }
}

ribi::cmap::Competency ribi::cmap::Example::StrToCompetency(const std::string& s)
{
  if (s == "uninitialized") return cmap::Competency::uninitialized;
  if (s == "profession") return cmap::Competency::profession;
  if (s == "organisations") return cmap::Competency::organisations;
  if (s == "social_surroundings") return cmap::Competency::social_surroundings;
  if (s == "target_audience") return cmap::Competency::target_audience;
  if (s == "ti_knowledge") return cmap::Competency::ti_knowledge;
  if (s == "prof_growth") return cmap::Competency::prof_growth;
  if (s == "misc") return cmap::Competency::misc;
  assert(!"Should not get here");
  throw std::logic_error("ribi::cmap::Example::StrToCompetency: unknown string");
}

void ribi::cmap::Example::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::Example::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(cmap::ExampleFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const cmap::Example> a = cmap::ExampleFactory::GetTests().at(i);
      boost::shared_ptr<      Example> b = cmap::ExampleFactory::GetTests().at(i);
      assert(operator==(*a,*a));
      assert(operator==(*a,*b));
      assert(operator==(*b,*a));
      assert(operator==(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const cmap::Example> c = cmap::ExampleFactory::GetTests().at(j);
        boost::shared_ptr<      Example> d = cmap::ExampleFactory::GetTests().at(j);
        assert(operator==(*c,*c));
        assert(operator==(*c,*d));
        assert(operator==(*d,*c));
        assert(operator==(*d,*d));
        if (i==j)
        {
          assert(operator==(*a,*c)); assert(operator==(*a,*d));
          assert(operator==(*b,*c)); assert(operator==(*b,*d));
          assert(operator==(*c,*a)); assert(operator==(*c,*b));
          assert(operator==(*d,*a)); assert(operator==(*d,*b));
        }
        else
        {
          assert(!operator==(*a,*c)); assert(!operator==(*a,*d));
          assert(!operator==(*b,*c)); assert(!operator==(*b,*d));
          assert(!operator==(*c,*a)); assert(!operator==(*c,*b));
          assert(!operator==(*d,*a)); assert(!operator==(*d,*b));
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<cmap::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert( operator==(*a,*a)); assert( operator==(*a,*b)); assert(!operator==(*a,*c));
    assert( operator==(*b,*a)); assert( operator==(*b,*b)); assert(!operator==(*b,*c));
    assert(!operator==(*c,*a)); assert(!operator==(*c,*b)); assert( operator==(*c,*c));
  }
  //Conversion between std::string and competency
  {
    const std::vector<Competency> v
      =
      {
        cmap::Competency::uninitialized,
        cmap::Competency::profession,
        cmap::Competency::organisations,
        cmap::Competency::social_surroundings,
        cmap::Competency::target_audience,
        cmap::Competency::ti_knowledge,
        cmap::Competency::prof_growth,
        cmap::Competency::misc
      };
    std::vector<std::string> w;
    std::transform(v.begin(),v.end(),std::back_inserter(w),
      [](const cmap::Competency& c)
      {
        return ribi::cmap::Example::CompetencyToStr(c);
      }
    );
    std::vector<Competency> x;
    std::transform(w.begin(),w.end(),std::back_inserter(x),
      [](const std::string& s)
      {
        return ribi::cmap::Example::StrToCompetency(s);
      }
    );
    assert(v == x);
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const cmap::Example> > v = AddConst(ribi::cmap::ExampleFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const cmap::Example>& e)
      {
        assert(e);
        const std::string s = ribi::cmap::Example::ToXml(e);
        const boost::shared_ptr<const cmap::Example> f(Example::FromXml(s));
        assert(operator==(*e,*f));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const cmap::Example> > v = AddConst(ribi::cmap::ExampleFactory::GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const cmap::Example>& e = v[i];
      const std::string s = ribi::cmap::Example::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const cmap::Example>& f = v[j];
        const std::string t = ribi::cmap::Example::ToXml(f);
        if (i == j)
        {
          assert(operator==(*e,*f));
          assert(s == t);
        }
        else
        {
          assert(!operator==(*e,*f));
          assert(s != t);
        }
      }
    }
  }
  TRACE("Example::Test finished successfully");
}

const std::string ribi::cmap::Example::ToXml(const boost::shared_ptr<const cmap::Example>& c)
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

bool ribi::cmap::operator==(const cmap::Example& lhs, const cmap::Example& rhs)
{
  return
       lhs.GetText() == rhs.GetText()
    && lhs.GetCompetency() == rhs.GetCompetency();
}

bool ribi::cmap::operator!=(const cmap::Example& lhs, const cmap::Example& rhs)
{
  return !(lhs == rhs);
}

bool ribi::cmap::operator<(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() < rhs->GetText()) return true;
  if (lhs->GetText() > rhs->GetText()) return false;
  return lhs->GetCompetency() < rhs->GetCompetency();
}

bool ribi::cmap::operator>(const boost::shared_ptr<const cmap::Example>& lhs,const boost::shared_ptr<const cmap::Example>& rhs)
{
  assert(lhs && rhs);
  if (lhs->GetText() > rhs->GetText()) return true;
  if (lhs->GetText() < rhs->GetText()) return false;
  return lhs->GetCompetency() > rhs->GetCompetency();
}
