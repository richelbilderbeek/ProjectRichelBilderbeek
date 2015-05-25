//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#include "conceptmapexamples.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <QRegExp>
#include "counter.h"
#include "conceptmaphelper.h"
#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Examples::Examples(const std::vector<boost::shared_ptr<cmap::Example> >& v)
  : m_signal_examples_changed{},
    m_v(v)
{
  #ifndef NDEBUG
  Test();
  #endif

  for(const auto example: m_v)
  {
    assert(example);
    example->m_signal_competency_changed.connect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_complex_changed.connect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_concrete_changed.connect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_specific_changed.connect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_text_changed.connect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
  }

  assert(std::count_if(m_v.begin(),m_v.end(),
    [](const boost::shared_ptr<Example>& e) { return !e; }
    ) == 0 && "All Example instances must be initialized");
}

ribi::cmap::Examples::~Examples() noexcept
{
  for(const auto example: m_v)
  {
    assert(example);
    example->m_signal_competency_changed.disconnect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_complex_changed.disconnect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_concrete_changed.disconnect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_is_specific_changed.disconnect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
    example->m_signal_text_changed.disconnect(
      boost::bind(&Examples::OnExampleChanged,this)
    );
  }

}

/*
void ribi::cmap::Examples::Add(const boost::shared_ptr<cmap::Example>& example)
{
  assert(example);
  //Connect the example
  example->m_signal_competency_changed.connect(
    boost::bind(
      &Examples::OnExampleChanged,
      this
    )
  );
  example->m_signal_text_changed.connect(
    boost::bind(
      &Examples::OnExampleChanged,
      this
    )
  );
  //Add the example and notify this change
  m_v.push_back(example);
  m_signal_examples_changed(this);
}
*/


std::vector<boost::shared_ptr<const ribi::cmap::Example> > ribi::cmap::Examples::Get() const noexcept
{
  return AddConst(m_v);
}

void ribi::cmap::Examples::OnExampleChanged() noexcept
{
  m_signal_examples_changed(this); 
}

void ribi::cmap::Examples::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Counter();
  ExampleFactory().GetTest(0);
  ExamplesFactory();
  ExamplesFactory().GetTest(0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test of operator== and operator!=
  {
    const int sz = ExamplesFactory().GetNumberOfTests();
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const Examples> a = ExamplesFactory().GetTest(i);
      boost::shared_ptr<      Examples> b = ExamplesFactory().GetTest(i);
      assert(*a == *a);
      assert(*a == *b);
      assert(*b == *a);
      assert(*b == *b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const Examples> c = ExamplesFactory().GetTest(j);
        boost::shared_ptr<      Examples> d = ExamplesFactory().GetTest(j);
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
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const Examples> > v = AddConst(ExamplesFactory().GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const Examples>& e)
      {
        assert(e);
        const std::string s { e->ToXml() };
        const boost::shared_ptr<const Examples> f(ExamplesFactory().FromXml(s));
        assert(*e == *f);
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const Examples> > v = AddConst(ExamplesFactory().GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const Examples>& e = v[i];
      const std::string s { e->ToXml() };
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const Examples>& f = v[j];
        const std::string t { f->ToXml() };
        if (i == j)
        {
          assert(*e == *f);
          assert( s ==  t);
        }
        else
        {
          assert(*e != *f);
          assert( s !=  t);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<Example> a = ExampleFactory().Create("1",Competency::misc);
    const boost::shared_ptr<Example> b = ExampleFactory().Create("1",Competency::misc);
    const boost::shared_ptr<Example> c = ExampleFactory().Create("1",Competency::uninitialized);
    assert(*a == *a); assert(*a == *b); assert(*a != *c);
    assert(*b == *a); assert(*b == *b); assert(*b != *c);
    assert(*c != *a); assert(*c != *b); assert(*c == *c);
    std::vector<boost::shared_ptr<const Example> > v; v.push_back(a);
    std::vector<boost::shared_ptr<const Example> > w; w.push_back(b);
    std::vector<boost::shared_ptr<const Example> > x; x.push_back(c);
    const boost::shared_ptr<Examples> d = ExamplesFactory().Create(v);
    const boost::shared_ptr<Examples> e = ExamplesFactory().Create(w);
    const boost::shared_ptr<Examples> f = ExamplesFactory().Create(x);
    assert(*d == *d); assert(*d == *e); assert(*d != *f);
    assert(*e == *d); assert(*e == *e); assert(*e != *f);
    assert(*f != *d); assert(*f != *e); assert(*f == *f);
  }
}

std::string ribi::cmap::Examples::ToStr() const noexcept
{
  std::stringstream s;
  s << "{ ";

  //const std::vector<boost::shared_ptr<const Example> > examples = c->GetExamples();
  for (const auto& example: Get())
  {
    s << example->ToStr() << " ";
  };
  s << "}";
  return s.str();
}

std::string ribi::cmap::Examples::ToXml() const noexcept
{
  std::stringstream s;
  s << "<examples>";

  //const std::vector<boost::shared_ptr<const Example> > examples = c->GetExamples();
  const auto example = Get();
  std::for_each(example.begin(),example.end(),
    [&s](const boost::shared_ptr<const Example>& t)
    {
      s << t->ToXml();
    }
  );
  s << "</examples>";

  const std::string r = s.str();
  assert(r.size() >= 20);
  assert(r.substr(0,10) == "<examples>");
  assert(r.substr(r.size() - 11,11) == "</examples>");
  return r;
}

bool ribi::cmap::operator==(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  if (lhs.Get().size() != rhs.Get().size())
  {
    return false;
  }
  if (lhs.Get().empty()) { assert(rhs.Get().empty()); return true; }
  const std::vector<boost::shared_ptr<const Example> > v = lhs.Get();
  const std::vector<boost::shared_ptr<const Example> > w = rhs.Get();
  return std::equal(v.begin(),v.end(),w.begin(),
    [](const boost::shared_ptr<const Example>& a, const boost::shared_ptr<const Example>& b)
    {
      return *a == *b;
    }
  );
}

bool ribi::cmap::operator!=(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  return !(lhs == rhs);
}

bool ribi::cmap::operator<(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  if (lhs.Get().size() < rhs.Get().size()) return true;
  if (lhs.Get().size() > rhs.Get().size()) return false;
  assert(lhs.Get().size() == rhs.Get().size());
  const int sz = lhs.Get().size();
  for (int i = 0; i!=sz; ++i)
  {
    if (*lhs.Get()[i] < *rhs.Get()[i]) return true;
    if (*lhs.Get()[i] > *rhs.Get()[i]) return false;
  }
  return false;
}
