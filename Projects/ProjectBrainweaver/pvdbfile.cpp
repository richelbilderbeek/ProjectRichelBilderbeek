#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "pvdbfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QFile>
#include <QRegExp>

#include "conceptmapcenternode.h"
#include "pvdbclusterfactory.h"
#include "pvdbcluster.h"
#include "conceptmapconcept.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "fileio.h"
#include "pvdbfilefactory.h"
#include "pvdbhelper.h"
#include "conceptmapnode.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const std::string ribi::pvdb::File::m_filename_extension = "cmp";

ribi::pvdb::File::File()
  : m_about("ProjectVanDenBogaart"),
    m_assessor_name(""),
    m_cluster(),
    m_concept_map(), //nullptr
    m_question(""),
    m_student_name(""),
    m_version("0.4")
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(!m_cluster);
  assert(!m_concept_map);
}

ribi::pvdb::File::File(
  const std::string& about,
  const std::string& assessor_name,
  const boost::shared_ptr<pvdb::Cluster>& cluster,
  const boost::shared_ptr<ribi::cmap::ConceptMap>& concept_map,
  const std::string& question,
  const std::string& student_name,
  const std::string& version)
  : m_about(about),
    m_assessor_name(assessor_name),
    m_cluster(cluster),
    m_concept_map(concept_map),
    m_question(question),
    m_student_name(student_name),
    m_version(version)
{
  #ifndef NDEBUG
  Test();
  //assert(!concept_map || this->GetQuestion() == concept_map->GetQuestion()); //BUG20131129
  #endif
}

void ribi::pvdb::File::AutoSave() const
{
  this->Save("autosave1." + m_filename_extension);
  this->Save("autosave2." + m_filename_extension);
}

const std::string ribi::pvdb::File::ConvertFrom_0_1(const std::string& s)
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

const std::string ribi::pvdb::File::ConvertFrom_0_2(const std::string& s)
{
  const std::string a = boost::algorithm::replace_all_copy(s,"</about><cluster>","</about><assessor_name></assessor_name><cluster>");
  const std::string b = boost::algorithm::replace_all_copy(a,"<version>0.2</version>","<version>0.3</version>");
  return b;
}

const std::string ribi::pvdb::File::ConvertFrom_0_3(const std::string& s)
{
  const std::string a
    = boost::algorithm::replace_all_copy(s,"<about>ProjectVanDenBogaart</about>","<about>Brainweaver</about>");
  const std::string b = boost::algorithm::replace_all_copy(a,"<version>0.3</version>","<version>0.4</version>");
  //Copy the question from the concept map
  const std::string question = DoXpressiveRegexReplace(
    b,
    "<concept_map><nodes><node><concept><name>(.*)</name></concept>",
    "$1");
  const std::string c = boost::algorithm::replace_all_copy(b,"</concept_map><student_name>"
    , std::string("</concept_map><question>") + question + "</question><student_name>");


  const std::string d
    = boost::algorithm::replace_all_copy(c,
      "</competency></example>",
      "</competency><is_complex>1</is_complex><is_concrete>1</is_concrete><is_specific>1</is_specific></example>");

  const std::string e
    = boost::algorithm::replace_all_copy(d,
      "</examples><complexity>",
      "</examples><concept_is_complex>1</concept_is_complex><complexity>");

  return e;
}

