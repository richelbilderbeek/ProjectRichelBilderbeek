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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmap.h"

#include <set>
#include <sstream>
#include <functional>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>

#include "conceptmapcenternodefactory.h"
#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandaddselectedrandom.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommandcreatenewedge.h"
#include "conceptmapcommandfactory.h"
#include "conceptmapcommandunselectrandom.h"
#include "conceptmapfactory.h"
#include "conceptmapnode.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::ConceptMap::ConceptMap(const std::string& question) noexcept
  : //Signals first, as these are public
    m_signal_add_edge{},
    m_signal_add_node{},
    m_signal_concept_map_changed{},
    m_signal_delete_edge{},
    m_signal_delete_node{},
    m_signal_selected_changed{},
    m_edges( {} ),
    m_nodes(CreateNodes(question, {} )),
    //m_font_height(18),
    //m_font_width(12),
    m_selected{},
    m_undo{}
{
  #ifndef NDEBUG
  Test();
  assert(ConceptMap::CanConstruct(m_nodes,m_edges));
  assert(FindCenterNode()
    && "Assume a CenterNode at the center of ConceptMap");
  assert(IsCenterNode(FindCenterNode())
    && "The CenterNode found must really be a CenterNode");
  assert(FindCenterNode()->GetConcept()
    && "The CenterNode must have an initialized Concept to display the focus");
  assert(FindCenterNode()->GetConcept()->GetName() == question
    && "The CenterNode must display the focus");
  #endif
  //assert(m_font_height > 0);
  //assert(m_font_width > 0);
}

ribi::cmap::ConceptMap::ConceptMap(
    const Nodes& nodes,
    const Edges& edges
)  noexcept
  :
    m_signal_add_edge{},
    m_signal_add_node{},
    m_signal_concept_map_changed{},
    m_signal_delete_edge{},
    m_signal_delete_node{},
    //m_signal_set_focus{},
    m_signal_selected_changed{},
    m_edges(edges),
    m_nodes(nodes),
    //m_font_height(18),
    //m_font_width(12),
    m_selected{},
    m_undo{}
{
  #ifndef NDEBUG
  Test();
  if (!ConceptMap::CanConstruct(nodes,edges))
  {
    TRACE("ERROR");
    const std::size_t n_nodes = nodes.size();
    for (std::size_t i=0; i!=n_nodes; ++i)
    {
      std::cout << i << ": " << nodes[i]->ToXml() << '\n';
    }

    const std::size_t n_edges = edges.size();
    for (std::size_t i=0; i!=n_edges; ++i)
    {
      const auto edge = edges[i];
      const auto const_nodes = AddConst(nodes);
      const auto from_iter = std::find(nodes.begin(),nodes.end(),edge->GetFrom());
      const auto to_iter = std::find(nodes.begin(),nodes.end(),edge->GetTo());
      assert(from_iter != nodes.end());
      assert(to_iter != nodes.end());
      std::cout
        << i << ": "
        << Edge::ToXml(boost::const_pointer_cast<const Edge>(edge),const_nodes)
        << '\n';
    }
  }
  assert(ConceptMap::CanConstruct(nodes,edges));
  #endif
}

