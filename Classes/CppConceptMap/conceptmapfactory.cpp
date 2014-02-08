#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapfactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

//#include "fileio.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapcenternode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmap.h"
#include "conceptmaphelper.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::ConceptMapFactory::Create(
  const std::vector<boost::shared_ptr<ribi::cmap::Node> >& nodes,
  const std::vector<boost::shared_ptr<ribi::cmap::Edge> >& edges)
{
  boost::shared_ptr<ribi::cmap::ConceptMap> p(new ConceptMap(nodes,edges));
  assert(p);
  assert(p->IsValid());
  return p;
}


const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::ConceptMapFactory::Create(
  const std::string& focal_question)
{
  //A single-node ConceptMap contains only the focal question
  const boost::shared_ptr<CenterNode> focal_node {
    CenterNodeFactory().Create(focal_question)
  };
  assert(focal_node);
  const std::vector<boost::shared_ptr<Node> > nodes = { focal_node };
  assert(nodes.at(0));
  const boost::shared_ptr<ConceptMap> p = Create(nodes);
  assert(p);
  assert(p->IsValid());
  assert(!p->GetNodes().empty());
  assert(p->FindCenterNode() && "A ConceptMap must have a CenterNode");

  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::ConceptMapFactory::DeepCopy(
  const boost::shared_ptr<const ribi::cmap::ConceptMap> map)
{
  if (!map) return boost::shared_ptr<ribi::cmap::ConceptMap>();
  assert(map->IsValid() && "Must be a valid original");

  //Deep-copy the center node if present
  //Deep-copy the non-center nodes
  const std::vector<boost::shared_ptr<const cmap::Node> > nodes = map->GetNodes();
  std::vector<boost::shared_ptr<ribi::cmap::Node> > new_nodes;
  for (const boost::shared_ptr<const cmap::Node> node: nodes)
  {
    assert(node);
    boost::shared_ptr<Node> new_node;
    if (const boost::shared_ptr<const cmap::CenterNode> center_node
     = boost::dynamic_pointer_cast<const cmap::CenterNode>(node))
    {
      assert(center_node);
      new_node = CenterNodeFactory().DeepCopy(center_node);
    }
    else
    {
      new_node = cmap::NodeFactory::DeepCopy(node);
    }
    assert(new_node);
    assert(operator==(*new_node,*node));
    new_nodes.push_back(new_node);
  }


  //Deep-copy the edges
  const std::vector<boost::shared_ptr<const cmap::Edge> > edges = map->GetEdges();
  std::vector<boost::shared_ptr<ribi::cmap::Edge> > new_edges;
  for (const boost::shared_ptr<const cmap::Edge> edge: edges)
  {
    assert(edge);
    //Find the new from node
    const auto from_iter = std::find(nodes.begin(),nodes.end(),edge->GetFrom());
    assert(from_iter != nodes.end());
    const int from_index = std::distance(nodes.begin(),from_iter);
    assert(from_index < boost::numeric_cast<int>(new_nodes.size()));
    const boost::shared_ptr<ribi::cmap::Node> from = new_nodes[from_index];

    //Find the new to node
    const auto to_iter = std::find(nodes.begin(),nodes.end(),edge->GetTo());
    assert(to_iter != nodes.end());
    const int to_index = std::distance(nodes.begin(),to_iter);
    assert(to_index < boost::numeric_cast<int>(new_nodes.size()));
    const boost::shared_ptr<ribi::cmap::Node> to = new_nodes[to_index];

    assert(from_index != to_index);
    assert(from);
    assert(to);
    assert(from != to);
    const boost::shared_ptr<ribi::cmap::Edge> new_edge = cmap::EdgeFactory::DeepCopy(edge,from,to);
    assert(new_edge);
    assert(operator==(*new_edge,*edge));
    new_edges.push_back(new_edge);
  }

  const boost::shared_ptr<ribi::cmap::ConceptMap> p = Create(new_nodes,new_edges);
  assert(p);
  assert(*p == *map && "Must be a copy");
  assert( p !=  map && "Must be a deep copy");
  assert(p->IsValid() && "Must be a valid copy");
  return p;
}
#endif

///TODO: let CenterNodes manage their own <center_node> tags
const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::ConceptMapFactory::FromXml(const std::string &s)
{
  assert(s.size() >= 27);
  assert(s.substr(0,13) == std::string("<concept_map>"));
  assert(s.substr(s.size() - 14,14) == std::string("</concept_map>"));


  //Obtain the <concept_map> ... </concept_map> string
  const std::vector<std::string> v
    = GetRegexMatches(s,QRegExp("(<concept_map>.*</concept_map>)"));
  assert(v.size() == 1);
  //Strip the <concept_map> tags
  const std::string concept_map_str = ribi::xml::StripXmlTag(v[0]);

  std::vector<boost::shared_ptr<Node> > nodes;
  {
    //Obtain the <nodes> ... </nodes> strings
    const std::vector<std::string> w
      = GetRegexMatches(concept_map_str,QRegExp("(<nodes>.*</nodes>)"));
    assert(w.size() == 1);
    //Strip the <nodes> tags
    const std::string nodes_str = ribi::xml::StripXmlTag(w[0]);
    //CenterNode
    {
      const std::vector<std::string> x
        = GetRegexMatches(nodes_str,QRegExp("(<center_node>.*</center_node>)"));
      assert(x.empty() || x.size() == 1);
      std::for_each(x.begin(),x.end(),
        [&nodes](const std::string& s)
        {
          nodes.push_back(CenterNodeFactory().FromXml(s) );
        }
      );
    }
    //Regular nodes
    {
      const std::vector<std::string> x
        = GetRegexMatches(nodes_str,QRegExp("(<node>.*</node>)"));
      std::for_each(x.begin(),x.end(),
        [&nodes](const std::string& s)
        {
          const boost::shared_ptr<Node> node {
            NodeFactory::FromXml(s)
          };
          assert(node);
          nodes.push_back(node);
        }
      );
    }
    //Replace the first node by its CenterNode equivalent
    if (!nodes.empty() && !IsCenterNode(nodes[0]))
    {
      const boost::shared_ptr<Node> old_node = nodes[0];
      const boost::shared_ptr<Concept> concept = old_node->GetConcept();
      const double x = old_node->GetX();
      const double y = old_node->GetY();
      const boost::shared_ptr<cmap::CenterNode> center_node(
        new cmap::CenterNode(concept,x,y));
      nodes[0] = center_node;
      assert(*old_node == *center_node);
    }
    assert(nodes.empty() || IsCenterNode(nodes[0]));
  }
  std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges;
  {
    //Obtain the <edges> ... </edges> strings
    const std::vector<std::string> w
      = GetRegexMatches(concept_map_str,QRegExp("(<edges>.*</edges>)"));
    assert(w.size() == 1);
    //Strip the <edges> tags
    const std::string nodes_str = ribi::xml::StripXmlTag(w[0]);
    //Obtain the <edge> ... </edge> strings
    const std::vector<std::string> x
      = GetRegexMatches(nodes_str,QRegExp("(<edge>.*</edge>)"));
    for (const std::string& s: x)
    {
      const boost::shared_ptr<Edge> edge = EdgeFactory::FromXml(s,nodes);
      assert(edge);
      edges.push_back(edge);
    }
  }

  const boost::shared_ptr<ConceptMap> concept_map(new ConceptMap(nodes,edges));
  assert(concept_map);
  assert(concept_map->IsValid());
  return concept_map;
}

const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > ribi::cmap::ConceptMapFactory::GetAllTests()
{
  std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v;
  {
    {
      const auto w = ribi::cmap::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    {
      const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > w = ribi::cmap::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    {
      const auto w = ribi::cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
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
    boost::shared_ptr<ribi::cmap::ConceptMap> p;
    assert(!p);
    v.push_back(p);
  }

  return v;
}

const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > ribi::cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v(20);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<ribi::cmap::ConceptMap>& p) { return p; } ) == 0);
  //[0]: as-empty-as-can-get concept map (X = focal question_
  {
    const Nodes nodes
      =
      {
        //CenterNodeFactory().Create("X"),
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[0]=concept_map;
  }
  //[1]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[1]=concept_map;
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        NodeFactory::Create("A"),
        NodeFactory::Create("B")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[2]=concept_map;
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("edge_a concept"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[3]=concept_map;
  }
  //[4]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("edge_a concept"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[4]=concept_map;
  }
  //[5]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("1"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[5]=concept_map;
  }
  //[6]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("1"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[6]=concept_map;
  }
  //[7]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);

    assert(concept_map);
    v[7]=concept_map;
  }
  //[8]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create());
    const boost::shared_ptr<Edge> edge_a(cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true));


    const Edges edges
      =
      {
        edge_a
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[8]=concept_map;
  }
  //[9]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create());
    const boost::shared_ptr<Edge> edge_a(cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(3),true));

    const Edges edges
      =
      {
        edge_a
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[9]=concept_map;
  }
  //[10]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create());
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create());

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(3),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[10]=concept_map;
  }
  //[11]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(nodes,edges);
    assert(concept_map);
    v[11]=concept_map;
  }

  //[12]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[12]=concept_map;
  }
  //[13]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("3"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("2"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[13]=concept_map;
  }

  //[14]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("3"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("2"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[14]=concept_map;
  }
  //[15]
  {
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("B", { {"B-1",cmap::Competency::uninitialized} },0,1,2));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("C", { {"C-1",cmap::Competency::uninitialized},{"C-2",cmap::Competency::misc}},-1,1,2));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("D", { {"D-1",cmap::Competency::misc},{"D-2",cmap::Competency::misc},{"D-3",cmap::Competency::misc}},-1,-1,-1));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));
    const boost::shared_ptr<Node> node_e(cmap::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_h(ConceptFactory().Create("2",{{"2-I",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3",{{"3-I",cmap::Competency::misc},{"3-II",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_i(ConceptFactory().Create("4",{{"4-I",cmap::Competency::misc},{"4-II",cmap::Competency::misc},{"4-III",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_j(ConceptFactory().Create("5",{{"5-I",cmap::Competency::misc},{"5-II",cmap::Competency::misc},{"5-III",cmap::Competency::misc},{"5-IV",cmap::Competency::misc} } ));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        cmap::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(15)=concept_map;
  }
  //[16]: complex rated concept map
  {
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("B", { {"B-1: profession",cmap::Competency::profession} },0,1,2));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("C", { {"C-1: organisations",cmap::Competency::organisations},{"C-2: social_surroundings",cmap::Competency::social_surroundings}},2,1,0));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("D", { {"D-1: target_audience",cmap::Competency::target_audience},{"D-2: ti_knowledge",cmap::Competency::ti_knowledge},{"D-3: prof_growth",cmap::Competency::prof_growth},{"D-4: misc",cmap::Competency::misc}},0,1,2));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));
    const boost::shared_ptr<Node> node_e(cmap::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_h(ConceptFactory().Create("2",{{"2-I",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3",{{"3-I",cmap::Competency::misc},{"3-II",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_i(ConceptFactory().Create("4",{{"4-I",cmap::Competency::misc},{"4-II",cmap::Competency::misc},{"4-III",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_j(ConceptFactory().Create("5",{{"5-I",cmap::Competency::misc},{"5-II",cmap::Competency::misc},{"5-III",cmap::Competency::misc},{"5-IV",cmap::Competency::misc} } ));


    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        cmap::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(16)=concept_map;
  }

  //[17]: complex rated concept map with many examples
  {
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("B",
      {
        {"B-P",cmap::Competency::profession},
        {"B-O",cmap::Competency::organisations},
        {"B-S",cmap::Competency::social_surroundings},
        {"B-TA",cmap::Competency::target_audience},
        {"B-TK",cmap::Competency::ti_knowledge},
        {"B-PG",cmap::Competency::prof_growth},
        {"B-M",cmap::Competency::misc}
      },
      0,1,2));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("C",
      { {"C-1: organisations",cmap::Competency::organisations},{"C-2: social_surroundings",cmap::Competency::social_surroundings}},
      2,1,0));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("D",
      { {"D-1: target_audience",cmap::Competency::target_audience},{"D-2: ti_knowledge",cmap::Competency::ti_knowledge},{"D-3: prof_growth",cmap::Competency::prof_growth},{"D-4: misc",cmap::Competency::misc}},
      0,1,2));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));
    const boost::shared_ptr<Node> node_e(cmap::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1",
      {{"2-I",cmap::Competency::misc}}
      ));
    const boost::shared_ptr<Concept> concept_h(ConceptFactory().Create("2",
      {{"2-I",cmap::Competency::misc} }
      ));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3",
      {{"3-I",cmap::Competency::misc},{"3-II",cmap::Competency::misc} }
      ));
    const boost::shared_ptr<Concept> concept_i(ConceptFactory().Create("4",
      {{"4-I",cmap::Competency::misc},{"4-II",cmap::Competency::misc},{"4-III",cmap::Competency::misc} }
      ));
    const boost::shared_ptr<Concept> concept_j(ConceptFactory().Create("5",
      {{"5-I",cmap::Competency::misc},{"5-II",cmap::Competency::misc},{"5-III",cmap::Competency::misc},{"5-IV",cmap::Competency::misc} }
      ));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        cmap::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(17)=concept_map;
  }
  //[18]: complex rated concept map with many long concept names and examples
  {
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create(
      "B: This is a concept that has all types of competencies as its examples, each example name being multiple lines as well",
      {
        {"B-P: this is B its first example (out of seven) and it is categorized as a competency in the profession domain",cmap::Competency::profession},
        {"B-O: this is B its second example (out of seven) and it is categorized as a competency in the organisation domain",cmap::Competency::organisations},
        {"B-S: this is B its third example (out of seven) and it is categorized as a competency in the social surroundings domain",cmap::Competency::social_surroundings},
        {"B-TA: this is B its fourth example (out of seven) and it is categorized as a competency in the target audience domain",cmap::Competency::target_audience},
        {"B-TK: this is B its fifth example (out of seven) and it is categorized as a competency in the technical instrumental knowledge domain",cmap::Competency::ti_knowledge},
        {"B-PG: this is B its sixth example (out of seven) and it is categorized as a competency in the professional growth domain",cmap::Competency::prof_growth},
        {"B-M: this is B its seventh example (out of seven) and it is categorized as a competency in the misc domain",cmap::Competency::misc}
      },
      0,1,2));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create(
      "C: This is a concept that has only two of the seven types of competencies as its examples, each example name being multiple lines as well",
      {
        {"C-O: this is C its first example (out of two) and it is categorized as a competency in the organisation domain",cmap::Competency::organisations},
        {"C-S: this is C its second example (out of two) and it is categorized as a competency in the social surroundings domain",cmap::Competency::social_surroundings}
      },
      2,1,0));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create(
      "D: This is a concept that has only four of the seven types of competencies as its examples, each example name being multiple lines as well",
      {
        {"D-TA: this is D its first example (out of four) and it is categorized as a competency in the target audience domain",cmap::Competency::target_audience},
        {"D-TK: this is D its second example (out of four) and it is categorized as a competency in the technical instrumental knowledge domain",cmap::Competency::ti_knowledge},
        {"D-PG: this is D its third example (out of four) and it is categorized as a competency in the professional growth domain",cmap::Competency::prof_growth},
        {"D-M: this is D its fourth example (out of four) and it is categorized as a competency in the misc domain",cmap::Competency::misc}
      },
      0,1,2));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));
    const boost::shared_ptr<Node> node_e(cmap::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X: This is the center node concept that can have no examples, oterwise each of its example name would be multiple lines"),
        cmap::NodeFactory::Create("A: This is a concept that has none of all types of competencies as its examples, oterwise each of its example name would be multiple lines"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<Concept> concept_f(
      ConceptFactory().Create(
        "1: the first description of a relation that has one example. This description spans multiple lines as it is longer than eighty characters",
        {
          //{"2-I: this misc example ",cmap::Competency::misc}
        }
      )
    );
    const boost::shared_ptr<Concept> concept_h(
      ConceptFactory().Create(
        "2: the second description of a relation that has one example. This description spans multiple lines as it is longer than eighty characters",
        {
          {"2-I: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc}
        }
      )
    );
    const boost::shared_ptr<Concept> concept_g(
      ConceptFactory().Create(
        "3: the third description of a relation that has one example. This description spans multiple lines as it is longer than eighty characters",
        {
          {"3-I: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"3-II: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc}
        }
      )
    );
    const boost::shared_ptr<Concept> concept_i(
      ConceptFactory().Create(
        "4: the fourth description of a relation that has one example. This description spans multiple lines as it is longer than eighty characters",
        {
          {"4-I: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"4-II: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"4-III: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc}
        }
      )
    );
    const boost::shared_ptr<Concept> concept_j(
      ConceptFactory().Create(
        "5: the fifth description of a relation that has one example. This description spans multiple lines as it is longer than eighty characters",
        {
          {"5-I: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"5-II: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"5-III: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc},
          {"5-IV: an example of a description of a relation. This example spans multiple lines as it is longer than eighty characters",cmap::Competency::misc}
        }
      )
    );

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true),
        cmap::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(18)=concept_map;
  }


  //[19]: complex rated concept map with all nodes connected
  {
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("B", { {"B-1: profession",cmap::Competency::profession} },0,1,2));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("C", { {"C-1: organisations",cmap::Competency::organisations},{"C-2: social_surroundings",cmap::Competency::social_surroundings}},2,1,0));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("D", { {"D-1: target_audience",cmap::Competency::target_audience},{"D-2: ti_knowledge",cmap::Competency::ti_knowledge},{"D-3: prof_growth",cmap::Competency::prof_growth},{"D-4: misc",cmap::Competency::misc}},0,1,2));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));
    const boost::shared_ptr<Node> node_e(cmap::NodeFactory::Create(concept_e));

    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        node_c,
        node_d,
        node_e
      };

    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_h(ConceptFactory().Create("2",{{"2-I",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3",{{"3-I",cmap::Competency::misc},{"3-II",cmap::Competency::misc} } ));
    const boost::shared_ptr<Concept> concept_i(ConceptFactory().Create("4",{{"4-I",cmap::Competency::misc},{"4-II",cmap::Competency::misc},{"4-III",cmap::Competency::misc} } ));

    ///Concepts connected to the center should never be visible
    const boost::shared_ptr<Concept> concept_j(ConceptFactory().Create("..."));
    const boost::shared_ptr<Concept> concept_k(ConceptFactory().Create("..."));
    const boost::shared_ptr<Concept> concept_l(ConceptFactory().Create("..."));
    const boost::shared_ptr<Concept> concept_m(ConceptFactory().Create("..."));
    const boost::shared_ptr<Concept> concept_n(ConceptFactory().Create("..."));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_f,1.2,3.4,nodes.at(2),false,nodes.at(1),true ),
        cmap::EdgeFactory::Create(concept_g,2.3,4.5,nodes.at(3),false,nodes.at(2),true ),
        cmap::EdgeFactory::Create(concept_h,3.4,5.6,nodes.at(4),false,nodes.at(3),true ),
        cmap::EdgeFactory::Create(concept_i,4.5,6.7,nodes.at(1),false,nodes.at(4),true ),
        cmap::EdgeFactory::Create(concept_j,5.6,7.8,nodes.at(0),false,nodes.at(1),true ),
        cmap::EdgeFactory::Create(concept_k,6.7,8.9,nodes.at(0),false,nodes.at(2),false),
        cmap::EdgeFactory::Create(concept_l,7.8,9.0,nodes.at(0),false,nodes.at(3),true ),
        cmap::EdgeFactory::Create(concept_m,8.9,0.1,nodes.at(0),true ,nodes.at(4),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.at(19)=concept_map;
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

const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > ribi::cmap::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v;
  //[0] (note: same as heteromorphous[11])
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C"),
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[1]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),false,nodes.at(1),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),false,nodes.at(2),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),false,nodes.at(3),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[4]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),false,nodes.at(3),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(2),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[5]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),false,nodes.at(2),true),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),false,nodes.at(1),true),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),false,nodes.at(3),true)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[6] (note: same as heteromorphous[11], yet arrows reversed
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),true,nodes.at(1),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),true,nodes.at(2),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),true,nodes.at(3),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[7]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),true,nodes.at(1),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),true,nodes.at(3),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(1),true,nodes.at(2),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[8]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C")
      };
    const boost::shared_ptr<Concept> concept_a(ConceptFactory().Create("X"));
    const boost::shared_ptr<Concept> concept_b(ConceptFactory().Create("B"));
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("A"));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("C"));
    const boost::shared_ptr<Node> node_a(cmap::NodeFactory::Create(concept_a));
    const boost::shared_ptr<Node> node_b(cmap::NodeFactory::Create(concept_b));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),true,nodes.at(2),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(3),true,nodes.at(1),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),true,nodes.at(3),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[9]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A")
      };
    const boost::shared_ptr<Concept> concept_a(ConceptFactory().Create("X"));
    const boost::shared_ptr<Concept> concept_b(ConceptFactory().Create("B"));
    const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("C"));
    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("A"));
    const boost::shared_ptr<Node> node_a(cmap::NodeFactory::Create(concept_a));
    const boost::shared_ptr<Node> node_b(cmap::NodeFactory::Create(concept_b));
    const boost::shared_ptr<Node> node_c(cmap::NodeFactory::Create(concept_c));
    const boost::shared_ptr<Node> node_d(cmap::NodeFactory::Create(concept_d));

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(1),true,nodes.at(3),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(2),true,nodes.at(1),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),true,nodes.at(2),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[10]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(3),true,nodes.at(2),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),true,nodes.at(3),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(2),true,nodes.at(1),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[11]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A")
      };

    const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("1"));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("2"));
    const boost::shared_ptr<Concept> concept_g(ConceptFactory().Create("3"));

    const Edges edges
      =
      {
        cmap::EdgeFactory::Create(concept_e,1.2,3.4,nodes.at(2),true,nodes.at(3),false),
        cmap::EdgeFactory::Create(concept_f,2.3,4.5,nodes.at(1),true,nodes.at(2),false),
        cmap::EdgeFactory::Create(concept_g,3.4,5.6,nodes.at(3),true,nodes.at(1),false)
      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
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

const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > ribi::cmap::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps()
{
  typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v(6);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<ribi::cmap::ConceptMap>& p) { return p; } ) == 0);
  //[0]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C")
      };
    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[0] = concept_map;
  }

  //[1]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B")
      };
    const Edges edges
      =
      {

      };
    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[1] = concept_map;
  }
  //[2]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("C")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[2] = concept_map;
  }
  //[3]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };
    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[3] = concept_map;
  }

  //[4]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("A"),
        cmap::NodeFactory::Create("B")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    v[4] = concept_map;
  }

  //[5]
  {
    const Nodes nodes
      =
      {
        CenterNodeFactory().Create("X"),
        cmap::NodeFactory::Create("C"),
        cmap::NodeFactory::Create("B"),
        cmap::NodeFactory::Create("A")
      };

    const Edges edges
      =
      {

      };

    const boost::shared_ptr<ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(nodes,edges));
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

