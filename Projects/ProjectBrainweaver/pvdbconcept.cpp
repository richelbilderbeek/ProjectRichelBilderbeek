#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbconcept.h"

#include <boost/lexical_cast.hpp>

#include "pvdbconceptfactory.h"
#include "pvdbhelper.h"
#include "pvdbcompetency.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbexamplesfactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Concept::Concept(
  const std::string& name,
  const boost::shared_ptr<pvdb::Examples>& examples,
  const int rating_complexity,
  const int rating_concreteness,
  const int rating_specificity)
  : m_examples(examples),
    m_is_complex(true),
    m_name(name),
    m_rating_complexity(rating_complexity),
    m_rating_concreteness(rating_concreteness),
    m_rating_specificity(rating_specificity)

{
  #ifndef NDEBUG
  Test();
  assert(m_examples);
  assert(m_rating_complexity   >= -1); //BUG 2013-02-03
  assert(m_rating_complexity   <=  2);
  assert(m_rating_concreteness >= -1);
  assert(m_rating_concreteness <=  2);
  assert(m_rating_specificity  >= -1);
  assert(m_rating_specificity  <=  2);
  #endif
}

const boost::shared_ptr<pvdb::Concept> pvdb::Concept::FromXml(const std::string& s)
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == std::string("<concept>"));
  assert(s.substr(s.size() - 10,10) == std::string("</concept>"));

  std::string name;
  boost::shared_ptr<pvdb::Examples> examples;
  int rating_complexity    = -2; //Not even unrated (which has -1 as its value)
  int rating_concreteness  = -2; //Not even unrated (which has -1 as its value)
  int rating_specificity   = -2; //Not even unrated (which has -1 as its value)
  //m_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<name>.*</name>)"));
    assert(v.size() == 1);
    name = pvdb::StripXmlTag(v[0]);
  }
  //m_examples
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<examples>.*</examples>)"));
    assert(v.size() == 1 && "<examples>*.</examples> must be present once in a Concept");
    examples = Examples::FromXml(v[0]);
  }
  //m_rating_complexity
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<complexity>.*</complexity>)"));
    assert(v.size() == 1 && "(<complexity>.*</complexity>) must be present once per Concept");
    rating_complexity = boost::lexical_cast<int>(StripXmlTag(v[0]));
    assert(rating_complexity >= -1);
    assert(rating_complexity <=  2);
  }
  //m_rating_concreteness
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<concreteness>.*</concreteness>)"));
    assert(v.size() == 1);
    rating_concreteness = boost::lexical_cast<int>(StripXmlTag(v[0]));
  }
  //m_rating_specificity
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<specificity>.*</specificity>)"));
    assert(v.size() == 1);
    rating_specificity = boost::lexical_cast<int>(StripXmlTag(v[0]));
  }
  return ConceptFactory::Create(name,examples,rating_complexity,rating_concreteness,rating_specificity);
}

const boost::shared_ptr<const pvdb::Examples> pvdb::Concept::GetExamples() const
{
  assert(m_examples);
  const boost::shared_ptr<const pvdb::Examples> p(m_examples);
  assert(p);
  return p;
}

void pvdb::Concept::SetExamples(const boost::shared_ptr<pvdb::Examples>& examples)
{
  if (examples != m_examples)
  {
    m_examples = examples;
    //m_signal_examples_changed(this); //CAUSE OF MAJOR BUG 2013-01-09
  }
}

void pvdb::Concept::SetName(const std::string& name)
{
  assert(this);
  assert(this->GetExamples());
  if (name != m_name)
  {
    m_name = name;
    //m_signal_name_changed(this); //CAUSE OF MAJOR BUG 2013-01-09
  }
}

void pvdb::Concept::SetRatingComplexity(const int rating_complexity)
{
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);

  if (m_rating_complexity != rating_complexity)
  {
    m_rating_complexity = rating_complexity;
    assert(m_rating_complexity >= -1);
    assert(m_rating_complexity <=  2);
    //m_signal_rating_complexity_changed(this); //CAUSE OF MAJOR BUG 2013-01-09
  }
}