#ifdef TO_ADD_TO_PROJECTBRAINWEAVER
ribi::cmap::ConceptMap::ConceptMap(
  const std::string& question,
  const boost::shared_ptr<cmap::Cluster>& cluster)
  : m_edges{},
    m_nodes(CreateNodes(question, {} ))
{
  #ifndef NDEBUG
  Test();
  #endif

  const std::vector<boost::shared_ptr<ribi::cmap::Concept>>& v = cluster->Get();
  const int n = boost::numeric_cast<int>(v.size());
  for (int i=0; i!=n; ++i)
  {
    const int x = 0;
    const int y = 0;
    const boost::shared_ptr<Node> node = NodeFactory().Create(v[i],x,y);
    assert(node);
    m_nodes.push_back(node);
  }
  assert(v.size() + 1 == m_nodes.size()
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
}
#endif //TO_ADD_TO_PROJECTBRAINWEAVER

ribi::cmap::ConceptMap::~ConceptMap() noexcept
{
  //OK
}

void ribi::cmap::ConceptMap::AddEdge(const EdgePtr& edge) noexcept
{
  assert(edge);
  if (std::find(std::begin(m_edges),std::end(m_edges),edge) != std::end(m_edges))
  {
    TRACE("Warning: edge already added");
    return;
  }

  assert(edge->GetFrom());
  assert(edge->GetTo());
  //Add Nodes if they are not present yet
  if (!HasNode(edge->GetFrom())) { AddNode(edge->GetFrom()); }
  if (!HasNode(edge->GetTo())  ) { AddNode(edge->GetTo()  ); }

  assert(HasNode(edge->GetFrom()));
  assert(HasNode(edge->GetTo()));
  assert(std::count(m_nodes.begin(),m_nodes.end(),edge->GetFrom()) == 1
    && "First enter the node this edge originates from");
  assert(std::count(m_nodes.begin(),m_nodes.end(),edge->GetTo()) == 1
    && "First enter the node this edge targets to");
  m_edges.push_back(edge);

  this->SetSelected( Edges( { edge } ) );

  m_signal_add_edge(edge);
}

void ribi::cmap::ConceptMap::AddNode(const NodePtr& node) noexcept
{
  assert(node);
  if (std::find(std::begin(m_nodes),std::end(m_nodes),node) != std::end(m_nodes))
  {
    TRACE("Warning: node already added");
    return;
  }

  this->AddSelected( { node } );

  m_nodes.push_back(node);
  m_signal_add_node(node);

  assert(std::count(m_nodes.begin(),m_nodes.end(),node) == 1
    && "Every node must be unique");
  //Do not let concept map signal that a new node has been added:
  //keep it as stupid as possible. Let ConceptMapWidget
  //have this behavior
}


bool ribi::cmap::ConceptMap::CanConstruct(
  const Nodes& /* nodes */,
  const Edges& edges) noexcept
{
  const bool trace_verbose = false;

  //Test if there are 'two-way' edges, that is, one edge going from A to B
  //and another edge going from B to A
  {
    const int n_edges = edges.size();
    for (int i=0; i!=n_edges; ++i)
    {
      const boost::shared_ptr<ribi::cmap::Edge> & a = edges[i];
      const auto a_from = a->GetFrom();
      const auto a_to   = a->GetTo();
      for (int j=i+1; j!=n_edges; ++j)
      {
        assert(i != j);
        assert(j < n_edges);
        const boost::shared_ptr<Edge> & b = edges[j];
        assert(a.get() != b.get() && "Assume different pointers");
        const auto b_from = b->GetFrom();
        const auto b_to   = b->GetTo();
        if (a_from.get() == b_from.get() && a_to.get() == b_to.get())
        {
          if (trace_verbose)
          {
            TRACE("Cannot have two edges from the same node to the same node");
          }
          return false;
        }
        if (a_from.get() == b_to.get() && a_to.get() == b_from.get())
        {
          if (trace_verbose)
          {
            TRACE("Cannot have two edges from the same node to the same node");
          }
          return false;
        }
      }
    }
  }
  return true;
}

ribi::cmap::ConceptMap::Nodes ribi::cmap::ConceptMap::CreateNodes(
  const std::string& question,
  const Nodes& nodes) noexcept
{
  Nodes v;
  const boost::shared_ptr<Concept> concept(
    ConceptFactory().Create(
      question,
      ExamplesFactory().Create(), //No examples
      false, //Is not complex
      -1, //No rated complexity
      -1, //No rated concreteness
      -1  //No rated specificity
    )
  );
  const boost::shared_ptr<CenterNode> center_node {
    CenterNodeFactory().Create(concept,0.0,0.0)
  };
  assert(center_node);
  v.push_back(center_node);
  std::copy(nodes.begin(),nodes.end(),std::back_inserter(v));
  assert(v.size() == nodes.size() + 1);
  return v;
}

ribi::cmap::ConceptMap::SubConceptMaps ribi::cmap::ConceptMap::CreateSubs() const noexcept
{
  SubConceptMaps v;
  for (const boost::shared_ptr<Node>& focal_node: m_nodes)
  {
    assert(focal_node);

    //Collect all edges connected top the focal node (which is m_nodes[i])
    Nodes nodes{};
    Edges edges{};

    nodes.push_back(focal_node);

    for (const boost::shared_ptr<Edge>& focal_edge: m_edges)
    {
     if (focal_edge->GetFrom() == focal_node)
      {
        edges.push_back(focal_edge);
        assert(focal_edge->GetTo() != focal_node);
        nodes.push_back(focal_edge->GetTo());
      }
      else if (focal_edge->GetTo() == focal_node)
      {
        edges.push_back(focal_edge);
        assert(focal_edge->GetFrom() != focal_node);
        nodes.push_back(focal_edge->GetFrom());
      }
    }
    assert(!nodes.empty());
    //Put CenterNode in front
    const auto iter = std::find_if(nodes.begin(),nodes.end(),[](const boost::shared_ptr<Node> node) { return IsCenterNode(node); } );
    if (iter != nodes.end()) { std::swap(*nodes.begin(),*iter); }
    assert(ConceptMap::CanConstruct(nodes,edges) && "Only construct valid concept maps");
    const boost::shared_ptr<ConceptMap> concept_map(new ConceptMap(nodes,edges));
    assert(concept_map->IsValid());
    v.push_back(concept_map);
  }
  return v;
}

void ribi::cmap::ConceptMap::DeleteEdge(const EdgePtr& edge) noexcept
{
  DeleteEdge(boost::dynamic_pointer_cast<const Edge>(edge));
}

void ribi::cmap::ConceptMap::DeleteEdge(const ReadOnlyEdgePtr& edge) noexcept
{
  #ifndef NDEBUG
  assert(edge);
  //One cannot be sure if the edges are already deleted or not
  if(std::count(m_edges.begin(),m_edges.end(),edge) == 0) return;
  assert(std::count(m_edges.begin(),m_edges.end(),edge) != 0
    && "The edge must exist");
  assert(std::count(m_edges.begin(),m_edges.end(),edge) == 1
    && "Every edge is unique");
  const std::size_t n_edges_before = m_edges.size();
  #endif


  assert(edge);

  ///Edge might already be deleted by something else
  if (GetEdges().empty()) return;
  {
    const auto& edges = GetEdges();
    if (std::find(edges.begin(),edges.end(),edge) == edges.end()) return;
  }

  m_edges.erase(std::remove(m_edges.begin(),m_edges.end(),edge),m_edges.end());

  m_signal_delete_edge(edge);


  #ifndef NDEBUG
  const std::size_t n_edges_after = m_edges.size();
  assert(n_edges_before - 1 == n_edges_after);
  #endif
}


void ribi::cmap::ConceptMap::DeleteNode(const NodePtr& node) noexcept
{
  DeleteNode(boost::dynamic_pointer_cast<const Node>(node));
}

void ribi::cmap::ConceptMap::DeleteNode(const ReadOnlyNodePtr& node) noexcept
{
  assert(node);
  if (std::count(m_nodes.begin(),m_nodes.end(),node) == 0)
  {
    //There are multiple ways to delete a node:
    // - QtConceptMap: delete the QtNode, which deletes the Node
    // - ConceptMapWidget: deletes the Node, which signals its observers of this event
    //Because the sequence
    return;
  }

  //Delete all edges going to this node
  std::vector<boost::shared_ptr<ribi::cmap::Edge>> to_be_deleted;
  std::copy_if(m_edges.begin(),m_edges.end(),std::back_inserter(to_be_deleted),
    [node](boost::shared_ptr<Edge> edge)
    {
      return edge->GetFrom() == node || edge->GetTo() == node;
    }
  );
  for (boost::shared_ptr<Edge> edge: to_be_deleted)
  {
    DeleteEdge(edge);
  }

  //Unselect the node
  this->Unselect( ConstNodes( { node } ) );

  //If there is no node selected anymore, give focus to a possible first node
  if (GetSelectedNodes().empty() && !GetNodes().empty())
  {
    this->SetSelected(Nodes( { GetNodes().front() } ) );
  }

  //Delete the node itself
  m_nodes.erase(
    std::remove(
      std::begin(m_nodes),
      std::end(m_nodes),
      node
    ),
    m_nodes.end()
  );

  m_signal_delete_node(node);
}

bool ribi::cmap::ConceptMap::Empty() const noexcept
{
  assert(!(m_nodes.empty() && !m_edges.empty())
    && "If there are no nodes, there cannot be edges");
  return m_nodes.empty(); // && m_edges.empty();
}

ribi::cmap::ConceptMap::ReadOnlyCenterNodePtr ribi::cmap::ConceptMap::FindCenterNode() const noexcept
{
  const auto iter = std::find_if(m_nodes.begin(),m_nodes.end(),
    [](const boost::shared_ptr<const Node> node)
    {
      return IsCenterNode(node);
    }
  );
  boost::shared_ptr<const CenterNode> center_node;
  if (iter == m_nodes.end())
  {
    assert(!center_node);
  }
  else
  {
    center_node = boost::dynamic_pointer_cast<const CenterNode>(*iter);
    assert(center_node);
  }
  return center_node;
}

ribi::cmap::ConceptMap::CenterNodePtr ribi::cmap::ConceptMap::FindCenterNode() noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  const ReadOnlyCenterNodePtr center_node {
    dynamic_cast<const ConceptMap*>(this)->FindCenterNodeConst() //Add const because compiler cannt find the right version
  };
  return boost::const_pointer_cast<CenterNode>(
    center_node
  );
}

