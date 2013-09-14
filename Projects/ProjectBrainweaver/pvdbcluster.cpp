#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
#pragma GCC diagnostic pop

ribi::pvdb::Cluster::Cluster(const std::vector<boost::shared_ptr<ribi::pvdb::Concept> >& v)
  : m_v(v)
{
  #ifndef NDEBUG
  Test();
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<ribi::pvdb::Concept>& p) { return !p; } ) == 0);
  #endif
}

void ribi::pvdb::Cluster::Add(const boost::shared_ptr<ribi::pvdb::Concept> & concept)
{
  assert(concept);
  assert(concept->GetRatingComplexity() >= -1);
  assert(concept->GetRatingComplexity() <=  2);
  m_v.push_back(concept);

}

bool ribi::pvdb::Cluster::Empty() const
{
  return m_v.empty();
}

const boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::Cluster::FromXml(const std::string &s)
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == std::string("<cluster>"));
  assert(s.substr(s.size() - 10,10) == std::string("</cluster>"));

  std::vector<boost::shared_ptr<ribi::pvdb::Concept> > concepts;

  //Obtain the <cluster> ... </cluster> string
  const std::vector<std::string> v
    = ribi::pvdb::GetRegexMatches(s,QRegExp("(<cluster>.*</cluster>)"));
  assert(v.size() == 1);
  //Strip the <cluster> tags
  const std::string cluster_str = pvdb::StripXmlTag(v[0]);
  //Obtain the <concept> ... </concept> strings
  const std::vector<std::string> w
    = pvdb::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
  std::for_each(w.begin(),w.end(),
    [&concepts](const std::string& s)
    {
      const boost::shared_ptr<ribi::pvdb::Concept> concept = Concept::FromXml(s);
      concepts.push_back(concept);
    }
  );

  const boost::shared_ptr<pvdb::Cluster> cluster(new Cluster(concepts));
  assert(cluster);
  return cluster;
}

const std::vector<boost::shared_ptr<const ribi::pvdb::Concept> > ribi::pvdb::Cluster::Get() const
{
  return std::vector<boost::shared_ptr<const ribi::pvdb::Concept> >(m_v.begin(),m_v.end());
}

const std::string ribi::pvdb::Cluster::ToXml(const boost::shared_ptr<const pvdb::Cluster>& cluster)
{
  std::stringstream s;
  s << "<cluster>";
  {
    const std::vector<boost::shared_ptr<const ribi::pvdb::Concept> >& v = cluster->Get();
    std::for_each(v.begin(), v.end(),
      [&s](const boost::shared_ptr<const ribi::pvdb::Concept>& concept)
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

bool ribi::pvdb::IsEqual(const ribi::pvdb::Cluster& lhs, const ribi::pvdb::Cluster& rhs)
{
  const std::vector<boost::shared_ptr<const ribi::pvdb::Concept> > lhs_concepts = lhs.Get(); //For cross-compiler
  const std::vector<boost::shared_ptr<const ribi::pvdb::Concept> > rhs_concepts = rhs.Get();
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

void ribi::pvdb::Cluster::SetConcepts(const std::vector<boost::shared_ptr<ribi::pvdb::Concept> >& concepts)
{
  m_v = concepts;
  assert(std::count_if(m_v.begin(),m_v.end(),
    [](boost::shared_ptr<ribi::pvdb::Concept> concept) { return !concept; } )
    == 0);
}
