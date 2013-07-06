#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbnode.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbnodefactory.h"
#include "pvdbexamplefactory.h"
#include "pvdbhelper.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Node::Node(const boost::shared_ptr<pvdb::Concept>& concept, const double x, const double y)
  : m_concept(concept),
    m_x(x),
    m_y(y)
{
  #ifndef NDEBUG
  Test();
  assert(m_concept);
  #endif
}

const boost::shared_ptr<pvdb::Node> pvdb::Node::FromXml(const std::string& s)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<node>"));
  assert(s.substr(s.size() - 7,7) == std::string("</node>"));

  //m_concept
  boost::shared_ptr<pvdb::Concept> concept;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = Concept::FromXml(v[0]);
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(StripXmlTag(v[0]));
  }
  //m_x
  double y = 0.0;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(StripXmlTag(v[0]));
  }
  assert(concept);
  const boost::shared_ptr<pvdb::Node> node(new Node(concept,x,y));
  return node;
}

const std::vector<boost::shared_ptr<pvdb::Node> > pvdb::Node::GetTests()
{
  const auto test_concepts = ConceptFactory::GetTests();
  std::vector<boost::shared_ptr<pvdb::Node> > result;
  std::for_each(test_concepts.begin(),test_concepts.end(),
    [&result](const boost::shared_ptr<pvdb::Concept>& concept)
    {
      const int x = (std::rand() % 256) - 128;
      const int y = (std::rand() % 256) - 128;
      const boost::shared_ptr<pvdb::Node> node(new Node(concept,x,y));
      result.push_back(node);
    }
  );
  return result;
}

bool pvdb::Node::HasSameContent(const boost::shared_ptr<const pvdb::Node>& lhs, const boost::shared_ptr<const pvdb::Node>& rhs)
{
  assert(lhs);
  assert(rhs);
  return IsEqual(*lhs->GetConcept(),*rhs->GetConcept());
}

void pvdb::Node::SetConcept(const boost::shared_ptr<pvdb::Concept> concept)
{
  if (m_concept != concept)
  {
    m_concept = concept;
    m_signal_node_changed(this);
  }
}

void pvdb::Node::SetX(const double x)
{
  if (m_x != x)
  {
    m_x = x;
    m_signal_node_changed(this);
  }
}

void pvdb::Node::SetY(const double y)
{
  if (m_y != y)
  {
    m_y = y;
    m_signal_node_changed(this);
  }
}

#ifndef NDEBUG
void pvdb::Node::Test()
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
  TRACE("Started pvdb::Node::Test");
  {
    const std::vector<boost::shared_ptr<pvdb::Node> > v = pvdb::Node::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::Node> node)
      {
        //Test copy constructor
        assert(node);
        const boost::shared_ptr<const pvdb::Node> c = NodeFactory::DeepCopy(node);
        assert(c);
        assert(IsEqual(*node,*c));
        const std::string s = ToXml(c);
        const boost::shared_ptr<pvdb::Node> d = FromXml(s);
        assert(d);
        assert(IsEqual(*c,*d));
      }
    );
  }
  //Test HasSameContent
  {
    {
      const boost::shared_ptr<pvdb::Concept> c(pvdb::ConceptFactory::Create("1"));
      const boost::shared_ptr<pvdb::Concept> d(pvdb::ConceptFactory::Create("1"));
      assert(IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(a);
      assert(b);
      assert(HasSameContent(a,b));
      assert(IsEqual(*a,*b));
    }
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized} } );
      const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized} } );
      assert(c != d);
      assert(IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(HasSameContent(a,b));
    }

    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized},{"3", pvdb::Competency::uninitialized} } );
      const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized},{"3", pvdb::Competency::uninitialized} } );
      assert(c != d);
      assert(IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(HasSameContent(a,b));
      assert(IsEqual(*a,*b));
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized},{"3", pvdb::Competency::uninitialized} } );
      const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::Create("1", { {"3", pvdb::Competency::uninitialized},{"2", pvdb::Competency::uninitialized} } );
      assert(c != d);
      assert(!IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(!HasSameContent(a,b) && "Order in examples is important and cannot be shuffled");
      assert(a != b);
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized},{"3", pvdb::Competency::uninitialized} } );
      const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::Create("1", { {"2", pvdb::Competency::uninitialized} } );
      assert(c != d);
      assert(!IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(a != b);
      assert(!HasSameContent(a,b));
      assert(!IsEqual(*a,*b));
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::GetTests()[i];
      const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::GetTests()[i];
      assert(c != d);
      assert(IsEqual(*c,*d));
      const boost::shared_ptr<pvdb::Node> a(new Node(c));
      const boost::shared_ptr<pvdb::Node> b(new Node(d));
      assert(a != b);
      assert(HasSameContent(a,b));
      assert(IsEqual(*a,*b));
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<pvdb::Concept> c = ConceptFactory::GetTests()[i];
        assert(c);
        const boost::shared_ptr<pvdb::Concept> d = ConceptFactory::GetTests()[j];
        assert(d);
        assert(c != d);
        if (i!=j)
        {
          assert(!IsEqual(*c,*d));
          const boost::shared_ptr<pvdb::Node> a(new Node(c));
          const boost::shared_ptr<pvdb::Node> b(new Node(d));
          assert(a != b);
          assert(!HasSameContent(a,b));
          assert(!IsEqual(*a,*b));
        }
        else
        {
          assert(IsEqual(*c,*d));
          const boost::shared_ptr<pvdb::Node> a(new Node(c));
          const boost::shared_ptr<pvdb::Node> b(new Node(d));
          assert(a != b);
          assert(HasSameContent(a,b));
          assert(IsEqual(*a,*b));
        }
      }
    }
  }

  TRACE("Node::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

const std::string pvdb::Node::ToXml(const boost::shared_ptr<const pvdb::Node>& node)
{
  std::stringstream s;
  s << "<node>";
  s << Concept::ToXml(node->GetConcept());
  s << "<x>" << node->GetX() << "</x>";
  s << "<y>" << node->GetY() << "</y>";
  s << "</node>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == std::string("<node>"));
  assert(r.substr(r.size() - 7,7) == std::string("</node>"));

  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::Node& lhs, const pvdb::Node& rhs)
{
  assert(lhs.GetConcept()); assert(rhs.GetConcept());
  return
       IsEqual(*lhs.GetConcept(),*rhs.GetConcept())
    && lhs.GetX()       == rhs.GetX()
    && lhs.GetY()       == rhs.GetY();
}

} //~namespace pvdb