ribi::cmap::ConceptMap::EdgePtr ribi::cmap::ConceptMap::GetEdge(const NodePtr& node) const noexcept
{
  const auto iter = std::find_if(
    std::begin(m_edges),
    std::end(m_edges),
    [node](const EdgePtr& edge) { return edge->GetNode().get() == node.get(); }
  );
  if (iter == std::end(m_edges)) { return EdgePtr(); }
  return *iter;
}

ribi::cmap::ConceptMap::ReadOnlyEdges ribi::cmap::ConceptMap::GetEdges() const noexcept
{
  return AddConst(m_edges);
}

ribi::cmap::ConceptMap::ReadOnlyNodePtr ribi::cmap::ConceptMap::GetFocalNode() const noexcept
{
  if (m_nodes.empty()) return boost::shared_ptr<const Node>();
  return m_nodes[0];
}

ribi::cmap::ConceptMap::NodePtr ribi::cmap::ConceptMap::GetFocalNode() noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  boost::shared_ptr<const Node> focal_node {
    dynamic_cast<const ConceptMap*>(this)->GetFocalNodeConst() //Compiler cannot distinguish member functions by type
  };
  return boost::const_pointer_cast<Node>(
    focal_node
  );
}


ribi::cmap::ConceptMap::ReadOnlyNodes ribi::cmap::ConceptMap::GetNodes() const noexcept
{
  return AddConst(m_nodes);
}

