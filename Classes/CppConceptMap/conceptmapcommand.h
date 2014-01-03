#ifndef CONCEPTMAPCOMMAND_H
#define CONCEPTMAPCOMMAND_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Command can be used to do and undo commands to a concept map Widget
///Command must use a Widget* because a Widget will call a Command with this:
///
///  some_command->CanDo(this);
///
struct Command
{
  virtual ~Command() noexcept {}
  bool CanDoCommand(const Widget * const widget) const noexcept;
  bool CanDoCommand(const boost::shared_ptr<const Widget> widget) const noexcept { return CanDoCommand(widget.get()); }
  void DoCommand(Widget * const widget) noexcept;
  void DoCommand(const boost::shared_ptr<Widget> widget) noexcept { DoCommand(widget.get()); }

  virtual const std::string ToStr() const noexcept = 0;
  virtual void Undo() noexcept = 0;

  private:
  ///Hook
  virtual bool CanDoCommandSpecific(const Widget * const widget) const noexcept = 0;

  ///Hook
  virtual void DoCommandSpecific(Widget * const widget) noexcept = 0;
};

///Start a new node
///-Can be used only when there is an existing concept map
struct CommandCreateNewNode : public Command
{
  CommandCreateNewNode() : m_node{}, m_widget{} {}
  CommandCreateNewNode(const CommandCreateNewNode&) = delete;
  CommandCreateNewNode& operator=(const CommandCreateNewNode&) = delete;
  ~CommandCreateNewNode() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "create new node"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Node> m_node;
  Widget * m_widget;
};

///Delete a concept map
///-Can be used only when there is an existing concept map
struct CommandDeleteConceptMap : public Command
{
  CommandDeleteConceptMap() : m_deleted_concept_map{}, m_widget{} {}
  CommandDeleteConceptMap(const CommandDeleteConceptMap&) = delete;
  CommandDeleteConceptMap& operator=(const CommandDeleteConceptMap&) = delete;
  ~CommandDeleteConceptMap() noexcept {}
  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "delete concept map"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<ConceptMap> m_deleted_concept_map;
  Widget * m_widget;
};

///Select an existing node
///-Can be used only when there is an existing concept map with at least one node
struct CommandSelectNode : public Command
{
  CommandSelectNode() : m_node{}, m_widget{} {}
  CommandSelectNode(const CommandSelectNode&) = delete;
  CommandSelectNode& operator=(const CommandSelectNode&) = delete;
  ~CommandSelectNode() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "select node"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Node> m_node;
  Widget * m_widget;
};

///Start a new concept map
///-Can be used only when there is no existing concept map
struct CommandStartConceptMap : public Command
{
  CommandStartConceptMap() : m_widget{} {}
  CommandStartConceptMap(const CommandStartConceptMap&) = delete;
  CommandStartConceptMap& operator=(const CommandStartConceptMap&) = delete;
  ~CommandStartConceptMap() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "start concept map"; }
  void Undo() noexcept;

  private:
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMAND_H
