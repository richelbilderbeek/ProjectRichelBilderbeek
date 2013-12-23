#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"

#include <sstream>
#include <set>
#include <iterator>

#ifdef MXE_SUPPORTS_THREADS
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "conceptmapcenternode.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapfactory.h"
//#include "conceptmapclusterfactory.h"
#include "conceptmapcompetency.h"
#include "conceptmapedgefactory.h"
#include "conceptmapexamplefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapnodefactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "conceptmapnode.h"
#include "conceptmapedge.h"
//#include "conceptmapcluster.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::ConceptMap::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
    {
  #endif
  TRACE("Started ribi::cmap::ConceptMap::Test");
  //typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  //Brute force tests
  {
    const std::vector<boost::shared_ptr<const ribi::cmap::ConceptMap> > v = AddConst(cmap::ConceptMapFactory::GetAllTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const ribi::cmap::ConceptMap> m)
      {
        if (m)
        {
          //Test copy constructor
          const boost::shared_ptr<ribi::cmap::ConceptMap> c(cmap::ConceptMapFactory::DeepCopy(m));
          assert(operator==(*c,*m));
          //Test XML conversions
          const std::string s = ToXml(c);
          const boost::shared_ptr<ribi::cmap::ConceptMap> d = ribi::cmap::ConceptMapFactory::FromXml(s);
          assert(operator==(*c,*d));
        }
      }
    );
  }
  //CanConstruct
  {
    const boost::shared_ptr<ribi::cmap::Concept> concept(cmap::ConceptFactory::Create("FOCAL QUESTION"));
    const boost::shared_ptr<ribi::cmap::Node> node = NodeFactory::Create(concept,123,234);
    assert(CanConstruct( { node }, {} ) && "Assume focal question without examples can be constructed");
  }
  {
    const boost::shared_ptr<ribi::cmap::Concept> concept(cmap::ConceptFactory::Create("FOCAL QUESTION", { {"No",cmap::Competency::misc},{"examples",cmap::Competency::misc},{"allowed",cmap::Competency::misc} } ));
    const boost::shared_ptr<ribi::cmap::Node> node = NodeFactory::Create(concept,123,234);
    assert(CanConstruct( { node }, {} )
      && "Assume focal question with examples can be constructed"
      && "for example, when creating a sub-concept map");
  }
  //HasSameContent
  {
    {
      const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::NodeFactory::Create("FOCAL QUESTION"));
      assert(node_a);
      const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::GetTests().at(1));
      assert(node_b);
      const boost::shared_ptr<ribi::cmap::Node> node_c(cmap::NodeFactory::GetTests().at(2));
      assert(node_c);
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_a(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"),
            cmap::NodeFactory::GetTests().at(1),
            cmap::NodeFactory::GetTests().at(2)
          }
        )
      );
      assert(map_a);
      assert(map_a->GetNodes().size() == 3);
      assert(map_a->GetNodes().at(0)->GetConcept());
      assert(map_a->GetNodes().at(0)->GetConcept()->GetExamples());
      assert(map_a->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size() == 0);
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_b(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"),
            cmap::NodeFactory::GetTests().at(1),
            cmap::NodeFactory::GetTests().at(2)
          }
        )
      );
      assert(map_b);
      assert(map_b->GetNodes().size() == 3);
      assert(map_b->GetNodes().at(0)->GetConcept());
      assert(map_b->GetNodes().at(0)->GetConcept()->GetExamples());
      assert(map_b->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size() == 0);
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ribi::cmap::ConceptMap> map_c(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"),
            cmap::NodeFactory::GetTests().at(1),
            cmap::NodeFactory::GetTests().at(2),
            cmap::NodeFactory::GetTests().at(2)
          }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));

    }
    {
      //const boost::shared_ptr<ribi::cmap::Concept> concept_a(cmap::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_b(cmap::ConceptFactory::Create("1", { {"2",cmap::Competency::misc},{"3",cmap::Competency::misc} } ));
      //const boost::shared_ptr<ribi::cmap::Concept> concept_c(cmap::ConceptFactory::Create();
      //const boost::shared_ptr<ribi::cmap::Concept> concept_d(cmap::ConceptFactory::Create("FOCAL QUESTION"));
      //const boost::shared_ptr<ribi::cmap::Concept> concept_e(cmap::ConceptFactory::Create("4", { {"5",cmap::Competency::misc},{"6",cmap::Competency::misc} } ));
      const boost::shared_ptr<ribi::cmap::Concept> concept_f(cmap::ConceptFactory::Create("1", { {"2",cmap::Competency::misc},{"3",cmap::Competency::misc} } ));
      //const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::NodeFactory::Create(concept_a,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::Create(concept_b,321,432));
      //const boost::shared_ptr<ribi::cmap::Node> node_d(cmap::NodeFactory::Create(concept_d,567,678));
      //const boost::shared_ptr<ribi::cmap::Node> node_e(cmap::NodeFactory::Create(concept_e,789,890));
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_a(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"),
            cmap::NodeFactory::GetTests().at(1),
            cmap::NodeFactory::Create("4", { {"5",cmap::Competency::misc},{"6",cmap::Competency::misc} },345,456)
          }
        )
      );
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_b(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"),
            cmap::NodeFactory::GetTests().at(1),
            cmap::NodeFactory::Create("4", { {"5",cmap::Competency::misc},{"6",cmap::Competency::misc} },901,012)
          }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      //const boost::shared_ptr<ribi::cmap::Concept> concept_g(cmap::ConceptFactory::Create("7",{ {"8",cmap::Competency::misc},{"9",cmap::Competency::misc} } ));
      const boost::shared_ptr<ribi::cmap::Node> node_g = NodeFactory::Create(concept_f,901,012);
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_c(
        ribi::cmap::ConceptMapFactory::Create(
          {
            cmap::CenterNodeFactory::Create("FOCAL QUESTION"), node_b, node_g
          }
        )
      );
      assert(map_a != map_c);
      assert(map_b != map_c);
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
    }
    {
      const boost::shared_ptr<ribi::cmap::Concept> concept_a(cmap::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_b(cmap::ConceptFactory::Create("1",{{"2",cmap::Competency::misc},{"3",cmap::Competency::misc}}));
      const boost::shared_ptr<ribi::cmap::Concept> concept_c(cmap::ConceptFactory::Create("4",{{"5",cmap::Competency::misc},{"6",cmap::Competency::misc}}));
      const boost::shared_ptr<ribi::cmap::Concept> concept_d(cmap::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e(cmap::ConceptFactory::Create("4",{{"5",cmap::Competency::misc},{"6",cmap::Competency::misc} } ));
      const boost::shared_ptr<ribi::cmap::Concept> concept_f(cmap::ConceptFactory::Create("1",{{"2",cmap::Competency::misc},{"3",cmap::Competency::misc} } ));
      const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::CenterNodeFactory::Create(concept_a,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::Create(concept_b,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_c(cmap::NodeFactory::Create(concept_c,345,456));
      const boost::shared_ptr<ribi::cmap::Node> node_d(cmap::CenterNodeFactory::Create(concept_d,567,678));
      const boost::shared_ptr<ribi::cmap::Node> node_e(cmap::NodeFactory::Create(concept_e,789,890));
      const boost::shared_ptr<ribi::cmap::Node> node_f(cmap::NodeFactory::Create(concept_f,901,012));
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_a(cmap::ConceptMapFactory::Create( { node_a, node_b, node_c } ));
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_b(cmap::ConceptMapFactory::Create( { node_d, node_f, node_e } )); //Swap e and f
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ribi::cmap::ConceptMap> map_c(cmap::ConceptMapFactory::Create( { node_d, node_d, node_d } ));
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    {
      const boost::shared_ptr<ribi::cmap::Concept> concept_n11(cmap::ConceptFactory::Create("1"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n12(cmap::ConceptFactory::Create("2"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n13(cmap::ConceptFactory::Create("3"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n21(cmap::ConceptFactory::Create("1"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n22(cmap::ConceptFactory::Create("2"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n23(cmap::ConceptFactory::Create("3"));

      const boost::shared_ptr<ribi::cmap::Node> node_11(cmap::CenterNodeFactory::Create(concept_n11,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_12(cmap::NodeFactory::Create(concept_n12,321,432));
      const boost::shared_ptr<ribi::cmap::Node> node_13(cmap::NodeFactory::Create(concept_n13,345,456));
      const boost::shared_ptr<ribi::cmap::Node> node_21(cmap::CenterNodeFactory::Create(concept_n21,567,678));
      const boost::shared_ptr<ribi::cmap::Node> node_22(cmap::NodeFactory::Create(concept_n22,789,890));
      const boost::shared_ptr<ribi::cmap::Node> node_23(cmap::NodeFactory::Create(concept_n23,901,012));

      const boost::shared_ptr<ribi::cmap::Concept> concept_e11(cmap::ConceptFactory::Create("9"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e12(cmap::ConceptFactory::Create("8"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e13(cmap::ConceptFactory::Create("7"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e21(cmap::ConceptFactory::Create("9"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e22(cmap::ConceptFactory::Create("8"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e23(cmap::ConceptFactory::Create("7"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<ribi::cmap::Edge> edge_11(cmap::EdgeFactory::Create(concept_e11,1.2,3.4,nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_12(cmap::EdgeFactory::Create(concept_e12,2.3,4.5,nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_13(cmap::EdgeFactory::Create(concept_e13,3.4,5.6,nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<ribi::cmap::Edge> edge_21(cmap::EdgeFactory::Create(concept_e21,4.5,6.7,nodes_2.at(0),false,nodes_2.at(1),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_22(cmap::EdgeFactory::Create(concept_e22,5.6,7.8,nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_23(cmap::EdgeFactory::Create(concept_e23,6.7,8.9,nodes_2.at(1),false,nodes_2.at(2),true));

      const boost::shared_ptr<ribi::cmap::ConceptMap> map_a(cmap::ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_b(cmap::ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<ribi::cmap::ConceptMap> map_c(cmap::ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22 }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }


    {
      const boost::shared_ptr<ribi::cmap::Concept> concept_n11(cmap::ConceptFactory::Create("1"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n12(cmap::ConceptFactory::Create("2"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n13(cmap::ConceptFactory::Create("3"));

      const boost::shared_ptr<ribi::cmap::Node> node_11(cmap::CenterNodeFactory::Create(concept_n11,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_12(cmap::NodeFactory::Create(concept_n12,321,432));
      const boost::shared_ptr<ribi::cmap::Node> node_13(cmap::NodeFactory::Create(concept_n13,345,456));

      const boost::shared_ptr<ribi::cmap::Concept> concept_e11(cmap::ConceptFactory::Create("1->2"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e12(cmap::ConceptFactory::Create("1->3"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e13(cmap::ConceptFactory::Create("2->3"));

      const boost::shared_ptr<ribi::cmap::Concept> concept_n21(cmap::ConceptFactory::Create("1"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n22(cmap::ConceptFactory::Create("3"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_n23(cmap::ConceptFactory::Create("2"));

      const boost::shared_ptr<ribi::cmap::Node> node_21(cmap::CenterNodeFactory::Create(concept_n21,123,234));
      const boost::shared_ptr<ribi::cmap::Node> node_22(cmap::NodeFactory::Create(concept_n22,321,432));
      const boost::shared_ptr<ribi::cmap::Node> node_23(cmap::NodeFactory::Create(concept_n23,345,456));

      const boost::shared_ptr<ribi::cmap::Concept> concept_e21(cmap::ConceptFactory::Create("2->3"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e22(cmap::ConceptFactory::Create("1->2"));
      const boost::shared_ptr<ribi::cmap::Concept> concept_e23(cmap::ConceptFactory::Create("1->3"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<ribi::cmap::Edge> edge_21(cmap::EdgeFactory::Create(concept_e21,1.2,3.4,nodes_2.at(2),false,nodes_2.at(1),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_22(cmap::EdgeFactory::Create(concept_e22,2.3,4.5,nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_23(cmap::EdgeFactory::Create(concept_e23,3.4,4.5,nodes_2.at(0),false,nodes_2.at(1),true));

      const boost::shared_ptr<ribi::cmap::Edge> edge_11(cmap::EdgeFactory::Create(concept_e11,1.2,3.4,nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_12(cmap::EdgeFactory::Create(concept_e12,2.3,4.5,nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<ribi::cmap::Edge> edge_13(cmap::EdgeFactory::Create(concept_e13,3.4,5.6,nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<ribi::cmap::ConceptMap> map_a(cmap::ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<ribi::cmap::ConceptMap> map_b(cmap::ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
    }
    {
      const auto v = AddConst(cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ribi::cmap::ConceptMap> a(cmap::ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert(operator==(*a,*v[i])); assert(operator==(*v[i],*a));
          const boost::shared_ptr<const ribi::cmap::ConceptMap> b(cmap::ConceptMapFactory::DeepCopy(v[j]));
          assert(operator==(*b,*v[j]));
          if (i == j)
          {
            assert(cmap::ConceptMap::HasSameContent(*a,*b));
            assert(operator==(*a,*b));
          }
          else
          {
            if (cmap::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing concept maps #" << i << " and #" << j << " must not be the same";
              TRACE(s.str());
            }
            assert(!cmap::ConceptMap::HasSameContent(*a,*b));
            assert(a != b);
          }
        }
      }
      //TRACE("ConceptMap::Test: heteromorphous testing concept maps are successfully identified as being different");
    }
    //Test simple homomorphous maps
    {
      const auto v = AddConst(cmap::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ribi::cmap::ConceptMap> a(cmap::ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert(operator==(*a,*v[i]));
          const boost::shared_ptr<const ribi::cmap::ConceptMap> b(cmap::ConceptMapFactory::DeepCopy(v[j]));
          assert(b);
          assert(operator==(*b,*v[j]));
          assert(a != b);
          if (i == j)
          {
            assert(cmap::ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!cmap::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing simple concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(cmap::ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: simple homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }
    //Test complex homomorphous maps
    {
      const std::vector<boost::shared_ptr<const ribi::cmap::ConceptMap> > v = AddConst(cmap::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const ribi::cmap::ConceptMap> a(cmap::ConceptMapFactory::DeepCopy(v[i]));
          assert(operator==(*a,*v[i]));
          const boost::shared_ptr<const ribi::cmap::ConceptMap> b(cmap::ConceptMapFactory::DeepCopy(v[j]));
          assert(a != b);
          assert(operator==(*b,*v[j]));
          if (i != j)
          {
            assert(cmap::ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!cmap::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing complex concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(cmap::ConceptMap::HasSameContent(*a,*b));
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
    const std::vector<boost::shared_ptr<cmap::Cluster> > clusters = cmap::ClusterFactory::GetTests();
    std::for_each(clusters.begin(),clusters.end(),
      [](const boost::shared_ptr<cmap::Cluster> & cluster)
      {
        if (cluster)
        {
          const boost::shared_ptr<ribi::cmap::ConceptMap> m(cmap::ConceptMapFactory::CreateFromCluster("Focal question",cluster));
          assert(m);
          const std::string s = ribi::cmap::ConceptMap::ToXml(m);
          const boost::shared_ptr<ribi::cmap::ConceptMap> n = ribi::cmap::ConceptMapFactory::FromXml(s);
          assert(n);
          assert(IsEqual(*m,*n));
        }
      }
    );
  }
  #endif
  //CreateSubs
  {
    {
      const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > maps
        = ConceptMapFactory::GetHeteromorphousTestConceptMaps();
      const int n_heteromorphous_concept_maps = 19;
      assert(n_heteromorphous_concept_maps == static_cast<int>(maps.size()));
      const std::vector<int> n_subs_expected = { 1,2,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5 } ;
      assert(n_heteromorphous_concept_maps == static_cast<int>(n_subs_expected.size()));
      assert(n_subs_expected[ 0] == 1);
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
        const boost::shared_ptr<ribi::cmap::ConceptMap>& map = maps[i];

        const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > subs = map->CreateSubs();
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
    //Just test all
    {
      const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > maps = ConceptMapFactory::GetAllTests();
      const int sz = boost::numeric_cast<int>(maps.size());
      for (int i=0; i!=sz; ++i)
      {
        if (!maps[i]) continue;
        const boost::shared_ptr<ribi::cmap::ConceptMap>& map = maps[i];
        const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > subs = map->CreateSubs();
        assert(!subs.empty());
      }
    }
  }
  //Test IsValid
  {
    boost::shared_ptr<ribi::cmap::Node> node_a = cmap::CenterNodeFactory::Create("...");

    boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::Create(
      { node_a } );
    assert(concept_map);
    assert(concept_map->IsValid());
    boost::shared_ptr<ribi::cmap::Node> node = cmap::NodeFactory::Create("...");
    concept_map->AddNode(node);
    assert(concept_map->IsValid());
  }
  //Add nodes and edges
  {
    const auto concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests();
    for (const auto concept_map: concept_maps)
    {
      if (!concept_map) continue;
      assert(concept_map);
      const int n_nodes_before = concept_map->GetNodes().size();
      const int n_edges_before = concept_map->GetEdges().size();
      const auto node_a = cmap::NodeFactory::GetTests().at(0);
      const auto node_b = cmap::NodeFactory::GetTests().at(1);
      const auto concept = ribi::cmap::ConceptFactory::GetTests().at(0);
      const auto edge = cmap::EdgeFactory::Create(
        concept,123.456,456.789,node_a,true,node_b,true);
      concept_map->AddNode(node_a);
      concept_map->AddNode(node_b);
      concept_map->AddEdge(edge);
      const int n_nodes_after = concept_map->GetNodes().size();
      const int n_edges_after = concept_map->GetEdges().size();
      assert(n_nodes_after == n_nodes_before + 2);
      assert(n_edges_after == n_edges_before + 1);
    }
  }
  //Deletion of nodes
  {
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory::GetAllTests()[i]) continue;
      assert(cmap::ConceptMapFactory::GetAllTests()[i]);
      const std::size_t n_nodes = ribi::cmap::ConceptMapFactory::GetAllTests()[i]->GetNodes().size();
      for (std::size_t j=0; j!=n_nodes; ++j)
      {
        boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetNodes().size() == n_nodes);
        assert(j < concept_map->GetNodes().size());
        const boost::shared_ptr<ribi::cmap::Node> node = concept_map->GetNodes()[j];
        concept_map->DeleteNode(node);
        assert(concept_map->GetNodes().size() == n_nodes - 1
          && "Node must really be gone");
      }
    }
  }
  //Deletion of edges
  {
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory::GetAllTests()[i]) continue;
      assert(cmap::ConceptMapFactory::GetAllTests()[i]);
      const std::size_t n_edges = ribi::cmap::ConceptMapFactory::GetAllTests()[i]->GetEdges().size();
      for (std::size_t j=0; j!=n_edges; ++j)
      {
        boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetEdges().size() == n_edges);
        assert(j < concept_map->GetEdges().size());
        const boost::shared_ptr<ribi::cmap::Edge> edge = concept_map->GetEdges()[j];
        concept_map->DeleteEdge(edge);
        assert(concept_map->GetEdges().size() == n_edges - 1
          && "Edge must really be gone");
      }
    }
  }
  //Is GetNode()[0] a CenterNode?
  {
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory::GetAllTests()[i]) continue;
      assert(cmap::ConceptMapFactory::GetAllTests()[i]);
      boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[i];
      if (!concept_map) continue;
      assert(concept_map);
      assert(!concept_map->GetNodes().empty());
      assert(boost::dynamic_pointer_cast<cmap::CenterNode>(concept_map->GetNodes()[0])
        && "Assume a CenterNode at the center of ConceptMap");
    }
  }
  TRACE("ConceptMap::Test finished successfully");
  #ifdef MXE_SUPPORTS_THREADS
    }
  );
  t.detach();
  #endif
}
#endif