std::string ribi::cmap::ConceptMap::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::cmap::ConceptMap::GetVersionHistory() noexcept
{
  return {
    "2013-12-xx: Version 1.0: initial version",
    "2013-12-23: Version 1.1: started versioning",
    "2014-02-08: Version 1.2: support an empty concept map"
    "2014-03-24: Version 1.3: distinguished correctly between focus and selected"
    "2015-08-13: Version 2.0: merge of ConceptMap and ConceptMapWidget",
    "2015-08-28: Version 2.1: removed many useless member variables"
  };
}

bool ribi::cmap::ConceptMap::HasEdge(const boost::shared_ptr<const Edge>& edge) const noexcept
{
  return std::count(std::begin(m_edges),std::end(m_edges),edge);
}

bool ribi::cmap::ConceptMap::HasNode(const boost::shared_ptr<const Node>& node) const noexcept
{
  return std::count(std::begin(m_nodes),std::end(m_nodes),node);
}

bool ribi::cmap::ConceptMap::HasSameContent(
  const ribi::cmap::ConceptMap& lhs,
  const ribi::cmap::ConceptMap& rhs
) noexcept
{
  const bool trace_verbose{false};

  if (lhs.GetEdges().size() != rhs.GetEdges().size())
  {
    if (trace_verbose) { TRACE("Number of edges differ"); }
    return false;
  }
  if (lhs.GetNodes().size() != rhs.GetNodes().size())
  {
    if (trace_verbose)
    {
      TRACE("Number of nodes differ");
      TRACE(lhs.GetNodes().size());
      TRACE(rhs.GetNodes().size());
    }
    return false;
  }
  //Function to compare Node smart pointers
  //typedef boost::shared_ptr<const Node> ConstNodePtr;
  //const std::function<bool(const boost::shared_ptr<const Node>& lhs,
  //  const boost::shared_ptr<const Node>& rhs)> node_cmp
  //  = [](const boost::shared_ptr<const Node>& lhs,
  //       const boost::shared_ptr<const Node>& rhs)
  //    {
  //      return *lhs < *rhs;
  //    };
  //Function to compare Concept smart pointers
  typedef boost::shared_ptr<const ribi::cmap::Concept> ConstConceptPtr;
  const std::function<bool(const boost::shared_ptr<const ribi::cmap::Concept>& lhs,
    const boost::shared_ptr<const ribi::cmap::Concept>& rhs)> concept_cmp
    = [](const boost::shared_ptr<const ribi::cmap::Concept>& lhs,
         const boost::shared_ptr<const ribi::cmap::Concept>& rhs)
      {
        return *lhs < *rhs;
      };


  //Same Concepts
  {
    const std::vector<boost::shared_ptr<const Node>> nodes_lhs = lhs.GetNodes();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_lhs(concept_cmp);
    std::transform(nodes_lhs.begin(),nodes_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](boost::shared_ptr<const Node> node)
      {
        assert(node);
        assert(node->GetConcept());
        ConstConceptPtr concept = node->GetConcept();
        return concept;
      }
    );

    const std::vector<boost::shared_ptr<const Node>> nodes_rhs = rhs.GetNodes();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_rhs(concept_cmp);

    std::transform(nodes_rhs.begin(),nodes_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const Node>& node)
      {
        return node->GetConcept();
      }
    );
    if (std::mismatch(concepts_lhs.begin(),concepts_lhs.end(),concepts_rhs.begin(),
      [](const ConstConceptPtr& a,
         const ConstConceptPtr& b)
        {
          return *a == *b;
        }
      )
      != std::make_pair(concepts_lhs.end(),concepts_rhs.end()))
    {
      if (trace_verbose) { TRACE("Node concepts differ"); }
      return false;
    }
  }
  //Same Edges
  {
    const std::vector<boost::shared_ptr<const Edge>> edges_lhs = lhs.GetEdges();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_lhs(concept_cmp);
    std::transform(edges_lhs.begin(),edges_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](const boost::shared_ptr<const Edge>& edge)
      {
        assert(edge);
        assert(edge->GetNode());
        assert(edge->GetNode()->GetConcept());
        return edge->GetNode()->GetConcept();
      }
    );

    const std::vector<boost::shared_ptr<const Edge>> edges_rhs = rhs.GetEdges();

    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_rhs(concept_cmp);
    std::transform(edges_rhs.begin(),edges_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const cmap::Edge>& edge)
      {
        assert(edge);
        assert(edge->GetNode());
        assert(edge->GetNode()->GetConcept());
        return edge->GetNode()->GetConcept();
      }
    );
    if (std::mismatch(concepts_lhs.begin(),concepts_lhs.end(),concepts_rhs.begin(),
      [](const ConstConceptPtr& a,const ConstConceptPtr& b)
        {
          return *a == *b;
        }
      )
      != std::make_pair(concepts_lhs.end(),concepts_rhs.end()))
    {
      if (trace_verbose) { TRACE("Edge concepts differ"); }
      return false;
    }
  }
  //Check if for each edge a same 'from' and 'to' concept can be found
  {
    typedef std::tuple<std::string,std::string,std::string> FakeEdge;
    typedef std::vector<FakeEdge> FakeEdges;

    assert(lhs.GetEdges().size() == rhs.GetEdges().size());

    FakeEdges v;
    const int sz = lhs.GetEdges().size();
    for (int i=0; i!=sz; ++i)
    {
      const auto from_node = lhs.GetEdges()[i]->GetFrom();
      const std::string str_from = from_node->GetConcept()->GetName();
      const std::string str_mid = lhs.GetEdges()[i]->GetNode()->GetConcept()->GetName();
      const auto to_node = lhs.GetEdges()[i]->GetTo();
      const std::string str_to = to_node->GetConcept()->GetName();
      //Only if arrow is reversed, reverse the fake edge
      if (
           lhs.GetEdges()[i]->HasTailArrow() == true
        && lhs.GetEdges()[i]->HasHeadArrow() == false)
      {
        v.push_back(std::make_tuple(str_to,str_mid,str_from));
      }
      else if (lhs.GetEdges()[i]->HasTailArrow() == lhs.GetEdges()[i]->HasHeadArrow())
      {
        //Two-way or zero-way arrow, add it in both directions
        v.push_back(std::make_tuple(str_to,str_mid,str_from));
        v.push_back(std::make_tuple(str_from,str_mid,str_to));
      }
      else
      {
        //Normal arrow
        v.push_back(std::make_tuple(str_from,str_mid,str_to));
      }
    }
    assert(boost::numeric_cast<int>(v.size()) >= sz);

    FakeEdges w;
    for (int i=0; i!=sz; ++i)
    {
      const auto from_node = rhs.GetEdges()[i]->GetFrom();
      const std::string str_from = from_node->GetConcept()->GetName();
      const std::string str_mid = rhs.GetEdges()[i]->GetNode()->GetConcept()->GetName();
      const auto to_node = rhs.GetEdges()[i]->GetTo();
      const std::string str_to = to_node->GetConcept()->GetName();
      //w.push_back(std::make_tuple(str_from,str_mid,str_to));
      //Only if arrow is reversed, reverse the fake edge
      if (
           rhs.GetEdges()[i]->HasTailArrow() == true
        && rhs.GetEdges()[i]->HasHeadArrow() == false)
      {
        w.push_back(std::make_tuple(str_to,str_mid,str_from));
      }
      else if (rhs.GetEdges()[i]->HasTailArrow() == rhs.GetEdges()[i]->HasHeadArrow())
      {
        //Two-way or zero-way arrow, add it in both directions
        w.push_back(std::make_tuple(str_to,str_mid,str_from));
        w.push_back(std::make_tuple(str_from,str_mid,str_to));
      }
      else
      {
        //Normal arrow
        w.push_back(std::make_tuple(str_from,str_mid,str_to));
      }
    }
    assert(static_cast<int>(w.size()) >= sz);
    if (v.size() != w.size()) return false;

    std::sort(v.begin(),v.end());
    std::sort(w.begin(),w.end());
    if (v != w)
    {
      //#define REALLY_SHOW_ME_THIS_7364894385876473475934758934753
      #ifdef REALLY_SHOW_ME_THIS_7364894385876473475934758934753
      #ifndef NDEBUG
      for (int i=0; i!=sz; ++i)
      {
        std::stringstream s;
        s << "[" << (i+1) << "/" << sz << "]: ("
          << std::get<0>(v[i]) << "," << std::get<1>(v[i]) << "," << std::get<2>(v[i])
          << ") , ("
          << std::get<0>(w[i]) << "," << std::get<1>(w[i]) << "," << std::get<2>(w[i])
          << ")";
        TRACE(s);
      }
      #endif
      #endif
      return false;
    }
  }
  return true;
}

