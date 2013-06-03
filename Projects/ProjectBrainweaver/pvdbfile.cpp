#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QRegExp>

#include "pvdbcluster.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbfilefactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmap.h"
#include "pvdbhelper.h"
#include "trace.h"
#include "pvdbclusterfactory.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const std::string pvdb::File::m_filename_extension = "cmp";

pvdb::File::File()
  : m_about("ProjectVanDenBogaart"),
    m_assessor_name(""),
    m_cluster(),
    m_concept_map(), //nullptr
    m_student_name(""),
    m_version("0.3")
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(!m_cluster);
  assert(!m_concept_map);
}

pvdb::File::File(
  const std::string& about,
  const std::string& assessor_name,
  const boost::shared_ptr<pvdb::Cluster>& cluster,
  const boost::shared_ptr<pvdb::ConceptMap>& concept_map,
  const std::string& student_name,
  const std::string& version)
  : m_about(about),
    m_assessor_name(assessor_name),
    m_cluster(cluster),
    m_concept_map(concept_map),
    m_student_name(student_name),
    m_version(version)
{
  #ifndef NDEBUG
  Test();
  assert(!concept_map || this->GetQuestion() == concept_map->GetQuestion());
  #endif
}

void pvdb::File::AutoSave() const
{
  this->Save("autosave1." + m_filename_extension);
  this->Save("autosave2." + m_filename_extension);
}

const std::string pvdb::File::ConvertFrom_0_1(const std::string& s)
{
  //Put <examples> around existing <example> tags
  const std::string a = boost::algorithm::replace_all_copy(s,"</name><example>","</name><examples><example>");
  const std::string b = boost::algorithm::replace_all_copy(a,"</example></concept>","</example></examples></concept>");
  const std::string c = boost::algorithm::replace_all_copy(b,"<example>","<e$xample><text>");
  const std::string d = boost::algorithm::replace_all_copy(c,"</example>","</text><competency>uninitialized</competency></e$xample>");
  const std::string e = boost::algorithm::replace_all_copy(d,"</examples></concept>","</examples><complexity>-1</complexity><concreteness>-1</concreteness><specificity>-1</specificity></concept>");
  //Add <examples> when no <example> tags are present
  const std::string f = boost::algorithm::replace_all_copy(e,"</name></concept>","</name><examples></examples><complexity>-1</complexity><concreteness>-1</concreteness><specificity>-1</specificity></concept>");
  const std::string g = boost::algorithm::replace_all_copy(f,"$","");
  const std::string h = boost::algorithm::replace_all_copy(f,"<version>0.1</version>","<version>0.2</version>");
  return h;
}

const std::string pvdb::File::ConvertFrom_0_2(const std::string& s)
{
  const std::string a = boost::algorithm::replace_all_copy(s,"</about><cluster>","</about><assessor_name></assessor_name><cluster>");
  return a;
}

/*
void pvdb::File::CreateConceptMapFromCluster()
{
  assert(GetCluster());
  assert(GetConceptMap());
  assert(GetConceptMap()->Empty());

  GetConceptMap()->ReadFromCluster(
    file->GetConceptMap()->GetQuestion(),
    file->GetCluster());

  // = pvdb::ConceptMapFactory::CreateFromCluster(
  //    file->GetConceptMap()->GetQuestion(),
  //    file->GetCluster()
  //  );
  assert((file->GetCluster()->Get().size() + 1)
    == (concept_map->GetNodes().size())
    && "As much cluster items as nodes + focus question");
}
*/

const std::string pvdb::File::FileToStr(const std::string& filename)
{
  assert(QFile::exists(filename.c_str()));
  std::string s;
  std::ifstream in(filename.c_str());
  while (!in.eof())
  {
    std::string t;
    std::getline(in,t);
    s+=t;
  }
  return s;
}

const boost::shared_ptr<pvdb::File> pvdb::File::FromXml(const std::string &s)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<file>"));
  assert(s.substr(s.size() - 7,7) == std::string("</file>"));

  boost::shared_ptr<pvdb::File> f(new File);
  //m_about_str
  {
    const std::vector<std::string> v
      = pvdb::GetRegexMatches(s,QRegExp("(<about>.*</about>)"));
    assert(v.size() == 1);
    f->m_about = pvdb::StripXmlTag(v[0]);
  }
  //m_assessor_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<assessor_name>.*</assessor_name>)"));
    assert(v.size() == 1);
    f->m_assessor_name = pvdb::StripXmlTag(v[0]);
  }
  //m_cluster
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<cluster>.*</cluster>)"));
    if (!v.empty())
    {
      assert(v.size() == 1);
      f->m_cluster = Cluster::FromXml(v[0]);
    }
    else
    {
      //No cluster yet
    }
  }
  //m_concept_map
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<concept_map>.*</concept_map>)"));
    if (!v.empty())
    {
      assert(v.size() == 1);
      f->m_concept_map = ConceptMapFactory::FromXml(v[0]);
    }
    else
    {
      //No concept map yet
    }
  }
  //m_student_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<student_name>.*</student_name>)"));
    assert(v.size() == 1);
    f->m_student_name = pvdb::StripXmlTag(v[0]);
  }
  assert(GetRegexMatches(s,QRegExp("(<question>.*</question>)")).empty()
    && "Must be obsolete");
  //m_version
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    f->m_version = pvdb::StripXmlTag(v[0]);
  }
  return f;
}

const std::string pvdb::File::GetQuestion() const
{
  if (m_concept_map)
  {
    assert(m_concept_map);
    return m_concept_map->GetQuestion();
  }
  else
  {
    return "";
  }
}

const std::string pvdb::File::GetTempFileName()
{
  return std::string("tmp.") + m_filename_extension;
}

const std::string pvdb::File::GetTestFileName()
{
  return std::string("test.") + m_filename_extension;
}

const std::vector<boost::shared_ptr<pvdb::File> > pvdb::File::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::File> > v;
  const std::vector<boost::shared_ptr<pvdb::Cluster> > clusters = pvdb::ClusterFactory::GetTests();
  assert(std::count_if(clusters.begin(),clusters.end(),[](const boost::shared_ptr<pvdb::Cluster>& p) { return !p; } ) == 0);
  //assert(std::all_of(clusters.begin(),clusters.end(),[](const boost::shared_ptr<pvdb::Cluster>& p) { return p; } )); //Do not use std::all_of when crosscompiling
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > concept_maps = pvdb::ConceptMapFactory::GetAllTests();
  const int n_clusters = static_cast<int>(clusters.size());
  const int n_concept_maps = static_cast<int>(concept_maps.size());
  for (int cluster=0; cluster!=n_clusters; ++cluster)
  {
    for (int concept_map=0; concept_map!=n_concept_maps; ++concept_map)
    {
      const std::string about = "about";
      const std::string assessor_name = "assessor_name";
      const std::string student_name = "student_name";
      const std::string version = "version";
      boost::shared_ptr<pvdb::File> file(new File(
        about,
        assessor_name,
        clusters[cluster],
        concept_maps[concept_map],
        student_name,
        version));
      v.push_back(file);
    }
  }
  return v;
}

const boost::shared_ptr<pvdb::File> pvdb::File::Load(const std::string &filename)
{
  std::string xml;
  //Read XML from file
  {
    const std::vector<std::string> v = pvdb::FileToVector(filename);
    assert(v.size() <= 2); //Allow empty line after text, due to difference in line ending
    xml = v[0];
  }
  //Backwards compatiblity with file format version 0.1
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(xml,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    const std::string version = pvdb::StripXmlTag(v[0]);
    if (version == std::string("0.1"))
    {
      xml = ConvertFrom_0_1(xml);
    }
  }
  //Backwards compatiblity with file format version 0.2
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(xml,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    const std::string version = pvdb::StripXmlTag(v[0]);
    if (version == std::string("0.2"))
    {
      xml = ConvertFrom_0_2(xml);
    }
  }

  const boost::shared_ptr<pvdb::File> file = pvdb::File::FromXml(xml);
  assert(file);
  return file;
}

void pvdb::File::Save(const std::string &filename) const
{
  //
  //Check for correct extension
  if (!(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == m_filename_extension))
  {
    TRACE(filename);
  }
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == m_filename_extension
    && "File must have correct file extension name");
  {
    std::ofstream f(filename.c_str());
    const std::string s = ToXml(*this);
    f << s;
  }
  #ifndef NDEBUG
  //Check if load results in the same File
  {
    const std::vector<std::string> v = pvdb::FileToVector(filename);
    assert(v.size() == 1 && "File must have one line of XML");
  }
  #endif
}

void pvdb::File::SetAssessorName(const std::string& assessor_name)
{
  assert(assessor_name.size() > 1);
  m_assessor_name = assessor_name;
  this->AutoSave();
}

void pvdb::File::SetConceptMap(const boost::shared_ptr<pvdb::ConceptMap> concept_map)
{
  assert(concept_map);
  assert(!m_concept_map);
  m_concept_map = concept_map;
  this->AutoSave();
}

void pvdb::File::SetCluster(const boost::shared_ptr<pvdb::Cluster>& cluster)
{
  assert(cluster);
  //assert(!m_cluster); //Don't care
  m_cluster = cluster;
  this->AutoSave();
}

void pvdb::File::SetStudentName(const std::string& student_name)
{
  assert(student_name.size() > 1);
  m_student_name = student_name;
  this->AutoSave();
}

#ifndef NDEBUG
void pvdb::File::Test()
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
  TRACE("Started pvdb::File::Test");
  const std::string tmp_filename = pvdb::File::GetTempFileName();
  //Test copy constructor
  {
    const boost::shared_ptr<pvdb::File> f(new File);
    f->SetAssessorName("debug assessor name");
    f->SetStudentName("debug student name");
    const boost::shared_ptr<pvdb::File> g = pvdb::FileFactory::DeepCopy(f);
    assert(f == g);
    //Modify g, to test operator!=
    g->SetStudentName( f->GetStudentName() + " (modified)");
    assert(f != g);
    g->SetStudentName( f->GetStudentName());
    assert(f == g);
    g->SetAssessorName( f->GetAssessorName() + " (modified)");
    assert(f != g);
    g->SetAssessorName( f->GetAssessorName());
    assert(f == g);
  }
  //Test Save/Load on empty File
  {
    boost::shared_ptr<pvdb::File> firstfile(new File);
    firstfile->Save(tmp_filename);
    const boost::shared_ptr<pvdb::File> secondfile(File::Load(tmp_filename));
    assert(firstfile->GetQuestion() == secondfile->GetQuestion());
    assert(firstfile == secondfile);
    //Modify f, to test operator!=
    firstfile->SetStudentName( firstfile->GetStudentName() + " (modified)");
    assert(firstfile != secondfile);
  }
  //Test Save/Load on file
  {
    boost::shared_ptr<pvdb::File> firstfile(new pvdb::File);
    firstfile->SetStudentName("Richel Bilderbeek");
    const std::string question = "Focal question?";
    {
      const boost::shared_ptr<pvdb::ConceptMap> concept_map
        = pvdb::ConceptMapFactory::Create(question);
      firstfile->SetConceptMap(concept_map);
    }
    //firstfile->SetQuestion("Focal question?");
    assert(firstfile->GetQuestion() == question);
    firstfile->Save(tmp_filename.c_str());
    assert(firstfile->GetQuestion() == question);
    const boost::shared_ptr<pvdb::File> second_file(File::Load(tmp_filename));
    assert(second_file);
    #ifndef NDEBUG
    if (second_file->GetQuestion() != firstfile->GetQuestion())
    {
      firstfile->Save("a.cmp");
      second_file->Save("b.cmp");
      TRACE(firstfile->GetQuestion());
      TRACE(second_file->GetQuestion());
    }
    #endif
    assert(second_file->GetQuestion() == firstfile->GetQuestion());
    assert(firstfile == second_file);
    //Modify f, to test operator!=
    firstfile->SetStudentName( firstfile->GetStudentName() + " (modified)");
    assert(firstfile != second_file);
  }
  {
    for (int i=1; i!=5; ++i)
    {
      const std::string filename = boost::lexical_cast<std::string>(i) + ".cmp";
      if (!QFile::exists(filename.c_str()))
      {
        //Copy the file from Qt resources to local file
        {
          const std::string qtfilename = ":/files/" + filename;
          QFile qtfile(qtfilename.c_str());
          qtfile.copy(filename.c_str());
          qtfile.close();
        }
        assert(QFile::exists(filename.c_str()));

        QFile file(filename.c_str());

        const bool success = file.setPermissions(
            QFile::ReadOwner
          | QFile::WriteOwner
          | QFile::ExeOwner
          | QFile::ReadUser
          | QFile::WriteUser
          | QFile::ExeUser
          | QFile::ReadGroup
          | QFile::WriteGroup
          | QFile::ExeGroup
          | QFile::ReadOther
          | QFile::WriteOther
          | QFile::ExeOther
          );
        assert(success);
        if (!success) { std::clog << "pvdb::File::Test(): Warning: !succes\n"; }
        file.open(QFile::ReadWrite);
        assert(file.isOpen());
        assert(file.isReadable());
        assert(file.isWritable());
        assert(file.size() > 0);
        file.close();

        assert(QFile::exists(filename.c_str()));
        pvdb::File::Load(filename);
        std::remove(filename.c_str());

        assert(!QFile::exists(filename.c_str()));
      }
    }
  }
  TRACE("File::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

const std::string pvdb::File::ToXml(const File& file)
{
  //assert(file.m_cluster);
  //assert(file.m_concept_map);

  std::stringstream s;
  s << "<file>";
  s << "<about>" << file.GetAbout() << "</about>";
  s << "<assessor_name>" << file.GetAssessorName() << "</assessor_name>";
  if (file.GetCluster()   ) s << Cluster::ToXml(file.GetCluster());
  if (file.GetConceptMap()) s << ConceptMap::ToXml(file.GetConceptMap());
  s << "<student_name>" << file.GetStudentName() << "</student_name>";
  s << "<version>" << file.GetVersion() << "</version>";
  s << "</file>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == std::string("<file>"));
  assert(r.substr(r.size() - 7,7) == std::string("</file>"));

  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::File& lhs, const pvdb::File& rhs)
{
  //assert(lhs.GetCluster());
  //assert(lhs.GetConceptMap());
  //assert(rhs.GetCluster());
  //assert(rhs.GetConceptMap());
  return
     lhs.GetAssessorName() == rhs.GetAssessorName()
  && (
       (!lhs.GetCluster() && !rhs.GetCluster())
      || IsEqual(*lhs.GetCluster(),*rhs.GetCluster())
     )
  && (
       (!lhs.GetConceptMap() && !rhs.GetConceptMap())
       || IsEqual(*lhs.GetConceptMap(),*rhs.GetConceptMap())
     )
  && lhs.GetStudentName() == rhs.GetStudentName()
  && lhs.GetVersion() == rhs.GetVersion();
}

bool operator==(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs)
{
  assert(lhs);
  //assert(lhs->GetCluster());
  //assert(lhs->GetConceptMap());
  assert(rhs);
  //assert(rhs->GetCluster());
  //assert(rhs->GetConceptMap());
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs)
{
  return boost::shared_ptr<const pvdb::File>(lhs) == boost::shared_ptr<const pvdb::File>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs)
{
  return boost::shared_ptr<const pvdb::File>(lhs) == boost::shared_ptr<const pvdb::File>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs)
{
  return boost::shared_ptr<const pvdb::File>(lhs) == boost::shared_ptr<const pvdb::File>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs)
{
  return !(lhs == rhs);
}


} //~namespace pvdb
