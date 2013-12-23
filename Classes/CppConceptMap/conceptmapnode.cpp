#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapnode.h"

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapnodefactory.h"
#include "conceptmapexamplefactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::Node::Node(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y)
  : m_signal_node_changed{},
    m_concept(concept),
    m_x(x),
    m_y(y)
{
  #ifndef NDEBUG
  Test();
  assert(m_concept);
  #endif
}

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::Node::FromXml(const std::string& s)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<node>"));
  assert(s.substr(s.size() - 7,7) == std::string("</node>"));

  //m_concept
  boost::shared_ptr<ribi::cmap::Concept> concept;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = Concept::FromXml(v[0]);
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double y = 0.0;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(concept);
  const boost::shared_ptr<ribi::cmap::Node> node(new Node(concept,x,y));
  return node;
}

const std::vector<boost::shared_ptr<ribi::cmap::Node> > ribi::cmap::Node::GetTests()
{
  const auto test_concepts = ConceptFactory::GetTests();
  std::vector<boost::shared_ptr<ribi::cmap::Node> > result;
  std::for_each(test_concepts.begin(),test_concepts.end(),
    [&result](const boost::shared_ptr<ribi::cmap::Concept>& concept)
    {
      const int x = (std::rand() % 256) - 128;
      const int y = (std::rand() % 256) - 128;
      const boost::shared_ptr<ribi::cmap::Node> node(new Node(concept,x,y));
      result.push_back(node);
    }
  );
  return result;
}

bool ribi::cmap::Node::HasSameContent(const boost::shared_ptr<const cmap::Node>& lhs, const boost::shared_ptr<const cmap::Node>& rhs)
{
  assert(lhs);
  assert(rhs);
  return operator==(*lhs->GetConcept(),*rhs->GetConcept());
}

void ribi::cmap::Node::SetConcept(const boost::shared_ptr<ribi::cmap::Concept> concept)
{
  if (m_concept != concept)
  {
    m_concept = concept;
    m_signal_node_changed(this);
  }
}

void ribi::cmap::Node::SetX(const double x)
{
  if (m_x != x)
  {
    m_x = x;
    m_signal_node_changed(this);
  }
}

void ribi::cmap::Node::SetY(const double y)
{
  if (m_y != y)
  {
    m_y = y;
    m_signal_node_changed(this);
  }
}

#ifndef NDEBUG
void ribi::cmap::Node::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::Node::Test");
  {
    const std::vector<boost::shared_ptr<ribi::cmap::Node> > v = ribi::cmap::Node::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::cmap::Node> node)
      {
        //Test copy constructor
        assert(node);
        const boost::shared_ptr<const cmap::Node> c = NodeFactory::DeepCopy(node);
        assert(c);
        assert(operator==(*node,*c));
        const std::string s = ToXml(c);
        const boost::shared_ptr<ribi::cmap::Node> d = FromXml(s);
        assert(d);
        assert(operator==(*c,*d));
      }
    );
  }
  //Test HasSameContent
  {
    {
      const boost::shared_ptr<ribi::cmap::Concept> c(cmap::ConceptFactory::Create("1"));
      const boost::shared_ptr<ribi::cmap::Concept> d(cmap::ConceptFactory::Create("1"));
      assert(operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(a);
      assert(b);
      assert(HasSameContent(a,b));
      assert(operator==(*a,*b));
    }
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(HasSameContent(a,b));
    }

    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(HasSameContent(a,b));
      assert(operator==(*a,*b));
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"3", cmap::Competency::uninitialized},{"2", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(!operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(!HasSameContent(a,b) && "Order in examples is important and cannot be shuffled");
      assert(a != b);
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::Create("1", { {"2", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(!operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(a != b);
      assert(!HasSameContent(a,b));
      assert(!operator==(*a,*b));
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::GetTests()[i];
      const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::GetTests()[i];
      assert(c != d);
      assert(operator==(*c,*d));
      const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
      const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
      assert(a != b);
      assert(HasSameContent(a,b));
      assert(operator==(*a,*b));
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<ribi::cmap::Concept> c = ConceptFactory::GetTests()[i];
        assert(c);
        const boost::shared_ptr<ribi::cmap::Concept> d = ConceptFactory::GetTests()[j];
        assert(d);
        assert(c != d);
        if (i!=j)
        {
          assert(!operator==(*c,*d));
          const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
          const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
          assert(a != b);
          assert(!HasSameContent(a,b));
          assert(!operator==(*a,*b));
        }
        else
        {
          assert(operator==(*c,*d));
          const boost::shared_ptr<ribi::cmap::Node> a(new Node(c));
          const boost::shared_ptr<ribi::cmap::Node> b(new Node(d));
          assert(a != b);
          assert(HasSameContent(a,b));
          assert(operator==(*a,*b));
        }
      }
    }
  }

  TRACE("Node::Test finished successfully");
}
#endif

const std::string ribi::cmap::Node::ToXml(const boost::shared_ptr<const cmap::Node>& node)
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

bool ribi::cmap::operator==(const cmap::Node& lhs, const cmap::Node& rhs)
{
  assert(lhs.GetConcept());
  assert(rhs.GetConcept());
  return
       *lhs.GetConcept() == *rhs.GetConcept()
    && lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY();
}

bool ribi::cmap::operator!=(const cmap::Node& lhs, const cmap::Node& rhs)
{
  return !(lhs == rhs);
}
