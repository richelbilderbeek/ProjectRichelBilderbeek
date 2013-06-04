#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconceptmap.h"

#include <sstream>
#include <set>
#include <iterator>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbclusterfactory.h"
#include "pvdbcompetency.h"
#include "pvdbedgefactory.h"
#include "pvdbexamplefactory.h"
#include "pvdbhelper.h"
#include "pvdbexamplesfactory.h"
#include "pvdbnodefactory.h"
#include "pvdbhelper.h"
#include "trace.h"
#include "pvdbnode.h"
#include "pvdbedge.h"
#include "pvdbcluster.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

#ifndef NDEBUG
void pvdb::ConceptMap::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  TRACE("Started pvdb::ConceptMap::Test");
  typedef std::vector<boost::shared_ptr<pvdb::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<pvdb::Node> > Nodes;

  //Brute force tests
  {
    const std::vector<boost::shared_ptr<const pvdb::ConceptMap> > v = AddConst(pvdb::ConceptMapFactory::GetAllTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::ConceptMap>& m)
      {
        //Test copy constructor
        const boost::shared_ptr<pvdb::ConceptMap> c(pvdb::ConceptMapFactory::DeepCopy(m));
        assert(IsEqual(*c,*m));
        //Test XML conversions
        const std::string s = ToXml(c);
        const boost::shared_ptr<pvdb::ConceptMap> d = pvdb::ConceptMapFactory::FromXml(s);
        assert(IsEqual(*c,*d));
      }
    );
  }
  //CanConstruct
  {
    const boost::shared_ptr<pvdb::Concept> concept(pvdb::ConceptFactory::Create("FOCAL QUESTION"));
    const boost::shared_ptr<pvdb::Node> node = NodeFactory::Create(concept,123,234);
    assert(CanConstruct( { node }, {} ) && "Assume focal question without examples can be constructed");
  }
  {
    const boost::shared_ptr<pvdb::Concept> concept(pvdb::ConceptFactory::Create("FOCAL QUESTION", { {"No",pvdb::Competency::misc},{"examples",pvdb::Competency::misc},{"allowed",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Node> node = NodeFactory::Create(concept,123,234);
    assert(CanConstruct( { node }, {} )
      && "Assume focal question with examples can be constructed"
      && "for example, when creating a sub-concept map");
  }
  //HasSameContent
  {
    {
      const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create("FOCAL QUESTION"));
      assert(node_a);
      const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::GetTests().at(1));
      assert(node_b);
      const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::GetTests().at(2));
      assert(node_c);
      const boost::shared_ptr<pvdb::ConceptMap> map_a(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"),
            pvdb::NodeFactory::GetTests().at(1),
            pvdb::NodeFactory::GetTests().at(2)
          }
        )
      );
      assert(map_a);
      assert(map_a->GetNodes().size() == 3);
      assert(map_a->GetNodes().at(0)->GetConcept());
      assert(map_a->GetNodes().at(0)->GetConcept()->GetExamples());
      assert(map_a->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size() == 0);
      const boost::shared_ptr<pvdb::ConceptMap> map_b(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"),
            pvdb::NodeFactory::GetTests().at(1),
            pvdb::NodeFactory::GetTests().at(2)
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

      const boost::shared_ptr<pvdb::ConceptMap> map_c(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"),
            pvdb::NodeFactory::GetTests().at(1),
            pvdb::NodeFactory::GetTests().at(2),
            pvdb::NodeFactory::GetTests().at(2)
          }
        )
      );
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));

    }
    {
      const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("1", { {"2",pvdb::Competency::misc},{"3",pvdb::Competency::misc} } ));
      //const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create();
      const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("4", { {"5",pvdb::Competency::misc},{"6",pvdb::Competency::misc} } ));
      const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1", { {"2",pvdb::Competency::misc},{"3",pvdb::Competency::misc} } ));
      const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a,123,234));
      const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b,321,432));
      //const boost::shared_ptr<pvdb::Node> node_c();
      //const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c,345,456));
      const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d,567,678));
      const boost::shared_ptr<pvdb::Node> node_e(pvdb::NodeFactory::Create(concept_e,789,890));
      //const boost::shared_ptr<pvdb::Node> node_f();
      //const boost::shared_ptr<pvdb::Node> node_f(pvdb::NodeFactory::Create(concept_f,901,012));
      const boost::shared_ptr<pvdb::ConceptMap> map_a(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"),
            pvdb::NodeFactory::GetTests().at(1),
            pvdb::NodeFactory::Create("4", { {"5",pvdb::Competency::misc},{"6",pvdb::Competency::misc} },345,456)
          }
        )
      );
      const boost::shared_ptr<pvdb::ConceptMap> map_b(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"),
            pvdb::NodeFactory::GetTests().at(1),
            pvdb::NodeFactory::Create("4", { {"5",pvdb::Competency::misc},{"6",pvdb::Competency::misc} },901,012)
          }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("7",{ {"8",pvdb::Competency::misc},{"9",pvdb::Competency::misc} } ));
      const boost::shared_ptr<pvdb::Node> node_g = NodeFactory::Create(concept_f,901,012);
      const boost::shared_ptr<pvdb::ConceptMap> map_c(
        pvdb::ConceptMapFactory::Create(
          {
            pvdb::NodeFactory::Create("FOCAL QUESTION"), node_b, node_g
          }
        )
      );
      assert(map_a != map_c);
      assert(map_b != map_c);
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
    }
    {
      const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("1",{{"2",pvdb::Competency::misc},{"3",pvdb::Competency::misc}}));
      const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("4",{{"5",pvdb::Competency::misc},{"6",pvdb::Competency::misc}}));
      const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("FOCAL QUESTION"));
      const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("4",{{"5",pvdb::Competency::misc},{"6",pvdb::Competency::misc} } ));
      const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1",{{"2",pvdb::Competency::misc},{"3",pvdb::Competency::misc} } ));
      const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a,123,234));
      const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b,123,234));
      const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c,345,456));
      const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d,567,678));
      const boost::shared_ptr<pvdb::Node> node_e(pvdb::NodeFactory::Create(concept_e,789,890));
      const boost::shared_ptr<pvdb::Node> node_f(pvdb::NodeFactory::Create(concept_f,901,012));
      const boost::shared_ptr<pvdb::ConceptMap> map_a(pvdb::ConceptMapFactory::Create( { node_a, node_b, node_c } ));
      const boost::shared_ptr<pvdb::ConceptMap> map_b(pvdb::ConceptMapFactory::Create( { node_d, node_f, node_e } )); //Swap e and f
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<pvdb::ConceptMap> map_c(pvdb::ConceptMapFactory::Create( { node_d, node_d, node_d } ));
      assert(!HasSameContent(*map_a,*map_c));
      assert(!HasSameContent(*map_b,*map_c));
      assert(map_a != map_c);
      assert(map_b != map_c);
    }
    {
      const boost::shared_ptr<pvdb::Concept> concept_n11(pvdb::ConceptFactory::Create("1"));
      const boost::shared_ptr<pvdb::Concept> concept_n12(pvdb::ConceptFactory::Create("2"));
      const boost::shared_ptr<pvdb::Concept> concept_n13(pvdb::ConceptFactory::Create("3"));
      const boost::shared_ptr<pvdb::Concept> concept_n21(pvdb::ConceptFactory::Create("1"));
      const boost::shared_ptr<pvdb::Concept> concept_n22(pvdb::ConceptFactory::Create("2"));
      const boost::shared_ptr<pvdb::Concept> concept_n23(pvdb::ConceptFactory::Create("3"));

      const boost::shared_ptr<pvdb::Node> node_11(pvdb::NodeFactory::Create(concept_n11,123,234));
      const boost::shared_ptr<pvdb::Node> node_12(pvdb::NodeFactory::Create(concept_n12,321,432));
      const boost::shared_ptr<pvdb::Node> node_13(pvdb::NodeFactory::Create(concept_n13,345,456));
      const boost::shared_ptr<pvdb::Node> node_21(pvdb::NodeFactory::Create(concept_n21,567,678));
      const boost::shared_ptr<pvdb::Node> node_22(pvdb::NodeFactory::Create(concept_n22,789,890));
      const boost::shared_ptr<pvdb::Node> node_23(pvdb::NodeFactory::Create(concept_n23,901,012));

      const boost::shared_ptr<pvdb::Concept> concept_e11(pvdb::ConceptFactory::Create("9"));
      const boost::shared_ptr<pvdb::Concept> concept_e12(pvdb::ConceptFactory::Create("8"));
      const boost::shared_ptr<pvdb::Concept> concept_e13(pvdb::ConceptFactory::Create("7"));
      const boost::shared_ptr<pvdb::Concept> concept_e21(pvdb::ConceptFactory::Create("9"));
      const boost::shared_ptr<pvdb::Concept> concept_e22(pvdb::ConceptFactory::Create("8"));
      const boost::shared_ptr<pvdb::Concept> concept_e23(pvdb::ConceptFactory::Create("7"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<pvdb::Edge> edge_11(pvdb::EdgeFactory::Create(concept_e11,1.2,3.4,nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<pvdb::Edge> edge_12(pvdb::EdgeFactory::Create(concept_e12,2.3,4.5,nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<pvdb::Edge> edge_13(pvdb::EdgeFactory::Create(concept_e13,3.4,5.6,nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<pvdb::Edge> edge_21(pvdb::EdgeFactory::Create(concept_e21,4.5,6.7,nodes_2.at(0),false,nodes_2.at(1),true));
      const boost::shared_ptr<pvdb::Edge> edge_22(pvdb::EdgeFactory::Create(concept_e22,5.6,7.8,nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<pvdb::Edge> edge_23(pvdb::EdgeFactory::Create(concept_e23,6.7,8.9,nodes_2.at(1),false,nodes_2.at(2),true));

      const boost::shared_ptr<pvdb::ConceptMap> map_a(pvdb::ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<pvdb::ConceptMap> map_b(pvdb::ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);

      const boost::shared_ptr<pvdb::ConceptMap> map_c(pvdb::ConceptMapFactory::Create(
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
      const boost::shared_ptr<pvdb::Concept> concept_n11(pvdb::ConceptFactory::Create("1"));
      const boost::shared_ptr<pvdb::Concept> concept_n12(pvdb::ConceptFactory::Create("2"));
      const boost::shared_ptr<pvdb::Concept> concept_n13(pvdb::ConceptFactory::Create("3"));

      const boost::shared_ptr<pvdb::Node> node_11(pvdb::NodeFactory::Create(concept_n11,123,234));
      const boost::shared_ptr<pvdb::Node> node_12(pvdb::NodeFactory::Create(concept_n12,321,432));
      const boost::shared_ptr<pvdb::Node> node_13(pvdb::NodeFactory::Create(concept_n13,345,456));

      const boost::shared_ptr<pvdb::Concept> concept_e11(pvdb::ConceptFactory::Create("1->2"));
      const boost::shared_ptr<pvdb::Concept> concept_e12(pvdb::ConceptFactory::Create("1->3"));
      const boost::shared_ptr<pvdb::Concept> concept_e13(pvdb::ConceptFactory::Create("2->3"));

      const boost::shared_ptr<pvdb::Concept> concept_n21(pvdb::ConceptFactory::Create("1"));
      const boost::shared_ptr<pvdb::Concept> concept_n22(pvdb::ConceptFactory::Create("3"));
      const boost::shared_ptr<pvdb::Concept> concept_n23(pvdb::ConceptFactory::Create("2"));

      const boost::shared_ptr<pvdb::Node> node_21(pvdb::NodeFactory::Create(concept_n21,123,234));
      const boost::shared_ptr<pvdb::Node> node_22(pvdb::NodeFactory::Create(concept_n22,321,432));
      const boost::shared_ptr<pvdb::Node> node_23(pvdb::NodeFactory::Create(concept_n23,345,456));

      const boost::shared_ptr<pvdb::Concept> concept_e21(pvdb::ConceptFactory::Create("2->3"));
      const boost::shared_ptr<pvdb::Concept> concept_e22(pvdb::ConceptFactory::Create("1->2"));
      const boost::shared_ptr<pvdb::Concept> concept_e23(pvdb::ConceptFactory::Create("1->3"));

      const Nodes nodes_1 = { node_11, node_12, node_13 };
      const Nodes nodes_2 = { node_21, node_22, node_23 };

      const boost::shared_ptr<pvdb::Edge> edge_21(pvdb::EdgeFactory::Create(concept_e21,1.2,3.4,nodes_2.at(2),false,nodes_2.at(1),true));
      const boost::shared_ptr<pvdb::Edge> edge_22(pvdb::EdgeFactory::Create(concept_e22,2.3,4.5,nodes_2.at(0),false,nodes_2.at(2),true));
      const boost::shared_ptr<pvdb::Edge> edge_23(pvdb::EdgeFactory::Create(concept_e23,3.4,4.5,nodes_2.at(0),false,nodes_2.at(1),true));

      const boost::shared_ptr<pvdb::Edge> edge_11(pvdb::EdgeFactory::Create(concept_e11,1.2,3.4,nodes_1.at(0),false,nodes_1.at(1),true));
      const boost::shared_ptr<pvdb::Edge> edge_12(pvdb::EdgeFactory::Create(concept_e12,2.3,4.5,nodes_1.at(0),false,nodes_1.at(2),true));
      const boost::shared_ptr<pvdb::Edge> edge_13(pvdb::EdgeFactory::Create(concept_e13,3.4,5.6,nodes_1.at(1),false,nodes_1.at(2),true));

      const boost::shared_ptr<pvdb::ConceptMap> map_a(pvdb::ConceptMapFactory::Create(
        { node_11, node_12, node_13 },
        { edge_11, edge_12, edge_13 }
        )
      );
      const boost::shared_ptr<pvdb::ConceptMap> map_b(pvdb::ConceptMapFactory::Create(
        { node_21, node_22, node_23 },
        { edge_21, edge_22, edge_23 }
        )
      );
      assert(HasSameContent(*map_a,*map_b));
      assert(map_a != map_b);
    }
    {
      const auto v = AddConst(pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const pvdb::ConceptMap> a(pvdb::ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert(IsEqual(*a,*v[i])); assert(IsEqual(*v[i],*a));
          const boost::shared_ptr<const pvdb::ConceptMap> b(pvdb::ConceptMapFactory::DeepCopy(v[j]));
          assert(IsEqual(*b,*v[j]));
          if (i == j)
          {
            assert(pvdb::ConceptMap::HasSameContent(*a,*b));
            assert(IsEqual(*a,*b));
          }
          else
          {
            if (pvdb::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing concept maps #" << i << " and #" << j << " must not be the same";
              TRACE(s.str());
            }
            assert(!pvdb::ConceptMap::HasSameContent(*a,*b));
            assert(a != b);
          }
        }
      }
      //TRACE("ConceptMap::Test: heteromorphous testing concept maps are successfully identified as being different");
    }
    //Test simple homomorphous maps
    {
      const auto v = AddConst(pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const pvdb::ConceptMap> a(pvdb::ConceptMapFactory::DeepCopy(v[i]));
          assert(a);
          assert(IsEqual(*a,*v[i]));
          const boost::shared_ptr<const pvdb::ConceptMap> b(pvdb::ConceptMapFactory::DeepCopy(v[j]));
          assert(b);
          assert(IsEqual(*b,*v[j]));
          assert(a != b);
          if (i == j)
          {
            assert(pvdb::ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!pvdb::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing simple concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(pvdb::ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: simple homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }
    //Test complex homomorphous maps
    {
      const std::vector<boost::shared_ptr<const pvdb::ConceptMap> > v = AddConst(pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps());
      const int sz = v.size();
      for (int i = 0; i!=sz; ++i)
      {
        for (int j = 0; j!=sz; ++j)
        {
          const boost::shared_ptr<const pvdb::ConceptMap> a(pvdb::ConceptMapFactory::DeepCopy(v[i]));
          assert(IsEqual(*a,*v[i]));
          const boost::shared_ptr<const pvdb::ConceptMap> b(pvdb::ConceptMapFactory::DeepCopy(v[j]));
          assert(a != b);
          assert(IsEqual(*b,*v[j]));
          if (i != j)
          {
            assert(pvdb::ConceptMap::HasSameContent(*a,*b));
          }
          else
          {
            if (!pvdb::ConceptMap::HasSameContent(*a,*b))
            {
              std::stringstream s;
              s << "Testing complex concept maps #" << i << " and #" << j << " must be homomorphous";
              TRACE(s.str());
            }
            assert(pvdb::ConceptMap::HasSameContent(*a,*b));
          }
        }
      }
      //TRACE("ConceptMap::Test: complex homomorphous testing concept maps are successfully identified as being different, yet homomorphous");
    }


    //OLD NOTE: There is no perfect check for shuffled, yet homomorphous concept maps
    //LATER NOTE: Yet, I cannot think of an example that wouldn't get caught
    //  so perhaps the check _is_ perfect?
  }
  //Conversion from Cluster
  {
    const std::vector<boost::shared_ptr<pvdb::Cluster> > clusters = pvdb::ClusterFactory::GetTests();
    assert(std::count_if(clusters.begin(),clusters.end(),[](const boost::shared_ptr<pvdb::Cluster>& p) { return !p; } ) == 0);
    //assert(std::all_of(clusters.begin(),clusters.end(),[](const boost::shared_ptr<pvdb::Cluster>& p) { return p; } ));
    std::for_each(clusters.begin(),clusters.end(),
      [](const boost::shared_ptr<pvdb::Cluster> & cluster)
      {
        const boost::shared_ptr<pvdb::ConceptMap> m(pvdb::ConceptMapFactory::CreateFromCluster("Focal question",cluster));
        assert(m);
        const std::string s = pvdb::ConceptMap::ToXml(m);
        const boost::shared_ptr<pvdb::ConceptMap> n = pvdb::ConceptMapFactory::FromXml(s);
        assert(n);
        assert(IsEqual(*m,*n));
      }
    );
  }
  //CreateSubs
  {
    {
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > maps
        = ConceptMapFactory::GetHeteromorphousTestConceptMaps();
      const std::vector<int> n_subs_expected = { 1,2,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5 } ;
      assert(n_subs_expected.size() == 18);
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
        const boost::shared_ptr<pvdb::ConceptMap>& map = maps[i];
        const std::vector<boost::shared_ptr<pvdb::ConceptMap> > subs = map->CreateSubs();
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
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > maps = ConceptMapFactory::GetAllTests();
      const int sz = boost::numeric_cast<int>(maps.size());
      for (int i=0; i!=sz; ++i)
      {
        const boost::shared_ptr<pvdb::ConceptMap>& map = maps[i];
        const std::vector<boost::shared_ptr<pvdb::ConceptMap> > subs = map->CreateSubs();
        assert(!subs.empty());
      }
    }
  }
  TRACE("ConceptMap::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
