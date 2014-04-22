//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapconceptfactory.h"

#include "conceptmapcompetency.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic push

ribi::cmap::ConceptFactory::ConceptFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::Create(
  const std::string& name,
  const boost::shared_ptr<ribi::cmap::Examples>& examples,
  const bool is_complex,
  const int rating_complexity,
  const int rating_concreteness,
  const int rating_specificity
) const noexcept
{
  assert(examples);
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);

  boost::shared_ptr<Concept> concept(
    new Concept(
      name,
      examples,
      is_complex,
      rating_complexity,
      rating_concreteness,
      rating_specificity
    )
  );
  assert(concept);
  return concept;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::DeepCopy(
  const boost::shared_ptr<const ribi::cmap::Concept>& concept
) const noexcept
{
  const boost::shared_ptr<Examples> examples
    = ExamplesFactory::Create(concept->GetExamples());
  assert(examples);
  assert(*examples == *concept->GetExamples());

  assert(concept->GetRatingComplexity() >= -1);
  assert(concept->GetRatingComplexity() <=  2);

  const boost::shared_ptr<Concept> q
    = Create(
      concept->GetName(),
      examples,
      concept->GetIsComplex(),
      concept->GetRatingComplexity(),
      concept->GetRatingConcreteness(),
      concept->GetRatingSpecificity());
  assert(q);
  assert(q->GetExamples());
  assert(*concept == *q);
  return q;
}
#endif

//Do not create this version: it will lead to ambiguities
//static const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::Create(
//  const std::string& name,
//  const std::vector<boost::shared_ptr<const cmap::Example> >& examples)
//{
//  return Create(name,ExamplesFactory::Create(examples));
//}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::Create(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& v,
  const bool is_complex,
  const int rating_complexity,
  const int rating_concreteness,
  const int rating_specificity
) const noexcept
{
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);

  std::vector<boost::shared_ptr<cmap::Example> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const std::pair<std::string,Competency>& p)
    {
      const boost::shared_ptr<cmap::Example> q
        = ExampleFactory::Create(
          p.first,
          p.second);
      assert(q);
      return q;
    }
  );

  const boost::shared_ptr<Examples> examples
    = ExamplesFactory::Create(w);
  assert(examples);

  const boost::shared_ptr<Concept> concept
    = Create(
    name,
    examples,
    is_complex,
    rating_complexity,
    rating_concreteness,
    rating_specificity);
  assert(concept);
  return concept;
}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::FromXml(const std::string& s) const noexcept
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == "<concept>");
  assert(s.substr(s.size() - 10,10) == "</concept>");

  std::string name;
  boost::shared_ptr<ribi::cmap::Examples> examples;
  bool is_complex = false;
  int rating_complexity    = -2; //Not even unrated (which has -1 as its value)
  int rating_concreteness  = -2; //Not even unrated (which has -1 as its value)
  int rating_specificity   = -2; //Not even unrated (which has -1 as its value)
  //m_name
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<name>.*</name>)"));
    assert(v.size() == 1);
    name = ribi::xml::StripXmlTag(v[0]);
  }
  //m_examples
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<examples>.*</examples>)"));
    assert(v.size() == 1 && "<examples>*.</examples> must be present once in a Concept");
    examples = ExamplesFactory().FromXml(v[0]);
  }

  //m_is_complex
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<concept_is_complex>.*</concept_is_complex>)"));
    assert(v.size() == 1 && "(<is_complex>.*</is_complex>) must be present once per Concept");
    is_complex = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }

  //m_rating_complexity
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<complexity>.*</complexity>)"));
    assert(v.size() == 1 && "(<complexity>.*</complexity>) must be present once per Concept");
    rating_complexity = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
    assert(rating_complexity >= -1);
    assert(rating_complexity <=  2);
  }
  //m_rating_concreteness
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<concreteness>.*</concreteness>)"));
    assert(v.size() == 1);
    rating_concreteness = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_rating_specificity
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<specificity>.*</specificity>)"));
    assert(v.size() == 1);
    rating_specificity = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }

  const boost::shared_ptr<Concept> concept {
    ConceptFactory().Create(name,examples,is_complex,rating_complexity,rating_concreteness,rating_specificity)
  };
  assert(concept);
  //assert(concept->ToXml() == s); //TODO RJCB: Put back in
  return concept;
}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::ConceptFactory::GetTest(
  const int i) const noexcept
{
  assert(i < GetNumberOfTests());
  const boost::shared_ptr<Concept> concept {
    GetTests()[i]
  };
  assert(concept);
  return concept;
}

const std::vector<boost::shared_ptr<ribi::cmap::Concept> > ribi::cmap::ConceptFactory::GetTests() const noexcept
{
  std::vector<boost::shared_ptr<Concept> > v;
  {
    const boost::shared_ptr<Examples> examples = ExamplesFactory::Create();
    assert(examples);
    const boost::shared_ptr<Concept> p = Create("Concept without examples", examples, false, 0, 1, 2);
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Concept> p = Create("Concept with one example", { { "Only example", cmap::Competency::profession } }, 1, 2, 0);
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  /*
  {
    const boost::shared_ptr<Concept> p = Create("Concept with two examples", { { "First example", cmap::Competency::organisations }, { "Second example", cmap::Competency::social_surroundings } }, 2, 0, 1);
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Concept> p = Create("Concept with three examples", { { "Example 1 of 3", cmap::Competency::target_audience }, { "Example 2 of 3", cmap::Competency::ti_knowledge }, { "Example 3 of 3", cmap::Competency::prof_growth } }, 0, 1, 2);
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Concept> p = Create("Concept with four Roman examples", { { "Example I/IV", cmap::Competency::misc }, { "Example II/IV", cmap::Competency::uninitialized }, { "Example III/IV", cmap::Competency::profession }, { "Example III/IV", cmap::Competency::social_surroundings } }, 1, 2, 0);
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  */
  {
    const boost::shared_ptr<Concept> p = Create(
      "Very long multi-line concept with four Roman examples that also each span multiple lines, that is, eighty characters",
      {
        { "Example I/IV, spanning multiple lines (that is, having at least eight characters) and is rated as cmap::Competency::misc", cmap::Competency::misc },
        { "Example II/IV, spanning multiple lines (that is, having at least eight characters) and is rated as cmap::Competency::uninitialized", cmap::Competency::uninitialized },
        { "Example III/IV, spanning multiple lines (that is, having at least eight characters) and is rated as cmap::Competency::profession", cmap::Competency::profession },
        { "Example III/IV, spanning multiple lines (that is, having at least eight characters) and is rated as cmap::Competency::social_surroundings", cmap::Competency::social_surroundings }
      }, 1, 2, 0
    );
    assert(p);
    assert(p->GetRatingComplexity() >= -1);
    assert(p->GetRatingComplexity() <=  2);
    v.push_back(p);
  }
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<Concept>& p) { return !p; } ) == 0); //FIX 2012-01-02
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<Concept>& p) { return p; } ));
  assert(v[0]->GetExamples());

  return v;
}

#ifndef NDEBUG
void ribi::cmap::ConceptFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::ConceptFactory::Test");
  TRACE("ConceptFactory::Test finished successfully");
}
#endif
