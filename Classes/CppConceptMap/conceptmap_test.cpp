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
#include "conceptmapcommandfactory.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommandcreatenewedge.h"
#include "conceptmapcommandunselectrandom.h"
#include "conceptmapcommandaddselectedrandom.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "testtimer.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::ConceptMap::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    CenterNodeFactory();
    ConceptFactory();
    ExamplesFactory();
    NodeFactory();
    EdgeFactory();
    TestHelperFunctions();
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  const bool verbose{false};
  typedef std::vector<boost::shared_ptr<Node>> Nodes;

  if (verbose) { TRACE("Create tests"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const std::vector<boost::shared_ptr<const ConceptMap>> v{AddConst(ConceptMapFactory().GetAllTests())};
    assert(!v.empty());
  }
  if (verbose) { TRACE("DeepCopy must result in two identical concept maps"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const boost::shared_ptr<const ConceptMap> m{ConceptMapFactory().GetHeteromorphousTestConceptMap(19)};
    const boost::shared_ptr<ConceptMap> c{ConceptMapFactory().DeepCopy(m)};
    assert(*c == *m);
  }

  if (verbose) { TRACE("ConceptMap->XML std::string has to be between <concept_map> tags"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    const auto s = ConceptMap::ToXml(conceptmap);
    assert(s.size() >= 27);
    assert(s.substr(0,13) == "<concept_map>");
    assert(s.substr(s.size() - 14,14) == "</concept_map>");
  }
  if (verbose) { TRACE("ConceptMap->XML->ConceptMap must result in two identical concept maps"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.2);
    const boost::shared_ptr<const ConceptMap> m{ConceptMapFactory().GetHeteromorphousTestConceptMap(19)};
    const std::string s{ToXml(m)};
    const boost::shared_ptr<ConceptMap> d = ConceptMapFactory().FromXml(s);
    assert(*m == *d);
  }
  if (verbose) { TRACE("CanConstruct"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    assert(CanConstruct( {}, {} ) && "Assume empty concept map can be constructed");
  }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const boost::shared_ptr<Concept> concept(ConceptFactory().Create("FOCAL QUESTION"));
    const boost::shared_ptr<Node> node = NodeFactory().Create(concept,123,234);
    assert(CanConstruct( { node }, {} ) && "Assume focal question without examples can be constructed");
  }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const boost::shared_ptr<Concept> concept(ConceptFactory().Create("FOCAL QUESTION", { {"No",Competency::misc},{"examples",Competency::misc},{"allowed",Competency::misc} } ));
    const boost::shared_ptr<Node> node = NodeFactory().Create(concept,123,234);
    assert(CanConstruct( { node }, {} )
      && "Assume focal question with examples can be constructed"
      && "for example, when creating a sub-concept map");
  }
  if (verbose) { TRACE("HasSameContent"); }
  {
    if (verbose) { TRACE("HasSameContent 1"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      assert(NodeFactory().GetTests().size() >= 3);
      const boost::shared_ptr<CenterNode> node_a(CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"));
      assert(node_a);
      const boost::shared_ptr<Node> node_b(NodeFactory().GetTests().at(1));
      assert(node_b);
      const boost::shared_ptr<Node> node_c(NodeFactory().GetTests().at(2));
      assert(node_c);
      const boost::shared_ptr<ConceptMap> map_a(
        ConceptMapFactory().Create(
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
        ConceptMapFactory().Create(
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
        ConceptMapFactory().Create(
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
    if (verbose) { TRACE("HasSameContent 2"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      const boost::shared_ptr<Concept> concept_b(ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } ));
      const boost::shared_ptr<Concept> concept_f(ConceptFactory().Create("1", { {"2",Competency::misc},{"3",Competency::misc} } ));
      const boost::shared_ptr<Node> node_b(NodeFactory().Create(concept_b,321,432));
      const boost::shared_ptr<ConceptMap> map_a(
        ConceptMapFactory().Create(
          {
            CenterNodeFactory().CreateFromStrings("FOCAL QUESTION"),
            NodeFactory().GetTests().at(1),
            NodeFactory().CreateFromStrings("4", { {"5",Competency::misc},{"6",Competency::misc} },345,456)
          }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(
        ConceptMapFactory().Create(
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
        ConceptMapFactory().Create(
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
    if (verbose) { TRACE("HasSameContent 3"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
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
      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory().Create( { node_a, node_b, node_c } ));
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory().Create( { node_d, node_f, node_e } )); //Swap e and f
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
      const boost::shared_ptr<ConceptMap> map_c(ConceptMapFactory().Create( { node_d, node_c, node_e } ));
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    if (verbose) { TRACE("HasSameContent 4"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
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

      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory().Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory().Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ConceptMap> map_c(ConceptMapFactory().Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22 }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    if (verbose) { TRACE("HasSameContent 5"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
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

      const boost::shared_ptr<ConceptMap> map_a(ConceptMapFactory().Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ConceptMap> map_b(ConceptMapFactory().Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
    }
    if (verbose) { TRACE("HasSameContent 6"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      const boost::shared_ptr<const ConceptMap> a{ConceptMapFactory().GetHeteromorphousTestConceptMap(19)};
      const boost::shared_ptr<const ConceptMap> b{ConceptMapFactory().GetHeteromorphousTestConceptMap(19)};
      assert(ConceptMap::HasSameContent(*a,*b));
    }
    if (verbose) { TRACE("HasSameContent 7"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      const boost::shared_ptr<const ConceptMap> a{ConceptMapFactory().GetHeteromorphousTestConceptMap(18)};
      const boost::shared_ptr<const ConceptMap> b{ConceptMapFactory().GetHeteromorphousTestConceptMap(19)};
      assert(!ConceptMap::HasSameContent(*a,*b));
    }
    if (verbose) { TRACE("Test simple homomorphous maps"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      const auto v = AddConst(ConceptMapFactory().GetSimpleHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = i; j!=sz; ++j)
        {
          const boost::shared_ptr<const ConceptMap> a(ConceptMapFactory().DeepCopy(v[i]));
          assert(a);
          assert( a !=  v[i]);
          assert(*a == *v[i]);
          const boost::shared_ptr<const ConceptMap> b(ConceptMapFactory().DeepCopy(v[j]));
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
            }
            assert(ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: simple homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }
    if (verbose) { TRACE("Test complex homomorphous maps"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
      const int sz = ConceptMapFactory().GetNumberOfComplexHomomorphousTestConceptMaps();
      for (int i = 1; i!=sz; ++i)
      {
        const int j = i - 1;
        const boost::shared_ptr<const ConceptMap> a{ConceptMapFactory().GetComplexHomomorphousTestConceptMap(i)};
        const boost::shared_ptr<const ConceptMap> b{ConceptMapFactory().GetComplexHomomorphousTestConceptMap(j)};
        assert(ConceptMap::HasSameContent(*a,*b));
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
          const boost::shared_ptr<ConceptMap> m(ConceptMapFactory().CreateFromCluster("Focal question",cluster));
          assert(m);
          const std::string s = ConceptMap::ToXml(m);
          const boost::shared_ptr<ConceptMap> n = ConceptMapFactory().FromXml(s);
          assert(n);
          assert(IsEqual(*m,*n));
        }
      }
    );
  }
  #endif
  if (verbose) { TRACE("CreateSubs"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    //Count the number of expected sub concept maps
    {
      const std::vector<boost::shared_ptr<ConceptMap> > maps
        = ConceptMapFactory().GetHeteromorphousTestConceptMaps();
      const int n_heteromorphous_conceptmaps = 20;
      assert(n_heteromorphous_conceptmaps == static_cast<int>(maps.size())
        && "To warn you if you change the number of testing concept maps");
      const std::vector<int> n_subs_expected = { 0,2,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5 } ;
      assert(n_heteromorphous_conceptmaps == static_cast<int>(n_subs_expected.size()));
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
        assert(static_cast<int>(subs.size()) == n_subs_expected[i]);
      }
    }
  }
  if (verbose) { TRACE("CountCenterNodes"); }
  //Count the number of CenterNode objects
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    for (const boost::shared_ptr<const ConceptMap> map: ConceptMapFactory().GetHeteromorphousTestConceptMaps())
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
      assert(n_center_nodes_expected == n_center_nodes_found);

    }
  }
  if (verbose) { TRACE("IsValid"); }
  {
    boost::shared_ptr<Node> node_a = CenterNodeFactory().CreateFromStrings("...");
    boost::shared_ptr<ConceptMap> conceptmap = ConceptMapFactory().Create(
      { node_a } );
    assert(conceptmap);
    assert(conceptmap->IsValid());
    const boost::shared_ptr<Node> node = NodeFactory().CreateFromStrings("...");
    conceptmap->AddNode(node);
    assert(conceptmap->IsValid());
  }
  if (verbose) { TRACE("Add two nodes, check selected"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    assert(conceptmap);
    const int n_nodes_before{static_cast<int>(conceptmap->GetNodes().size())};
    const auto node_a = NodeFactory().GetTests().at(0);
    const auto node_b = NodeFactory().GetTests().at(1);

    assert(conceptmap->GetSelectedNodes().size() == 0);

    conceptmap->AddNode(node_a);

    assert(conceptmap->GetSelectedNodes().size() == 1);

    conceptmap->AddNode(node_b);

    assert(conceptmap->GetSelectedNodes().size() == 2);

    const int n_nodes_after{static_cast<int>(conceptmap->GetNodes().size())};
    assert(n_nodes_after == n_nodes_before + 2);
  }
  if (verbose) { TRACE("Add node twice, must give a warning"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    assert(conceptmap);
    const auto node_a = NodeFactory().GetTests().at(0);
    assert(conceptmap->GetNodes().size() == 0);
    conceptmap->AddNode(node_a);
    assert(conceptmap->GetNodes().size() == 1);
    conceptmap->AddNode(node_a);
    assert(conceptmap->GetNodes().size() == 1);
  }
  if (verbose) { TRACE("Add two nodes and delete one, check selected"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    assert(conceptmap);
    const auto node_a = NodeFactory().GetTests().at(0);
    const auto node_b = NodeFactory().GetTests().at(1);
    assert(conceptmap->GetSelectedNodes().size() == 0);
    conceptmap->AddNode(node_a);
    assert(conceptmap->GetSelectedNodes().size() == 1);
    conceptmap->AddNode(node_b);
    assert(conceptmap->GetSelectedNodes().size() == 2);
    conceptmap->DeleteNode(node_a);
    assert(conceptmap->GetSelectedNodes().size() == 1);
  }
  if (verbose) { TRACE("Add nodes and edge, edge its node must be in between the nodes"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    assert(conceptmap);
    const double x1{100.0};
    const double y1{200.0};
    const double x2{300.0};
    const double y2{400.0};
    const double x3{(x1+x2)/2.0};
    const double y3{(y1+y2)/2.0};
    const auto node_a = NodeFactory().GetTests().at(0);
    const auto node_b = NodeFactory().GetTests().at(0);
    node_a->SetX(x1);
    node_a->SetY(y1);
    node_b->SetX(x2);
    node_b->SetY(y2);
    const auto edge = EdgeFactory().Create(node_a,node_b);
    conceptmap->AddEdge(edge);
    assert(std::abs(edge->GetNode()->GetX() - x3) < 1.0);
    assert(std::abs(edge->GetNode()->GetY() - y3) < 1.0);
  }
  if (verbose) { TRACE("Add nodes and edge, check selected"); }
  {
    const auto conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    assert(conceptmap);
    const auto node_a = NodeFactory().GetTests().at(0);
    const auto node_b = NodeFactory().GetTests().at(1);
    const auto edge = EdgeFactory().Create(node_a,node_b);
    conceptmap->AddNode(node_a);
    conceptmap->AddNode(node_b);
    conceptmap->AddEdge(edge);
    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetSelectedEdges().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == 0);
  }
  if (verbose) { TRACE("DeleteNode: delete all two nodes of a concept map"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap = ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    assert(conceptmap);
    assert(conceptmap->GetNodes().size() == 2);
    {
      const auto node = conceptmap->GetNodes().back();
      conceptmap->DeleteNode(node);
      assert(conceptmap->GetNodes().size() == 1);
    }
    {
      const auto node = conceptmap->GetNodes().back();
      conceptmap->DeleteNode(node);
      assert(conceptmap->GetNodes().size() == 0);
    }
  }
  if (verbose) { TRACE("DeleteNode: delete node of a concept map twice"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap = ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    assert(conceptmap);
    assert(conceptmap->GetNodes().size() == 2);
    const auto node = conceptmap->GetNodes().back();
    conceptmap->DeleteNode(node);
    assert(conceptmap->GetNodes().size() == 1);
    conceptmap->DeleteNode(node);
    assert(conceptmap->GetNodes().size() == 1);
  }
  if (verbose) { TRACE("Deletion of edge"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const int test_index{19};
    const std::size_t n_edges = ConceptMapFactory().GetHeteromorphousTestConceptMap(test_index)->GetEdges().size();
    for (std::size_t j=0; j!=n_edges; ++j)
    {
      const boost::shared_ptr<ConceptMap> conceptmap = ConceptMapFactory().GetHeteromorphousTestConceptMap(test_index);
      assert(conceptmap);
      assert(conceptmap->GetEdges().size() == n_edges);
      assert(j < conceptmap->GetEdges().size());
      const boost::shared_ptr<Edge> edge = conceptmap->GetEdges()[j];
      conceptmap->DeleteEdge(edge);
      assert(conceptmap->GetEdges().size() == n_edges - 1
        && "Edge must really be gone");
    }
  }
  if (verbose) { TRACE("Deletion of edge, by deleting the from node"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap = ConceptMapFactory().GetEmptyConceptMap();
    const auto node_from = NodeFactory().GetTest(0);
    const auto node_to = NodeFactory().GetTest(0);
    conceptmap->AddNode(node_from);
    conceptmap->AddNode(node_to);
    const auto edge = EdgeFactory().GetTest(0,node_from,node_to);
    conceptmap->AddEdge(edge);
    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetEdges().size() == 1);
    conceptmap->DeleteNode(node_from);
    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetEdges().size() == 0);
  }
  if (verbose) { TRACE("Is GetNode()[0] a CenterNode?"); }
  {
    ////const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,0.1);
    const auto conceptmaps = ConceptMapFactory().GetHeteromorphousTestConceptMaps();
    for (const auto& conceptmap: conceptmaps)
    {
      if (conceptmap->GetNodes().empty()) continue;
      assert(conceptmap->FindCenterNode() && "Assume a CenterNode at the center of ConceptMap");
    }
  }

  //Commands
  if (verbose) { TRACE("A new command must be put in QUndoStack"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap(new ConceptMap);
    CommandCreateNewNode * const command {new CommandCreateNewNode(conceptmap)};
    assert(conceptmap->GetUndo().count() == 0);

    conceptmap->DoCommand(command);

    assert(conceptmap->GetUndo().count() == 1);

    command->undo();

    assert(conceptmap->GetUndo().count() == 0);
  }
  if (verbose) { TRACE("Start a concept map, create a node using a command"); }
  {
    const boost::shared_ptr<ConceptMap> cmap(new ConceptMap);
    assert(cmap->GetNodes().empty()
      && "Concept map starts empty");
    CommandCreateNewNode * const command {new CommandCreateNewNode(cmap)};
    cmap->DoCommand(command);
    assert(cmap->GetNodes().size() == 1);
    assert(cmap->CanUndo());
    command->undo();
    assert(cmap->GetNodes().size() == 0);
  }
  if (verbose) { TRACE("Start a concept map, create two nodes, unselect both, then select both using AddSelected"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap(new ConceptMap);
    const int n_nodes = 2;
    //Create nodes
    for (int i=0; i!=n_nodes; ++i)
    {
      CommandCreateNewNode * const command {
        new CommandCreateNewNode(conceptmap)
      };
      conceptmap->DoCommand(command);
    }
    assert(static_cast<int>(conceptmap->GetNodes().size()) == n_nodes
      && "Concept map must have two nodes");
    assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 2
      && "Freshly created nodes are selected");

    //Unselect both
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 2 - i);
      CommandUnselectRandom * const command {
        new CommandUnselectRandom(conceptmap)
      };
      conceptmap->DoCommand(command);
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 1 - i);
    }
    assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 0);

    //Select both again
    assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 0);
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == i);
      CommandAddSelectedRandom * const command {
        new CommandAddSelectedRandom(conceptmap)
      };
      conceptmap->DoCommand(command);
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == i + 1);
    }
    assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 2);

    //Undo selection
    for (int i=0; i!=n_nodes; ++i)
    {
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 2 - i);
      CommandUnselectRandom * const command {
        new CommandUnselectRandom(conceptmap)
      };
      conceptmap->DoCommand(command);
      assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 1 - i);
    }
    assert(static_cast<int>(conceptmap->GetSelectedNodes().size()) == 0);
  }

  //Do all do and undo of a single command
  {
    const auto conceptmap = ConceptMapFactory().GetHeteromorphousTestConceptMap(17);
    const int n_commands { static_cast<int>(CommandFactory().GetSize()) };
    for (const boost::shared_ptr<ConceptMap> conceptmap: ConceptMapFactory().GetAllTests())
    {
      for (int i=0; i!=n_commands; ++i)
      {
        if (!conceptmap) continue;
        try
        {
          assert(conceptmap);
          const auto cmd = CommandFactory().CreateTestCommand(i,conceptmap);
          if (cmd)
          {
            TRACE(cmd->text().toStdString());
            assert(conceptmap);
            conceptmap->DoCommand(cmd);
            conceptmap->Undo();
          }
        }
        catch (std::logic_error& )
        {
          //No problem: cannot do command
        }
      }
    }
  }
  //Do all combinations of two commands
  const int n_depth = 1;
  if (n_depth >= 2)
  {
    const int n_commands { static_cast<int>(CommandFactory().GetSize()) };
    for (int i=0; i!=n_commands; ++i)
    {
      for (int j=0; j!=n_commands; ++j)
      {
        for (const boost::shared_ptr<ConceptMap> conceptmap: ConceptMapFactory().GetAllTests())
        {
          for (const auto cmd:
            {
              CommandFactory().CreateTestCommand(i,conceptmap),
              CommandFactory().CreateTestCommand(j,conceptmap)
            }
          )
          {
            if (cmd)
            {
              conceptmap->DoCommand(cmd);
              conceptmap->Undo();
              conceptmap->DoCommand(cmd);
            }
          }
        }
      }
    }
  }
}
#endif
