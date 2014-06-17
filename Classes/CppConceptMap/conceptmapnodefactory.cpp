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
#include "conceptmapnodefactory.h"

#include "conceptmapcenternode.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "geometry.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::NodeFactory::NodeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y
) const noexcept
{
  assert(concept);
  const boost::shared_ptr<Node> node(
    new Node(concept,x,y,*this)
  );
  assert(node);
  assert(node->GetConcept());
  #ifndef NDEBUG
  if(*concept != *node->GetConcept())
  {
    TRACE(concept);
    TRACE(node->GetConcept());
    TRACE(*concept);
    TRACE(*node->GetConcept());
    TRACE("BREAK");
  }
  #endif
  assert(*concept == *node->GetConcept());
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::CreateFromStrings(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y
) const noexcept
{
  const boost::shared_ptr<Node> node(
    new Node(
      ConceptFactory().Create(name,examples),
      x,
      y,
      *this
    )
  );
  assert(node);
  assert(node->GetConcept());
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

#ifndef NDEBUG
boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::DeepCopy(
  const boost::shared_ptr<const cmap::Node>& node) const noexcept
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<Concept> new_concept
    = ConceptFactory().DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(*node->GetConcept() == *new_concept);
  const boost::shared_ptr<Node> new_node
    = Create(new_concept,
      node->GetX(),
      node->GetY()
    );
  assert(new_node);
  assert(new_node->GetConcept());
  assert(*node == *new_node);
  return new_node;
}
#endif

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::FromXml(const std::string& s) const noexcept
{
  {
    const boost::shared_ptr<CenterNode> center_node {
      CenterNodeFactory().FromXml(s)
    };
    if (center_node) { return center_node; }
  }

  const bool verbose = false;
  if (s.size() < 13)
  {
    if (verbose) TRACE("string too short");
    return boost::shared_ptr<Node>();

  }
  if (s.substr(0,6) != "<node>")
  {
    if (verbose) TRACE("incorrect starting tag");
    return boost::shared_ptr<Node>();
  }
  if (s.substr(s.size() - 7,7) != "</node>")
  {
    if (verbose) TRACE("incorrect ending tag");
    return boost::shared_ptr<Node>();
  }

  //m_concept
  boost::shared_ptr<Concept> concept;
  {
    const std::vector<std::string> v
      = Geometry().GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = ConceptFactory().FromXml(v[0]);
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v
      = Geometry().GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double y = 0.0;
  {
    const std::vector<std::string> v
      = Geometry().GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(concept);
  const boost::shared_ptr<Node> node(NodeFactory().Create(concept,x,y));
  assert(node);
  //assert(node->ToXml() == s); //TODO RJCB: Put back in
  return node;
}

int ribi::cmap::NodeFactory::GetNumberOfTests() const noexcept
{
  return static_cast<int>(GetTests().size());
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::GetTest(const int i) const noexcept
{
  const auto tests = GetTests();
  assert(i >= 0);
  assert(i < static_cast<int>(tests.size()));
  return tests[i];
}

std::vector<boost::shared_ptr<ribi::cmap::Node>> ribi::cmap::NodeFactory::GetTests() const noexcept
{
  std::vector<boost::shared_ptr<ribi::cmap::Node> > nodes;
  const auto v = ConceptFactory().GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(nodes),
    [](const boost::shared_ptr<ribi::cmap::Concept>& c)
    {
      static int x = 0;
      static int y = 1;
      const boost::shared_ptr<Node> p(NodeFactory().Create(c,x,y));
      ++x;
      ++y;
      assert(p);
      return p;
    }
  );
  return nodes;
}

#ifndef NDEBUG
void ribi::cmap::NodeFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::NodeFactory::Test");
  TRACE("Finished ribi::cmap::NodeFactory successfully");
}
#endif