const std::string ribi::pvdb::File::FileToStr(const std::string& filename)
{
  assert(fileio::IsRegularFile(filename.c_str()));
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

const boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::File::FromXml(const std::string &s)
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
    f->m_about = ribi::xml::StripXmlTag(v[0]);
  }
  //m_assessor_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<assessor_name>.*</assessor_name>)"));
    assert(v.size() == 1);
    f->m_assessor_name = ribi::xml::StripXmlTag(v[0]);
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
      f->m_concept_map = cmap::ConceptMapFactory::FromXml(v[0]);
    }
    else
    {
      //No concept map yet
    }
  }
  //m_question
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<question>.*</question>)"));
    if (v.empty())
    {
      TRACE(s);
      TRACE("Sometimes, this happens at the first startup and ");
    }
    assert(!v.empty());
    assert(v.size() == 1);
    f->m_question = ribi::xml::StripXmlTag(v[0]);
  }
  //m_student_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<student_name>.*</student_name>)"));
    assert(v.size() == 1);
    f->m_student_name = ribi::xml::StripXmlTag(v[0]);
  }
  //m_version
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    f->m_version = ribi::xml::StripXmlTag(v[0]);
  }

  assert( (!f->GetConceptMap() || !f->GetConceptMap()->GetNodes().empty() )
    && "Either a file has no concept map or it has at least one node");
  assert( (!f->GetConceptMap() || boost::dynamic_pointer_cast<cmap::CenterNode>(f->GetConceptMap()->GetNodes()[0]) )
    && "Either a file has no concept map or the first node in a file's ConceptMap is be a CenterNode");

  return f;
}

const std::string ribi::pvdb::File::GetQuestion() const
{
  return m_question;
}

const std::string ribi::pvdb::File::GetTempFileName()
{
  return std::string("tmp.") + m_filename_extension;
}

const std::string ribi::pvdb::File::GetTestFileName()
{
  return std::string("test.") + m_filename_extension;
}

const std::vector<boost::shared_ptr<ribi::pvdb::File> > ribi::pvdb::File::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::File> > v;
  const int n_clusters = static_cast<int>(pvdb::ClusterFactory::GetTests().size());
  const int n_concept_maps = static_cast<int>(cmap::ConceptMapFactory::GetAllTests().size());
  for (int cluster_index=0; cluster_index!=n_clusters; ++cluster_index)
  {
    for (int concept_map_index=0; concept_map_index!=n_concept_maps; ++concept_map_index)
    {
      const std::string about = "about";
      const std::string assessor_name = "assessor_name";
      std::string question = "question";
      const std::string student_name = "student_name";
      const std::string version = "version";
      const auto cluster = pvdb::ClusterFactory::GetTests()[cluster_index];
      const auto concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[concept_map_index];
      if (concept_map)
      {
        assert(!concept_map->GetNodes().empty());
        question = concept_map->GetNodes()[0]->GetConcept()->GetName();
      }
      //assert(!concept_map || question == concept_map->GetQuestion()); //BUG20131129
      boost::shared_ptr<pvdb::File> file(new File(
        about,
        assessor_name,
        cluster,
        concept_map,
        question,
        student_name,
        version));
      v.push_back(file);
    }
  }
  return v;
}

const boost::shared_ptr<ribi::pvdb::File> ribi::pvdb::File::Load(const std::string &filename)
{
  std::string xml;
  //Read XML from file
  {
    const std::vector<std::string> v = pvdb::SafeFileToVector(filename);
    //FileToVector allowed an empty line after text, due to difference in line ending
    //SafeFileToVector should remove this line
    assert(v.size() == 1);
    xml = v[0];
  }
  //Backwards compatiblity with file format version 0.1
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(xml,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    const std::string version = ribi::xml::StripXmlTag(v[0]);
    if (version == std::string("0.1"))
    {
      xml = ConvertFrom_0_1(xml);
    }
  }
  //Backwards compatiblity with file format version 0.2
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(xml,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    const std::string version = ribi::xml::StripXmlTag(v[0]);
    if (version == std::string("0.2"))
    {
      xml = ConvertFrom_0_2(xml);
    }
  }
  //Backwards compatiblity with file format version 0.3
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(xml,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    const std::string version = ribi::xml::StripXmlTag(v[0]);
    if (version == std::string("0.3"))
    {
      xml = ConvertFrom_0_3(xml);
    }
  }

  const boost::shared_ptr<pvdb::File> file = ribi::pvdb::File::FromXml(xml);
  assert(file);

  assert( (!file->GetConceptMap() || !file->GetConceptMap()->GetNodes().empty() )
    && "Either a file has no concept map or it has at least one node");
  assert( (!file->GetConceptMap() || boost::dynamic_pointer_cast<cmap::CenterNode>(file->GetConceptMap()->GetNodes()[0]) )
    && "Either a file has no concept map or the first node in a file's ConceptMap is be a CenterNode");

  return file;
}