void pvdb::Concept::SetRatingConcreteness(const int rating_concreteness)
{
  if (m_rating_concreteness != rating_concreteness)
  {
    m_rating_concreteness = rating_concreteness;
    assert(m_rating_concreteness >= -1);
    assert(m_rating_concreteness <=  2);
    //m_signal_rating_concreteness_changed(this); //CAUSE OF MAJOR BUG 2013-01-09
  }
}

void pvdb::Concept::SetRatingSpecificity(const int rating_specificity)
{
  if (m_rating_specificity != rating_specificity)
  {
    m_rating_specificity = rating_specificity;
    assert(m_rating_specificity >= -1);
    assert(m_rating_specificity <=  2);
    //m_signal_rating_specificity_changed(this); //CAUSE OF MAJOR BUG 2013-01-09
  }
}

const std::string pvdb::Concept::ToXml(const boost::shared_ptr<const pvdb::Concept> &c)
{
  std::stringstream s;
  s << "<concept>";
  s <<   "<name>";
  s <<     c->GetName();
  s <<   "</name>";
  s <<   Examples::ToXml(c->GetExamples());
  s <<   "<complexity>";
  s <<     c->GetRatingComplexity();
  s <<   "</complexity>";
  s <<   "<concreteness>";
  s <<     c->GetRatingConcreteness();
  s <<   "</concreteness>";
  s <<   "<specificity>";
  s <<     c->GetRatingSpecificity();
  s <<   "</specificity>";
  s << "</concept>";
  const std::string r = s.str();

  assert(r.size() >= 19);
  assert(r.substr(0,9) == std::string("<concept>"));
  assert(r.substr(r.size() - 10,10) == std::string("</concept>"));
  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::Concept& lhs, const pvdb::Concept& rhs)
{
  const boost::shared_ptr<const pvdb::Examples> lhs_examples = lhs.GetExamples();
  assert(lhs_examples);
  const boost::shared_ptr<const pvdb::Examples> rhs_examples = rhs.GetExamples();
  assert(rhs_examples);
  return
       lhs.GetName()               == rhs.GetName()
    && IsEqual(*lhs_examples,*rhs_examples)
    && lhs.GetRatingComplexity()   == rhs.GetRatingComplexity()
    && lhs.GetRatingConcreteness() == rhs.GetRatingConcreteness()
    && lhs.GetRatingSpecificity()  == rhs.GetRatingSpecificity();
}

/*
bool operator==(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) == boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) == boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) == boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) != boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) != boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) != boost::shared_ptr<const pvdb::Concept>(rhs);
}
*/

bool operator<(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  if (lhs->GetName() < rhs->GetName()) return true;
  if (lhs->GetName() > rhs->GetName()) return false;
  if (lhs->GetExamples() < rhs->GetExamples()) return true;
  if (lhs->GetExamples() != rhs->GetExamples()) return false;
  assert(lhs->GetExamples() == rhs->GetExamples());
  if (lhs->GetRatingComplexity() < rhs->GetRatingComplexity()) return true;
  if (lhs->GetRatingComplexity() > rhs->GetRatingComplexity()) return false;
  if (lhs->GetRatingConcreteness() < rhs->GetRatingConcreteness()) return true;
  if (lhs->GetRatingConcreteness() > rhs->GetRatingConcreteness()) return false;
  return lhs->GetRatingSpecificity() < rhs->GetRatingSpecificity();
}

bool operator<(const boost::shared_ptr<const pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) < boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator<(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<const pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) < boost::shared_ptr<const pvdb::Concept>(rhs);
}

bool operator<(const boost::shared_ptr<pvdb::Concept>& lhs, const boost::shared_ptr<pvdb::Concept>& rhs)
{
  assert(lhs); assert(rhs);
  return boost::shared_ptr<const pvdb::Concept>(lhs) < boost::shared_ptr<const pvdb::Concept>(rhs);
}


} //~namespace pvdb
