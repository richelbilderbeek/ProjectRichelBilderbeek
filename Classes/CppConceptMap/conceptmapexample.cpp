//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapexample.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <QRegExp>

#include "counter.h"
#include "conceptmapcompetencies.h"
#include "conceptmapcompetency.h"
#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::Example::Example(
  const ExampleFactory&,
  const std::string& text,
  const cmap::Competency competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific
  )
  : m_signal_competency_changed{},
    m_signal_is_complex_changed{},
    m_signal_is_concrete_changed{},
    m_signal_is_specific_changed{},
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

/*
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
*/

void ribi::cmap::Example::SetCompetency(const Competency competency) noexcept
{
  const bool verbose{true};
  const Competency competency_before = m_competency;
  const Competency competency_after  =   competency;
  if (competency_before != competency_after)
  {
    assert(m_competency == competency_before);

    if (verbose)
    {
      std::stringstream s;
      s << "Example will change Competency from " << Competencies().ToStr(competency_before)
        << " to " << Competencies().ToStr(competency_after);
      TRACE(s.str());
    }

    m_competency = competency;

    assert(m_competency == competency_after);

    m_signal_competency_changed(this);

    assert(m_competency == competency_after);
    if (verbose)
    {
      std::stringstream s;
      s << "Competency changed to " << Competencies().ToStr(m_competency);
      TRACE(s.str());
    }
  }
}

void ribi::cmap::Example::SetIsComplex(const bool is_complex) noexcept
{
  if (m_is_complex != is_complex)
  {
    m_is_complex = is_complex;
    m_signal_is_complex_changed(this);
  }
}

void ribi::cmap::Example::SetIsConcrete(const bool is_concrete) noexcept
{
  if (m_is_concrete != is_concrete)
  {
    m_is_concrete = is_concrete;
    m_signal_is_concrete_changed(this);
  }
}

void ribi::cmap::Example::SetIsSpecific(const bool is_specific) noexcept
{
  if (m_is_specific != is_specific)
  {
    m_is_specific = is_specific;
    m_signal_is_specific_changed(this);
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

#ifndef NDEBUG
void ribi::cmap::Example::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::Example::Test");
  const bool verbose{false};


  if (verbose) { TRACE("Set and get must be symmetric"); }
  {
    const Competency competency_before = Competency::uninitialized;
    const Competency competency_after = Competency::misc;
    const bool is_complex_before  = false;
    const bool is_complex_after   = true;
    const bool is_concrete_before = true;
    const bool is_concrete_after  = false;
    const bool is_specific_before = true;
    const bool is_specific_after  = false;
    const std::string text_before = "before";
    const std::string text_after  = "after";

    auto example  = ExampleFactory().Create(
      text_before,
      competency_before,
      is_complex_before,
      is_concrete_before,
      is_specific_before
    );
    assert(example->GetCompetency() == competency_before);
    assert(example->GetCompetency() != competency_after);
    assert(example->GetIsComplex() == is_complex_before);
    assert(example->GetIsComplex() != is_complex_after);
    assert(example->GetIsConcrete() == is_concrete_before);
    assert(example->GetIsConcrete() != is_concrete_after);
    assert(example->GetIsSpecific() == is_specific_before);
    assert(example->GetIsSpecific() != is_specific_after);
    assert(example->GetText() == text_before);
    assert(example->GetText() != text_after);

    example->SetCompetency(competency_after);
    example->SetIsComplex(is_complex_after);
    example->SetIsConcrete(is_concrete_after);
    example->SetIsSpecific(is_specific_after);
    example->SetText(text_after);

    assert(example->GetCompetency() != competency_before);
    assert(example->GetCompetency() == competency_after);
    assert(example->GetIsComplex() != is_complex_before);
    assert(example->GetIsComplex() == is_complex_after);
    assert(example->GetIsConcrete() != is_concrete_before);
    assert(example->GetIsConcrete() == is_concrete_after);
    assert(example->GetIsSpecific() != is_specific_before);
    assert(example->GetIsSpecific() == is_specific_after);
    assert(example->GetText() != text_before);
    assert(example->GetText() == text_after);
  }
  if (verbose) { TRACE("Test of operator== and operator!="); }
  {
    const int sz = ExampleFactory().GetNumberOfTests();
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const Example> a = ExampleFactory().GetTest(i);
      boost::shared_ptr<      Example> b = ExampleFactory().GetTest(i);
      assert(*a == *a);
      assert(*a == *b);
      assert(*b == *a);
      assert(*b == *b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const Example> c = ExampleFactory().GetTest(j);
        boost::shared_ptr<      Example> d = ExampleFactory().GetTest(j);
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
  if (verbose) { TRACE("Unrated and rated examples must be noticed as different"); }
  {
    const boost::shared_ptr<Example> a = ExampleFactory().Create("1",Competency::misc);
    const boost::shared_ptr<Example> b = ExampleFactory().Create("1",Competency::misc);
    const boost::shared_ptr<Example> c = ExampleFactory().Create("1",Competency::uninitialized);
    assert(*a == *a); assert(*a == *b); assert(*a != *c);
    assert(*b == *a); assert(*b == *b); assert(*b != *c);
    assert(*c != *a); assert(*c != *b); assert(*c == *c);
  }
  //Conversion between std::string and competency
  //Checked by Competencies

  if (verbose) { TRACE("Conversion from class->XML->class must result in something equal to the class"); }
  {
    const std::vector<boost::shared_ptr<const Example>> v = AddConst(ExampleFactory().GetTests());
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
  if (verbose) { TRACE("Conversion from class->XML->class must differ between classes"); }
  {
    const auto v = AddConst(ExampleFactory().GetTests());
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
  if (verbose) { TRACE("When setting the competency, a signal must be emitted"); }
  {
    const auto example = ExampleFactory().GetTest(0);
    example->SetCompetency(Competency::uninitialized);
    Counter c{0}; //For receiving the signal
    example->m_signal_competency_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    example->SetCompetency(Competency::misc);
    assert(c.Get() == 1);
  }
  if (verbose) { TRACE("When setting the text, a signal must be emitted"); }
  {
    const auto example = ExampleFactory().GetTest(0);
    example->SetText("A");
    Counter c{0}; //For receiving the signal
    example->m_signal_text_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    example->SetText("B");
    assert(c.Get() == 1);
  }
  TRACE("Example::Test finished successfully");
}
#endif

std::string ribi::cmap::Example::ToStr() const noexcept
{
  std::stringstream s;
  s
    << GetText() << " "
    << Competencies().ToStr(GetCompetency()) << " "
    << GetIsComplex() << " "
    << GetIsConcrete() << " "
    << GetIsSpecific()
  ;
  return s.str();

}

std::string ribi::cmap::Example::ToXml() const noexcept
{
  std::stringstream s;
  s << "<example>";
  s <<   "<text>";
  s <<     GetText();
  s <<   "</text>";
  s <<   "<competency>";
  s << Competencies().ToStr(GetCompetency());
  //s <<     CompetencyToStr(GetCompetency());
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
