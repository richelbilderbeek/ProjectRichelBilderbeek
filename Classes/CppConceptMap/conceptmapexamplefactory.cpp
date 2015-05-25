//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapexamplefactory.h"

#include <cassert>

//#include <boost/lexical_cast.hpp>
//#include <boost/make_shared.hpp>

#include "conceptmaphelper.h"
#include "counter.h"
#include "conceptmapexample.h"
#include "conceptmapregex.h"
#include "testtimer.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::cmap::ExampleFactory::ExampleFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::Create(
  const std::string& text,
  const cmap::Competency& competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific
) const noexcept
{
  boost::shared_ptr<Example> example(
    new Example(
      *this,
      text,
      competency,
      is_complex,
      is_concrete,
      is_specific
    )
  );
  assert(example);
  return example;
}

boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::FromXml(const std::string& s) const noexcept
{
  assert(s.size() >= 17);
  assert(s.substr(0,9) == "<example>");
  assert(s.substr(s.size() - 10,10) == "</example>");

  std::string text;
  cmap::Competency competency = cmap::Competency::uninitialized;
  bool is_complex = false;
  bool is_concrete = false;
  bool is_specific = false;

  //competency
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexCompetency());
    assert(v.size() == 1);
    competency = Example::StrToCompetency(ribi::xml::StripXmlTag(v[0]));
  }
  //is_complex
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexIsComplex());
    assert(v.size() == 1);
    is_complex = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_concrete
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexIsConcrete());
    assert(v.size() == 1);
    is_concrete = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_specific
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexIsSpecific());
    assert(v.size() == 1);
    is_specific = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //text
  {
    const std::vector<std::string> v
      = Regex().GetRegexMatches(s,Regex().GetRegexText());
    assert(v.size() == 1 && "GetRegexText must be present once in an Example");
    text = ribi::xml::StripXmlTag(v[0]);
  }

  const boost::shared_ptr<Example> example
    = Create(text,competency,is_complex,is_concrete,is_specific)
  ;
  assert(example);
  assert(example->ToXml() == s);
  return example;
}

boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::GetTest(const int i) const noexcept
{
  assert(i < GetNumberOfTests());
  return GetTests()[i];
}

std::vector<boost::shared_ptr<ribi::cmap::Example>> ribi::cmap::ExampleFactory::GetTests() const noexcept
{
  return
  {
    Create("Test example 0",Competency::profession,true,false,false),
    Create("Test example 1",Competency::organisations,false,true,false),
    Create("Test example 2",Competency::social_surroundings,false,false,true),
    Create("Test example 3",Competency::target_audience,true,true,false),
    Create("Test example 4",Competency::ti_knowledge,false,true,true),
    Create("Test example 5",Competency::prof_growth,true,false,true),
    Create("Test example 6",Competency::misc,true,true,true),
    Create("",Competency::uninitialized,true,false,true),
  };
}

#ifndef NDEBUG
void ribi::cmap::ExampleFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Counter();
  Example(ExampleFactory(),"Test example 0",Competency::profession,true,false,false);
  ExampleFactory().GetTest(0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif // NDEBUG
