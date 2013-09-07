#include "pvdbconcept.h"

#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include "trace.h"
#include "pvdbhelper.h"
#include "pvdbconceptfactory.h"

#ifndef NDEBUG
void ribi::pvdb::Concept::Test()
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

  pvdb::TestHelperFunctions();
  TRACE("Started ribi::pvdb::Concept::Test");
  //Test operator== and operator!=
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    assert(sz > 0);
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_a = ConceptFactory::GetTests();
      const auto tmp_b = ConceptFactory::GetTests();
      const boost::shared_ptr<const ribi::pvdb::Concept> a = tmp_a.at(i);
      const boost::shared_ptr<      ribi::pvdb::Concept> b = tmp_b.at(i);
      assert(b); //FAILS AT CROSSCOMPILER
      assert(a);
      assert(a!=b);
      assert(IsEqual(*a,*a));
      assert(IsEqual(*b,*a));
      assert(IsEqual(*a,*b));
      assert(IsEqual(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const ribi::pvdb::Concept> c = ConceptFactory::GetTests().at(j);
        const boost::shared_ptr<      ribi::pvdb::Concept> d = ConceptFactory::GetTests().at(j);
        assert(c); assert(d);
        assert(IsEqual(*c,*c));
        assert(IsEqual(*d,*c));
        assert(IsEqual(*c,*d));
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
  //Test operator<
  {
    //Check correct ordering by name
    {
      const boost::shared_ptr<const ribi::pvdb::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      ribi::pvdb::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const ribi::pvdb::Concept> c = ConceptFactory::Create("2");
      const boost::shared_ptr<      ribi::pvdb::Concept> d = ConceptFactory::Create("2");
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering by examples' size, sizes 0 versus 1
    {
      const boost::shared_ptr<const ribi::pvdb::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      ribi::pvdb::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const ribi::pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering by examples' size, sizes 1 versus 2
    {
      const boost::shared_ptr<const ribi::pvdb::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      ribi::pvdb::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<const ribi::pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering for equal examples' size, lexicographically in the 2nd text
    {
      const boost::shared_ptr<const ribi::pvdb::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      ribi::pvdb::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<const ribi::pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      const boost::shared_ptr<      ribi::pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
  }
  //Test XML conversion
  {
    const auto v = AddConst(ConceptFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const ribi::pvdb::Concept>& original)
      {
        //Test copy constructor and operator==
        boost::shared_ptr<ribi::pvdb::Concept> c = ConceptFactory::DeepCopy(original);
        assert(c);
        assert(IsEqual(*c,*original));
        //Test operator!=
        c->m_name = c->m_name + " (modified)";
        assert(!IsEqual(*c,*original));
        //Test ToXml and FromXml
        const std::string s = ToXml(c);
        const boost::shared_ptr<ribi::pvdb::Concept> d = FromXml(s);
        assert(d);
        assert(IsEqual(*c,*d));
      }
    );
  }
  TRACE("Concept::Test finished successfully");

  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