void ribi::pvdb::File::Save(const std::string &filename) const
{
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
    const std::vector<std::string> v = pvdb::SafeFileToVector(filename);
    if (v.size() != 1) { TRACE(v.size()); TRACE(filename); }
    assert(v.size() == 1 && "File must have one line of XML");
  }
  #endif
}

void ribi::pvdb::File::SetAssessorName(const std::string& assessor_name)
{
  assert(assessor_name.size() > 1);
  m_assessor_name = assessor_name;
  this->AutoSave();
}

void ribi::pvdb::File::SetConceptMap(const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map)
{
  assert(!m_concept_map && "Can only set when there is no concept map present yet");
  m_concept_map = concept_map;
  assert(!m_concept_map->GetNodes().empty());
  assert(boost::dynamic_pointer_cast<cmap::CenterNode>(m_concept_map->GetNodes()[0])
    && "The first node in a file's ConceptMap must be a CenterNode");
  this->AutoSave();
}

void ribi::pvdb::File::SetCluster(const boost::shared_ptr<pvdb::Cluster>& cluster)
{
  assert(cluster);
  //Don't care: m_cluster will be overwritten more often,
  //because the TreeWidget has no Model/View architecture: the resulting
  //cluster is allocated new and calculated every save
  //assert(!m_cluster);

  m_cluster = cluster;
  this->AutoSave();
}

void ribi::pvdb::File::SetQuestion(const std::string& question)
{
  assert(question.size() > 0);
  m_question = question;
  this->AutoSave();
}

void ribi::pvdb::File::SetStudentName(const std::string& student_name)
{
  assert(student_name.size() > 1);
  m_student_name = student_name;
  this->AutoSave();
}

#ifndef NDEBUG
void ribi::pvdb::File::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::pvdb::File::Test");
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  //Test copy constructor
  {
    const boost::shared_ptr<pvdb::File> f(new File);
    f->SetAssessorName("debug assessor name");
    f->SetStudentName("debug student name");
    const boost::shared_ptr<pvdb::File> g = pvdb::FileFactory::DeepCopy(f);
    assert(f != g);
    assert(operator==(*f,*g));
    //Modify g, to test operator!=
    g->SetStudentName( f->GetStudentName() + " (modified)");
    assert(!operator==(*f,*g));
    g->SetStudentName( f->GetStudentName());
    assert(operator==(*f,*g));
    g->SetAssessorName( f->GetAssessorName() + " (modified)");
    assert(!operator==(*f,*g));
    g->SetAssessorName( f->GetAssessorName());
    assert(operator==(*f,*g));
  }
  //Test Save/Load on empty File
  {
    boost::shared_ptr<pvdb::File> firstfile(new File);
    firstfile->Save(tmp_filename);
    const boost::shared_ptr<pvdb::File> secondfile(File::Load(tmp_filename));
    assert(firstfile->GetQuestion() == secondfile->GetQuestion());
    assert(firstfile != secondfile);
    assert(operator==(*firstfile,*secondfile));
    //Modify f, to test operator!=
    firstfile->SetStudentName( firstfile->GetStudentName() + " (modified)");
    assert(!operator==(*firstfile,*secondfile));
  }
  //Test Save/Load on file
  {
    boost::shared_ptr<pvdb::File> firstfile(new pvdb::File);
    firstfile->SetStudentName("Richel Bilderbeek");
    const std::string question = "Focal question?";
    {
      const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
        = ribi::cmap::ConceptMapFactory::Create(question);
      assert(!concept_map->GetNodes().empty());
      assert(boost::dynamic_pointer_cast<cmap::CenterNode>(concept_map->GetNodes()[0])
        && "The first node in a file's ConceptMap must be a CenterNode");

      firstfile->SetConceptMap(concept_map);
    }
    firstfile->SetQuestion("Focal question?");
    assert(firstfile->GetQuestion() == question);
    firstfile->Save(tmp_filename.c_str());
    assert(firstfile->GetQuestion() == question);
    const boost::shared_ptr<pvdb::File> second_file(File::Load(tmp_filename));
    assert(second_file);
    assert(second_file->GetQuestion() == firstfile->GetQuestion());
    assert(operator==(*firstfile,*second_file));
    //Modify f, to test operator!=
    firstfile->SetStudentName( firstfile->GetStudentName() + " (modified)");
    assert(!operator==(*firstfile,*second_file));
  }
  {
    ///Continue loop until no file is found
    for (int i=0; i!=100; ++i)
    {
      //Testing filenames start at 1
      const std::string filename = boost::lexical_cast<std::string>(i) + ".cmp";
      if (!fileio::IsRegularFile(filename))
      {
        //Copy the file from Qt resources to local file
        {
          const std::string qtfilename = ":/files/" + filename;
          QFile qtfile(qtfilename.c_str());
          qtfile.copy(filename.c_str());
          qtfile.close();
        }
        if (!fileio::IsRegularFile(filename))
        {
          //TRACE("First filename not found: ");
          //TRACE(filename);
          continue;
        }

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
        file.open(QFile::ReadWrite);
        assert(file.isOpen());
        assert(file.isReadable());
        assert(file.isWritable());
        assert(file.size() > 0);
        file.close();

        assert(fileio::IsRegularFile(filename));
        ribi::pvdb::File::Load(filename);
        std::remove(filename.c_str());

        assert(!fileio::IsRegularFile(filename));
      }
    }
  }
  TRACE("File::Test finished successfully");
}
#endif

