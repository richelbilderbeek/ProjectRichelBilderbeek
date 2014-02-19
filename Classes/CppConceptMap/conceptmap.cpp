#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmap.h"

#include <set>
#include <sstream>
#include <functional>
#include "conceptmapcenternodefactory.h"
#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "trace.h"
//#include "conceptmapcluster.h"
#pragma GCC diagnostic pop

ribi::cmap::ConceptMap::ConceptMap(const std::string& question)
  : m_edges( {} ),
    m_nodes(CreateNodes(question, {} ))
{
  #ifndef NDEBUG
  Test();
  assert(ConceptMap::CanConstruct(m_nodes,m_edges));
  assert(this->GetQuestion() == question);

  assert(FindCenterNode()
    && "Assume a CenterNode at the center of ConceptMap");
  assert(IsCenterNode(FindCenterNode())
    && "Assume a CenterNode at the center of ConceptMap");
  #endif
}

ribi::cmap::ConceptMap::ConceptMap(
    const std::vector<boost::shared_ptr<ribi::cmap::Node> >& nodes,
    const std::vector<boost::shared_ptr<ribi::cmap::Edge> >& edges)
  : m_edges(edges),
    m_nodes(nodes)
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
      #ifndef NDEBUG
      const auto from_iter = std::find(nodes.begin(),nodes.end(),edge->GetFrom());
      const auto to_iter = std::find(nodes.begin(),nodes.end(),edge->GetTo());
      assert(from_iter != nodes.end());
      assert(to_iter != nodes.end());
      #endif
      std::cout << i << ": " << Edge::ToXml(edge,const_nodes) << '\n';
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

  const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& v = cluster->Get();
  const int n = boost::numeric_cast<int>(v.size());
  for (int i=0; i!=n; ++i)
  {
    const int x = 0;
    const int y = 0;
    const boost::shared_ptr<Node> node = cmap::NodeFactory::Create(v[i],x,y);
    assert(node);
    m_nodes.push_back(node);
  }
  assert(v.size() + 1 == m_nodes.size()
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
}
#endif //TO_ADD_TO_PROJECTBRAINWEAVER

void ribi::cmap::ConceptMap::AddEdge(const boost::shared_ptr<Edge> edge)
{
  assert(edge);
  assert(std::count(m_nodes.begin(),m_nodes.end(),edge->GetFrom()) == 1
    && "First enter the node this edge originates from");
  assert(std::count(m_nodes.begin(),m_nodes.end(),edge->GetTo()) == 1
    && "First enter the node this edge targets to");
  m_edges.push_back(edge);
}

void ribi::cmap::ConceptMap::AddNode(const boost::shared_ptr<Node> node)
{
  assert(node);
  m_nodes.push_back(node);
  assert(std::count(m_nodes.begin(),m_nodes.end(),node) == 1
    && "Every node must be unique");
}


bool ribi::cmap::ConceptMap::CanConstruct(
  const std::vector<boost::shared_ptr<ribi::cmap::Node> >& /* nodes */,
  const std::vector<boost::shared_ptr<ribi::cmap::Edge> >& edges)
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