#ifndef NDEBUG
bool ribi::cmap::ConceptMap::IsValid() const noexcept
{
  for (const boost::shared_ptr<Node>& node: m_nodes)
  {
    if (!node)
    {
      TRACE("Node is nullptr");
      return false;
    }
  }
  for (const boost::shared_ptr<Edge>& edge: m_edges)
  {
    if (!edge)
    {
      TRACE("Edge is nullptr");
      return false;
    }
    if (!edge->GetTo())
    {
      TRACE("edge->GetTo() is nullptr");
      return false;
    }
    if (!edge->GetFrom())
    {
      TRACE("edge->GetFrom() is nullptr");
      return false;
    }
    if (std::count(
      m_nodes.begin(),
      m_nodes.end(),
      edge->GetTo()) != 1)
    {
      TRACE("edge->GetTo() points to node not in the concept map");
      return false;
    }
    if(std::count(
      m_nodes.begin(),
      m_nodes.end(),
      edge->GetFrom()) != 1)
    {
      TRACE("edge->GetFrom() points to node not in the concept map");
      return false;
    }
  }
  return true;
}
#endif

std::string ribi::cmap::ConceptMap::ToXml(const ReadOnlyConceptMapPtr& map) noexcept
{
  std::stringstream s;
  s << "<concept_map>";
  s << "<nodes>";
  const std::vector<boost::shared_ptr<const Node>>& nodes = map->GetNodes();
  for (const boost::shared_ptr<const Node> node: nodes)
  {
    s << node->ToXml();
  }
  s << "</nodes>";
  s << "<edges>";
  const std::vector<boost::shared_ptr<const cmap::Edge>>& edges = map->GetEdges();
  for (const boost::shared_ptr<const cmap::Edge> edge: edges)
  {
    s << Edge::ToXml(edge,nodes);
  }
  s << "</edges>";
  s << "</concept_map>";

  const std::string r = s.str();
  assert(r.size() >= 27);
  assert(r.substr(0,13) == "<concept_map>");
  assert(r.substr(r.size() - 14,14) == "</concept_map>");

  return r;
}