const std::string ribi::pvdb::File::ToXml(const File& file)
{
  //assert(file.m_cluster);
  //assert(file.m_concept_map);

  std::stringstream s;
  s << "<file>";
  s << "<about>" << file.GetAbout() << "</about>";
  s << "<assessor_name>" << file.GetAssessorName() << "</assessor_name>";
  if (file.GetCluster()   ) s << Cluster::ToXml(file.GetCluster());
  if (file.GetConceptMap()) s << cmap::ConceptMap::ToXml(file.GetConceptMap());
  s << "<question>" << file.GetQuestion() << "</question>";
  s << "<student_name>" << file.GetStudentName() << "</student_name>";
  s << "<version>" << file.GetVersion() << "</version>";
  s << "</file>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == std::string("<file>"));
  assert(r.substr(r.size() - 7,7) == std::string("</file>"));

  return r;
}

const std::string ribi::pvdb::File::DoXpressiveRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str)
{
  try
  {
    return boost::xpressive::regex_replace(
      str,
      boost::xpressive::sregex(boost::xpressive::sregex::compile(regex_str)),
      format_str,
      boost::xpressive::regex_constants::match_default
        | boost::xpressive::regex_constants::format_all
        | boost::xpressive::regex_constants::format_no_copy);
  }
  catch (boost::xpressive::regex_error& e)
  {
    const std::string s
      = "boost::xpressive::regex_error: " + std::string(e.what());
    TRACE(str);
    TRACE(regex_str);
    TRACE(format_str);
    TRACE(s);
    assert(!"Should not get here");
    throw std::logic_error(s.c_str());
  }
}

bool ribi::pvdb::operator==(const pvdb::File& lhs, const pvdb::File& rhs)
{
  //assert(lhs.GetCluster());
  //assert(lhs.GetConceptMap());
  //assert(rhs.GetCluster());
  //assert(rhs.GetConceptMap());
  return
     lhs.GetAssessorName() == rhs.GetAssessorName()
  && (
       (!lhs.GetCluster() && !rhs.GetCluster())
      || operator==(*lhs.GetCluster(),*rhs.GetCluster())
     )
  && (
       (!lhs.GetConceptMap() && !rhs.GetConceptMap())
       || *lhs.GetConceptMap() == *rhs.GetConceptMap()
     )
  && lhs.GetStudentName() == rhs.GetStudentName()
  && lhs.GetVersion() == rhs.GetVersion();
}
