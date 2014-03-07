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

std::string ribi::cmap::Example::CompetencyToStr(const cmap::Competency competency) noexcept
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


void ribi::cmap::Example::SetCompetency(const cmap::Competency competency) noexcept
{
  if (m_competency != competency)
  {
    m_competency = competency;
    m_signal_competency_changed(this);
  }
}

void ribi::cmap::Example::SetText(const std::string& text) noexcept
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
    const int sz = ExampleFactory().GetNumberOfTests();
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const cmap::Example> a = ExampleFactory().GetTest(i);
      boost::shared_ptr<      Example> b = ExampleFactory().GetTest(i);
      assert(*a == *a);
      assert(*a == *b);
      assert(*b == *a);
      assert(*b == *b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const cmap::Example> c = cmap::ExampleFactory().GetTest(j);
        boost::shared_ptr<      Example> d = cmap::ExampleFactory().GetTest(j);
        assert(*c == *c);
        assert(*c == *d);
        assert(*d == *c);
        assert(*d == *d);
        if (i==j)
        {
          assert(*a == *c); assert(*a == *d);
          assert(*b == *c); assert(*b == *d);
          assert(*c == *a); assert(*c == *b);
          assert(*d == *a); assert(*d == *b);
        }
        else
        {
          assert(*a != *c); assert(*a != *d);
          assert(*b != *c); assert(*b != *d);
          assert(*c != *a); assert(*c != *b);
          assert(*d != *a); assert(*d != *b);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<cmap::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert(*a == *a); assert(*a == *b); assert(*a != *c);
    assert(*b == *a); assert(*b == *b); assert(*b != *c);
    assert(*c != *a); assert(*c != *b); assert(*c == *c);
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
        return Example::StrToCompetency(s);
      }
    );
    assert(v == x);
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const Example> > v = AddConst(ExampleFactory().GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const Example>& e)
      {
        assert(e);
        const std::string s { e->ToXml() };
        const boost::shared_ptr<const Example> f(ExampleFactory().FromXml(s));
        assert(*e == *f);
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const Example> > v = AddConst(ExampleFactory().GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const Example>& e = v[i];
      const std::string s { e->ToXml() };
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const Example>& f = v[j];
        const std::string t = f->ToXml();
        if (i == j)
        {
          assert(*e == *f);
          assert(s == t);
        }
        else
        {
          assert(*e != *f);
          assert( s !=  t);
        }
      }
    }
  }
  TRACE("Example::Test finished successfully");
}

std::string ribi::cmap::Example::ToXml() const noexcept
{
  std::stringstream s;
  s << "<example>";
  s <<   "<text>";
  s <<     GetText();
  s <<   "</text>";
  s <<   "<competency>";
  s <<     CompetencyToStr(GetCompetency());
  s <<   "</competency>";
  s <<   "<is_complex>";
  s <<     GetIsComplex();
  s <<   "</is_complex>";
  s <<   "<is_concrete>";
  s <<     GetIsConcrete();
  s <<   "</is_concrete>";
  s <<   "<is_specific>";
  s <<     GetIsSpecific();
  s <<   "</is_specific>";
  s << "</example>";

  const std::string r = s.str();
  assert(r.size() >= 17);
  assert(r.substr(0,9) == "<example>");
  assert(r.substr(r.size() - 10,10) == "</example>");
  return r;
}

bool ribi::cmap::operator==(const cmap::Example& lhs, const cmap::Example& rhs) noexcept
{
  return
       lhs.GetText() == rhs.GetText()
    && lhs.GetCompetency() == rhs.GetCompetency();
}

bool ribi::cmap::operator!=(const cmap::Example& lhs, const cmap::Example& rhs) noexcept
{
  return !(lhs == rhs);
}

bool ribi::cmap::operator<(const cmap::Example& lhs,const cmap::Example& rhs) noexcept
{
  if (lhs.GetText() < rhs.GetText()) return true;
  if (lhs.GetText() > rhs.GetText()) return false;
  return lhs.GetCompetency() < rhs.GetCompetency();
}

bool ribi::cmap::operator>(const cmap::Example& lhs,const cmap::Example& rhs) noexcept
{
  if (lhs.GetText() > rhs.GetText()) return true;
  if (lhs.GetText() < rhs.GetText()) return false;
  return lhs.GetCompetency() > rhs.GetCompetency();
}
