#include "conceptmapwidget.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandcreatenewconceptmap.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeleteconceptmap.h"
#include "conceptmapcommandfactory.h"
#include "conceptmapedgefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "conceptmapwidgetfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Widget::Widget(const boost::shared_ptr<ConceptMap> conceptmap)
  : //Signals first, as these are public
    m_signal_add_edge{},
    m_signal_add_node{},
    m_signal_concept_map_changed{},
    m_signal_delete_edge{},
    m_signal_delete_node{},
    m_signal_lose_focus_nodes{},
    m_signal_set_selected_nodes{},
    m_conceptmap(conceptmap),
    m_focus{},
    m_font_height(18),
    m_font_width(12),
    m_selected{},
    m_undo{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert( (m_conceptmap || !m_conceptmap )
    && "Allow a widget with and without an actual concept map");
  assert(m_font_height > 0);
  assert(m_font_width > 0);
}

#ifndef NDEBUG
ribi::cmap::Widget::Widget(const Widget& other)
  : //Signals first, as these are public
    m_signal_add_edge{},
    m_signal_add_node{},
    m_signal_concept_map_changed{},
    m_signal_delete_edge{},
    m_signal_delete_node{},
    m_signal_lose_focus_nodes{},
    m_signal_set_selected_nodes{},
    m_conceptmap(ConceptMapFactory::DeepCopy(other.m_conceptmap)),
    m_focus{other.m_focus},
    m_font_height(other.m_font_height),
    m_font_width(other.m_font_width),
    m_selected{},
    m_undo{}
{
  assert(static_cast<bool>(m_conceptmap) == static_cast<bool>(other.m_conceptmap));
  assert( (!m_conceptmap || *m_conceptmap == *other.m_conceptmap) && "Must be a copy");
  assert( (!m_conceptmap || m_conceptmap != other.m_conceptmap) && "Must be a deep copy");
  //assert( (m_focus == other.m_focus || m_focus != other.m_focus)
  //  && "Cannot copy focus");

  assert( (m_undo == other.m_undo || m_undo != other.m_undo)
    && "Cannot copy undo");
}
#endif


void ribi::cmap::Widget::AddNode(const boost::shared_ptr<ribi::cmap::Node> node) noexcept
{
  #ifndef NDEBUG
  const auto before = this->GetConceptMap()->GetNodes().size();
  #endif

  //ConceptMap does not signal the newly added node...
  m_conceptmap->AddNode(node);
  //But ConceptMapWidget does
  m_signal_add_node(node);

  #ifndef NDEBUG
  const auto after = this->GetConceptMap()->GetNodes().size();
  assert(after == before + 1);
  #endif
}

void ribi::cmap::Widget::AddSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept
{
  assert(std::count(nodes.begin(),nodes.end(),nullptr) == 0);
  std::copy(nodes.begin(),nodes.end(),std::back_inserter(m_selected));
  m_signal_set_selected_nodes(nodes);
}

bool ribi::cmap::Widget::CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept
{
  return command->CanDoCommand(this);
}

boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::Widget::CreateEmptyConceptMap() noexcept
{
  const boost::shared_ptr<ConceptMap> concept_map {
    ConceptMapFactory().Create()
  };
  assert(concept_map);
  return concept_map;
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::Widget::CreateNewEdge() noexcept
{
  #ifndef NDEBUG
  const auto before = this->GetConceptMap()->GetEdges().size();

  assert(GetSelected().size() == 2);
  #endif
  const boost::shared_ptr<Node> from { GetSelected()[0] };
  const boost::shared_ptr<Node> to   { GetSelected()[1] };
  assert(from);
  assert(to);
  #ifndef NDEBUG
  if (!m_conceptmap->HasNode(from))
  {
    TRACE("ERROR");
  }
  #endif
  assert(m_conceptmap->HasNode(from));
  assert(m_conceptmap->HasNode(to));
  const boost::shared_ptr<Edge> edge {
    EdgeFactory().Create(from,to)
  };

  //ConceptMap does not signal the newly added node...
  m_conceptmap->AddEdge(edge);
  //But ConceptMapWidget does
  m_signal_add_edge(edge);

  #ifndef NDEBUG
  const auto after = this->GetConceptMap()->GetEdges().size();
  assert(after == before + 1);
  #endif
  return edge;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::Widget::CreateNewNode() noexcept
{
  #ifndef NDEBUG
  const auto before = this->GetConceptMap()->GetNodes().size();
  #endif
  const boost::shared_ptr<Node> node {
    NodeFactory().CreateFromStrings("...")
  };

  //ConceptMap does not signal the newly added node...
  m_conceptmap->AddNode(node);
  //But ConceptMapWidget does
  m_signal_add_node(node);

  #ifndef NDEBUG
  const auto after = this->GetConceptMap()->GetNodes().size();
  assert(after == before + 1);
  #endif
  return node;
}

void ribi::cmap::Widget::DeleteEdge(const boost::shared_ptr<Edge> edge) noexcept
{
  assert(edge);
  ///Edge might already be deleted by something else
  if (m_conceptmap->GetEdges().empty()) return;
  {
    const std::vector<boost::shared_ptr<Edge> >& edges { m_conceptmap->GetEdges() };
    if (std::find(edges.begin(),edges.end(),edge) == edges.end()) return;
  }

  assert(!m_conceptmap->GetEdges().empty());
  #ifndef NDEBUG
  const int n_edges_before = static_cast<int>(m_conceptmap->GetEdges().size());
  #endif
  m_conceptmap->DeleteEdge(edge);
  #ifndef NDEBUG
  const int n_edges_after = static_cast<int>(m_conceptmap->GetEdges().size());
  assert(n_edges_after + 1 == n_edges_before);
  #endif
  m_signal_delete_edge(edge);
}

void ribi::cmap::Widget::DeleteNode(const boost::shared_ptr<Node> node) noexcept
{
  assert(node);
  ///Node might already be deleted by something else
  if (m_conceptmap->GetNodes().empty()) return;
  {
    const std::vector<boost::shared_ptr<Node> >& nodes { m_conceptmap->GetNodes() };
    if (std::find(nodes.begin(),nodes.end(),node) == nodes.end()) return;
  }

  assert(!m_conceptmap->GetNodes().empty());
  #ifndef NDEBUG
  const int n_nodes_before = static_cast<int>(m_conceptmap->GetNodes().size());
  #endif
  m_conceptmap->DeleteNode(node);
  #ifndef NDEBUG
  const int n_nodes_after = static_cast<int>(m_conceptmap->GetNodes().size());
  assert(n_nodes_after + 1 == n_nodes_before);
  #endif
  m_signal_delete_node(node);
}

void ribi::cmap::Widget::DoCommand(const boost::shared_ptr<Command> command) noexcept
{
  assert(command);
  if (!CanDoCommand(command))
  {
    TRACE("ERROR");
    TRACE(command->ToStr());
    TRACE("BREAK");
  }

  assert(CanDoCommand(command));
  //TRACE(command->ToStr());

  //Undo
  m_undo.push_back(command);

  //Actually do the move
  command->DoCommand(this);
}

boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::Widget::FindNodeAt(
  const double x,
  const double y
) const noexcept
{
  if (!this->GetConceptMap()) { return boost::shared_ptr<const Node>(); }
  for (const boost::shared_ptr<const Node> node: GetConceptMap()->GetNodes())
  {
    const double width  = (m_font_width * node->GetConcept()->GetName().size());
    const double height = m_font_height;

    const double left   = node->GetX() - (0.5 * width);
    const double top    = node->GetY() - (0.5 * height);
    const double right  = node->GetX() + (0.5 * width);
    const double bottom = node->GetY() + (0.5 * height);
    if (x >= left && x <= right && y >= top && y <= bottom) return node;
  }
  return boost::shared_ptr<const Node>();
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::Widget::FindNodeAt(const double x, const double y) noexcept
{
  const boost::shared_ptr<const ribi::cmap::Node> node {
    const_cast<const Widget*>(this)->FindNodeAt(x,y)
  };
  assert(node);
  return boost::const_pointer_cast<Node>(node);
}

std::vector<boost::shared_ptr<const ribi::cmap::Node>> ribi::cmap::Widget::GetSelected() const noexcept
{
  if (m_selected.empty()) { return std::vector<boost::shared_ptr<const Node>>(); }
  assert(std::count(m_selected.begin(),m_selected.end(),nullptr) == 0);
  const std::vector<boost::shared_ptr<const Node>> focus {
    AddConst(m_selected)
  };
  assert(std::count(focus.begin(),focus.end(),nullptr) == 0);
  return focus;
}

std::vector<boost::shared_ptr<ribi::cmap::Node>> ribi::cmap::Widget::GetSelected() noexcept
{
  assert(std::count(m_selected.begin(),m_selected.end(),nullptr) == 0);
  return m_selected;
}

std::vector<boost::shared_ptr<ribi::cmap::Node>> ribi::cmap::Widget::GetRandomNodes(
  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude
) noexcept
{
  assert(!GetConceptMap()->GetNodes().empty());
  auto nodes(GetConceptMap()->GetNodes());
  std::sort(nodes.begin(),nodes.end());
  std::sort(nodes_to_exclude.begin(),nodes_to_exclude.end());
  //Find the Nodes present in nodes, absent in nodes_to_exclude
  decltype(nodes) focus_nodes;
  std::set_difference(
    nodes.begin(),nodes.end(),
    nodes_to_exclude.begin(),nodes_to_exclude.end(),
    std::back_inserter(focus_nodes)
  );

  if (focus_nodes.empty()) return focus_nodes;
  if (focus_nodes.size() == 1) return focus_nodes;
  std::random_shuffle(focus_nodes.begin(),focus_nodes.end());
  const int n = 1 + (std::rand() % (focus_nodes.size() - 1));
  focus_nodes.resize(n);
  return focus_nodes;
}

std::string ribi::cmap::Widget::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::cmap::Widget::GetVersionHistory() noexcept
{
  return {
    "2013-12-xx: Version 1.0: initial version",
    "2013-12-23: Version 1.1: started versioning",
    "2013-12-23: Version 1.2: started versioning"
  };
}

void ribi::cmap::Widget::SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept
{
  m_conceptmap = conceptmap;
  m_signal_concept_map_changed();
}

void ribi::cmap::Widget::SetSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept
{
  assert(std::count(nodes.begin(),nodes.end(),nullptr) == 0);
  m_selected = nodes;
  m_signal_set_selected_nodes(nodes);
}

#ifndef NDEBUG
void ribi::cmap::Widget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::Widget::Test()");
  //operator<<
  /*
  for (const boost::shared_ptr<Widget> widget:
    WidgetFactory::GetAllTests())
  {
    std::cout << *widget << std::endl;
  }
  */
  //Test if individual commands have the intended effect
  //Delete concept map
  /*
  {
    static int cnt_no = 0;
    static int cnt_yes = 0;
    for (const boost::shared_ptr<Widget> widget:
      WidgetFactory::GetAllTests())
    {
      CommandDeleteConceptMap c;
      if (widget->GetConceptMap())
      {
        assert(c.CanDoCommand(widget.get()) && "Can delete a concept map when present");
        assert(widget->GetConceptMap() && "Concept map must be present before deletion");
        c.DoCommand(widget.get());
        assert(!widget->GetConceptMap() && "Concept map must be deleted");
        c.Undo();
        assert(widget->GetConceptMap() && "Concept map must be restored by undo");
        ++cnt_yes;
      }
      else
      {
        assert(!widget->GetConceptMap());
        assert(!c.CanDoCommand(widget.get()) && "Cannot delete a concept map when absent");
        ++cnt_no;
      }
    }
    assert(cnt_no > 0);
    assert(cnt_yes > 0);
  }
  */
  //Start concept map
  /*
  {
    static int cnt_no = 0;
    static int cnt_yes = 0;

    for (const boost::shared_ptr<Widget> widget:
      WidgetFactory::GetAllTests())
    {
      CommandCreateNewConceptMap c;
      if (!widget->GetConceptMap())
      {
        assert(c.CanDoCommand(widget.get()) && "Can start a concept map when none is present");
        c.DoCommand(widget.get());
        assert(widget->GetConceptMap() && "Concept map must be created");
        assert(widget->GetConceptMap()->GetNodes().size() == 1);
        assert(widget->GetConceptMap()->GetEdges().size() == 0);
        c.Undo();
        assert(!widget->GetConceptMap() && "Concept map must be deleted by undo");
        ++cnt_yes;
      }
      else
      {
        assert(widget->GetConceptMap());
        assert(!c.CanDoCommand(widget.get()) && "Cannot start when a concept map already exists");
        ++cnt_no;
      }
    }
    assert(cnt_no > 0);
    assert(cnt_yes > 0);
  }
  */
  //Start a concept map, add a node using the concept map
  {
    const boost::shared_ptr<Widget> widget(new Widget);
    assert(widget->GetConceptMap());
    assert(widget->GetConceptMap()->GetNodes().empty()
      && "Concept map starts empty");
    const boost::shared_ptr<Node> node {
      NodeFactory().GetTest(0)
    };
    assert(node);
    widget->GetConceptMap()->AddNode(node);
    assert(widget->GetConceptMap()->GetNodes().size() == 1
      && "Concept map must have one node added now");
    widget->GetConceptMap()->DeleteNode(node);
    assert(widget->GetConceptMap()->GetNodes().empty()
      && "Concept map must be empty again now");
  }
  //Start a concept map, add a node using a command
  {
    const boost::shared_ptr<Widget> widget(new Widget);
    assert(widget->GetConceptMap());
    assert(widget->GetConceptMap()->GetNodes().empty()
      && "Concept map starts empty");
    const boost::shared_ptr<CommandCreateNewNode> command {
      new CommandCreateNewNode
    };
    assert(widget->CanDoCommand(command));
    widget->DoCommand(command);
    assert(widget->GetConceptMap()->GetNodes().size() == 1
      && "Concept map must have one node added now");
    command->Undo();
    assert(widget->GetConceptMap()->GetNodes().empty()
      && "Concept map must be empty again now");
  }
  //Do all do and undo of a single command
  const int n_commands { static_cast<int>(CommandFactory::CreateTestCommands().size()) };
  for (int i=0; i!=n_commands; ++i)
  {
    for (const boost::shared_ptr<Widget> widget: WidgetFactory::GetAllTests())
    {
      assert(widget);
      const boost::shared_ptr<Command> cmd(CommandFactory::CreateTestCommands()[i]);
      assert(cmd);
      //TRACE(cmd->ToStr());
      if (widget->CanDoCommand(cmd))
      {
        widget->DoCommand(cmd);
        widget->Undo();
      }
    }
  }
  //Do all combinations of two commands
  for (int i=0; i!=n_commands; ++i)
  {
    for (int j=0; j!=n_commands; ++j)
    {
      for (const boost::shared_ptr<Widget> widget: WidgetFactory::GetAllTests())
      {
        for (const boost::shared_ptr<Command> cmd:
          {
            CommandFactory::CreateTestCommands()[i],
            CommandFactory::CreateTestCommands()[j]
          }
        )
        {
          assert(cmd);
          if (widget->CanDoCommand(cmd))
          {
            widget->DoCommand(cmd);
          }
        }
      }
    }
  }
  TRACE("Finished ribi::cmap::Widget::Test()");
}
#endif

void ribi::cmap::Widget::Undo() noexcept
{
  assert(!m_undo.empty());
  assert(m_undo.back());
  m_undo.back()->Undo();
  m_undo.pop_back();
}

bool ribi::cmap::operator==(const Widget& lhs, const Widget& rhs) noexcept
{
  if (static_cast<bool>(lhs.m_conceptmap.get()) != static_cast<bool>(rhs.m_conceptmap.get()))
  {
    return false;
  }
  assert(static_cast<bool>(nullptr) == static_cast<bool>(nullptr));
  if (lhs.m_conceptmap && *lhs.m_conceptmap != *rhs.m_conceptmap) return false;
  if (lhs.m_focus != rhs.m_focus) return false;
  if (lhs.m_selected != rhs.m_selected) return false;
  if (lhs.m_undo.size() != rhs.m_undo.size()) return false;
  return std::equal(
    std::begin(lhs.m_undo),
    std::end(lhs.m_undo),
    std::begin(rhs.m_undo),
    [](boost::shared_ptr<const Command> p,
       boost::shared_ptr<const Command> q)
    {
      return p->ToStr() == q->ToStr();
    }
  );
}

bool ribi::cmap::operator!=(const Widget& lhs, const Widget& rhs) noexcept
{
  return !(lhs == rhs);
}

/*
std::ostream& ribi::cmap::operator<<(std::ostream& os, const Widget& w)
{
  const boost::shared_ptr<const ConceptMap> concept_map { w.GetConceptMap() };
  const std::vector<boost::shared_ptr<const Edge> > edges { concept_map->GetEdges() };
  const std::vector<boost::shared_ptr<const Node> > nodes { concept_map->GetEdges() };
  //In reverse order of importance

  //Draw edge lines


}
*/