int ribi::cmap::CountCenterNodes(
  const ribi::cmap::ConceptMap::ReadOnlyConceptMapPtr& conceptmap
) noexcept
{
  const auto v = conceptmap->GetNodes();
  const int cnt = std::count_if(v.begin(),v.end(),
    [](const boost::shared_ptr<const Node> node)
    {
      return IsCenterNode(node);
    }
  );
  assert(cnt < 2 && "A concept map can have one or zero (a sub-conceptmap) center nodes");
  return cnt;
}

int ribi::cmap::CountCenterNodeEdges(
  const ribi::cmap::ConceptMap::ReadOnlyConceptMapPtr& conceptmap
) noexcept
{
  const int n_center_nodes{CountCenterNodes(conceptmap)};
  assert(n_center_nodes < 2 && "A concept map can have one or zero (a sub-conceptmap) center nodes");
  if (n_center_nodes == 0) return 0;
  const auto v = conceptmap->GetEdges();
  const int cnt{
    std::count_if(v.begin(),v.end(),
      [](const boost::shared_ptr<const Edge> edge)
      {
        return IsConnectedToCenterNode(edge);
      }
    )
  };
  return cnt;
}

bool ribi::cmap::operator==(const ribi::cmap::ConceptMap& lhs, const ribi::cmap::ConceptMap& rhs) noexcept
{
  //Compare nodes
  {
    const std::vector<boost::shared_ptr<const Node>> lhs_nodes = lhs.GetNodes();
    const std::vector<boost::shared_ptr<const Node>> rhs_nodes = rhs.GetNodes();
    if (lhs_nodes.size() != rhs_nodes.size()) return false;
    if (!
      std::equal(
        std::begin(lhs_nodes),
        std::end(  lhs_nodes),
        std::begin(rhs_nodes),
        [](const boost::shared_ptr<const Node> lhs_node,
           const boost::shared_ptr<const Node> rhs_node)
        {
          return *lhs_node == *rhs_node;
        }
      )
    )
    {
      return false;
    }
  }
  //Compare edges
  {
    const std::vector<boost::shared_ptr<const cmap::Edge>> lhs_edges = lhs.GetEdges();
    const std::vector<boost::shared_ptr<const cmap::Edge>> rhs_edges = rhs.GetEdges();
    if (lhs_edges.size() != rhs_edges.size()) return false;
    if (!
      std::equal(
        std::begin(lhs_edges),
        std::end(  lhs_edges),
        std::begin(rhs_edges),
        [](const boost::shared_ptr<const cmap::Edge> lhs_edge,
           const boost::shared_ptr<const cmap::Edge> rhs_edge)
        {
          return *lhs_edge == *rhs_edge;
        }
      )
    )
    {
      return false;
    }
  }


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

  return true;

}

bool ribi::cmap::operator!=(const ribi::cmap::ConceptMap& lhs, const ribi::cmap::ConceptMap& rhs) noexcept
{
  return !(lhs == rhs);
}




void ribi::cmap::ConceptMap::AddSelected(const std::vector<boost::shared_ptr<Edge>>& edges) noexcept
{
  assert(std::count(edges.begin(),edges.end(),nullptr) == 0);
  std::copy(edges.begin(),edges.end(),std::back_inserter(m_selected.first));

  //Remove duplicates
  std::sort(std::begin(m_selected.first),std::end(m_selected.first));
  const auto new_end = std::unique(std::begin(m_selected.first),std::end(m_selected.first));
  m_selected.first.erase(new_end,std::end(m_selected.first));

  m_signal_selected_changed(m_selected);
}

