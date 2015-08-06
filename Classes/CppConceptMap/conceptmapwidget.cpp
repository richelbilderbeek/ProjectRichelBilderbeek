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
#include "conceptmapwidget.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "conceptmap.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandaddselectedrandom.h"
#include "conceptmapcommandcreatenewconceptmap.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeleteconceptmap.h"
#include "conceptmapcommandfactory.h"
#include "conceptmapcommandunselectrandom.h"
#include "conceptmapedgefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "conceptmapwidgetfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop


/*
std::vector<boost::shared_ptr<ribi::cmap::Node> > RemoveConst(
  std::vector<boost::shared_ptr<const ribi::cmap::Node> > v) noexcept
{
  const std::vector<boost::shared_ptr<ribi::cmap::Node> > w(v.begin(),v.end());
  #ifndef NDEBUG
  assert(v.size() == w.size());
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i) { assert(v[i] == w[i]); }
  #endif
  return w;
}
*/

/*
template <class T>
std::vector<boost::shared_ptr<T> > RemoveConst(
  const std::vector<boost::shared_ptr<const T> > v) noexcept
{
  const std::vector<boost::shared_ptr<T> > w(v.begin(),v.end());
  #ifndef NDEBUG
  assert(v.size() == w.size());
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i) { assert(v[i] == w[i]); }
  #endif
  return w;
}
*/

ribi::cmap::Widget::Widget(const boost::shared_ptr<ConceptMap> conceptmap)
  : //Signals first, as these are public
    m_signal_add_edge{},
    m_signal_add_node{},
    m_signal_concept_map_changed{},
    m_signal_delete_edge{},
    m_signal_delete_node{},
    m_signal_lose_focus{},
    m_signal_lose_selected{},
    //m_signal_set_focus{},
    m_signal_set_selected{},
    m_conceptmap(conceptmap),
    m_focus{},
    m_font_height(18),
    m_font_width(12),
    m_mouse_pos{0.0,0.0},
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
    m_signal_lose_focus{},
    m_signal_lose_selected{},
    //m_signal_set_focus{},
    m_signal_set_selected{},
    m_conceptmap(ConceptMapFactory().DeepCopy(other.m_conceptmap)),
    m_focus{other.m_focus},
    m_font_height(other.m_font_height),
    m_font_width(other.m_font_width),
    m_mouse_pos{0.0,0.0},
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

void ribi::cmap::Widget::AddSelected(const std::vector<boost::shared_ptr<Edge>>& edges) noexcept
{
  assert(std::count(edges.begin(),edges.end(),nullptr) == 0);
  std::copy(edges.begin(),edges.end(),std::back_inserter(m_selected.first));
  m_signal_set_selected(m_selected.first,m_selected.second);
}

void ribi::cmap::Widget::AddSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept
{
  assert(std::count(nodes.begin(),nodes.end(),nullptr) == 0);
  std::copy(nodes.begin(),nodes.end(),std::back_inserter(m_selected.second));
  m_signal_set_selected(m_selected.first,m_selected.second);
}

