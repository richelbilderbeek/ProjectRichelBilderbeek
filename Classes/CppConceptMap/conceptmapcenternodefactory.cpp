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
#include "conceptmapcenternodefactory.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "conceptmapcenternode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmaphelper.h"
#include "geometry.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::CenterNodeFactory::CenterNodeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y) const noexcept
{
  assert(concept);
  boost::shared_ptr<CenterNode> node(
    new cmap::CenterNode(
      concept,x,y,*this
    )
  );
  assert(node);
  assert(*concept == *node->GetConcept());
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::CreateFromStrings(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y
) const noexcept
{
  boost::shared_ptr<CenterNode> node(
    new CenterNode(
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
const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::DeepCopy(
  const boost::shared_ptr<const cmap::CenterNode>& node
) const noexcept
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<Concept> new_concept {
    ConceptFactory().DeepCopy(node->GetConcept())
  };
  assert(new_concept);
  assert(*node->GetConcept() == *new_concept);
  const boost::shared_ptr<CenterNode> new_node
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

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::FromXml(
  const std::string& s
) const noexcept
{
  if (s.size() < 27)
  {
    return boost::shared_ptr<CenterNode>();
  }
  if (s.substr(0,13) != "<center_node>")
  {
    return boost::shared_ptr<CenterNode>();
  }
  if (s.substr(s.size() - 14,14) != "</center_node>")
  {
    return boost::shared_ptr<CenterNode>();
  }

  //m_concept
  boost::shared_ptr<Concept> concept;
  {
    const std::vector<std::string> v
      = Geometry().GetRegexMatches(s,("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = ConceptFactory().FromXml(v[0]);
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = Geometry().GetRegexMatches(s,("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double y = 0.0;
  {
    const std::vector<std::string> v
      = Geometry().GetRegexMatches(s,("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(concept);
  const boost::shared_ptr<CenterNode> node(new CenterNode(concept,x,y,*this));
  assert(node);
  assert(node->ToXml() == s);
  return node;
}

#ifndef NDEBUG
void ribi::cmap::CenterNodeFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::CenterNodeFactory::Test");
  TRACE("CenterNodeFactory::Test finished successfully");
}
#endif
