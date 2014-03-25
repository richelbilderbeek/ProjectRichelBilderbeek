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
#include "conceptmapexamplefactory.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QRegExp>

#include "conceptmaphelper.h"
#include "conceptmapexample.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::Create(
  const std::string& text,
  const cmap::Competency& competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific)
{
  boost::shared_ptr<cmap::Example> example(
    new Example(
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

const boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::FromXml(const std::string& s)
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
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<competency>.*</competency>)"));
    assert(v.size() == 1);
    competency = Example::StrToCompetency(ribi::xml::StripXmlTag(v[0]));
  }
  //is_complex
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<is_complex>.*</is_complex>)"));
    assert(v.size() == 1);
    is_complex = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_concrete
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<is_concrete>.*</is_concrete>)"));
    assert(v.size() == 1);
    is_concrete = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //is_specific
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<is_specific>.*</is_specific>)"));
    assert(v.size() == 1);
    is_specific = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //text
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<text>.*</text>)"));
    assert(v.size() == 1 && "<text>.*</text> must be present once in an Example");
    text = ribi::xml::StripXmlTag(v[0]);
  }

  const boost::shared_ptr<Example> example {
    Create(text,competency,is_complex,is_concrete,is_specific)
  };
  assert(example);
  assert(example->ToXml() == s);
  return example;
}

const boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::GetTest(const int i) const noexcept
{
  assert(i < GetNumberOfTests());
  return GetTests()[i];
}

const std::vector<boost::shared_ptr<ribi::cmap::Example> > ribi::cmap::ExampleFactory::GetTests() const noexcept
{
  return
  {
    Create("Test example 0",Competency::profession),
    Create("Test example 1",Competency::organisations),
    Create("Test example 2",Competency::social_surroundings),
    Create("Test example 3",Competency::target_audience),
    Create("Test example 4",Competency::ti_knowledge),
    Create("Test example 5",Competency::prof_growth),
    Create("Test example 6",Competency::misc),
    Create("",Competency::uninitialized),
  };
}
