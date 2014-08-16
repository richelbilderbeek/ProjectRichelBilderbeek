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
#include "conceptmapedgefactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "conceptmapregex.h"
#include "testtimer.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::EdgeFactory::EdgeFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}


ribi::cmap::EdgeFactory::EdgePtr ribi::cmap::EdgeFactory::Create(
  const NodePtr& from,
  const NodePtr& to
) const noexcept
{
  assert(from);
  assert(to);
  assert(from != to);
  const double x{(from->GetX() + to->GetX()) / 2.0};
  const double y{(from->GetY() + to->GetY()) / 2.0};
  const bool tail_arrow{false};
  const bool head_arrow{true};
  const auto concept = ConceptFactory().Create();
  assert(concept->GetExamples());

  const auto node = NodeFactory().Create(concept,x,y);
  assert(node);
  const EdgePtr p {
    new Edge(
      node,
      from,
      tail_arrow,
      to,
      head_arrow
    )
  };
  assert(p);
  return p;
}

ribi::cmap::EdgeFactory::EdgePtr ribi::cmap::EdgeFactory::Create(
  const NodePtr& node,
  const NodePtr& from,
  const bool tail_arrow,
  const NodePtr& to,
  const bool head_arrow
) const noexcept
{
  assert(node);
  assert(node->GetConcept());
  assert(node->GetConcept()->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  EdgePtr p(new Edge(node,from,tail_arrow,to,head_arrow));
  assert(p);
  return p;
}

#ifndef NDEBUG
ribi::cmap::EdgeFactory::EdgePtr ribi::cmap::EdgeFactory::DeepCopy(
  const ReadOnlyEdge& edge,
  const NodePtr& from,
  const NodePtr& to
) const noexcept
{
  assert(edge);
  assert(edge->GetNode());
  assert(edge->GetNode()->GetConcept());
  assert(edge->GetNode()->GetConcept()->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  //const boost::shared_ptr<Concept> concept = ConceptFactory().DeepCopy(edge->GetNode());
  const auto node = NodeFactory().DeepCopy(edge->GetNode());
  assert(node);
  const EdgePtr p {
    EdgeFactory::Create(
      node,
      from,
      edge->HasTailArrow(),
      to,
      edge->HasHeadArrow()
    )
  };
  assert(p);
  assert(*edge == *p);
  return p;
}
#endif

ribi::cmap::EdgeFactory::EdgePtr ribi::cmap::EdgeFactory::FromXml(
  const std::string& s,
  const Nodes& nodes
) const noexcept
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == "<edge>");
  assert(s.substr(s.size() - 7,7) == "</edge>");
  //m_concept
  boost::shared_ptr<Concept> concept;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexConcept());
    assert(v.size() == 1);
    concept = ConceptFactory().FromXml(v[0]);
  }
  //m_from
  int from = -1;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexFrom());
    assert(v.size() == 1);
    from = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_head_arrow
  bool head_arrow = false;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexHeadArrow());
    assert(v.size() == 1);
    head_arrow = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_tail_arrow
  bool tail_arrow = false;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexTailArrow());
    assert(v.size() == 1);
    tail_arrow = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_to
  int to = -1;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexTo());
    assert(v.size() == 1);
    to = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexX());
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_y
  double y = 0.0;
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexY());
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(from != to);
  assert(from < boost::numeric_cast<int>(nodes.size()));
  assert(to   < boost::numeric_cast<int>(nodes.size()));
  const auto node = NodeFactory().Create(concept,x,y);
  const EdgePtr edge(new Edge(node,nodes[from],tail_arrow,nodes[to],head_arrow));
  assert(edge);
  return edge;
}

int ribi::cmap::EdgeFactory::GetNumberOfTests() const noexcept
{
  return ConceptFactory().GetNumberOfTests();
}

ribi::cmap::EdgeFactory::EdgePtr ribi::cmap::EdgeFactory::GetTest(
  const int index,
  const NodePtr& from,
  const NodePtr& to
) const noexcept
{
  assert(from);
  assert(to);
  assert(index >= 0);
  assert(index < GetNumberOfTests());
  return GetTests(from,to)[index];
}

ribi::cmap::EdgeFactory::Edges ribi::cmap::EdgeFactory::GetTests(
  const NodePtr& from,
  const NodePtr& to
) const noexcept
{
  assert(from);
  assert(to);
  const int n{NodeFactory().GetNumberOfTests()};
  std::vector<EdgePtr> result;

  for(int i{0}; i!=n; ++i)
  {
    {
      const auto node = NodeFactory().GetTest(i);
      const EdgePtr edge{new Edge(node,from,false,to,true)};
      result.push_back(edge);
    }
    /*
    {
      const EdgePtr edge(new Edge(concept,0,2,true));
      result.push_back(edge);
    }
    {
      const EdgePtr edge(new Edge(concept,0,3,true));
      result.push_back(edge);
    }
    {
      const EdgePtr edge(new Edge(concept,1,2,false));
      result.push_back(edge);
    }
    {
      const EdgePtr edge(new Edge(concept,1,3,false));
      result.push_back(edge);
    }
    {
      const EdgePtr edge(new Edge(concept,2,3,false));
      result.push_back(edge);
    }
    */
  }
  if (GetNumberOfTests() != static_cast<int>(result.size()))
  {
    TRACE("ERROR");
    std::stringstream s;
    s << "GetNumberOfTests should return " << result.size();
    TRACE(s.str());
  }
  assert(GetNumberOfTests() == static_cast<int>(result.size()));
  return result;
}


#ifndef NDEBUG
void ribi::cmap::EdgeFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  EdgeFactory().GetTest(
     0,
     NodeFactory().GetTest(0),
     NodeFactory().GetTest(0)
  );
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif // NDEBUG