const std::vector<boost::shared_ptr<ribi::cmap::Node> > ribi::cmap::ConceptMap::CreateNodes(
  const std::string& question,
  const std::vector<boost::shared_ptr<ribi::cmap::Node> >& nodes)
{
  std::vector<boost::shared_ptr<Node> > v;
  const boost::shared_ptr<Concept> concept(
    ConceptFactory().Create(
      question,
      ExamplesFactory::Create(), //No examples
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

const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > ribi::cmap::ConceptMap::CreateSubs() const
{
  std::vector<boost::shared_ptr<ConceptMap> > v;
  for (const boost::shared_ptr<Node> focal_node: m_nodes)
  {
    assert(focal_node);

    //Collect all edges connected top the focal node (which is m_nodes[i])
    std::vector<boost::shared_ptr<Node> > nodes;
    std::vector<boost::shared_ptr<Edge> > edges;

    nodes.push_back(focal_node);

    for (const boost::shared_ptr<Edge> focal_edge: m_edges)
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

void ribi::cmap::ConceptMap::DeleteEdge(const boost::shared_ptr<Edge> edge)
{
  #ifndef NDEBUG
  assert(edge);
  assert(std::count(m_edges.begin(),m_edges.end(),edge) != 0
    && "The edge must exist");
  assert(std::count(m_edges.begin(),m_edges.end(),edge) == 1
    && "Every edge is unique");
  const std::size_t n_edges_before = m_edges.size();
  #endif

  //Copied from http://www.richelbilderbeek.nl/CppVector.htm
  m_edges.erase(std::remove(m_edges.begin(),m_edges.end(),edge),m_edges.end());

  #ifndef NDEBUG
  const std::size_t n_edges_after = m_edges.size();
  assert(n_edges_before - 1 == n_edges_after);
  #endif
}

void ribi::cmap::ConceptMap::DeleteNode(const boost::shared_ptr<Node> node)
{
  #ifndef NDEBUG
  assert(node);
  if (std::count(m_nodes.begin(),m_nodes.end(),node) == 0)
  {
    TRACE("BREAK");
  }
  assert(std::count(m_nodes.begin(),m_nodes.end(),node) > 0
    && "Can only delete an existing node");
  assert(std::count(m_nodes.begin(),m_nodes.end(),node) == 1
    && "Every node is unique");
  const std::size_t n_nodes_before = m_nodes.size();
  #endif

  //Delete all edges going to this node
  std::vector<boost::shared_ptr<ribi::cmap::Edge> > to_be_deleted;
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

  //Delete the node itself
  //Copied from http://www.richelbilderbeek.nl/CppVector.htm
  m_nodes.erase(std::remove(m_nodes.begin(),m_nodes.end(),node),m_nodes.end());

  #ifndef NDEBUG
  const std::size_t n_nodes_after = m_nodes.size();
  assert(n_nodes_before - 1 == n_nodes_after);
  #endif
}


bool ribi::cmap::ConceptMap::Empty() const
{
  return m_nodes.empty() && m_edges.empty();
}

const boost::shared_ptr<const ribi::cmap::CenterNode> ribi::cmap::ConceptMap::FindCenterNode() const noexcept
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

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::ConceptMap::FindCenterNode() noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  const boost::shared_ptr<const ribi::cmap::CenterNode> center_node {
    dynamic_cast<const ConceptMap*>(this)->FindCenterNodeConst() //Add const because compiler cannt find the right version
  };
  return boost::const_pointer_cast<CenterNode>(
    center_node
  );
}


const std::vector<boost::shared_ptr<const ribi::cmap::Edge> > ribi::cmap::ConceptMap::GetEdges() const
{
  return AddConst(m_edges);
}

const boost::shared_ptr<const ribi::cmap::Node> ribi::cmap::ConceptMap::GetFocalNode() const noexcept
{
  if (m_nodes.empty()) return nullptr;
  return m_nodes[0];
}

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::ConceptMap::GetFocalNode() noexcept
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


const std::vector<boost::shared_ptr<const ribi::cmap::Node> > ribi::cmap::ConceptMap::GetNodes() const
{
  return AddConst(m_nodes);
}

const std::string ribi::cmap::ConceptMap::GetQuestion() const noexcept
{
  const boost::shared_ptr<const CenterNode> center_node(FindCenterNode());
  if (center_node)
  {
    assert(center_node->GetConcept());
    return center_node->GetConcept()->GetName();
  }
  else return "";
}

const std::string ribi::cmap::ConceptMap::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::cmap::ConceptMap::GetVersionHistory() noexcept
{
  return {
    "2013-xx-xx: Version 1.0: initial version",
    "2013-12-23: Version 1.1: started versioning",
    "2014-02-08: Version 1.2: support an empty concept map"
  };
}

bool ribi::cmap::ConceptMap::HasSameContent(
  const ribi::cmap::ConceptMap& lhs,
  const ribi::cmap::ConceptMap& rhs)
{
  const bool trace_verbose = false;
  if (lhs.GetQuestion() != rhs.GetQuestion())
  {
    if (trace_verbose) { TRACE("Questions differ"); }
    return false;
  }
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
    const std::vector<boost::shared_ptr<const cmap::Node> > nodes_lhs = lhs.GetNodes();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_lhs(concept_cmp);
    std::transform(nodes_lhs.begin(),nodes_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](boost::shared_ptr<const cmap::Node> node)
      {
        assert(node);
        assert(node->GetConcept());
        ConstConceptPtr concept = node->GetConcept();
        return concept;
      }
    );

    const std::vector<boost::shared_ptr<const cmap::Node> > nodes_rhs = rhs.GetNodes();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_rhs(concept_cmp);

    std::transform(nodes_rhs.begin(),nodes_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const cmap::Node>& node)
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
    const std::vector<boost::shared_ptr<const cmap::Edge> > edges_lhs = lhs.GetEdges();
    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_lhs(concept_cmp);
    std::transform(edges_lhs.begin(),edges_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](const boost::shared_ptr<const cmap::Edge>& edge)
      {
        assert(edge);
        assert(edge->GetConcept());
        return edge->GetConcept();
      }
    );

    const std::vector<boost::shared_ptr<const cmap::Edge> > edges_rhs = rhs.GetEdges();

    std::multiset<ConstConceptPtr,decltype(concept_cmp)> concepts_rhs(concept_cmp);
    std::transform(edges_rhs.begin(),edges_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const cmap::Edge>& edge)
      {
        return edge->GetConcept();
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
      const std::string str_mid = lhs.GetEdges()[i]->GetConcept()->GetName();
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
      const std::string str_mid = rhs.GetEdges()[i]->GetConcept()->GetName();
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
bool ribi::cmap::ConceptMap::IsValid() const
{
  for (const boost::shared_ptr<Node> node: m_nodes)
  {
    if (!node)
    {
      TRACE("Node is nullptr");
      return false;
    }
  }
  for (const boost::shared_ptr<Edge> edge: m_edges)
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

const std::string ribi::cmap::ConceptMap::ToXml(const boost::shared_ptr<const ribi::cmap::ConceptMap> map)
{
  std::stringstream s;
  s << "<concept_map>";
  s << "<nodes>";
  const std::vector<boost::shared_ptr<const cmap::Node> >& nodes = map->GetNodes();
  for (const boost::shared_ptr<const cmap::Node> node: nodes)
  {
    s << node->ToXml();
  }
  s << "</nodes>";
  s << "<edges>";
  const std::vector<boost::shared_ptr<const cmap::Edge> >& edges = map->GetEdges();
  for (const boost::shared_ptr<const cmap::Edge> edge: edges)
  {
    s << Edge::ToXml(edge,nodes);
  }
  s << "</edges>";
  s << "</concept_map>";

  const std::string r = s.str();
  assert(r.size() >= 27);
  assert(r.substr(0,13) == std::string("<concept_map>"));
  assert(r.substr(r.size() - 14,14) == std::string("</concept_map>"));

  return r;
}

int ribi::cmap::CountCenterNodes(const boost::shared_ptr<const ConceptMap> conceptmap) noexcept
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

int ribi::cmap::CountCenterNodeEdges(const boost::shared_ptr<const ConceptMap> conceptmap) noexcept
{
  const int n_center_nodes = CountCenterNodes(conceptmap);
  assert(n_center_nodes < 2 && "A concept map can have one or zero (a sub-conceptmap) center nodes");
  if (n_center_nodes == 0) return 0;
  const auto v = conceptmap->GetEdges();
  const int cnt = std::count_if(v.begin(),v.end(),
    [](const boost::shared_ptr<const Edge> edge)
    {
      return IsConnectedToCenterNode(edge);
    }
  );
  return cnt;
}

bool ribi::cmap::operator==(const ribi::cmap::ConceptMap& lhs, const ribi::cmap::ConceptMap& rhs)
{
  //Compare nodes
  {
    const std::vector<boost::shared_ptr<const cmap::Node> > lhs_nodes = lhs.GetNodes();
    const std::vector<boost::shared_ptr<const cmap::Node> > rhs_nodes = rhs.GetNodes();
    if (lhs_nodes.size() != rhs_nodes.size()) return false;
    if (!
      std::equal(
        std::begin(lhs_nodes),
        std::end(  lhs_nodes),
        std::begin(rhs_nodes),
        [](const boost::shared_ptr<const cmap::Node> lhs_node,
           const boost::shared_ptr<const cmap::Node> rhs_node)
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
    const std::vector<boost::shared_ptr<const cmap::Edge> > lhs_edges = lhs.GetEdges();
    const std::vector<boost::shared_ptr<const cmap::Edge> > rhs_edges = rhs.GetEdges();
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
  return true;

}

bool ribi::cmap::operator!=(const ribi::cmap::ConceptMap& lhs, const ribi::cmap::ConceptMap& rhs)
{
  return !(lhs == rhs);
}
