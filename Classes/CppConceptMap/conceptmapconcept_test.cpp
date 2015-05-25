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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapconcept.h"

#include <cassert>

#include "conceptmaphelper.h"
#include "conceptmapconceptfactory.h"
#include "counter.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::Concept::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestHelperFunctions();
  const bool verbose{false};
  const TestTimer test_timer(__func__,__FILE__,1.0);
  if (verbose) { TRACE("Test operator== and operator!="); }
  {
    const int sz = static_cast<int>(ConceptFactory().GetTests().size());
    assert(sz > 0);
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_a = ConceptFactory().GetTests();
      const auto tmp_b = ConceptFactory().GetTests();
      const boost::shared_ptr<const ribi::cmap::Concept> a = tmp_a.at(i);
      const boost::shared_ptr<      ribi::cmap::Concept> b = tmp_b.at(i);
      assert(b); //FAILS AT CROSSCOMPILER
      assert(a);
      assert(a!=b);
      assert(*a == *a);
      assert(*b == *a);
      assert(*a == *b);
      assert(*b == *b);
      for (int j=0; j!=sz; ++j)
      {
        assert(j < static_cast<int>(ConceptFactory().GetTests().size()));
        const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory().GetTests().at(j);
        const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory().GetTests().at(j);
        assert(c); assert(d);
        assert(*c == *c);
        assert(*d == *c);
        assert(*c == *d);
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
  if (verbose) { TRACE("Test operator<"); }
  {
    if (verbose) { TRACE("operator< must order by name"); }
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory().Create("1");
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory().Create("1");
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory().Create("2");
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory().Create("2");
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    if (verbose) { TRACE("operator< must order by examples' size, sizes 0 versus 1"); }
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory().Create("1");
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory().Create("1");
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory().Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory().Create("1", { {"2",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    if (verbose) { TRACE("operator< must order by examples' size, sizes 1 versus 2"); }
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory().Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory().Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    if (verbose) { TRACE("Check correct ordering for equal examples' size, lexicographically in the 2nd text"); }
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory().Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory().Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
  }
  if (verbose) { TRACE("Test XML conversion"); }
  {
    const auto v = AddConst(ConceptFactory().GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const ribi::cmap::Concept>& original)
      {
        //Test copy constructor and operator==
        boost::shared_ptr<Concept> c = ConceptFactory().DeepCopy(original);
        assert(c);
        assert(*c == *original);
        //Test operator!=
        c->m_name = c->m_name + " (modified)";
        assert(*c != *original);
        //Test ToXml and FromXml
        const std::string s = c->ToXml();
        const boost::shared_ptr<Concept> d = ConceptFactory().FromXml(s);
        assert(d);
        assert(*c == *d);
      }
    );
  }
  if (verbose) { TRACE("When setting the name, a signal must be emitted"); }
  {
    const auto concept = ConceptFactory().GetTest(0);
    concept->SetName("A");
    Counter c{0}; //For receiving the signal
    concept->m_signal_name_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    concept->SetName("B");
    assert(c.Get() == 1);
  }
}
#endif
