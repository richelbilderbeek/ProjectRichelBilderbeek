#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconcept.h"

#include <cassert>
#include "trace.h"
#include "pvdbhelper.h"
#include "pvdbconceptfactory.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

void pvdb::Concept::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  pvdb::TestHelperFunctions();
  TRACE("Started pvdb::Concept::Test");
  //Test operator== and operator!=
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    assert(sz > 0);
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_a = ConceptFactory::GetTests();
      const auto tmp_b = ConceptFactory::GetTests();
      const boost::shared_ptr<const pvdb::Concept> a = tmp_a.at(i);
      const boost::shared_ptr<      pvdb::Concept> b = tmp_b.at(i);
      assert(b); //FAILS AT CROSSCOMPILER
      assert(a);
      assert(a==a); assert(a==b); assert(b==a); assert(b==b);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const pvdb::Concept> c = ConceptFactory::GetTests().at(j);
        const boost::shared_ptr<      pvdb::Concept> d = ConceptFactory::GetTests().at(j);
        assert(c); assert(d);
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
  //Test operator<
  {
    //Check correct ordering by name
    {
      const boost::shared_ptr<const pvdb::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      pvdb::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const pvdb::Concept> c = ConceptFactory::Create("2");
      const boost::shared_ptr<      pvdb::Concept> d = ConceptFactory::Create("2");
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering by examples' size, sizes 0 versus 1
    {
      const boost::shared_ptr<const pvdb::Concept> a = ConceptFactory::Create("1");
      const boost::shared_ptr<      pvdb::Concept> b = ConceptFactory::Create("1");
      const boost::shared_ptr<const pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering by examples' size, sizes 1 versus 2
    {
      const boost::shared_ptr<const pvdb::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<      pvdb::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc} } );
      const boost::shared_ptr<const pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
    //Check correct ordering for equal examples' size, lexicographically in the 2nd text
    {
      const boost::shared_ptr<const pvdb::Concept> a = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<      pvdb::Concept> b = ConceptFactory::Create("1", { {"2",Competency::misc},{"3",Competency::misc} } );
      const boost::shared_ptr<const pvdb::Concept> c = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      const boost::shared_ptr<      pvdb::Concept> d = ConceptFactory::Create("1", { {"2",Competency::misc},{"4",Competency::misc} } );
      assert(a); assert(b); assert(c); assert(d);
      assert(a < c); assert(a < d);
      assert(b < c); assert(b < d);
    }
  }
  //Test XML conversion
  {
    const auto v = AddConst(ConceptFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::Concept>& original)
      {
        //Test copy constructor and operator==
        boost::shared_ptr<pvdb::Concept> c = ConceptFactory::DeepCopy(original);
        assert(c);
        assert(c == original);
        //Test operator!=
        c->m_name = c->m_name + " (modified)";
        assert(c != original);
        //Test ToXml and FromXml
        const std::string s = ToXml(c);
        const boost::shared_ptr<pvdb::Concept> d = FromXml(s);
        assert(d);
        assert(c == d);
      }
    );
  }
  TRACE("Concept::Test finished successfully");
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
