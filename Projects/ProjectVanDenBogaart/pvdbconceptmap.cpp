#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconceptmap.h"

#include <set>
#include <sstream>

#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbhelper.h"
#include "trace.h"
#include "pvdbexamplesfactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "pvdbedge.h"
#include "pvdbcluster.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::ConceptMap::ConceptMap(const std::string& question)
  : m_edges( {} ),
    m_nodes(CreateNodes(question, {} ))
{
  #ifndef NDEBUG
  Test();
  assert(ConceptMap::CanConstruct(m_nodes,m_edges));
  assert(this->GetQuestion() == question);
  #endif
}

pvdb::ConceptMap::ConceptMap(
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
    const std::vector<boost::shared_ptr<pvdb::Edge> >& edges)
  : m_edges(edges),
    m_nodes(nodes)
{
  #ifndef NDEBUG
  Test();
  assert(ConceptMap::CanConstruct(nodes,edges));
  assert(this->GetQuestion() == nodes[0]->GetConcept()->GetName());
  #endif
}

pvdb::ConceptMap::ConceptMap(
  const std::string& question,
  const boost::shared_ptr<pvdb::Cluster>& cluster)
  : m_nodes(CreateNodes(question, {} ))
{
  #ifndef NDEBUG
  Test();
  #endif

  const std::vector<boost::shared_ptr<pvdb::Concept> >& v = cluster->Get();
  const int n = static_cast<int>(v.size());
  //const double ray = 100.0; //pixels
  for (int i=0; i!=n; ++i)
  {
    //const double angle = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(n);
    //const int x = static_cast<int>(0.0 + (std::sin(angle) * ray));
    //const int y = static_cast<int>(0.0 - (std::cos(angle) * ray));
    //Let QtPvdbConceptMapWidget arrange the positioning of the concepts
    const int x = 0;
    const int y = 0;
    const boost::shared_ptr<pvdb::Node> node = pvdb::NodeFactory::Create(v[i],x,y);
    assert(node);
    m_nodes.push_back(node);
  }
  assert(v.size() + 1 == m_nodes.size()
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
}

bool pvdb::ConceptMap::CanConstruct(
  const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
  const std::vector<boost::shared_ptr<pvdb::Edge> >& edges)
{
  //if (question.empty() && "Cannot construct empty questions") return false;
  //Test if first node, which is the focal question, does not have examples
  if (nodes.empty())
  {

    return false;
  }
  assert(nodes[0]->GetConcept());
  //The center node CAN have examples, when the center node is the focal node of a sub-concept map
  ///if (!nodes[0]->GetConcept()->GetExamples().empty()) { return false; }
  //Test if all edges are in range
  {
    const int n_nodes = static_cast<int>(nodes.size());
    const int n_invalid = std::count_if(edges.begin(), edges.end(),
      [n_nodes](const boost::shared_ptr<pvdb::Edge> & edge)
      {
        return edge->GetTo() >= n_nodes || edge->GetFrom() >= n_nodes;
      }
    );
    if (n_invalid)
    {
      return false;
    }
  }
  //Test if there are 'two-way' edges, that is, one edge going from A to B
  //and another edge going from B to A
  {
    const int n_edges = edges.size();
    for (int i=0; i!=n_edges; ++i)
    {
      const boost::shared_ptr<pvdb::Edge> & a = edges[i];
      const int a_from = a->GetFrom();
      const int a_to   = a->GetTo();
      for (int j=i+1; j!=n_edges; ++j)
      {
        assert(i != j);
        assert(j < n_edges);
        const boost::shared_ptr<pvdb::Edge> & b = edges[j];
        assert(a.get() != b.get() && "Assume different pointers");
        const int b_from = b->GetFrom();
        const int b_to   = b->GetTo();
        if (a_from == b_from && a_to == b_to)
        {
          return false;
        }
        if (a_from == b_to && a_to == b_from)
        {
          return false;
        }
      }
    }
  }

  return true;
}

const std::vector<boost::shared_ptr<pvdb::Node> > pvdb::ConceptMap::CreateNodes(
  const std::string& question,
  const std::vector<boost::shared_ptr<pvdb::Node> >& nodes)
{
  std::vector<boost::shared_ptr<pvdb::Node> > v;
  const boost::shared_ptr<pvdb::Concept> concept(
    pvdb::ConceptFactory::Create(
      question,
      pvdb::ExamplesFactory::Create(), //No examples
      -1, //No rated complexity
      -1, //No rated concreteness
      -1  //No rated specificity
    )
  );
  const boost::shared_ptr<pvdb::Node> center_node = pvdb::NodeFactory::Create(concept,0,0);
  assert(center_node);
  v.push_back(center_node);
  std::copy(nodes.begin(),nodes.end(),std::back_inserter(v));
  assert(v.size() == nodes.size() + 1);
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMap::CreateSubs() const
{
  assert(m_nodes.size() >= 1 && "Concept map must have a focal question");

  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v;
  const int n_nodes = static_cast<int>(m_nodes.size());
  for (int i=0; i!=n_nodes; ++i)
  {
    //Collect all edges connected top the focal node (which is m_nodes[i])
    std::vector<boost::shared_ptr<pvdb::Edge> > edges;
    std::set<int> node_indices_set; //Which nodes must be copied later?
    const int n_edges = static_cast<int>(m_edges.size());
    for (int j=0; j!=n_edges; ++j)
    {
      const boost::shared_ptr<pvdb::Edge> focal_edge = m_edges[j];
      if (focal_edge->GetFrom() == i || focal_edge->GetTo() == i)
      {
        edges.push_back(focal_edge); //FIX? 2012-12-31
        //const boost::shared_ptr<pvdb::Edge> new_edge(new pvdb::Edge(focal_edge)); //BUG? 2012-12-31
        //edges.push_back(new_edge); //BUG? 2012-12-31
        node_indices_set.insert(focal_edge->GetFrom());
        node_indices_set.insert(focal_edge->GetTo());
      }
    }
    const std::vector<int> node_indices(node_indices_set.begin(), node_indices_set.end());
    assert(std::is_sorted(node_indices.begin(),node_indices.end()));

    //Copy the collected node indices
    std::vector<boost::shared_ptr<pvdb::Node> > nodes;
    std::transform(node_indices.begin(),node_indices.end(),
      std::back_inserter(nodes),
      [this](const int& index)
      {
        assert(index < static_cast<int>(m_nodes.size()));
        return m_nodes[index]; //FIX? 2012-12-31
        //const boost::shared_ptr<pvdb::Node> new_node = pvdb::NodeFactory::Create(*m_nodes[index])); //BUG? 2012-12-31
        //return new_node; //BUG? 2012-12-31
      }
    );
    //Make the to and from indices of the new concept map correct
    //Luckily, we already have a remapping table:
    //new node index = the index in the std::vector node_indices
    std::for_each(edges.begin(),edges.end(),
      [node_indices](boost::shared_ptr<pvdb::Edge>& edge)
      {
        //Remap
        {
          const int index_old = edge->GetFrom();
          assert(std::count(node_indices.begin(),node_indices.end(),index_old) == 1
            && "There must be only one unique known index");
          const auto new_index_iter = std::find(node_indices.begin(),node_indices.end(),index_old);
          assert(new_index_iter != node_indices.end());
          const int index_new = std::distance(node_indices.begin(),new_index_iter);
          assert(index_new >= 0);
          edge->SetFrom(index_new);
        }
        {
          const int index_old = edge->GetTo();
          assert(std::count(node_indices.begin(),node_indices.end(),index_old) == 1
            && "There must be only one unique known index");
          const auto new_index_iter = std::find(node_indices.begin(),node_indices.end(),index_old);
          assert(new_index_iter != node_indices.end());
          const int index_new = std::distance(node_indices.begin(),new_index_iter);
          assert(index_new >= 0);
          edge->SetTo(index_new);
        }
      }
    );
    if (nodes.empty())
    {
      //An unconnected node is zoomed in on
      nodes.push_back(m_nodes[i]); //FIX? 2012-12-31
      //const boost::shared_ptr<pvdb::Node> new_node(new pvdb::Node(*m_nodes[i])); //BUG? 2012-12-31
      //nodes.push_back(new_node); //BUG? 2012-12-31
    }
    assert(!nodes.empty());
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(new pvdb::ConceptMap(nodes,edges));
    v.push_back(concept_map);
  }
  return v;
}

bool pvdb::ConceptMap::Empty() const
{
  return m_nodes.empty() && m_edges.empty();
}

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMap::FromXml(const std::string &s)
{
  assert(s.size() >= 27);
  assert(s.substr(0,13) == std::string("<concept_map>"));
  assert(s.substr(s.size() - 14,14) == std::string("</concept_map>"));


  //Obtain the <concept_map> ... </concept_map> string
  const std::vector<std::string> v
    = pvdb::GetRegexMatches(s,QRegExp("(<concept_map>.*</concept_map>)"));
  assert(v.size() == 1);
  //Strip the <concept_map> tags
  const std::string concept_map_str = pvdb::StripXmlTag(v[0]);

  std::vector<boost::shared_ptr<pvdb::Node> > nodes;
  {
    //Obtain the <nodes> ... </nodes> strings
    const std::vector<std::string> w
      = pvdb::GetRegexMatches(concept_map_str,QRegExp("(<nodes>.*</nodes>)"));
    assert(w.size() == 1);
    //Strip the <nodes> tags
    const std::string nodes_str = pvdb::StripXmlTag(w[0]);
    //Obtain the <concept> ... </concept> strings
    const std::vector<std::string> x
      = pvdb::GetRegexMatches(nodes_str,QRegExp("(<node>.*</node>)"));
    std::for_each(x.begin(),x.end(),
      [&nodes](const std::string& s)
      {
        nodes.push_back( Node::FromXml(s) );
      }
    );
  }
  std::vector<boost::shared_ptr<pvdb::Edge> > edges;
  {
    //Obtain the <edges> ... </edges> strings
    const std::vector<std::string> w
      = pvdb::GetRegexMatches(concept_map_str,QRegExp("(<edges>.*</edges>)"));
    assert(w.size() == 1);
    //Strip the <edges> tags
    const std::string nodes_str = pvdb::StripXmlTag(w[0]);
    //Obtain the <edge> ... </edge> strings
    const std::vector<std::string> x
      = pvdb::GetRegexMatches(nodes_str,QRegExp("(<edge>.*</edge>)"));
    std::for_each(x.begin(),x.end(),
      [&edges](const std::string& s)
      {
        edges.push_back( Edge::FromXml(s) );
      }
    );
  }

  const boost::shared_ptr<pvdb::ConceptMap> concept_map(new ConceptMap(nodes,edges));
  return concept_map;
}

const std::vector<boost::shared_ptr<const pvdb::Edge> > pvdb::ConceptMap::GetEdges() const
{
  return AddConst(m_edges);
}

const std::vector<boost::shared_ptr<const pvdb::Node> > pvdb::ConceptMap::GetNodes() const
{
  return AddConst(m_nodes);
}

const std::string pvdb::ConceptMap::GetQuestion() const
{
  assert(!m_nodes.empty());
  assert(m_nodes[0]->GetConcept());
  //A Concept Map CAN have examples at node[0]: when it is a sub-cluster
  //assert(m_nodes[0]->GetConcept()->GetExamples().size() == 0);
  return m_nodes[0]->GetConcept()->GetName();
}

bool pvdb::ConceptMap::HasSameContent(
  const boost::shared_ptr<const pvdb::ConceptMap>& lhs,
  const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  assert(lhs); assert(rhs);
  if (lhs->GetQuestion() != rhs->GetQuestion())
  {
    return false;
  }
  if (lhs->GetEdges().size() != rhs->GetEdges().size())
  {
    return false;
  }
  if (lhs->GetNodes().size() != rhs->GetNodes().size())
  {
    return false;
  }
  //Same Concepts
  {
    const std::vector<boost::shared_ptr<const pvdb::Node> > nodes_lhs = lhs->GetNodes();
    std::multiset<boost::shared_ptr<const pvdb::Concept> > concepts_lhs;
    std::transform(nodes_lhs.begin(),nodes_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](const boost::shared_ptr<const pvdb::Node>& node)
      {
        assert(node);
        assert(node->GetConcept());
        return node->GetConcept();
      }
    );

    const std::vector<boost::shared_ptr<const pvdb::Node> > nodes_rhs = rhs->GetNodes();

    std::multiset<boost::shared_ptr<const pvdb::Concept> > concepts_rhs;
    std::transform(nodes_rhs.begin(),nodes_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const pvdb::Node>& node)
      {
        return node->GetConcept();
      }
    );
    if (std::mismatch(concepts_lhs.begin(),concepts_lhs.end(),concepts_rhs.begin(),
      [](const boost::shared_ptr<const pvdb::Concept>& a,
        const boost::shared_ptr<const pvdb::Concept>& b)
        {
          return a == b;
        }
      )
      != std::make_pair(concepts_lhs.end(),concepts_rhs.end()))
    {
      return false;
    }
  }
  //Same Edges
  {
    const std::vector<boost::shared_ptr<const pvdb::Edge> > edges_lhs = lhs->GetEdges();
    std::multiset<boost::shared_ptr<const pvdb::Concept> > concepts_lhs;
    std::transform(edges_lhs.begin(),edges_lhs.end(),
      std::inserter(concepts_lhs,concepts_lhs.begin()),
      [](const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        assert(edge);
        assert(edge->GetConcept());
        return edge->GetConcept();
      }
    );

    const std::vector<boost::shared_ptr<const pvdb::Edge> > edges_rhs = rhs->GetEdges();

    std::multiset<boost::shared_ptr<const pvdb::Concept> > concepts_rhs;
    std::transform(edges_rhs.begin(),edges_rhs.end(),
      std::inserter(concepts_rhs,concepts_rhs.begin()),
      [](const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        return edge->GetConcept();
      }
    );
    if (std::mismatch(concepts_lhs.begin(),concepts_lhs.end(),concepts_rhs.begin(),
      [](const boost::shared_ptr<const pvdb::Concept>& a,
        const boost::shared_ptr<const pvdb::Concept>& b)
        {
          return a == b;
        }
      )
      != std::make_pair(concepts_lhs.end(),concepts_rhs.end()))
    {
      return false;
    }
  }
  //Check if for each edge a same 'from' and 'to' concept can be found
  {
    typedef std::tuple<std::string,std::string,std::string> FakeEdge;
    typedef std::vector<FakeEdge> FakeEdges;

    assert(lhs->GetEdges().size() == rhs->GetEdges().size());

    FakeEdges v;
    const int sz = lhs->GetEdges().size();
    for (int i=0; i!=sz; ++i)
    {
      const int index_from = lhs->GetEdges()[i]->GetFrom();
      assert(index_from >= 0 && index_from < static_cast<int>(lhs->GetNodes().size()));
      const std::string str_from = lhs->GetNodes()[index_from]->GetConcept()->GetName();
      const std::string str_mid = lhs->GetEdges()[i]->GetConcept()->GetName();
      const int index_to = lhs->GetEdges()[i]->GetTo();
      assert(index_to >= 0 && index_to < static_cast<int>(lhs->GetNodes().size()));
      const std::string str_to = lhs->GetNodes()[index_to]->GetConcept()->GetName();
      //Only if arrow is reversed, reverse the fake edge
      if (
           lhs->GetEdges()[i]->HasTailArrow() == true
        && lhs->GetEdges()[i]->HasHeadArrow() == false)
      {
        v.push_back(std::make_tuple(str_to,str_mid,str_from));
      }
      else if (lhs->GetEdges()[i]->HasTailArrow() == lhs->GetEdges()[i]->HasHeadArrow())
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
    assert(static_cast<int>(v.size()) >= sz);

    FakeEdges w;
    for (int i=0; i!=sz; ++i)
    {
      const int index_from = rhs->GetEdges()[i]->GetFrom();
      assert(index_from >= 0 && index_from < static_cast<int>(rhs->GetNodes().size()));
      const std::string str_from = rhs->GetNodes()[index_from]->GetConcept()->GetName();
      const std::string str_mid = rhs->GetEdges()[i]->GetConcept()->GetName();
      const int index_to = rhs->GetEdges()[i]->GetTo();
      assert(index_to >= 0 && index_to < static_cast<int>(rhs->GetNodes().size()));
      const std::string str_to = rhs->GetNodes()[index_to]->GetConcept()->GetName();
      //w.push_back(std::make_tuple(str_from,str_mid,str_to));
      //Only if arrow is reversed, reverse the fake edge
      if (
           rhs->GetEdges()[i]->HasTailArrow() == true
        && rhs->GetEdges()[i]->HasHeadArrow() == false)
      {
        w.push_back(std::make_tuple(str_to,str_mid,str_from));
      }
      else if (rhs->GetEdges()[i]->HasTailArrow() == rhs->GetEdges()[i]->HasHeadArrow())
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

        TRACE(s.str());
      }
      #endif
      #endif
      return false;
    }
  }
  return true;
}

