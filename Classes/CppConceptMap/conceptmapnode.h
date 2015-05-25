//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#ifndef CONCEPTMAPNODE_H
#define CONCEPTMAPNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include "conceptmapfwd.h"
#include "conceptmapelement.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct NodeFactory;

///A Node is a Concept with coordinats, that is used as an Element in a ConceptMap
///A Node is the GUI independent part of a node. It is displayed as:
/// - QtNode (as QtConceptMapElement: a QGraphicsItem, to be used in a QGraphicsView)
/// - QtNodeDialog (as a QDialog, to be used in a QDialog)
///Node is used as a base class by:
/// - CenterNode
struct  Node : public Element
{
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  ///Get the Concept
  boost::shared_ptr<const Concept>  GetConcept() const noexcept { return m_concept; }
  boost::shared_ptr<      Concept>& GetConcept()       noexcept { return m_concept; }

  ///Get some test nodes
  static std::vector<boost::shared_ptr<Node>> GetTests() noexcept;

  ///Get the x coordinat
  double GetX() const noexcept { return m_x; }

  ///Get the y coordinat
  double GetY() const noexcept { return m_y; }

  ///Similar to operator==, except that GUI elements are not tested for equality
  static bool HasSameContent(const boost::shared_ptr<const Node>& lhs, const boost::shared_ptr<const Node>& rhs) noexcept;

  ///Set the concept
  void SetConcept(const boost::shared_ptr<Concept>& concept) noexcept;

  ///Set the position
  void SetPos(const double x, const double y) noexcept { SetX(x); SetY(y); }

  ///Set the x coordinat
  void SetX(const double x) noexcept;

  ///Set the y coordinat
  void SetY(const double y) noexcept;

  virtual std::string ToXml() const noexcept;
  std::string ToStr() const noexcept;

  mutable boost::signals2::signal<void(Node *)> m_signal_concept_changed;
  mutable boost::signals2::signal<void(Node *)> m_signal_x_changed;
  mutable boost::signals2::signal<void(Node *)> m_signal_y_changed;

  protected:
  ///Block construction, except for NodeFactory and derived classes
  Node() = delete;
  friend class NodeFactory;

  ///Use NodeFactory as an unused argument to enforce using it
  explicit Node(
    const boost::shared_ptr<Concept>& concept,
    const double x,
    const double y,
    const NodeFactory& lock
  );

  ///Block destructor, except for the friend boost::checked_delete
  virtual ~Node() noexcept {}
  friend void boost::checked_delete<>(Node* x);

  private:

  ///The Concept
  boost::shared_ptr<Concept> m_concept;

  ///The x-coordinat
  double m_x;

  ///The y-coordinat
  double m_y;

  ///Called whenever something on Concept changes
  ///Re-emits m_concept_changed with 'this'
  void OnConceptChanged(Concept * const this_concept) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};


bool operator==(const Node& lhs, const Node& rhs) noexcept;
bool operator!=(const Node& lhs, const Node& rhs) noexcept;
bool operator<(const Node& lhs, const Node& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Node& node) noexcept;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPNODE_H
