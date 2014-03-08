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
  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  boost::shared_ptr<const ConceptMap> GetConceptMap() const noexcept { return m_conceptmap; }
  boost::shared_ptr<      ConceptMap> GetConceptMap()       noexcept { return m_conceptmap; }

  std::vector<boost::shared_ptr<const Node>> GetFocus() const noexcept;
  std::vector<boost::shared_ptr<      Node>> GetFocus()       noexcept;

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

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
  boost::signals2::signal<void(std::vector<boost::shared_ptr<Node>>)> m_signal_lose_focus_nodes;

  ///Emitted when multiple Nodes receive focus
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(std::vector<boost::shared_ptr<Node>>)> m_signal_set_focus_nodes;

  private:

  boost::shared_ptr<ConceptMap> m_conceptmap;

  ///The elements in focus, if any. These might be:
  ///- a true Node
  ///- the label in the middle of an edge
  ///- the CenterNode
  std::vector<boost::shared_ptr<Node>> m_focus;

  const int m_font_height;
  const int m_font_width;

  ///The undo stack (use std::vector because it is a true STL container)
  ///The Commands aren't const, because Command::Undo changes their state
  std::vector<boost::shared_ptr<Command>> m_undo;

  ///Add the nodes to the current (can be zero) nodes in focus
  void AddFocus(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept;

  ///Adds back a deleted Node
  //This is used by CommandDeleteNode::Undo
  void AddNode(const boost::shared_ptr<Node> node) noexcept;

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


  ///Used by CommandAddFocusRandom and CommandSetFocusRandom
  ///Of all the concept maps its nodes, except for the uses supplied as the
  ///argument, return 1 to all the nodes, except when there is no node
  ///left (as all are excluded) or the concept map does not have any nodes
  std::vector<boost::shared_ptr<Node>> GetRandomNodes(std::vector<boost::shared_ptr<const Node>> nodes_to_exclude = {}) noexcept;

  ///Start, reset or delete a/the concept map
  void SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept;

  ///Set the nodes to the only nodes in focus
  void SetFocus(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  //friend class Command;
  friend class CommandAddFocusRandom;
  friend class CommandCreateNewConceptMap;
  friend class CommandCreateNewEdge;
  friend class CommandCreateNewNode;
  friend class CommandDeleteConceptMap;
  friend class CommandDeleteFocusNode;
  friend class CommandDeleteNode;
  friend class CommandLoseFocus;
  friend class CommandSetFocusRandom;
  friend class CommandSetFocusWithCoordinat;
  friend bool operator==(const Widget& lhs, const Widget& rhs) noexcept;

};

bool operator==(const Widget& lhs, const Widget& rhs) noexcept;
bool operator!=(const Widget& lhs, const Widget& rhs) noexcept;

//std::ostream& operator<<(std::ostream& os, const Widget& w);

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPWIDGET_H
