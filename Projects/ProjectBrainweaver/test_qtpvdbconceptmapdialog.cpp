#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbconceptmapdialog.h"

#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/shared_ptr.hpp>

//#include <boost/lambda/lambda.hpp>

#include "conceptmapcenternode.h"
#include "conceptmapcenternodefactory.h"
#include "pvdbclusterfactory.h"
#include "pvdbcluster.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "pvdbfile.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapitem.h"
#include "qtconceptmapwidget.h"
#include "qtconceptmapedgeitem.h"
#include "qtconceptmapnodeitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapDialog::Test()
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

  //typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  //If this dialog is fed with a file with only a focal question, it will create a one-node concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(cmap::ConceptMapFactory::Create(question));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);
    assert(file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->GetConceptMap()->GetNodes().size() == 1);
  }
  //If this dialog is fed with a file with a cluster and without a concept map (that is, one node (the focal question) only_
  //it will create a concept map from the cluster
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    assert(file);
    file->SetQuestion(question);
    assert(file->GetQuestion() == question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<ribi::cmap::Concept> concept_a(cmap::ConceptFactory::Create("Concept A"));
    const boost::shared_ptr<pvdb::Cluster> cluster(pvdb::ClusterFactory::Create( { concept_a } ));
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(pvdb::QtPvdbConceptMapDialog::CreateFromCluster(question,cluster));
    assert(concept_map);
    file->SetCluster(cluster);
    file->SetConceptMap(concept_map);
    //file->CreateConceptMapFromCluster();
    assert(file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());

    assert(d.GetWidget()->GetConceptMap()->GetNodes().size()
      == cluster->Get().size() + 1); //+1 because of focus question

  }
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(file->GetQuestion() == question);

    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( {0,1,2} );
    file->SetCluster(cluster);
    assert(cluster->Get().size() == 3);

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(pvdb::QtPvdbConceptMapDialog::CreateFromCluster(question,cluster));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());
    assert(d.GetWidget()->GetConceptMap()->GetNodes().size()
      == cluster->Get().size() + 1); //+1 because of focus question
    assert(d.GetWidget()->GetConceptMap()->GetEdges().size() == 0);
  }
  //If this dialog is fed with a file with a cluster and a concept map
  //it will read the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( { 0,1,2 } );
    file->SetCluster(cluster);

    assert( file->GetCluster());
    assert(!file->GetConceptMap());

    const boost::shared_ptr<ribi::cmap::Concept> concept_d(cmap::ConceptFactory::Create("Concept F"));
    const boost::shared_ptr<ribi::cmap::Concept> concept_e(cmap::ConceptFactory::GetTests().at(3));
    const boost::shared_ptr<ribi::cmap::Concept> concept_f(cmap::ConceptFactory::GetTests().at(4));
    const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::CenterNodeFactory::Create(question));
    const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::GetTests().at(3));
    const boost::shared_ptr<ribi::cmap::Node> node_c(cmap::NodeFactory::GetTests().at(4));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<ribi::cmap::Edge> edge_a(cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_b(cmap::EdgeFactory::Create(concept_e,2.3,4.5,nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_c(cmap::EdgeFactory::Create(concept_f,3.4,5.6,nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(
        nodes,
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert( file->GetCluster());
    assert( file->GetConceptMap());

    assert(file->GetConceptMap() == concept_map);
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    assert(file->GetQuestion() == question);

    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());
    assert(d.GetWidget()->GetConceptMap() == concept_map);
    assert(d.GetWidget()->GetConceptMap()->GetNodes().size()
      == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    assert(d.GetWidget()->GetConceptMap()->GetEdges().size()
      == concept_map->GetEdges().size());
  }
  //If this dialog is fed with a file without a cluster, but with concept map
  //it will read the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());

    const boost::shared_ptr<ribi::cmap::Concept> concept_d(cmap::ConceptFactory::GetTests().at(0));
    const boost::shared_ptr<ribi::cmap::Concept> concept_e(cmap::ConceptFactory::GetTests().at(1));
    const boost::shared_ptr<ribi::cmap::Concept> concept_f(cmap::ConceptFactory::GetTests().at(2));
    const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::CenterNodeFactory::Create(question));
    const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<ribi::cmap::Node> node_c(cmap::NodeFactory::GetTests().at(1));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<ribi::cmap::Edge> edge_a(cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_b(cmap::EdgeFactory::Create(concept_e,2.3,4.5,nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_c(cmap::EdgeFactory::Create(concept_f,3.4,5.6,nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(
        nodes,
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert(!file->GetCluster());
    assert( file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    assert(file->GetQuestion() == question);
    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());
    assert(d.GetWidget()->GetConceptMap() == concept_map);
    //const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map_out
    //  = d.GetWidget()->GetConceptMap();
    //assert(concept_map_out->GetNodes().size()
    //  == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    //assert(concept_map_out->GetEdges().size()
    //  == concept_map->GetEdges().size());
    //assert(cmap::ConceptMap::HasSameContent(concept_map,concept_map_out));
  }

  //If this dialog is fed with a file without a cluster, but with concept map
  //it will read the concept map and alter the node positions. If the dialog is
  //fed with this second concept map, it will keep the nodes in the same place
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(file->GetQuestion() == question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());

    const boost::shared_ptr<ribi::cmap::Concept> concept_d(cmap::ConceptFactory::GetTests().at(0));
    const boost::shared_ptr<ribi::cmap::Concept> concept_e(cmap::ConceptFactory::GetTests().at(1));
    const boost::shared_ptr<ribi::cmap::Concept> concept_f(cmap::ConceptFactory::GetTests().at(2));
    const boost::shared_ptr<ribi::cmap::Node> node_a(cmap::CenterNodeFactory::Create(question));
    const boost::shared_ptr<ribi::cmap::Node> node_b(cmap::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<ribi::cmap::Node> node_c(cmap::NodeFactory::GetTests().at(1));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<ribi::cmap::Edge> edge_a(cmap::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_b(cmap::EdgeFactory::Create(concept_e,2.3,4.5,nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<ribi::cmap::Edge> edge_c(cmap::EdgeFactory::Create(concept_f,3.4,5.6,nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory::Create(
        nodes,
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(!file->GetCluster());
    assert( file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    //Let the dialog position the nodes
    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());
    assert(concept_map == d.GetWidget()->GetConceptMap());
    //const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map_out
    //  = d.GetWidget()->GetConceptMap();

    //assert(concept_map_out->GetNodes().size()
    //  == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    //assert(concept_map_out->GetEdges().size()
    //  == concept_map->GetEdges().size());
    //assert(cmap::ConceptMap::HasSameContent(concept_map,concept_map_out));
    //assert(concept_map != concept_map_out
    //  && "QtConceptMapDialog repositions the nodes");
    //Save the repositioned nodes
    file->Save(pvdb::File::GetTestFileName());

    //Load the repositioned nodes
    const boost::shared_ptr<pvdb::File> file_again = pvdb::File::Load(pvdb::File::GetTestFileName());

    assert(cmap::ConceptMap::HasSameContent(*file->GetConceptMap(),*file_again->GetConceptMap()));
    assert(IsEqual(*file->GetConceptMap(),*file_again->GetConceptMap())
      && "Save and load must yield identical concept maps");

    assert(file_again->GetConceptMap());
    assert(!file_again->GetConceptMap()->GetNodes().empty());
    assert(boost::dynamic_pointer_cast<cmap::CenterNode>(file_again->GetConceptMap()->GetNodes()[0])
      && "The first node in a file's ConceptMap must be a CenterNode");

    //Let another dialog keep the node positions in the same place
    const QtPvdbConceptMapDialog d_again(file_again);
    assert(IsEqual(*file->GetConceptMap(),*file_again->GetConceptMap())
      && "QtPvdbConceptMapDialog must not reposition concept maps");

    std::remove(pvdb::File::GetTestFileName().c_str());
  }

  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::File>& file)
      {
        const bool had_cluster = file->GetCluster().get();
        const bool had_concept_map = file->GetConceptMap().get();
        const boost::shared_ptr<QtPvdbConceptMapDialog> dialog(new QtPvdbConceptMapDialog(file));

        if (!had_cluster && !had_concept_map)
        {
          assert(!file->GetCluster());
          assert( file->GetConceptMap()); //Created
        }
        if ( had_cluster && !had_concept_map)
        {
          assert( file->GetCluster());
          assert( file->GetConceptMap()); //Created from concept map
        }
        if (!had_cluster &&  had_concept_map)
        {
          assert(!file->GetCluster());
          assert( file->GetConceptMap());
        }
        if ( had_cluster &&  had_concept_map)
        {
          assert( file->GetCluster());
          assert( file->GetConceptMap());
        }
      }
    );
  }
  //When putting in each of the heteromorphous concept maps, shuffling it, saving it, loading
  //it, the resulting concept map must be homomorphous with the input map
  {
    const auto v = ribi::cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
    const int sz = v.size();
    for (int i = 0; i!=sz; ++i)
    {
      //Put a concept maps in dialog, shuffle it, saving it
      {
        const boost::shared_ptr<pvdb::File> file(new pvdb::File);
        assert(v[i]);
        file->SetConceptMap(v[i]);
        QtPvdbConceptMapDialog d(file);
        assert(file->GetConceptMap());
        d.Shuffle();
        d.Save(pvdb::File::GetTestFileName());
      }
      //loading it, the resulting concept map must be homomorphous with the input map
      {
        const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(pvdb::File::GetTestFileName());
        assert(cmap::ConceptMap::HasSameContent(*file->GetConceptMap(),*v[i]));
        std::remove(pvdb::File::GetTestFileName().c_str());
      }
    }
  }
  //If the relation is moved, the new locations must be saved
  {
    //Done with Shuffle above
  }
  TRACE("ribi::pvdb::QtPvdbConceptMapDialog::Test completed successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
