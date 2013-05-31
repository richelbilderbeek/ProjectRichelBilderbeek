#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconceptmapfactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbexamplefactory.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::Create(
  const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
  const std::vector<boost::shared_ptr<pvdb::Edge> >& edges)
{
  boost::shared_ptr<pvdb::ConceptMap> p(new ConceptMap(nodes,edges));
  assert(p);
  return p;
}

const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::CreateFromCluster(
  const std::string& question,
  const boost::shared_ptr<pvdb::Cluster>& cluster)
{
  boost::shared_ptr<pvdb::ConceptMap> p(new ConceptMap(question,cluster));
  assert(p);
  return p;
}


const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::Create(
  const std::string& focal_question)
{
  //A single-node ConceptMap contains only the focal question
  const boost::shared_ptr<pvdb::ConceptMap> p = Create( { pvdb::NodeFactory::Create(focal_question) } );;
  assert(p);
  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<pvdb::ConceptMap> pvdb::ConceptMapFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::ConceptMap>& map)
{
  assert(map);
  const std::vector<boost::shared_ptr<const pvdb::Edge> > a = map->GetEdges();
  std::vector<boost::shared_ptr<pvdb::Edge> > edges;
  std::transform(a.begin(),a.end(),std::back_inserter(edges),
    [](const boost::shared_ptr<const pvdb::Edge>& e)
    {
      assert(e);
      const boost::shared_ptr<pvdb::Edge> f = pvdb::EdgeFactory::DeepCopy(e);
      assert(f);
      assert(IsEqual(*f,*e));
      return f;
    }
  );

  const std::vector<boost::shared_ptr<const pvdb::Node> > v = map->GetNodes();
  std::vector<boost::shared_ptr<pvdb::Node> > nodes;
  std::transform(v.begin(),v.end(),std::back_inserter(nodes),
    [](const boost::shared_ptr<const pvdb::Node>& e)
    {
      assert(e);
      const boost::shared_ptr<pvdb::Node> f = pvdb::NodeFactory::DeepCopy(e);
      assert(f);
      assert(IsEqual(*e,*f));
      return f;
    }
  );

  const boost::shared_ptr<pvdb::ConceptMap> p = Create(nodes,edges);
  assert(p);
  assert(IsEqual(*p,*map));
  return p;
}
#endif

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
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return !p; } ) == 0); //FIX 2012-01-02
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ));
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps()
{
  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v(18);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == 0);
  //[0]: as-empty-as-can-get concept map (X = focal question_
  {
    boost::shared_ptr<pvdb::ConceptMap> concept_map = Create("X");
    assert(concept_map);
    v[0]=concept_map;
  }
  //[1]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A")
        }
        , {}
      )
    );
    assert(concept_map);
    v[1]=concept_map;
  }
  //[2]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        }
      )
    );
    assert(concept_map);
    v[2]=concept_map;
  }
  //[3]
  {
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,1,false,2,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[3]=concept_map;
  }
  //[4]
  {
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,2,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[4]=concept_map;
  }
  //[5]
  {
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,1,false,2,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[5]=concept_map;
  }
  //[6]
  {
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,2,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[6]=concept_map;
  }
  //[7]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        }
      )
    );
    assert(concept_map);
    v[7]=concept_map;
  }
  //[8]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,2,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[8]=concept_map;
  }
  //[9]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a
        }
      )
    );
    assert(concept_map);
    v[9]=concept_map;
  }
  //[10]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create());
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,1.2,3.4,2,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a,
          edge_b
        }
      )
    );
    assert(concept_map);
    v[10]=concept_map;
  }
  //[11]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a,
          edge_b,
          edge_c
        }
      )
    );
    assert(concept_map);
    v[11]=concept_map;
  }

  //[12]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a,
          edge_b,
          edge_c
        }
      )
    );
    assert(concept_map);
    v[12]=concept_map;
  }
  //[13]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a,
          edge_b,
          edge_c
        }
      )
    );
    assert(concept_map);
    v[13]=concept_map;
  }

  //[14]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        {
          edge_a,
          edge_b,
          edge_c
        }
      )
    );
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

    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_h(pvdb::ConceptFactory::Create("2",{{"2-I",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3",{{"3-I",pvdb::Competency::misc},{"3-II",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_i(pvdb::ConceptFactory::Create("4",{{"4-I",pvdb::Competency::misc},{"4-II",pvdb::Competency::misc},{"4-III",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_j(pvdb::ConceptFactory::Create("5",{{"5-I",pvdb::Competency::misc},{"5-II",pvdb::Competency::misc},{"5-III",pvdb::Competency::misc},{"5-IV",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_f,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_g,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_h,3.4,5.6,4,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_d(pvdb::EdgeFactory::Create(concept_i,4.5,6.7,1,false,4,true));
    const boost::shared_ptr<pvdb::Edge> edge_e(pvdb::EdgeFactory::Create(concept_j,5.6,7.8,0,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          node_c,
          node_d,
          node_e
        },
        {
          edge_a,
          edge_b,
          edge_c,
          edge_d,
          edge_e
        }
      )
    );
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

    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_h(pvdb::ConceptFactory::Create("2",{{"2-I",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3",{{"3-I",pvdb::Competency::misc},{"3-II",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_i(pvdb::ConceptFactory::Create("4",{{"4-I",pvdb::Competency::misc},{"4-II",pvdb::Competency::misc},{"4-III",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Concept> concept_j(pvdb::ConceptFactory::Create("5",{{"5-I",pvdb::Competency::misc},{"5-II",pvdb::Competency::misc},{"5-III",pvdb::Competency::misc},{"5-IV",pvdb::Competency::misc} } ));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_f,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_g,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_h,3.4,5.6,4,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_d(pvdb::EdgeFactory::Create(concept_i,4.5,6.7,1,false,4,true));
    const boost::shared_ptr<pvdb::Edge> edge_e(pvdb::EdgeFactory::Create(concept_j,5.6,7.8,0,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          node_c,
          node_d,
          node_e
        },
        {
          edge_a,
          edge_b,
          edge_c,
          edge_d,
          edge_e
        }
      )
    );
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
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_f,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_g,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_h,3.4,5.6,4,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_d(pvdb::EdgeFactory::Create(concept_i,4.5,6.7,1,false,4,true));
    const boost::shared_ptr<pvdb::Edge> edge_e(pvdb::EdgeFactory::Create(concept_j,5.6,7.8,0,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          node_c,
          node_d,
          node_e
        },
        {
          edge_a,
          edge_b,
          edge_c,
          edge_d,
          edge_e
        }
      )
    );
    assert(concept_map);
    v.at(17)=concept_map;
  }

  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == boost::numeric_cast<int>(v.size()));
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ));
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps()
{
  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v;
  //[0] (note: same as heteromorphous[11])
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        },
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[1]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,2,false,1,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B") },
          { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[2]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,1,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,false,2,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[3]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,3,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,2,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[4]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,false,3,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,false,2,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[5]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,3,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,false,3,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A") }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[6] (note: same as heteromorphous[11], yet arrows reversed
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,true,1,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,true,2,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,true,3,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[7]
  {
    const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("X"));
    const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("A"));
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("C"));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("B"));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,3,true,1,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,true,3,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,1,true,2,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[8]
  {
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
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,true,2,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,3,true,1,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,2,true,3,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }
  //[9]
  {
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
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,1,true,3,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,2,true,1,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,true,2,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[10]
  {
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,3,true,2,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,1,true,3,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,2,true,1,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  //[11]
  {
    const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("X"));
    const boost::shared_ptr<pvdb::Concept> concept_b(pvdb::ConceptFactory::Create("C"));
    const boost::shared_ptr<pvdb::Concept> concept_c(pvdb::ConceptFactory::Create("B"));
    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("A"));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(concept_a));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::Create(concept_b));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::Create(concept_c));
    const boost::shared_ptr<pvdb::Node> node_d(pvdb::NodeFactory::Create(concept_d));

    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::Create("1"));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::Create("2"));
    const boost::shared_ptr<pvdb::Concept> concept_g(pvdb::ConceptFactory::Create("3"));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_e,1.2,3.4,2,true,3,false));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_f,2.3,4.5,1,true,2,false));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_g,3.4,5.6,3,true,1,false));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A")
        }, { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    v.push_back(concept_map);
  }

  assert(v.size() == 12);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == boost::numeric_cast<int>(v.size()));
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ));
  return v;
}

const std::vector<boost::shared_ptr<pvdb::ConceptMap> > pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps()
{
  std::vector<boost::shared_ptr<pvdb::ConceptMap> > v(6);
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ) == 0);
  //[0]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C")
        }
      )
    );
    assert(concept_map);
    v[0] = concept_map;
  }

  //[1]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B")
        }
      )
    );
    assert(concept_map);
    v[1] = concept_map;
  }
  //[2]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("C")
        }
      )
    );

    assert(concept_map);
    v[2] = concept_map;
  }
  //[3]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A")
        }
      )
    );
    assert(concept_map);
    v[3] = concept_map;
  }

  //[4]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("A"),
          pvdb::NodeFactory::Create("B")
        }
      )
    );
    assert(concept_map);
    v[4] = concept_map;
  }

  //[5]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      new pvdb::ConceptMap(
        {
          pvdb::NodeFactory::Create("X"),
          pvdb::NodeFactory::Create("C"),
          pvdb::NodeFactory::Create("B"),
          pvdb::NodeFactory::Create("A")
        }
      )
    );
    assert(concept_map);
    v[5] = concept_map;
  }

  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return p; } ));
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::ConceptMap>& p) { return !p; } ) == 0);
  return v;
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif

