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

ribi::pvdb::FileFactory::FileFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::FileFactory::Create() const noexcept
{
  boost::shared_ptr<pvdb::File> file(new pvdb::File);
  assert(file);
  return file;
}

#ifndef NDEBUG
boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::FileFactory::DeepCopy(const boost::shared_ptr<const pvdb::File>& file) const noexcept
{
  assert(file);

  boost::shared_ptr<pvdb::Cluster> cluster;
  if (file->GetCluster())
  {
    cluster = pvdb::ClusterFactory().DeepCopy(file->GetCluster());
    assert(cluster);
    assert(operator==(*cluster,*file->GetCluster()));
  }

  boost::shared_ptr<ribi::cmap::ConceptMap> concept_map;
  if (file->GetConceptMap())
  {
    concept_map = ribi::cmap::ConceptMapFactory().DeepCopy(file->GetConceptMap());
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


std::vector<boost::shared_ptr<ribi::pvdb::File> > ribi::pvdb::FileFactory::GetTests() const noexcept
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
      = cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(0);
    if (!concept_map->GetNodes().empty())
    {
      assert(concept_map);
      f->SetConceptMap(concept_map);
      v.push_back(f);
    }
  }
  //[2]: file with complex concept map
  {
    boost::shared_ptr<pvdb::File> f = Create();
    assert(f);
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(15);
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
      = cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory().GetTests().at(3);
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
      = cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(16);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory().GetTests().at(3);
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
      = cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(17);
    assert(concept_map);
    f->SetConceptMap(concept_map);
    const boost::shared_ptr<pvdb::Cluster> cluster
      = ClusterFactory().GetTests().at(3);
    assert(cluster);
    f->SetCluster(cluster);
    v.push_back(f);
  }

  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::File>& p) { return !p; } ) == 0);
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::File>& p) { return p; } ));
  return v;
}

#ifndef NDEBUG
void ribi::pvdb::FileFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  FileFactory f;
  assert(f.GetNumberOfTests() == static_cast<int>(f.GetTests().size()));
  assert(!"Green");
}
#endif