bool pvdb::ConceptMap::HasSameContent(
  const boost::shared_ptr<const pvdb::ConceptMap>& lhs,
  const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return HasSameContent(
    boost::shared_ptr<const pvdb::ConceptMap>(lhs),
    boost::shared_ptr<const pvdb::ConceptMap>(rhs)
  );
}

bool pvdb::ConceptMap::HasSameContent(
  const boost::shared_ptr<pvdb::ConceptMap>& lhs,
  const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  return HasSameContent(
    boost::shared_ptr<const pvdb::ConceptMap>(lhs),
    boost::shared_ptr<const pvdb::ConceptMap>(rhs)
  );
}

bool pvdb::ConceptMap::HasSameContent(
  const boost::shared_ptr<pvdb::ConceptMap>& lhs,
  const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return HasSameContent(
    boost::shared_ptr<const pvdb::ConceptMap>(lhs),
    boost::shared_ptr<const pvdb::ConceptMap>(rhs)
  );
}

const std::string pvdb::ConceptMap::ToXml(const boost::shared_ptr<const pvdb::ConceptMap>& map)
{
  std::stringstream s;
  s << "<concept_map>";
  s << "<nodes>";
  const std::vector<boost::shared_ptr<const pvdb::Node> >& nodes = map->GetNodes();
  std::for_each(nodes.begin(), nodes.end(),
    [&s](const boost::shared_ptr<const pvdb::Node>& node)
    {
      s << Node::ToXml(node);
    }
  );
  s << "</nodes>";
  s << "<edges>";
  const std::vector<boost::shared_ptr<const pvdb::Edge> >& edges = map->GetEdges();
  std::for_each(edges.begin(), edges.end(),
    [&s](const boost::shared_ptr<const pvdb::Edge>& edge)
    {
      s << Edge::ToXml(edge);
    }
  );
  s << "</edges>";
  s << "</concept_map>";

  const std::string r = s.str();
  assert(r.size() >= 27);
  assert(r.substr(0,13) == std::string("<concept_map>"));
  assert(r.substr(r.size() - 14,14) == std::string("</concept_map>"));

  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::ConceptMap& lhs, const pvdb::ConceptMap& rhs)
{
  //Compare nodes
  {
    const std::vector<boost::shared_ptr<const pvdb::Node> > lhs_nodes = lhs.GetNodes();
    const std::vector<boost::shared_ptr<const pvdb::Node> > rhs_nodes = rhs.GetNodes();
    if (lhs_nodes.size() != rhs_nodes.size()) return false;
    const int n_nodes = static_cast<int>(lhs_nodes.size());
    for (int i=0; i!=n_nodes; ++i)
    {
      if (lhs_nodes[i] != rhs_nodes[i]) return false;
    }
  }
  //Compare edges
  {
    const std::vector<boost::shared_ptr<const pvdb::Edge> > lhs_edges = lhs.GetEdges();
    const std::vector<boost::shared_ptr<const pvdb::Edge> > rhs_edges = rhs.GetEdges();
    if (lhs_edges.size() != rhs_edges.size()) return false;
    const int n_edges = static_cast<int>(lhs_edges.size());
    for (int i=0; i!=n_edges; ++i)
    {
      if (lhs_edges[i] != rhs_edges[i]) return false;
    }
  }
  return true;

}



bool operator==(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  assert(lhs); assert(rhs);
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) == boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) == boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) == boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) != boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) != boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs)
{
  return boost::shared_ptr<const pvdb::ConceptMap>(lhs) != boost::shared_ptr<const pvdb::ConceptMap>(rhs);
}

} //~namespace pvdb
