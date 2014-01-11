#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapconcept.h"

#include <cassert>

#ifdef MXE_SUPPORTS_THREADS
#include <thread>
#endif

#include "trace.h"
#include "conceptmaphelper.h"
#include "conceptmapconceptfactory.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::Concept::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
    {
  #endif

  cmap::TestHelperFunctions();
  TRACE("Started ribi::cmap::Concept::Test");
  //Test operator== and operator!=
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    assert(sz > 0);
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_a = ConceptFactory::GetTests();
      const auto tmp_b = ConceptFactory::GetTests();
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
        assert(j < static_cast<int>(ConceptFactory::GetTests().size()));
        const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory::GetTests().at(j);
        const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory::GetTests().at(j);
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
  //Test operator<
  {
    //Check correct ordering by name
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory::Create("2");
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory::Create("2");
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    //Check correct ordering by examples' size, sizes 0 versus 1
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    //Check correct ordering by examples' size, sizes 1 versus 2
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
    //Check correct ordering for equal examples' size, lexicographically in the 2nd text
    {
      const boost::shared_ptr<const ribi::cmap::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<const ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      const boost::shared_ptr<      ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(*a < *c); assert(*a < *d);
      assert(*b < *c); assert(*b < *d);
    }
  }
  //Test XML conversion
  {
    const auto v = AddConst(ConceptFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const ribi::cmap::Concept>& original)
      {
        //Test copy constructor and operator==
        boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::DeepCopy(original);
        assert(c);
        assert(operator==(*c,*original));
        //Test operator!=
        c->m_name = c->m_name + " (modified)";
        assert(!operator==(*c,*original));
        //Test ToXml and FromXml
        const std::string s = ToXml(c);
        const boost::shared_ptr<ribi::cmap::Concept> d = FromXml(s);
        assert(d);
        assert(*c == *d);
      }
    );
  }
  TRACE("Concept::Test finished successfully");

  #ifdef MXE_SUPPORTS_THREADS
    }
  );
  t.detach();
  #endif
}
#endif