void ribi::cmap::ConceptMap::AddSelected(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept
{
  assert(std::count(nodes.begin(),nodes.end(),nullptr) == 0);
  std::copy(std::begin(nodes),std::end(nodes),std::back_inserter(m_selected.second));

  //Remove duplicates
  std::sort(std::begin(m_selected.second),std::end(m_selected.second));
  const auto new_end = std::unique(std::begin(m_selected.second),std::end(m_selected.second));
  m_selected.second.erase(new_end,std::end(m_selected.second));

  m_signal_selected_changed(m_selected);
}

void ribi::cmap::ConceptMap::AddSelected(
  const std::vector<boost::shared_ptr<Edge>>& edges,
  const std::vector<boost::shared_ptr<Node>>& nodes
) noexcept
{
  AddSelected(edges);
  AddSelected(nodes);
}

bool ribi::cmap::ConceptMap::CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept
{
  return command->CanDoCommand(this);
}

boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::ConceptMap::CreateEmptyConceptMap() noexcept
{
  const boost::shared_ptr<ConceptMap> concept_map {
    ConceptMapFactory().Create()
  };
  assert(concept_map);
  return concept_map;
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::ConceptMap::CreateNewEdge() noexcept
{
  assert(GetSelectedNodes().size() == 2);

  const boost::shared_ptr<Node> from { GetSelectedNodes()[0] };
  const boost::shared_ptr<Node> to   { GetSelectedNodes()[1] };
  const boost::shared_ptr<Edge> edge { EdgeFactory().Create(from,to) };

  //Add the Edge
  AddEdge(edge);

  //Signal the new Edge
  m_signal_add_edge(edge);

  //Keep track of what is selected
  this->AddSelected( { edge } );
  this->Unselect( { edge->GetFrom() } );
  this->Unselect( { edge->GetTo() } );

  return edge;
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::ConceptMap::CreateNewNode() noexcept
{
  #ifndef NDEBUG
  static std::string my_string = "A";
  const boost::shared_ptr<Node> node {
    NodeFactory().CreateFromStrings(my_string)
  };
  ++my_string[0];
  #else
  const boost::shared_ptr<Node> node {
    NodeFactory().CreateFromStrings("...")
  };
  #endif

  //Add the Node
  AddNode(node);

  //Signal the new Node
  m_signal_add_node(node);

  //Adding a Node should select it
  this->AddSelected( { node } ); //Must be after 'm_signal_add_node(node);'

  return node;
}

void ribi::cmap::ConceptMap::DoCommand(const boost::shared_ptr<Command> command) noexcept
{
  assert(command);
  if (!CanDoCommand(command))
  {
    TRACE("ERROR");
    TRACE(command->ToStr());
    TRACE("BREAK");
  }

  assert(CanDoCommand(command));

  command->m_signal_undo.connect(
    boost::bind(&ribi::cmap::ConceptMap::OnUndo,this,boost::lambda::_1)
  );

  //Undo
  m_undo.push_back(command);

  //Actually do the Command
  command->DoCommand(this);

  assert(CanUndo());
}

boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::ConceptMap::FindNodeAt(
  const double x,
  const double y
) const noexcept
{
  assert(!"Am I used??");
  const int font_height{18};
  const int font_width{12};

  for (const boost::shared_ptr<const Node> node: GetNodes())
  {
    const double width  = (font_width * node->GetConcept()->GetName().size());
    const double height = font_height;

    const double left   = node->GetX() - (0.5 * width);
    const double top    = node->GetY() - (0.5 * height);
    const double right  = node->GetX() + (0.5 * width);
    const double bottom = node->GetY() + (0.5 * height);
    if (x >= left && x <= right && y >= top && y <= bottom) return node;
  }
  return boost::shared_ptr<const Node>();
}

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::ConceptMap::FindNodeAt(const double x, const double y) noexcept
{
  const boost::shared_ptr<const ribi::cmap::Node> node {
    const_cast<const ConceptMap*>(this)->FindNodeAt(x,y)
  };
  assert(node);
  return boost::const_pointer_cast<Node>(node);
}

ribi::cmap::ConceptMap::ConstEdgesAndNodes ribi::cmap::ConceptMap::GetSelected() const noexcept
{
  if (GetSelectedEdges().empty() && GetSelectedNodes().empty()) { return ConstEdgesAndNodes(); }
  return std::make_pair(GetSelectedEdges(),GetSelectedNodes());
}

ribi::cmap::ConceptMap::ConstEdges ribi::cmap::ConceptMap::GetSelectedEdges() const noexcept
{
  assert(std::count(std::begin(m_selected.first),std::end(m_selected.first),nullptr) == 0);
  const std::vector<boost::shared_ptr<const Edge>> selected {
    AddConst(m_selected.first)
  };
  return selected;
}

ribi::cmap::ConceptMap::ConstNodes ribi::cmap::ConceptMap::GetSelectedNodes() const noexcept
{
  assert(std::count(std::begin(m_selected.second),std::end(m_selected.second),nullptr) == 0);
  const std::vector<boost::shared_ptr<const Node>> selected {
    AddConst(m_selected.second)
  };
  return selected;
}

std::vector<boost::shared_ptr<ribi::cmap::Edge>> ribi::cmap::ConceptMap::GetRandomEdges(
  std::vector<boost::shared_ptr<const Edge>> edges_to_exclude
) noexcept
{
  if (GetEdges().empty()) { return Edges(); }
  Edges edges = GetEdges();
  const auto cmp = [](const boost::shared_ptr<const Edge>& lhs, const boost::shared_ptr<const Edge>& rhs) { return lhs.get() < rhs.get(); };
  std::sort(std::begin(edges),std::end(edges),cmp);
  std::sort(std::begin(edges_to_exclude),std::end(edges_to_exclude),cmp);
  //Find the Edges present in nodes, absent in nodes_to_exclude
  Edges focus_edges;
  std::set_difference(
    std::begin(edges),std::end(edges),
    std::begin(edges_to_exclude),std::end(edges_to_exclude),
    std::back_inserter(focus_edges),
    cmp
  );

  if (focus_edges.empty()) return focus_edges;
  if (focus_edges.size() == 1) return focus_edges;
  std::random_shuffle(focus_edges.begin(),focus_edges.end());
  const int n = 1 + (std::rand() % (focus_edges.size() - 1));
  focus_edges.resize(n);
  return focus_edges;
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::ConceptMap::GetRandomEdge(
  std::vector<boost::shared_ptr<const Edge>> edges_to_exclude) noexcept
{
  const auto v(GetRandomEdges(edges_to_exclude));
  boost::shared_ptr<Edge> p;
  if (!v.empty()) p = v[0];
  return p;
}

std::vector<boost::shared_ptr<ribi::cmap::Node>> ribi::cmap::ConceptMap::GetRandomNodes(
  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude
) noexcept
{
  if (GetNodes().empty()) { return Nodes(); }
  Nodes nodes = GetNodes();
  std::sort(nodes.begin(),nodes.end());
  std::sort(nodes_to_exclude.begin(),nodes_to_exclude.end());
  //Find the Nodes present in nodes, absent in nodes_to_exclude
  Nodes focus_nodes;
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

boost::shared_ptr<ribi::cmap::Node> ribi::cmap::ConceptMap::GetRandomNode(
  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude) noexcept
{
  const auto v(GetRandomNodes(nodes_to_exclude));
  boost::shared_ptr<Node> p;
  if (!v.empty()) p = v[0];
  return p;
}

void ribi::cmap::ConceptMap::OnUndo(const Command * const
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

void ribi::cmap::ConceptMap::SetSelected(
  const ConstEdges& edges,
  const ConstNodes& nodes
) noexcept
{
  const Edges non_const_edges = RemoveConst(edges);
  const Nodes non_const_nodes = RemoveConst(nodes);
  m_selected.first = non_const_edges;
  m_selected.second = non_const_nodes;
  m_signal_selected_changed(m_selected);
}

void ribi::cmap::ConceptMap::SetSelected(const Edges& edges) noexcept
{
  SetSelected( AddConst(edges), {});
}

void ribi::cmap::ConceptMap::SetSelected(const Nodes& nodes) noexcept
{
  SetSelected( {}, AddConst(nodes));
}

void ribi::cmap::ConceptMap::SetSelected(const ConstEdgesAndNodes& nodes_and_edges) noexcept
{
  SetSelected(nodes_and_edges.first, nodes_and_edges.second);
}

void ribi::cmap::ConceptMap::Undo() noexcept
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

void ribi::cmap::ConceptMap::Unselect(
  const ConstEdgesAndNodes& edges_and_nodes
) noexcept
{
  Unselect(edges_and_nodes.first);
  Unselect(edges_and_nodes.second);
}

void ribi::cmap::ConceptMap::Unselect(
  const ConstEdges& edges
) noexcept
{
  for (const auto edge: edges)
  {
    m_selected.first.erase(
      std::remove(
        std::begin(m_selected.first),
        std::end(m_selected.first),
        edge
      ),
      std::end(m_selected.first)
    );
  }

  m_signal_selected_changed(m_selected);
}

void ribi::cmap::ConceptMap::Unselect(
  const ConstNodes& nodes
) noexcept
{
  for (const auto node: nodes)
  {
    m_selected.second.erase(
      std::remove(
        std::begin(m_selected.second),
        std::end(m_selected.second),
        node
      ),
      std::end(m_selected.second)
    );
  }
  m_signal_selected_changed(m_selected);
}
