#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconceptmapfactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include "pvdbcenternodefactory.h"
#include "pvdbcenternode.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbhelper.h"
#include "pvdbexamplefactory.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::Create(
  const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
  const std::vector<boost::shared_ptr<pvdb::Edge> >& edges)
{
  boost::shared_ptr<pvdb::ConceptMap> p(new ConceptMap(nodes,edges));
  assert(p);
  assert(p->IsValid());
  return p;
}

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::CreateFromCluster(
  const std::string& question,
  const boost::shared_ptr<pvdb::Cluster>& cluster)
{
  boost::shared_ptr<pvdb::ConceptMap> p(new ConceptMap(question,cluster));
  assert(p);
  assert(p->IsValid());
  return p;
}


const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::Create(
  const std::string& focal_question)
{
  //A single-node ConceptMap contains only the focal question
  const boost::shared_ptr<pvdb::Node> focal_node = pvdb::NodeFactory::Create(focal_question);
  assert(focal_node);
  const std::vector<boost::shared_ptr<pvdb::Node> > nodes = { focal_node };
  assert(nodes.at(0));
  const boost::shared_ptr<pvdb::ConceptMap> p = Create(nodes);
  assert(p);
  assert(p->IsValid());
  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::ConceptMap> map)
{
  if (!map) return boost::shared_ptr<pvdb::ConceptMap>();
  assert(map->IsValid() && "Must be a valid original");

  //Deep-copy the nodes
  const std::vector<boost::shared_ptr<const pvdb::Node> > nodes = map->GetNodes();
  std::vector<boost::shared_ptr<pvdb::Node> > new_nodes;
  for (const boost::shared_ptr<const pvdb::Node> node: nodes)
  {
    assert(node);
    const boost::shared_ptr<pvdb::Node> new_node = pvdb::NodeFactory::DeepCopy(node);
    assert(new_node);
    assert(IsEqual(*new_node,*node));
    new_nodes.push_back(new_node);
  }

  //Deep-copy the edges
  const std::vector<boost::shared_ptr<const pvdb::Edge> > edges = map->GetEdges();
  std::vector<boost::shared_ptr<pvdb::Edge> > new_edges;
  for (const boost::shared_ptr<const pvdb::Edge> edge: edges)
  {
    assert(edge);
    //Find the new from node
    const auto from_iter = std::find(nodes.begin(),nodes.end(),edge->GetFrom());
    assert(from_iter != nodes.end());
    const int from_index = std::distance(nodes.begin(),from_iter);
    assert(from_index < boost::numeric_cast<int>(new_nodes.size()));
    const boost::shared_ptr<pvdb::Node> from = new_nodes[from_index];

    //Find the new to node
    const auto to_iter = std::find(nodes.begin(),nodes.end(),edge->GetTo());
    assert(to_iter != nodes.end());
    const int to_index = std::distance(nodes.begin(),to_iter);
    assert(to_index < boost::numeric_cast<int>(new_nodes.size()));
    const boost::shared_ptr<pvdb::Node> to = new_nodes[to_index];

    assert(from_index != to_index);
    assert(from);
    assert(to);
    assert(from != to);
    const boost::shared_ptr<pvdb::Edge> new_edge = pvdb::EdgeFactory::DeepCopy(edge,from,to);
    assert(new_edge);
    assert(IsEqual(*new_edge,*edge));
    new_edges.push_back(new_edge);
  }

  const boost::shared_ptr<pvdb::ConceptMap> p = Create(new_nodes,new_edges);
  assert(p);
  assert(p!=map && "Must be a DEEP copy");
  assert(IsEqual(*p,*map) && "Must be a deep COPY");
  assert(p->IsValid() && "Must be a valid copy");
  return p;
}
#endif

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::FromXml(const std::string &s)
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
    for (const std::string& s: x)
    {
      const boost::shared_ptr<pvdb::Edge> edge = EdgeFactory::FromXml(s,nodes);
      assert(edge);
      edges.push_back(edge);
    }
  }

  const boost::shared_ptr<pvdb::ConceptMap> concept_map(new ConceptMap(nodes,edges));
  assert(concept_map);
  assert(concept_map->IsValid());
  return concept_map;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetAllTests()
{
  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v;
  {
    {
      const auto w = pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    {
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > w = pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    {
      const auto w = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }
  #ifndef NDEBUG
  for (const auto concept_map: v)
  {
    assert(concept_map);
    assert(concept_map->IsValid());
    for (const auto node: concept_map->GetNodes())
    {
      assert(node);
    }
    for (const auto edge: concept_map->GetEdges())
    {
      assert(edge);
      assert(edge->GetTo());
      assert(edge->GetFrom());
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetTo()) == 1);
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetFrom()) == 1);
    }
  }
  #endif
  //Add empty concept map
  {
    boost::shared_ptr<pvdb::ConceptMap> p;
    assert(!p);
    v.push_back(p);
  }

  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<pvdb::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<pvdb::Node> > Nodes;

  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v(18);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == 0);
  //[0]: as-empty-as-can-get concept map (X = focal question_
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[0]=concept_map;
  }
  //[1]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[1]=concept_map;
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[2]=concept_map;
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("edge_a concept"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[3]=concept_map;
  }
  //[4]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("edge_a concept"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[4]=concept_map;
  }
  //[5]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("1"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[5]=concept_map;
  }
  //[6]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("1"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[6]=concept_map;
  }
  //[7]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[7]=concept_map;
  }
  //[8]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true));


    const Edges edges
      =
      {
        edge_a
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[8]=concept_map;
  }
  //[9]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(3),true));

    const Edges edges
      =
      {
        edge_a
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[9]=concept_map;
  }
  //[10]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create());

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(3),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[10]=concept_map;
  }
  //[11]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[11]=concept_map;
  }

  //[12]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[12]=concept_map;
  }
  //[13]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("2"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[13]=concept_map;
  }

  //[14]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("2"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[14]=concept_map;
  }
  //[15]
  {
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("B", { {"B-1",pvdb::Competency::uninitialized} },0,1,2));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("C", { {"C-1",pvdb::Competency::uninitialized},{"C-2",pvdb::Competency::misc}},-1,1,2));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("D", { {"D-1",pvdb::Competency::misc},{"D-2",pvdb::Competency::misc},{"D-3",pvdb::Competency::misc}},-1,-1,-1));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));
    const boost::shared_ptr<pvdb::Node> node_e(pvdb::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_h(pvdb::ConceptFactory::Create("2",{{"2-I",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3",{{"3-I",pvdb::Competency::misc},{"3-II",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_i(pvdb::ConceptFactory::Create("4",{{"4-I",pvdb::Competency::misc},{"4-II",pvdb::Competency::misc},{"4-III",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_j(pvdb::ConceptFactory::Create("5",{{"5-I",pvdb::Competency::misc},{"5-II",pvdb::Competency::misc},{"5-III",pvdb::Competency::misc},{"5-IV",pvdb::Competency::misc} } ));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        pvdb::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(15)=concept_map;
  }
  //[16]: complex rated concept map
  {
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("B", { {"B-1: profession",pvdb::Competency::profession} },0,1,2));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("C", { {"C-1: organisations",pvdb::Competency::organisations},{"C-2: social_surroundings",pvdb::Competency::social_surroundings}},2,1,0));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("D", { {"D-1: target_audience",pvdb::Competency::target_audience},{"D-2: ti_knowledge",pvdb::Competency::ti_knowledge},{"D-3: prof_growth",pvdb::Competency::prof_growth},{"D-4: misc",pvdb::Competency::misc}},0,1,2));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));
    const boost::shared_ptr<pvdb::Node> node_e(pvdb::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_h(pvdb::ConceptFactory::Create("2",{{"2-I",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3",{{"3-I",pvdb::Competency::misc},{"3-II",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_i(pvdb::ConceptFactory::Create("4",{{"4-I",pvdb::Competency::misc},{"4-II",pvdb::Competency::misc},{"4-III",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_j(pvdb::ConceptFactory::Create("5",{{"5-I",pvdb::Competency::misc},{"5-II",pvdb::Competency::misc},{"5-III",pvdb::Competency::misc},{"5-IV",pvdb::Competency::misc} } ));


    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        pvdb::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(16)=concept_map;
  }

  //[17]: complex rated concept map with many examples
  {
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("B",
      {
        {"B-P",pvdb::Competency::profession},
        {"B-O",pvdb::Competency::organisations},
        {"B-S",pvdb::Competency::social_surroundings},
        {"B-TA",pvdb::Competency::target_audience},
        {"B-TK",pvdb::Competency::ti_knowledge},
        {"B-PG",pvdb::Competency::prof_growth},
        {"B-M",pvdb::Competency::misc}
      },
      0,1,2));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("C",
      { {"C-1: organisations",pvdb::Competency::organisations},{"C-2: social_surroundings",pvdb::Competency::social_surroundings}},
      2,1,0));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("D",
      { {"D-1: target_audience",pvdb::Competency::target_audience},{"D-2: ti_knowledge",pvdb::Competency::ti_knowledge},{"D-3: prof_growth",pvdb::Competency::prof_growth},{"D-4: misc",pvdb::Competency::misc}},
      0,1,2));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));
    const boost::shared_ptr<pvdb::Node> node_e(pvdb::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1",
      {{"2-I",pvdb::Competency::misc}}
      ));
    const boost::shared_ptr<pvdb::Concept> concept_h(pvdb::ConceptFactory::Create("2",
      {{"2-I",pvdb::Competency::misc} }
      ));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3",
      {{"3-I",pvdb::Competency::misc},{"3-II",pvdb::Competency::misc} }
      ));
    const boost::shared_ptr<pvdb::Concept> concept_i(pvdb::ConceptFactory::Create("4",
      {{"4-I",pvdb::Competency::misc},{"4-II",pvdb::Competency::misc},{"4-III",pvdb::Competency::misc} }
      ));
    const boost::shared_ptr<pvdb::Concept> concept_j(pvdb::ConceptFactory::Create("5",
      {{"5-I",pvdb::Competency::misc},{"5-II",pvdb::Competency::misc},{"5-III",pvdb::Competency::misc},{"5-IV",pvdb::Competency::misc} }
      ));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        pvdb::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(17)=concept_map;
  }

  #ifndef NDEBUG
  for (const auto concept_map: v)
  {
    assert(concept_map);
    for (const auto node: concept_map->GetNodes())
    {
      assert(node);
    }
    for (const auto edge: concept_map->GetEdges())
    {
      assert(edge);
      assert(edge->GetTo());
      assert(edge->GetFrom());
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetTo()) == 1);
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetFrom()) == 1);
    }
  }
  #endif
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<pvdb::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<pvdb::Node> > Nodes;

  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v;
  //[0] (note: same as heteromorphous[11])
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C"),
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[1]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(2),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),false,nodes.at(3),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[4]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(3),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[5]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),false,nodes.at(2),true),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(1),true),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[6] (note: same as heteromorphous[11], yet arrows reversed
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),true,nodes.at(1),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),true,nodes.at(2),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),true,nodes.at(3),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[7]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),true,nodes.at(1),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),true,nodes.at(3),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),true,nodes.at(2),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[8]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C")
      };
    const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("X"));
    const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("B"));
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("A"));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("C"));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),true,nodes.at(2),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),true,nodes.at(1),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),true,nodes.at(3),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[9]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A")
      };
    const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("X"));
    const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("B"));
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("C"));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("A"));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),true,nodes.at(3),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),true,nodes.at(1),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),true,nodes.at(2),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[10]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),true,nodes.at(2),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),true,nodes.at(3),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),true,nodes.at(1),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[11]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A")
      };

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));

    const Edges edges
      =
      {
        pvdb::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),true,nodes.at(3),false),
        pvdb::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),true,nodes.at(2),false),
        pvdb::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),true,nodes.at(1),false)
      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  assert(v.size() == 12);
  #ifndef NDEBUG
  for (const auto concept_map: v)
  {
    assert(concept_map);
    for (const auto node: concept_map->GetNodes())
    {
      assert(node);
    }
    for (const auto edge: concept_map->GetEdges())
    {
      assert(edge);
      assert(edge->GetTo());
      assert(edge->GetFrom());
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetTo()) == 1);
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetFrom()) == 1);
    }
  }
  #endif
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<pvdb::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<pvdb::Node> > Nodes;

  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v(6);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == 0);
  //[0]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C")
      };
    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[0] = concept_map;
  }

  //[1]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B")
      };
    const Edges edges
      =
      {

      };
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[1] = concept_map;
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("C")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[2] = concept_map;
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[3] = concept_map;
  }

  //[4]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("A"),
        pvdb::NodeFactory::Create("B")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[4] = concept_map;
  }

  //[5]
  {
    const Nodes nodes
      =
      {
        pvdb::CenterNodeFactory::Create("X"),
        pvdb::NodeFactory::Create("C"),
        pvdb::NodeFactory::Create("B"),
        pvdb::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[5] = concept_map;
  }

  #ifndef NDEBUG
  for (const auto concept_map: v)
  {
    assert(concept_map);
    for (const auto node: concept_map->GetNodes())
    {
      assert(node);
    }
    for (const auto edge: concept_map->GetEdges())
    {
      assert(edge);
      assert(edge->GetTo());
      assert(edge->GetFrom());
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetTo()) == 1);
      assert(std::count(
        concept_map->GetNodes().begin(),
        concept_map->GetNodes().end(),
        edge->GetFrom()) == 1);
    }
  }
  #endif
  return v;
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif

