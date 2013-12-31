#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "pvdbfilefactory.h"

#include <cassert>
#include "conceptmapfactory.h"
#include "pvdbclusterfactory.h"
#include "conceptmap.h"
#include "pvdbcluster.h"
#include "pvdbclusterfactory.h"
#include "pvdbfile.h"
#include "trace.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::FileFactory::Create()
{
  boost::shared_ptr<pvdb::File> file(new pvdb::File);
  assert(file);
  return file;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::FileFactory::DeepCopy(const boost::shared_ptr<const pvdb::File>& file)
{
  assert(file);

  boost::shared_ptr<pvdb::Cluster> cluster;
  if (file->GetCluster())
  {
    cluster = pvdb::ClusterFactory::DeepCopy(file->GetCluster());
    assert(cluster);
    assert(operator==(*cluster,*file->GetCluster()));
  }

  boost::shared_ptr<ribi::cmap::ConceptMap> concept_map;
  if (file->GetConceptMap())
  {
    concept_map = ribi::cmap::ConceptMapFactory::DeepCopy(file->GetConceptMap());
    assert(concept_map);
    assert(*concept_map == *file->GetConceptMap());
  }

 //assert(!concept_map || file->GetQuestion() == concept_map->GetQuestion()); //BUG20131129
 const boost::shared_ptr<pvdb::File> p(
    new File(
      file->GetAbout(),
      file->GetAssessorName(),
      cluster,
      concept_map,
      file->GetQuestion(),
      file->GetStudentName(),
      file->GetVersion()));
  assert(p);
  assert(file != p && "It must be a DEEP copy");
  assert(operator==(*file,*p) && "It must be a deep COPY");
  return p;
}
#endif
const std::vector<boost::shared_ptr<ribi::pvdb::File> > ribi::pvdb::FileFactory::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::File> > v;
  //[0]: empty file
  {
    v.push_back(Create());
  }
  //[1]: file with focal question
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(0);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    v.push_back(f);
  }
  //[2]: file with complex concept map
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    v.push_back(f);
  }
  //[3]: file with complex concept map and complex cluster
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    f->SetStudentName("ribi::pvdb::FileFactory::GetTests()[3] name");
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory::GetTests().at(3);
    assert(cluster);
    f->SetCluster(cluster);
    v.push_back(f);
  }
  //[4]: file with rated complex concept map and complex cluster
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    f->SetStudentName("ribi::pvdb::FileFactory::GetTests()[4] name");
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(16);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory::GetTests().at(3);
    assert(cluster);
    f->SetCluster(cluster);
    v.push_back(f);
  }
  //[5]: file with rated complex concept map and complex cluster, all multiple lines
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    f->SetStudentName("ribi::pvdb::FileFactory::GetTests()[5] name");
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(17);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory::GetTests().at(3);
    assert(cluster);
    f->SetCluster(cluster);
    v.push_back(f);
  }

  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::File>& p) { return !p; } ) == 0);
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::File>& p) { return p; } ));
  return v;
}



#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
