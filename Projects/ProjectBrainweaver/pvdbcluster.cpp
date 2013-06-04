#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbcluster.h"

#include <sstream>
#include <QRegExp>

#include "pvdbcompetency.h"
#include "pvdbhelper.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Cluster::Cluster(const std::vector<boost::shared_ptr<pvdb::Concept> >& v)
  : m_v(v)
{
  #ifndef NDEBUG
  Test();
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::Concept>& p) { return !p; } ) == 0); //FIX 2012-01-02
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<pvdb::Concept>& p) { return p; } )); //BUG 2012-01-02
  #endif
}

void pvdb::Cluster::Add(const boost::shared_ptr<pvdb::Concept> & concept)
{
  assert(concept);
  assert(concept->GetRatingComplexity() >= -1);
  assert(concept->GetRatingComplexity() <=  2);
  m_v.push_back(concept);

}

bool pvdb::Cluster::Empty() const
{
  return m_v.empty();
}

const boost::shared_ptr<pvdb::Cluster> pvdb::Cluster::FromXml(const std::string &s)
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == std::string("<cluster>"));
  assert(s.substr(s.size() - 10,10) == std::string("</cluster>"));

  std::vector<boost::shared_ptr<pvdb::Concept> > concepts;

  //Obtain the <cluster> ... </cluster> string
  const std::vector<std::string> v
    = pvdb::GetRegexMatches(s,QRegExp("(<cluster>.*</cluster>)"));
  assert(v.size() == 1);
  //Strip the <cluster> tags
  const std::string cluster_str = pvdb::StripXmlTag(v[0]);
  //Obtain the <concept> ... </concept> strings
  const std::vector<std::string> w
    = pvdb::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
  std::for_each(w.begin(),w.end(),
    [&concepts](const std::string& s)
    {
      const boost::shared_ptr<pvdb::Concept> concept = Concept::FromXml(s);
      concepts.push_back(concept);
    }
  );

  const boost::shared_ptr<pvdb::Cluster> cluster(new Cluster(concepts));
  assert(cluster);
  return cluster;
}

const std::vector<boost::shared_ptr<const pvdb::Concept> > pvdb::Cluster::Get() const
{
  return std::vector<boost::shared_ptr<const pvdb::Concept> >(m_v.begin(),m_v.end());
}

const std::string pvdb::Cluster::ToXml(const boost::shared_ptr<const pvdb::Cluster>& cluster)
{
  std::stringstream s;
  s << "<cluster>";
  {
    const std::vector<boost::shared_ptr<const pvdb::Concept> >& v = cluster->Get();
    std::for_each(v.begin(), v.end(),
      [&s](const boost::shared_ptr<const pvdb::Concept>& concept)
      {
        s << Concept::ToXml(concept);
      }
    );
  }
  s << "</cluster>";

  const std::string r = s.str();
  assert(r.size() >= 19);
  assert(r.substr(0,9) == std::string("<cluster>"));
  assert(r.substr(r.size() - 10,10) == std::string("</cluster>"));

  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs)
{
  const std::vector<boost::shared_ptr<const pvdb::Concept> > lhs_concepts = lhs.Get(); //For cross-compiler
  const std::vector<boost::shared_ptr<const pvdb::Concept> > rhs_concepts = rhs.Get();
  if (lhs_concepts.size() != rhs_concepts.size()) return false;
  const int sz = static_cast< int>(lhs_concepts.size());
  for (int i=0; i!=sz; ++i)
  {
    assert(lhs_concepts[i]);
    assert(rhs_concepts[i]);
    if (!IsEqual(*lhs_concepts[i],*rhs_concepts[i])) return false;
  }
  return true;
}

/*
bool operator==(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Cluster>(lhs) == boost::shared_ptr<const pvdb::Cluster>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Cluster>(lhs) == boost::shared_ptr<const pvdb::Cluster>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Cluster>(lhs) == boost::shared_ptr<const pvdb::Cluster>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs)
{
  assert(lhs); assert(rhs);
  return !(lhs == rhs);
}
*/

} //~namespace pvdb
