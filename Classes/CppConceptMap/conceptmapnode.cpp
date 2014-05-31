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
  const double y,
  const NodeFactory&
) : m_signal_concept_changed{},
    m_signal_x_changed{},
    m_signal_y_changed{},
    m_concept(concept),
    m_x(x),
    m_y(y)
{
  #ifndef NDEBUG
  Test();
  assert(m_concept);
  #endif
}


std::vector<boost::shared_ptr<ribi::cmap::Node> > ribi::cmap::Node::GetTests() noexcept
{
  const auto test_concepts = ConceptFactory().GetTests();
  std::vector<boost::shared_ptr<Node> > result;
  std::for_each(test_concepts.begin(),test_concepts.end(),
    [&result](const boost::shared_ptr<Concept>& concept)
    {
      const int x = (std::rand() % 256) - 128;
      const int y = (std::rand() % 256) - 128;
      const auto node = NodeFactory().Create(concept,x,y);
      result.push_back(node);
    }
  );
  return result;
}

bool ribi::cmap::Node::HasSameContent(const boost::shared_ptr<const cmap::Node>& lhs, const boost::shared_ptr<const cmap::Node>& rhs) noexcept
{
  assert(lhs);
  assert(rhs);
  return *lhs->GetConcept() == *rhs->GetConcept();
}

void ribi::cmap::Node::SetConcept(const boost::shared_ptr<Concept> concept) noexcept
{
  if (m_concept != concept)
  {
    m_concept = concept;
    m_signal_concept_changed(this);
  }
}

void ribi::cmap::Node::SetX(const double x) noexcept
{
  if (m_x != x)
  {
    m_x = x;
    m_signal_x_changed(this);
  }
}

void ribi::cmap::Node::SetY(const double y) noexcept
{
  if (m_y != y)
  {
    m_y = y;
    m_signal_y_changed(this);
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
    const std::vector<boost::shared_ptr<Node> > v = Node::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<Node> node)
      {
        //Test copy constructor
        assert(node);
        const boost::shared_ptr<const Node> c { NodeFactory().DeepCopy(node) };
        assert(c);
        assert(*node == *c);
        const std::string s = c->ToXml();
        const boost::shared_ptr<Node> d = NodeFactory().FromXml(s);
        assert(d);
        assert(*c == *d);
      }
    );
  }
  //Test HasSameContent
  {
    {
      const boost::shared_ptr<Concept> c(ConceptFactory().Create("1"));
      const boost::shared_ptr<Concept> d(ConceptFactory().Create("1"));
      assert(*c == *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(a);
      assert(b);
      assert(HasSameContent(a,b));
      assert(*a == *b);
    }
    const int sz = static_cast<int>(ConceptFactory().GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<Concept> c = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<Concept> d = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized} } );
      assert( c !=  d);
      assert(*c == *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(HasSameContent(a,b));
    }

    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<Concept> c = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<Concept> d = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      assert( c !=  d);
      assert(*c == *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(HasSameContent(a,b));
      assert(*a == *b);
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<Concept> c = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<Concept> d = ConceptFactory().Create("1", { {"3", cmap::Competency::uninitialized},{"2", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(*c != *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(!HasSameContent(a,b) && "Order in examples is important and cannot be shuffled");
      assert(a != b);
    }
    {
      //Cannot shuffle Concept its examples. No need to as well: the order is important
      const boost::shared_ptr<Concept> c = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized},{"3", cmap::Competency::uninitialized} } );
      const boost::shared_ptr<Concept> d = ConceptFactory().Create("1", { {"2", cmap::Competency::uninitialized} } );
      assert(c != d);
      assert(*c != *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(a != b);
      assert(!HasSameContent(a,b));
      assert(*a != *b);
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory().GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      assert(i < static_cast<int>(ConceptFactory().GetTests().size()));
      const boost::shared_ptr<Concept> c = ConceptFactory().GetTests()[i];
      const boost::shared_ptr<Concept> d = ConceptFactory().GetTests()[i];
      assert(c != d);
      assert(*c == *d);
      const boost::shared_ptr<Node> a(NodeFactory().Create(c));
      const boost::shared_ptr<Node> b(NodeFactory().Create(d));
      assert(a != b);
      assert(HasSameContent(a,b));
      assert(*a == *b);
    }
  }
  //Test ConceptFactory reproductions
  {
    const int sz = static_cast<int>(ConceptFactory().GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        assert(i < static_cast<int>(ConceptFactory().GetTests().size()));
        const boost::shared_ptr<Concept> c = ConceptFactory().GetTests()[i];
        assert(c);
        const boost::shared_ptr<Concept> d = ConceptFactory().GetTests()[j];
        assert(d);
        assert(c != d);
        if (i!=j)
        {
          assert(*c != *d);
          const boost::shared_ptr<Node> a(NodeFactory().Create(c));
          const boost::shared_ptr<Node> b(NodeFactory().Create(d));
          assert(a != b);
          assert(!HasSameContent(a,b));
          assert(*a != *b);
        }
        else
        {
          assert(*c == *d);
          const boost::shared_ptr<Node> a(NodeFactory().Create(c));
          const boost::shared_ptr<Node> b(NodeFactory().Create(d));
          assert(a != b);
          assert(HasSameContent(a,b));
          assert(*a == *b);
        }
      }
    }
  }

  TRACE("Node::Test finished successfully");
}
#endif

std::string ribi::cmap::Node::ToStr() const noexcept
{
  std::stringstream s;
  s
    << GetConcept()->ToStr() << " "
    << GetX() << " "
    << GetY()
  ;
  return s.str();
}


std::string ribi::cmap::Node::ToXml() const noexcept
{
  std::stringstream s;
  s << "<node>";
  s << GetConcept()->ToXml();
  s << "<x>" << GetX() << "</x>";
  s << "<y>" << GetY() << "</y>";
  s << "</node>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == "<node>");
  assert(r.substr(r.size() - 7,7) == "</node>");

  return r;
}

bool ribi::cmap::operator==(const cmap::Node& lhs, const cmap::Node& rhs) noexcept
{
  assert(lhs.GetConcept());
  assert(rhs.GetConcept());
  return
       *lhs.GetConcept() == *rhs.GetConcept()
    && lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY();
}

bool ribi::cmap::operator!=(const cmap::Node& lhs, const cmap::Node& rhs) noexcept
{
  return !(lhs == rhs);
}
