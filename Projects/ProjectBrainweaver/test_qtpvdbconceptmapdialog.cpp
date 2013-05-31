#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapdialog.h"

#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

//#include <boost/lambda/lambda.hpp>

#include "pvdbclusterfactory.h"
#include "pvdbcluster.h"
#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbedgefactory.h"
#include "pvdbedge.h"
#include "pvdbexamplefactory.h"
#include "pvdbfile.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptmapitem.h"
#include "qtpvdbconceptmapwidget.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbnodeitem.h"
#include "trace.h"

void QtPvdbConceptMapDialog::Test()
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
  //If this dialog is fed with a file with only a focal question, it will create a one-node concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(question));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);
    QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->WriteToConceptMap()->GetNodes().size() == 1);
  }
  //If this dialog is fed with a file with a cluster and without a concept map (that is, one node (the focal question) only_
  //it will create a concept map from the cluster
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    const boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(question));
    assert(concept_map);
    const boost::shared_ptr<pvdb::Concept> concept_a(pvdb::ConceptFactory::Create("Concept A"));
    const boost::shared_ptr<pvdb::Cluster> cluster(pvdb::ClusterFactory::Create( { concept_a } ));
    file->SetConceptMap(concept_map);
    file->SetCluster(cluster);
    assert(file->GetQuestion() == question);
    const QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->WriteToConceptMap()->GetNodes().size()
      == cluster->Get().size() + 1); //+1 because of focus question
  }
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);

    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( {0,1,2} );
    file->SetCluster(cluster);
    assert(cluster->Get().size() == 3);

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(question));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);
    const QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->WriteToConceptMap()->GetNodes().size()
      == cluster->Get().size() + 1); //+1 because of focus question
    assert(d.GetWidget()->WriteToConceptMap()->GetEdges().size() == 0);
  }
  //If this dialog is fed with a file with a cluster and a concept map
  //it will read the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( { 0,1,2 } );

    file->SetCluster(cluster);

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("Concept F"));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::GetTests().at(3));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::GetTests().at(4));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(question));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::GetTests().at(3));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::GetTests().at(4));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,0,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_e,2.3,4.5,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_f,3.4,5.6,2,false,0,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(
        { node_a, node_b, node_c },
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert(file->GetQuestion() == question);
    const QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->WriteToConceptMap()->GetNodes().size()
      == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    assert(d.GetWidget()->WriteToConceptMap()->GetEdges().size()
      == concept_map->GetEdges().size());
  }
  //If this dialog is fed with a file without a cluster, but with concept map
  //it will read the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::GetTests().at(0));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::GetTests().at(2));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(question));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,0,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_e,2.3,4.5,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_f,3.4,5.6,2,false,0,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(
        { node_a, node_b, node_c },
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert(file->GetQuestion() == question);
    const QtPvdbConceptMapDialog d(file);
    const boost::shared_ptr<pvdb::ConceptMap> concept_map_out
      = d.GetWidget()->WriteToConceptMap();
    assert(concept_map_out->GetNodes().size()
      == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    assert(concept_map_out->GetEdges().size()
      == concept_map->GetEdges().size());
    assert(pvdb::ConceptMap::HasSameContent(concept_map,concept_map_out));
  }

  //If this dialog is fed with a file without a cluster, but with concept map
  //it will read the concept map and alter the node positions. If the dialog is
  //fed with this second concept map, it will keep the nodes in the same place
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::GetTests().at(0));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::GetTests().at(2));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(question));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,0,false,1,true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_e,2.3,4.5,1,false,2,true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_f,3.4,5.6,2,false,0,true));

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(
        { node_a, node_b, node_c },
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);

    //Let the dialog position the nodes
    const QtPvdbConceptMapDialog d(file);
    const boost::shared_ptr<pvdb::ConceptMap> concept_map_out
      = d.GetWidget()->WriteToConceptMap();

    assert(concept_map_out->GetNodes().size()
      == concept_map->GetNodes().size() ); //+0 because focus question is node[0]
    assert(concept_map_out->GetEdges().size()
      == concept_map->GetEdges().size());
    assert(pvdb::ConceptMap::HasSameContent(concept_map,concept_map_out));
    assert(concept_map != concept_map_out
      && "QtConceptMapDialog repositions the nodes");
    //Save the repositioned nodes
    file->Save(pvdb::File::GetTestFileName());

    //Load the repositioned nodes
    const boost::shared_ptr<pvdb::File> file_again = pvdb::File::Load(pvdb::File::GetTestFileName());
    assert(pvdb::ConceptMap::HasSameContent(file->GetConceptMap(),file_again->GetConceptMap()));
    assert(file->GetConceptMap() == file_again->GetConceptMap()
      && "Save and load must yield identical concept maps");

    //Let another dialog keep the node positions in the same place
    const QtPvdbConceptMapDialog d_again(file_again);
    assert(file->GetConceptMap() == file_again->GetConceptMap()
      && "QtPvdbConceptMapDialog must not reposition concept maps");

    std::remove(pvdb::File::GetTestFileName().c_str());
  }

  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::File>& file)
      {
        if (file->GetConceptMap()->GetNodes().size() > 1
          || file->GetCluster()->Empty())
        {
          const boost::shared_ptr<pvdb::ConceptMap> file_concept_map = file->GetConceptMap();
          //Will the concept map remain the same after writing and reading
          const boost::shared_ptr<QtPvdbConceptMapDialog> dialog(new QtPvdbConceptMapDialog(file));
          assert(dialog);
          assert(dialog->GetWidget());
          const boost::shared_ptr<pvdb::ConceptMap> dialog_concept_map = dialog->GetWidget()->WriteToConceptMap();
          assert(dialog_concept_map);
          if (!pvdb::ConceptMap::HasSameContent(dialog_concept_map,file_concept_map))
          {
            TRACE(pvdb::ConceptMap::ToXml(file_concept_map));
            TRACE(pvdb::ConceptMap::ToXml(dialog_concept_map));
          }
          assert(pvdb::ConceptMap::HasSameContent(dialog_concept_map,file_concept_map)
            && "ConceptMap written must have the same content as the ConceptMap read");
        }
      }
    );
  }
  //When putting in each of the heteromorphous concept maps, shuffling it, saving it, loading
  //it, the resulting concept map must be homomorphous with the input map
  {
    const auto v = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
    const int sz = v.size();
    for (int i = 0; i!=sz; ++i)
    {
      //Put a concept maps in dialog, shuffle it, saving it
      {
        const boost::shared_ptr<pvdb::File> file(new pvdb::File);
        assert(v[i]);
        file->SetConceptMap(v[i]);
        QtPvdbConceptMapDialog d(file);
        d.Shuffle();
        d.Save(pvdb::File::GetTestFileName());
      }
      //loading it, the resulting concept map must be homomorphous with the input map
      {
        const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(pvdb::File::GetTestFileName());
        assert(pvdb::ConceptMap::HasSameContent(file->GetConceptMap(),v[i]));
        std::remove(pvdb::File::GetTestFileName().c_str());
      }
    }
  }
  //If the relation is moved, the new locations must be saved
  {
    //Done with Shuffle above
  }
  TRACE("QtPvdbConceptMapDialog::Test completed successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

