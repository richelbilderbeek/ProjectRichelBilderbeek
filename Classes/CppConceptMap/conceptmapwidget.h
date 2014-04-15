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
#ifndef CONCEPTMAPWIDGET_H
#define CONCEPTMAPWIDGET_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <QPoint>

#include "conceptmapfwd.h"
#include "conceptmapfactory.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Widget does the Command-driven communication with ConceptMap
///Note that a Widget does not know the type of ConceptMap (Display/Edit/Rate)
struct Widget
{
  Widget(const boost::shared_ptr<ConceptMap> conceptmap = CreateEmptyConceptMap());

  #ifndef NDEBUG
  Widget(const Widget& other); //Only to be used in debugging
  #else
  Widget(const Widget& other) = delete;
  #endif

  Widget& operator=(const Widget& rhs) = delete;

  bool CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept;
  bool CanUndo() const noexcept { return !m_undo.empty(); }
  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  boost::shared_ptr<const ConceptMap> GetConceptMap() const noexcept { return m_conceptmap; }
  boost::shared_ptr<      ConceptMap> GetConceptMap()       noexcept { return m_conceptmap; }

  ///There is one item in focus at most
  ///There can be multiple items selected
  ///The node in focus is never in the collection of selected nodes
  ///Use GetFocusAndSelected to get all
  boost::shared_ptr<const Node> GetFocus() const noexcept;
  boost::shared_ptr<      Node> GetFocus()       noexcept;

  ///There can be multiple items selected
  ///There is one item in focus at most
  ///The node in focus is never in the collection of selected nodes
  ///Use GetFocusAndSelected to get all
  std::vector<boost::shared_ptr<const Node>> GetSelected() const noexcept;
  std::vector<boost::shared_ptr<      Node>> GetSelected()       noexcept;

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  void MouseMoveEvent(const QPointF& mouse_pos) noexcept;

  void Undo() noexcept;

  ///Emitted when an Edge is added
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Edge>)> m_signal_add_edge;

  ///Emitted when a Node is added
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_add_node;

  ///Emitted when the ConceptMap is modified as a whole: deleted, created or overwritten
  boost::signals2::signal<void()> m_signal_concept_map_changed;

  ///Emitted when an Edge is deleted
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Edge>)> m_signal_delete_edge;

  ///Emitted when a Node is deleted
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_delete_node;

  ///Emitted when a Node loses focus
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_lose_focus;

  ///Emitted when one or more Nodes lose to be selected
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(std::vector<boost::shared_ptr<Node>>)> m_signal_lose_selected;

  ///Emitted when a Node receives focus
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_set_focus;

  ///Emitted when multiple Nodes are selected
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(std::vector<boost::shared_ptr<Node>>)> m_signal_set_selected;

  private:

  boost::shared_ptr<ConceptMap> m_conceptmap;

  ///The elements in focus, if any. These might be:
  ///- a true Node
  ///- the label in the middle of an edge
  ///- the CenterNode
  boost::shared_ptr<Node> m_focus;


  const int m_font_height;
  const int m_font_width;

  QPointF m_mouse_pos;

  ///The elements selected
  ///- a true Node
  ///- the label in the middle of an edge
  ///- the CenterNode
  std::vector<boost::shared_ptr<Node>> m_selected;

  ///The undo stack (use std::vector because it is a true STL container)
  ///The Commands aren't const, because Command::Undo changes their state
  std::vector<boost::shared_ptr<Command>> m_undo;


  ///Adds back a deleted Node
  //This is used by CommandDeleteNode::Undo
  void AddNode(const boost::shared_ptr<Node> node) noexcept;

  ///Add the nodes to the current (can be zero) selecetd nodes
  void AddSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept;

  static boost::shared_ptr<ConceptMap> CreateEmptyConceptMap() noexcept;

  ///Creates a new Node in the concept map. The return value is
  ///that node. This is used by CommandCreateNode::Undo
  boost::shared_ptr<Edge> CreateNewEdge() noexcept;

  ///Creates a new Node in the concept map. The return value is
  ///that node. This is used by CommandCreateNode::Undo
  boost::shared_ptr<Node> CreateNewNode() noexcept;

  ///Delete an Edge in the concept map
  void DeleteEdge(const boost::shared_ptr<Edge> edge) noexcept;

  ///Delete a Node in the concept map
  void DeleteNode(const boost::shared_ptr<Node> node) noexcept;

  ///Find a Node at a coordinat
  ///Returns nullptr if none is present
  boost::shared_ptr<      Node> FindNodeAt(const double x, const double y)       noexcept;
  boost::shared_ptr<const Node> FindNodeAt(const double x, const double y) const noexcept;

  ///Lose the current focus, assumes something has focus
  void LoseFocus() noexcept;

  ///Used by CommandAddFocusRandom and CommandSetFocusRandom
  ///Of all the concept maps its nodes, except for the uses supplied as the
  ///argument, return 1 to all the nodes, except when there is no node
  ///left (as all are excluded) or the concept map does not have any nodes
  std::vector<boost::shared_ptr<Node>> GetRandomNodes(std::vector<boost::shared_ptr<const Node>> nodes_to_exclude = {}) noexcept;
  boost::shared_ptr<Node> GetRandomNode(std::vector<boost::shared_ptr<const Node>> nodes_to_exclude = {}) noexcept;

  ///Called by m_undo its top command when it calles Undo itself,
  ///by which the Command indicates that it must be removed from that m_undo vector
  void OnUndo(const Command * const command_to_remove) noexcept;

  ///Start, reset or delete a/the concept map
  void SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept;

  ///Set the node to the only node in focus
  void SetFocus(const boost::shared_ptr<Node>& node) noexcept;

  ///Set the nodes to the only nodes selected
  void SetSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Unselect the node, assumes it is selected
  void Unselect(const boost::shared_ptr<Node>& node) noexcept;

  //friend class Command;
  friend class CommandAddSelectedRandom;
  friend class CommandCreateNewConceptMap;
  friend class CommandCreateNewEdge;
  friend class CommandCreateNewNode;
  friend class CommandDeleteConceptMap;
  friend class CommandDeleteFocusNode;
  friend class CommandDeleteNode;
  friend class CommandLoseFocus;
  friend class CommandSetFocusRandom;
  friend class CommandSetFocusWithCoordinat;
  friend class CommandUnselectRandom;
  friend bool operator==(const Widget& lhs, const Widget& rhs) noexcept;

};

bool operator==(const Widget& lhs, const Widget& rhs) noexcept;
bool operator!=(const Widget& lhs, const Widget& rhs) noexcept;

//std::ostream& operator<<(std::ostream& os, const Widget& w);

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPWIDGET_H
