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
#include "conceptmapfwd.h"
#include "conceptmapfactory.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Widget does the Command-driven communication with ConceptMap
struct Widget
{
  Widget(const boost::shared_ptr<ConceptMap> conceptmap = boost::shared_ptr<ConceptMap>());
  Widget(const Widget& other);
  Widget& operator=(const Widget& rhs) = delete;

  bool CanDoCommand(const boost::shared_ptr<Command> command) const noexcept;

  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  const boost::shared_ptr<const ConceptMap> GetConceptMap() const noexcept { return m_conceptmap; }
  const boost::shared_ptr<      ConceptMap> GetConceptMap()       noexcept { return m_conceptmap; }

  ///Obtain all commands possible
  //const std::vector<boost::shared_ptr<Command>> GetAllCommands() const noexcept;

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  void Undo();

  private:

  boost::shared_ptr<ConceptMap> m_conceptmap;

  ///The element (either a Node or Edge) having focus
  ///nullptr denotes no Element has focus
  Element * m_focus;

  //The undo stack (use std::vector because it is a true STL container)
  //first: the ConceptMap before the command
  //second: the last Command done to the Widget
  std::vector<std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Command>>> m_undo;

  void SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept { m_conceptmap = conceptmap; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  //friend class Command;
  friend class CommandDeleteConceptMap;
  friend class CommandStartConceptMap;
  friend bool operator==(const Widget& lhs, const Widget& rhs);

};

bool operator==(const Widget& lhs, const Widget& rhs);
bool operator!=(const Widget& lhs, const Widget& rhs);

std::ostream& operator<<(std::ostream& os, const Widget& w);

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPWIDGET_H
