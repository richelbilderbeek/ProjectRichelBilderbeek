//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"

#include <sstream>
#include <set>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QRegExp>

#include "conceptmapcenternode.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapcompetency.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::ConceptMap::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::ConceptMap::Test");
  const bool trace_verbose = false;
  typedef std::vector<boost::shared_ptr<Node> > Nodes;

  if (trace_verbose) { TRACE("operator==, DeepCopy"); }
  {
    const std::vector<boost::shared_ptr<const ConceptMap>> v = AddConst(ConceptMapFactory::GetAllTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const ConceptMap> m)
      {
        if (m)
        {
          //Test copy constructor
          const boost::shared_ptr<ConceptMap> c(ConceptMapFactory::DeepCopy(m));
          assert(*c == *m);
          //Test XML conversions
          const std::string s = ToXml(c);
          const boost::shared_ptr<ConceptMap> d = ConceptMapFactory::FromXml(s);
          assert(*c == *d);
        }
      }
    );
  }
  if (trace_verbose) { TRACE("CanConstruct"); }
  {
    assert(CanConstruct( {}, {} ) && "Assume empty concept map can be constructed");
  }
  {
    const boost::shared_ptr<Concept> concept(ConceptFactory().Create("FOCAL QUESTION"));
    const boost::shared_ptr<Node> node = NodeFactory().Create(concept,123,234);
    assert(CanConstruct( { node }, {} ) && "Assume focal question without examples can be constructed");
  }
  {
    const boost::shared_ptr<Concept> concept(ConceptFactory().Create("FOCAL QUESTION", { {"No",Competency::misc},{"examples",Competency::misc},{"allowed",Competency::misc} } ));
    const boost::shared_ptr<Node> node = NodeFactory().Create(concept,123,234);
    assert(CanConstruct( { node }, {} )
      && "Assume focal question with examples can be constructed"
      && "for example, when creating a sub-concept map");
  }
  if (trace_verbose) { TRACE("HasSameContent"); }
  {
    if (trace_verbose) { TRACE("HasSameContent 1"); }
    {
      assert(NodeFactory().GetTests().size() >= 3);
      const boost::shared_ptr<CenterNode> node_a(CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"));
      assert(node_a);
      const boost::shared_ptr<Node> node_b(NodeFactory().GetTests().at(1));
      assert(node_b);
      const boost::shared_ptr<Node> node_c(NodeFactory().GetTests().at(2));
      assert(node_c);
      const boost::shared_ptr<ConceptMap> map_a(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().GetTests().at(2)
          }
        )
      );
      assert(map_a);
      assert(map_a->GetNodes().size() == 3);
      const boost::shared_ptr<ConceptMap> map_b(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().GetTests().at(2)
          }
        )
      );
      assert(map_b);
      assert(map_b->GetNodes().size() == 3);
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ConceptMap> map_c(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().GetTests().at(2),
            NodeFactory().GetTests().at(2)
          }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));

    }
    if (trace_verbose) { TRACE("HasSameContent 2"); }
    {
      const boost::shared_ptr<Concept> concept_b(ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } ));
      const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } ));
      const boost::shared_ptr<Node> node_b(NodeFactory().Create(concept_b,321,432));
      const boost::shared_ptr<ConceptMap> map_a(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().CreateFromStrings("4", { {"5",Competency::misc},{"6",Competency::misc} },345,456)
          }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().CreateFromStrings("4", { {"5",Competency::misc},{"6",Competency::misc} },901,012)
          }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<Node> node_g = NodeFactory().Create(concept_f,901,012);
      const boost::shared_ptr<ConceptMap> map_c(
        ConceptMapFactory::Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"), node_b, node_g
          }
        )
      );
      assert(map_a != map_c);
      assert(map_b != map_c);
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
    }
    if (trace_verbose) { TRACE("HasSameContent 3"); }
    {
      const boost::shared_ptr<Concept> concept_a(ConceptFactory().Create("FOCAL QUESTION"));
      const boost::shared_ptr<Concept> concept_b(ConceptFactory().Create("1",{{"2",Competency::misc},{"3",Competency::misc}}));
      const boost::shared_ptr<Concept> concept_c(ConceptFactory().Create("4",{{"5",Competency::misc},{"6",Competency::misc}}));
      const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("FOCAL QUESTION"));
      const boost::shared_ptr<Concept> concept_e(ConceptFactory().Create("4",{{"5",Competency::misc},{"6",Competency::misc} } ));
      const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1",{{"2",Competency::misc},{"3",Competency::misc} } ));
      const boost::shared_ptr<Node> node_a(CenterNodeFactory().Create(concept_a,123,234));
      const boost::shared_ptr<Node> node_b(NodeFactory().Create(concept_b,123,234));
      const boost::shared_ptr<Node> node_c(NodeFactory().Create(concept_c,345,456));
      const boost::shared_ptr<Node> node_d(CenterNodeFactory().Create(concept_d,567,678));
      const boost::shared_ptr<Node> node_e(NodeFactory().Create(concept_e,789,890));
      const boost::shared_ptr<Node> node_f(NodeFactory().Create(concept_f,901,012));
      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory::Create( { node_a, node_b, node_c } ));
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory::Create( { node_d, node_f, node_e } )); //Swap e and f
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
      const boost::shared_ptr<ConceptMap> map_c(ConceptMapFactory::Create( { node_d, node_c, node_e } ));
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    if (trace_verbose) { TRACE("HasSameContent 4"); }
    {
      const boost::shared_ptr<Concept> concept_n11(ConceptFactory().Create("1"));
      const boost::shared_ptr<Concept> concept_n12(ConceptFactory().Create("2"));
      const boost::shared_ptr<Concept> concept_n13(ConceptFactory().Create("3"));
      const boost::shared_ptr<Concept> concept_n21(ConceptFactory().Create("1"));
      const boost::shared_ptr<Concept> concept_n22(ConceptFactory().Create("2"));
      const boost::shared_ptr<Concept> concept_n23(ConceptFactory().Create("3"));

      const boost::shared_ptr<Node> node_11(CenterNodeFactory().Create(concept_n11,123,234));
      const boost::shared_ptr<Node> node_12(NodeFactory().Create(concept_n12,321,432));
      const boost::shared_ptr<Node> node_13(NodeFactory().Create(concept_n13,345,456));
      const boost::shared_ptr<Node> node_21(CenterNodeFactory().Create(concept_n21,567,678));
      const boost::shared_ptr<Node> node_22(NodeFactory().Create(concept_n22,789,890));
      const boost::shared_ptr<Node> node_23(NodeFactory().Create(concept_n23,901,012));

      const boost::shared_ptr<Concept> concept_e11(ConceptFactory().Create("9"));
      const boost::shared_ptr<Concept> concept_e12(ConceptFactory().Create("8"));
      const boost::shared_ptr<Concept> concept_e13(ConceptFactory().Create("7"));
      const boost::shared_ptr<Concept> concept_e21(ConceptFactory().Create("9"));
      const boost::shared_ptr<Concept> concept_e22(ConceptFactory().Create("8"));
      const boost::shared_ptr<Concept> concept_e23(ConceptFactory().Create("7"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<Edge> edge_11(EdgeFactory().Create(NodeFactory().Create(concept_e11,1.2,3.4),nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<Edge> edge_12(EdgeFactory().Create(NodeFactory().Create(concept_e12,2.3,4.5),nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<Edge> edge_13(EdgeFactory().Create(NodeFactory().Create(concept_e13,3.4,5.6),nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<Edge> edge_21(EdgeFactory().Create(NodeFactory().Create(concept_e21,4.5,6.7),nodes_2.at(0),false,nodes_2.at(1),true));
      const boost::shared_ptr<Edge> edge_22(EdgeFactory().Create(NodeFactory().Create(concept_e22,5.6,7.8),nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<Edge> edge_23(EdgeFactory().Create(NodeFactory().Create(concept_e23,6.7,8.9),nodes_2.at(1),false,nodes_2.at(2),true));

      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ConceptMap> map_c(ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22 }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    if (trace_verbose) { TRACE("HasSameContent 5"); }
    {
      const boost::shared_ptr<Concept> concept_n11(ConceptFactory().Create("1"));
      const boost::shared_ptr<Concept> concept_n12(ConceptFactory().Create("2"));
      const boost::shared_ptr<Concept> concept_n13(ConceptFactory().Create("3"));

      const boost::shared_ptr<Node> node_11(CenterNodeFactory().Create(concept_n11,123,234));
      const boost::shared_ptr<Node> node_12(NodeFactory().Create(concept_n12,321,432));
      const boost::shared_ptr<Node> node_13(NodeFactory().Create(concept_n13,345,456));

      const boost::shared_ptr<Concept> concept_e11(ConceptFactory().Create("1->2"));
      const boost::shared_ptr<Concept> concept_e12(ConceptFactory().Create("1->3"));
      const boost::shared_ptr<Concept> concept_e13(ConceptFactory().Create("2->3"));

      const boost::shared_ptr<Concept> concept_n21(ConceptFactory().Create("1"));
      const boost::shared_ptr<Concept> concept_n22(ConceptFactory().Create("3"));
      const boost::shared_ptr<Concept> concept_n23(ConceptFactory().Create("2"));

      const boost::shared_ptr<Node> node_21(CenterNodeFactory().Create(concept_n21,123,234));
      const boost::shared_ptr<Node> node_22(NodeFactory().Create(concept_n22,321,432));
      const boost::shared_ptr<Node> node_23(NodeFactory().Create(concept_n23,345,456));

      const boost::shared_ptr<Concept> concept_e21(ConceptFactory().Create("2->3"));
      const boost::shared_ptr<Concept> concept_e22(ConceptFactory().Create("1->2"));
      const boost::shared_ptr<Concept> concept_e23(ConceptFactory().Create("1->3"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<Edge> edge_21(EdgeFactory().Create(NodeFactory().Create(concept_e21,1.2,3.4),nodes_2.at(2),false,nodes_2.at(1),true));
      const boost::shared_ptr<Edge> edge_22(EdgeFactory().Create(NodeFactory().Create(concept_e22,2.3,4.5),nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<Edge> edge_23(EdgeFactory().Create(NodeFactory().Create(concept_e23,3.4,4.5),nodes_2.at(0),false,nodes_2.at(1),true));

      const boost::shared_ptr<Edge> edge_11(EdgeFactory().Create(NodeFactory().Create(concept_e11,1.2,3.4),nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<Edge> edge_12(EdgeFactory().Create(NodeFactory().Create(concept_e12,2.3,4.5),nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<Edge> edge_13(EdgeFactory().Create(NodeFactory().Create(concept_e13,3.4,5.6),nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
    }
    if (trace_verbose) { TRACE("HasSameContent 6"); }
    {
      const auto v = AddConst(ConceptMapFactory::GetHeteromorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ConceptMap> a(ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert(*a == *v[i]); assert(*v[i] == *a);
          const boost::shared_ptr<const ConceptMap> b(ConceptMapFactory::DeepCopy(v[j]));
          assert(*b == *v[j]);
          if (i == j)
          {
            assert(ConceptMap::HasSameContent(*a,*b));
            assert(*a == *b);
          }
          else
          {
            if (ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing concept maps #" << i << " and #" << j << " must not be the same";
              TRACE(s.str());
            }
            assert(!ConceptMap::HasSameContent(*a,*b));
            assert(a != b);
          }
        }
      }
      //TRACE("ConceptMap::Test: heteromorphous testing concept maps are successfully identified as being different");
    }
    if (trace_verbose) { TRACE("Test simple homomorphous maps"); }
    {
      const auto v = AddConst(ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ConceptMap> a(ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert( a !=  v[i]);
          assert(*a == *v[i]);
          const boost::shared_ptr<const ConceptMap> b(ConceptMapFactory::DeepCopy(v[j]));
          assert(b);
          assert( b !=  v[j]);
          assert(*b == *v[j]);
          assert(a != b);
          if (i == j)
          {
            assert(ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing simple concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: simple homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }
    if (trace_verbose) { TRACE("Test complex homomorphous maps"); }
    {
      const std::vector<boost::shared_ptr<const ConceptMap> > v = AddConst(ConceptMapFactory::GetComplexHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ConceptMap> a(ConceptMapFactory::DeepCopy(v[i]));
          assert(*a == *v[i]);
          const boost::shared_ptr<const ConceptMap> b(ConceptMapFactory::DeepCopy(v[j]));
          assert(a != b);
          assert(*b == *v[j]);
          if (i != j)
          {
            assert(ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing complex concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: complex homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }


    //OLD NOTE: There is no perfect check for shuffled, yet homomorphous concept maps
    //LATER NOTE: Yet, I cannot think of an example that wouldn't get caught
    //  so perhaps the check _is_ perfect?
  }

  #ifdef TO_ADD_TO_PROJECTBRAINWEAVER
  //Conversion from Cluster
  {
    const std::vector<boost::shared_ptr<Cluster> > clusters = ClusterFactory::GetTests();
    std::for_each(clusters.begin(),clusters.end(),
      [](const boost::shared_ptr<Cluster> & cluster)
      {
        if (cluster)
        {
          const boost::shared_ptr<ConceptMap> m(ConceptMapFactory::CreateFromCluster("Focal question",cluster));
          assert(m);
          const std::string s = ConceptMap::ToXml(m);
          const boost::shared_ptr<ConceptMap> n = ConceptMapFactory::FromXml(s);
          assert(n);
          assert(IsEqual(*m,*n));
        }
      }
    );
  }
  #endif
  if (trace_verbose) { TRACE("CreateSubs"); }
  {
    //Count the number of expected sub concept maps
    {
      const std::vector<boost::shared_ptr<ConceptMap> > maps
        = ConceptMapFactory::GetHeteromorphousTestConceptMaps();
      const int n_heteromorphous_concept_maps = 20;
      assert(n_heteromorphous_concept_maps == static_cast<int>(maps.size())
        && "To warn you if you change the number of testing concept maps");
      const std::vector<int> n_subs_expected = { 0,2,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5 } ;
      assert(n_heteromorphous_concept_maps == static_cast<int>(n_subs_expected.size()));
      assert(n_subs_expected[ 0] == 0);
      assert(n_subs_expected[ 1] == 2);
      assert(n_subs_expected[ 2] == 3);
      assert(n_subs_expected[ 6] == 3);
      assert(n_subs_expected[ 7] == 4);
      assert(n_subs_expected[14] == 4);
      assert(n_subs_expected[15] == 5);
      //assert(n_subs_expected[16] == 5);

      assert(maps.size() == n_subs_expected.size());
      const int sz = static_cast<int>(n_subs_expected.size());
      for (int i=0; i!=sz; ++i)
      {
        if (!maps[i]) continue;
        const boost::shared_ptr<ConceptMap>& map = maps[i];

        const std::vector<boost::shared_ptr<ConceptMap> > subs = map->CreateSubs();
        #ifndef NDEBUG
        if (static_cast<int>(subs.size()) != n_subs_expected[i])
        {
          TRACE(i);
          TRACE(subs.size());
          TRACE(n_subs_expected[i]);
        }
        #endif
        assert(static_cast<int>(subs.size()) == n_subs_expected[i]);
      }
    }
    if (trace_verbose) { TRACE("CountCenterNodes"); }
    //Count the number of CenterNode objects
    {
      for (const boost::shared_ptr<const ConceptMap> map: ConceptMapFactory::GetHeteromorphousTestConceptMaps())
      {
        if (CountCenterNodes(map) == 0) continue;

        //Count the edges connected to CenterNode
        const int n_edges_connected_to_center { CountCenterNodeEdges(map) };
        const int n_center_nodes_expected
          = n_edges_connected_to_center + 1; //+1, because with no edges, you expect the center node only

        //Count the number of sub concept maps with a center node
        const std::vector<boost::shared_ptr<ConceptMap> > subs = map->CreateSubs();
        const int n_center_nodes_here {
          static_cast<int>(
            std::count_if(subs.begin(),subs.end(),
              [](const boost::shared_ptr<const ConceptMap> sub)
              {
                return CountCenterNodes(sub) > 0;
              }
            )
          )
        };
        const int n_center_nodes_found = n_center_nodes_here;
        if (n_center_nodes_expected != n_center_nodes_found)
        {
          TRACE("ERROR");
          TRACE("Original map next:");
          for (const std::string s: xml::XmlToPretty(ToXml(map))) { TRACE(s); }
          TRACE(n_center_nodes_expected);
          TRACE(n_center_nodes_found);
          TRACE(subs.size());
        }
        assert(n_center_nodes_expected == n_center_nodes_found);

      }
    }
  }
  if (trace_verbose) { TRACE("IsValid"); }
  {
    boost::shared_ptr<Node> node_a = CenterNodeFactory().CreateFromStrings("...");

    boost::shared_ptr<ConceptMap> concept_map = ConceptMapFactory::Create(
      { node_a } );
    assert(concept_map);
    assert(concept_map->IsValid());
    const boost::shared_ptr<Node> node = NodeFactory().CreateFromStrings("...");
    concept_map->AddNode(node);
    assert(concept_map->IsValid());
  }
  if (trace_verbose) { TRACE("Add nodes and edges"); }
  {
    const auto concept_maps = ConceptMapFactory::GetHeteromorphousTestConceptMaps();
    for (const auto concept_map: concept_maps)
    {
      assert(concept_map);
      const int n_nodes_before = concept_map->GetNodes().size();
      const int n_edges_before = concept_map->GetEdges().size();
      const auto node_a = NodeFactory().GetTests().at(0);
      const auto node_b = NodeFactory().GetTests().at(1);
      const int index = 0;
      assert(index < static_cast<int>(ConceptFactory().GetTests().size()));
      const auto concept = ConceptFactory().GetTests().at(index);
      const auto edge = EdgeFactory().Create(
        NodeFactory().Create(concept,123.456,456.789),node_a,true,node_b,true);
      concept_map->AddNode(node_a);
      concept_map->AddNode(node_b);
      concept_map->AddEdge(edge);
      const int n_nodes_after = concept_map->GetNodes().size();
      const int n_edges_after = concept_map->GetEdges().size();
      assert(n_nodes_after == n_nodes_before + 2);
      assert(n_edges_after == n_edges_before + 1);
    }
  }
  if (trace_verbose) { TRACE("Deletion of nodes"); }
  {
    const std::size_t n_concept_maps = ConceptMapFactory::GetHeteromorphousTestConceptMaps().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      assert(ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i]);
      const std::size_t n_nodes = ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i]->GetNodes().size();
      for (std::size_t j=0; j!=n_nodes; ++j)
      {
        const boost::shared_ptr<ConceptMap> concept_map = ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i];
        assert(concept_map);
        assert(concept_map->GetNodes().size() == n_nodes);
        assert(j < concept_map->GetNodes().size());
        const boost::shared_ptr<Node> node = concept_map->GetNodes()[j];
        concept_map->DeleteNode(node);
        assert(concept_map->GetNodes().size() == n_nodes - 1
          && "Node must really be gone");
      }
    }
  }
  if (trace_verbose) { TRACE("Deletion of edges"); }
  {
    const std::size_t n_concept_maps = ConceptMapFactory::GetHeteromorphousTestConceptMaps().size();

    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      assert(ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i]);
      const std::size_t n_edges = ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i]->GetEdges().size();
      for (std::size_t j=0; j!=n_edges; ++j)
      {
        const boost::shared_ptr<ConceptMap> concept_map = ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i];
        assert(concept_map);
        assert(concept_map->GetEdges().size() == n_edges);
        assert(j < concept_map->GetEdges().size());
        const boost::shared_ptr<Edge> edge = concept_map->GetEdges()[j];
        concept_map->DeleteEdge(edge);
        assert(concept_map->GetEdges().size() == n_edges - 1
          && "Edge must really be gone");
      }
    }
  }
  if (trace_verbose) { TRACE("Is GetNode()[0] a CenterNode?"); }
  {
    //const std::size_t n_concept_maps = ConceptMapFactory::GetAllTests().size();
    const std::size_t n_concept_maps = ConceptMapFactory::GetHeteromorphousTestConceptMaps().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {

      assert(ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i]);
      const boost::shared_ptr<ConceptMap> concept_map = ConceptMapFactory::GetHeteromorphousTestConceptMaps()[i];
      assert(concept_map);
      if (concept_map->GetNodes().empty()) continue;
      assert(concept_map->FindCenterNode() && "Assume a CenterNode at the center of ConceptMap");
    }
  }
  TRACE("ConceptMap::Test finished successfully");
}
#endif
