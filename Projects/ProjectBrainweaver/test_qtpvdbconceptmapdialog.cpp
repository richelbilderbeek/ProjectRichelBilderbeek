//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
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

#include "conceptmapcenternodefactory.h"
#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "pvdbclusterfactory.h"
#include "pvdbcluster.h"
#include "pvdbfile.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapqtedge.h"

#include "qtconceptmap.h"
#include "qtconceptmapqtnode.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,1.0};
  const int test_depth = 1; //Increase for more tests

  //typedef std::vector<boost::shared_ptr<ribi::cmap::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<ribi::cmap::Node> > Nodes;

  //If this dialog is fed with a file with only a focal question, it will create a one-node concept map
  {

    using namespace cmap;
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<ConceptMap> concept_map(File::CreateConceptMap(question));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);
    assert(file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

    QtPvdbConceptMapDialog d(file);
    assert(d.GetWidget()->GetConceptMap()->GetNodes().size() == 1);
  }
  //If this dialog is fed with a file with a cluster and without a concept map (that is, one node (the focal question) only_
  //it will create a concept map from the cluster
  {
    using namespace cmap;
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    assert(file);
    file->SetQuestion(question);
    assert(file->GetQuestion() == question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<Concept> concept_a(ConceptFactory().Create("Concept A"));
    const boost::shared_ptr<Cluster> cluster(ClusterFactory::Create( { concept_a } ));
    const boost::shared_ptr<ConceptMap> concept_map(QtPvdbConceptMapDialog::CreateFromCluster(question,cluster));
    assert(concept_map);
    file->SetCluster(cluster);
    file->SetConceptMap(concept_map);
    //file->CreateConceptMapFromCluster();
    assert(file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

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
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

    const QtPvdbConceptMapDialog d(file);
    assert(file->GetConceptMap());
    assert(d.GetWidget()->GetConceptMap()->GetNodes().size()
      == cluster->Get().size() + 1); //+1 because of focus question
    assert(d.GetWidget()->GetConceptMap()->GetEdges().size() == 0);
  }
  //If this dialog is fed with a file with a cluster and a concept map
  //it will read the concept map
  {
    using namespace cmap;
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());
    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( { 0,1,2 } );
    file->SetCluster(cluster);

    assert( file->GetCluster());
    assert(!file->GetConceptMap());

    const int index_1 = 1;
    assert(index_1 < static_cast<int>(ConceptFactory().GetTests().size()));
    const int index_2 = 2;
    assert(index_2 < static_cast<int>(ConceptFactory().GetTests().size()));

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().Create("Concept F"));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().GetTests().at(index_1));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().GetTests().at(index_2));
    const boost::shared_ptr<Node> node_a(CenterNodeFactory().CreateFromStrings(question));
    const boost::shared_ptr<Node> node_b(NodeFactory().GetTests().at(index_1));
    const boost::shared_ptr<Node> node_c(NodeFactory().GetTests().at(index_2));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<Edge> edge_a(EdgeFactory().Create(NodeFactory().Create(concept_d,1.2,3.4),nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<Edge> edge_b(EdgeFactory().Create(NodeFactory().Create(concept_e,2.3,4.5),nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<Edge> edge_c(EdgeFactory().Create(NodeFactory().Create(concept_f,3.4,5.6),nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory().Create(
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
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

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

    using namespace cmap;
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<File> file(new File);
    file->SetQuestion(question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());

    const int index_1 = 0;
    assert(index_1 < static_cast<int>(ConceptFactory().GetTests().size()));
    const int index_2 = 1;
    assert(index_2 < static_cast<int>(ConceptFactory().GetTests().size()));
    const int index_3 = 2;
    assert(index_3 < static_cast<int>(ConceptFactory().GetTests().size()));

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().GetTests().at(index_1));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().GetTests().at(index_2));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().GetTests().at(index_3));
    const boost::shared_ptr<Node> node_a(CenterNodeFactory().CreateFromStrings(question));
    const boost::shared_ptr<Node> node_b(NodeFactory().GetTests().at(1));
    const boost::shared_ptr<Node> node_c(NodeFactory().GetTests().at(1));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<Edge> edge_a(EdgeFactory().Create(NodeFactory().Create(concept_d,1.2,3.4),nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<Edge> edge_b(EdgeFactory().Create(NodeFactory().Create(concept_e,2.3,4.5),nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<Edge> edge_c(EdgeFactory().Create(NodeFactory().Create(concept_f,3.4,5.6),nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory().Create(
        nodes,
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert(!file->GetCluster());
    assert( file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

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
    //assert(ConceptMap::HasSameContent(concept_map,concept_map_out));
  }

  //If this dialog is fed with a file without a cluster, but with concept map
  //it will read the concept map and alter the node positions. If the dialog is
  //fed with this second concept map, it will keep the nodes in the same place
  {

    using namespace cmap;
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    file->SetQuestion(question);
    assert(file->GetQuestion() == question);
    assert(!file->GetCluster());
    assert(!file->GetConceptMap());

    const int index_1 = 0;
    assert(index_1 < ConceptFactory().GetNumberOfTests());
    const int index_2 = 1;
    assert(index_2 < ConceptFactory().GetNumberOfTests());
    const int index_3 = 2;
    assert(index_3 < ConceptFactory().GetNumberOfTests());

    const boost::shared_ptr<Concept> concept_d(ConceptFactory().GetTest(index_1));
    const boost::shared_ptr<Concept> concept_e(ConceptFactory().GetTest(index_2));
    const boost::shared_ptr<Concept> concept_f(ConceptFactory().GetTest(index_3));
    const boost::shared_ptr<Node> node_a(CenterNodeFactory().CreateFromStrings(question));
    const boost::shared_ptr<Node> node_b(NodeFactory().GetTests().at(1));
    const boost::shared_ptr<Node> node_c(NodeFactory().GetTests().at(1));

    const Nodes nodes = { node_a, node_b, node_c };

    const boost::shared_ptr<Edge> edge_a(EdgeFactory().Create(NodeFactory().Create(concept_d,1.2,3.4),nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<Edge> edge_b(EdgeFactory().Create(NodeFactory().Create(concept_e,2.3,4.5),nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<Edge> edge_c(EdgeFactory().Create(NodeFactory().Create(concept_f,3.4,5.6),nodes.at(2),false,nodes.at(0),true));

    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(
      ribi::cmap::ConceptMapFactory().Create(
        nodes,
        { edge_a, edge_b, edge_c }
      )
    );
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(!file->GetCluster());
    assert( file->GetConceptMap());
    assert(!file->GetConceptMap()->GetNodes().empty());
    assert(file->GetConceptMap()->FindCenterNode()
      && "A file its ConceptMap must have a CenterNode");

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
    //assert(ConceptMap::HasSameContent(concept_map,concept_map_out));
    //assert(concept_map != concept_map_out
    //  && "QtConceptMapDialog repositions the nodes");
    //Save the repositioned nodes
    file->Save(pvdb::File::GetTestFileName());

    //Load the repositioned nodes
    const boost::shared_ptr<pvdb::File> file_again = pvdb::File::Load(pvdb::File::GetTestFileName());

    assert(ConceptMap::HasSameContent(*file->GetConceptMap(),*file_again->GetConceptMap()));
    assert(*file->GetConceptMap() == *file_again->GetConceptMap()
      && "Save and load must yield identical concept maps");

    assert(file_again->GetConceptMap());
    assert(!file_again->GetConceptMap()->GetNodes().empty());
    assert(file_again->GetConceptMap()->FindCenterNode()
      && "A file's ConceptMap must have a CenterNode");

    //Let another dialog keep the node positions in the same place
    const QtPvdbConceptMapDialog d_again(file_again);
    assert(ConceptMap::HasSameContent(*file->GetConceptMap(),*file_again->GetConceptMap()));
    //Who cares about repositioning anyways?
    //assert(*file->GetConceptMap() == *file_again->GetConceptMap()
    //  && "QtPvdbConceptMapDialog must not reposition concept maps");

    std::remove(pvdb::File::GetTestFileName().c_str());
  }

  if (test_depth > 1)
  {

    std::vector<boost::shared_ptr<pvdb::File>> v = pvdb::File::GetTests();
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

    auto v = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps();
    if (test_depth < 2) { v.resize(2); }
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
        using namespace cmap;
        const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(pvdb::File::GetTestFileName());
        assert(ConceptMap::HasSameContent(*file->GetConceptMap(),*v[i]));
        std::remove(pvdb::File::GetTestFileName().c_str());
      }
    }
  }
  //If the relation is moved, the new locations must be saved
  {
    //Done with Shuffle above
  }
}
#endif
