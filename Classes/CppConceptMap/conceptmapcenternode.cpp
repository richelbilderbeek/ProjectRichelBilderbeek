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
#include "conceptmapcenternode.h"

#include <cassert>
#include <sstream>

#include "conceptmapconcept.h"
#include "conceptmapnodefactory.h"
#include "testtimer.h"

ribi::cmap::CenterNode::CenterNode(
  const boost::shared_ptr<Concept>& concept,
  const double x,
  const double y,
  const CenterNodeFactory&
)
  : Node(concept,x,y,NodeFactory())
{

}

bool ribi::cmap::IsCenterNode(const boost::shared_ptr<const ribi::cmap::Node> node) noexcept
{
  assert(node);
  return boost::dynamic_pointer_cast<const CenterNode>(node).get();
}

std::string ribi::cmap::CenterNode::ToXml() const noexcept
{
  std::stringstream s;
  s << "<center_node>";
  s << GetConcept()->ToXml();
  s << "<x>" << GetX() << "</x>";
  s << "<y>" << GetY() << "</y>";
  s << "</center_node>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,13) == "<center_node>");
  assert(r.substr(r.size() - 14,14) == "</center_node>");

  return r;
}