void ribi::cmap::Widget::AddSelected(
  const std::vector<boost::shared_ptr<Edge>>& edges,
  const std::vector<boost::shared_ptr<Node>>& nodes
) noexcept
{
  AddSelected(edges);
  AddSelected(nodes);
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

  assert(GetSelectedNodes().size() == 2);
  #endif
  const boost::shared_ptr<Node> from { GetSelectedNodes()[0] };
  const boost::shared_ptr<Node> to   { GetSelectedNodes()[1] };
  assert(from);
  assert(to);
  assert(m_conceptmap->HasNode(from));
  assert(m_conceptmap->HasNode(to));
  const boost::shared_ptr<Edge> edge {
    EdgeFactory().Create(from,to)
  };

  //ConceptMap does not signal the newly added edge (as it does no signalling at all)
  m_conceptmap->AddEdge(edge);

  //But ConceptMapWidget does
  m_signal_add_edge(edge);

  //Widget must keep track of what is selected
  m_selected.first.push_back(edge);
  //Remove selection away from 'from'
  const auto from_iter = std::find(std::begin(m_selected.second),std::end(m_selected.second),from);
  assert(from_iter != std::end(m_selected.second));
  std::swap(*from_iter,m_selected.second.back());
  m_selected.second.pop_back();

  const auto to_iter = std::find(std::begin(m_selected.second),std::end(m_selected.second),to);
  assert(to_iter != std::end(m_selected.second));
  std::swap(*to_iter,m_selected.second.back());
  m_selected.second.pop_back();

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

  //Adding a Node should select it
  this->AddSelected( { node } ); //Must be after 'm_signal_add_node(node);'

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

  command->m_signal_undo.connect(
    boost::bind(&ribi::cmap::Widget::OnUndo,this,boost::lambda::_1)
  );

  //Undo
  m_undo.push_back(command);

  //Actually do the move
  command->DoCommand(this);

  assert(CanUndo());
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

boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::Widget::GetFocus() const noexcept
{
  return m_focus;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::Widget::GetFocus() noexcept
{
  return m_focus;
}

ribi::cmap::Widget::ConstEdgesAndNodes ribi::cmap::Widget::GetSelected() const noexcept
{
  if (GetSelectedEdges().empty() && GetSelectedNodes().empty()) { return ConstEdgesAndNodes(); }
  return std::make_pair(GetSelectedEdges(),GetSelectedNodes());
}

ribi::cmap::Widget::ConstEdges ribi::cmap::Widget::GetSelectedEdges() const noexcept
{
  assert(std::count(std::begin(m_selected.first),std::end(m_selected.first),nullptr) == 0);
  const std::vector<boost::shared_ptr<const Edge>> selected {
    AddConst(m_selected.first)
  };
  return selected;
}

ribi::cmap::Widget::ConstNodes ribi::cmap::Widget::GetSelectedNodes() const noexcept
{
  assert(std::count(std::begin(m_selected.second),std::end(m_selected.second),nullptr) == 0);
  const std::vector<boost::shared_ptr<const Node>> selected {
    AddConst(m_selected.second)
  };
  return selected;
}

std::vector<boost::shared_ptr<ribi::cmap::Edge>> ribi::cmap::Widget::GetRandomEdges(
  std::vector<boost::shared_ptr<const Edge>> edges_to_exclude
) noexcept
{
  if (!GetConceptMap()->GetEdges().empty()) { return Edges(); }
  auto nodes(GetConceptMap()->GetEdges());
  std::sort(nodes.begin(),nodes.end());
  std::sort(edges_to_exclude.begin(),edges_to_exclude.end());
  //Find the Edges present in nodes, absent in nodes_to_exclude
  decltype(nodes) focus_nodes;
  std::set_difference(
    nodes.begin(),nodes.end(),
    edges_to_exclude.begin(),edges_to_exclude.end(),
    std::back_inserter(focus_nodes)
  );

  if (focus_nodes.empty()) return focus_nodes;
  if (focus_nodes.size() == 1) return focus_nodes;
  std::random_shuffle(focus_nodes.begin(),focus_nodes.end());
  const int n = 1 + (std::rand() % (focus_nodes.size() - 1));
  focus_nodes.resize(n);
  return focus_nodes;
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::Widget::GetRandomEdge(
  std::vector<boost::shared_ptr<const Edge>> edges_to_exclude) noexcept
{
  const auto v(GetRandomEdges(edges_to_exclude));
  boost::shared_ptr<Edge> p;
  if (!v.empty()) p = v[0];
  return p;
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

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::Widget::GetRandomNode(
  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude) noexcept
{
  const auto v(GetRandomNodes(nodes_to_exclude));
  boost::shared_ptr<Node> p;
  if (!v.empty()) p = v[0];
  return p;
}

std::string ribi::cmap::Widget::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::cmap::Widget::GetVersionHistory() noexcept
{
  return {
    "2013-12-xx: Version 1.0: initial version",
    "2013-12-23: Version 1.1: started versioning",
    "2014-03-24: Version 1.2: distinguished correctly between focus and selected"
  };
}

void ribi::cmap::Widget::LoseFocus() noexcept
{
  assert(m_focus);

  m_focus = boost::shared_ptr<Node>() ;

  assert(!m_focus);
}

void ribi::cmap::Widget::OnUndo(const Command * const
  #ifndef NDEBUG
  command_to_remove
  #endif
) noexcept
{
  assert(command_to_remove);
  assert(!m_undo.empty());
  assert(m_undo.back().get() == command_to_remove
    && "Assume the last command signals to be removed from the undo stack");
  m_undo.pop_back();
}

void ribi::cmap::Widget::SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept
{
  m_conceptmap = conceptmap;
  m_signal_concept_map_changed();
}

/*
void ribi::cmap::Widget::SetFocus(const boost::shared_ptr<Node>& node) noexcept
{
  assert(node);
  m_focus = node;
  //m_signal_set_focus(node);
}
*/

void ribi::cmap::Widget::SetSelected(
  const ConstEdges& edges,
  const ConstNodes& nodes
) noexcept
{
  const Edges non_const_edges = RemoveConst(edges);
  const Nodes non_const_nodes = RemoveConst(nodes);
  m_selected.first = non_const_edges;
  m_selected.second = non_const_nodes;
  m_signal_set_selected(non_const_edges,non_const_nodes);
}

void ribi::cmap::Widget::SetSelected(const Edges& edges) noexcept
{
  SetSelected( AddConst(edges), {});
}

void ribi::cmap::Widget::SetSelected(const Nodes& nodes) noexcept
{
  SetSelected( {}, AddConst(nodes));
}

void ribi::cmap::Widget::SetSelected(const ConstEdgesAndNodes& nodes_and_edges) noexcept
{
  SetSelected(nodes_and_edges.first, nodes_and_edges.second);
}

#ifndef NDEBUG
void ribi::cmap::Widget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const int n_depth = 1;
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
  //Start a concept map, create a node using a command
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
    assert(widget->CanUndo());
    command->Undo();
    assert(widget->GetConceptMap()->GetNodes().empty()
      && "Concept map must be empty again now");
  }
  //Start a concept map, create two nodes, unselect both, then select both using AddSelected
  {
    const boost::shared_ptr<Widget> widget(new Widget);
    const int n_nodes = 2;
    //Create nodes
    for (int i=0; i!=n_nodes; ++i)
    {
      const boost::shared_ptr<CommandCreateNewNode> command {
        new CommandCreateNewNode
      };
      assert(widget->CanDoCommand(command));
      widget->DoCommand(command);
    }
    assert(static_cast<int>(widget->GetConceptMap()->GetNodes().size()) == n_nodes
      && "Concept map must have two nodes");
    assert(static_cast<int>(widget->GetSelectedNodes().size()) == 2
      && "Freshly created nodes are selected");

    //Unselect both
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == 2 - i);
      const boost::shared_ptr<CommandUnselectRandom> command {
        new CommandUnselectRandom
      };
      assert(widget->CanDoCommand(command));
      widget->DoCommand(command);
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == 1 - i);
    }
    assert(static_cast<int>(widget->GetSelectedNodes().size()) == 0);

    //Select both again
    assert(static_cast<int>(widget->GetSelectedNodes().size()) == 0);
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == i);
      const boost::shared_ptr<CommandAddSelectedRandom> command {
        new CommandAddSelectedRandom
      };
      assert(widget->CanDoCommand(command));
      widget->DoCommand(command);
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == i + 1);
    }
    assert(static_cast<int>(widget->GetSelectedNodes().size()) == 2);

    //Undo selection
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == 2 - i);
      const boost::shared_ptr<CommandUnselectRandom> command {
        new CommandUnselectRandom
      };
      assert(widget->CanDoCommand(command));
      widget->Undo();
      assert(static_cast<int>(widget->GetSelectedNodes().size()) == 1 - i);
    }
    assert(static_cast<int>(widget->GetSelectedNodes().size()) == 0);
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
  if (n_depth >= 2)
  {
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
              widget->Undo();
              widget->DoCommand(cmd);
            }
          }
        }
      }
    }
  }
}
#endif

void ribi::cmap::Widget::Undo() noexcept
{
  assert(CanUndo());
  assert(!m_undo.empty());
  assert(m_undo.back());
  #ifndef NDEBUG
  const std::size_t sz_before = m_undo.size();
  #endif
  m_undo.back()->Undo();
  #ifndef NDEBUG
  const std::size_t sz_after = m_undo.size();
  assert(sz_after < sz_before
    && "The undo Command calls DoUndo itself;"
       "DoUndo shortens the m_undo stack"
  );
  //m_undo.pop_back(); //DON'T, DoUndo does this
  #endif
}

void ribi::cmap::Widget::Unselect(
  const Nodes& nodes
) noexcept
{
  m_signal_lose_selected(nodes);
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
  if (lhs.GetSelected() != rhs.GetSelected()) return false;
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
