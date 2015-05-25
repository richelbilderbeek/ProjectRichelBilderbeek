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
#include "conceptmapexamplesfactory.h"

#include <cassert>

#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapregex.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::ExamplesFactory::ExamplesFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create() const noexcept
{
  boost::shared_ptr<Examples> examples(new Examples( {} ));
  assert(examples);
  return examples;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const boost::shared_ptr<const cmap::Examples>& examples) const noexcept
{
  assert(examples);
  const boost::shared_ptr<Examples> p = Create(examples->Get());
  assert(p);
  return p;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<boost::shared_ptr<cmap::Example> >& v) const noexcept
{
  boost::shared_ptr<Examples> p(new Examples(v));
  assert(p);
  return p;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<boost::shared_ptr<const cmap::Example> >& v) const noexcept
{
  std::vector<boost::shared_ptr<cmap::Example> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const boost::shared_ptr<const cmap::Example>& p)
    {
      boost::shared_ptr<Example> q
        = ExampleFactory().Create(p->GetText(),p->GetCompetency());
      assert(q);
      return q;
    }
  );

  const boost::shared_ptr<ribi::cmap::Examples> examples(new Examples(w));
  assert(examples);
  return examples;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<std::pair<std::string,Competency> >& v) const noexcept
{
  std::vector<boost::shared_ptr<Example> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const std::pair<std::string,Competency>& p)
    {
      const boost::shared_ptr<Example> q
        = ExampleFactory().Create(p.first,p.second);
      assert(q);
      return q;
    }
  );
  const boost::shared_ptr<ribi::cmap::Examples> q = Create(w);
  assert(q);
  return q;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::FromXml(const std::string& s) const
{
  if (s.size() < 20)
  {
    return boost::shared_ptr<Examples>();
  }
  if (s.substr(0,10) != "<examples>")
  {
    return boost::shared_ptr<Examples>();
  }
  if (s.substr(s.size() - 11,11) != "</examples>")
  {
    return boost::shared_ptr<Examples>();
  }
  assert(Regex().GetRegexMatches(s,"(<examples>)").size()
      == Regex().GetRegexMatches(s,"(</examples>)").size());

  std::vector<boost::shared_ptr<Example> > examples;
  {

    assert(Regex().GetRegexMatches(s,"(<example>)").size()
        == Regex().GetRegexMatches(s,"(</example>)").size());
    const auto v = Regex().GetRegexMatches(s,Regex().GetRegexExample());
    std::transform(v.begin(),v.end(),std::back_inserter(examples),
      [](const std::string& s)
      {
        return ExampleFactory().FromXml(s);
      }
    );
  }
  const boost::shared_ptr<Examples> result {
    Create(examples)
  };
  return result;
}

boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::GetTest(const int i) const noexcept
{
  assert(i >= 0);
  assert(i < GetNumberOfTests());
  return GetTests()[i];
}

std::vector<boost::shared_ptr<ribi::cmap::Examples> > ribi::cmap::ExamplesFactory::GetTests() const noexcept
{
  const std::vector<std::vector<int> > is = { {0}, {1}, {0,1,2,3}, {} };
  std::vector<boost::shared_ptr<Examples> > v;
  std::transform(is.begin(),is.end(),std::back_inserter(v),
    [this](const std::vector<int>& js)
    {
      std::vector<boost::shared_ptr<Example> > w;
      std::transform(js.begin(),js.end(),std::back_inserter(w),
        [](const int& j)
        {
          const boost::shared_ptr<Example> p
            = ExampleFactory().GetTest(j);
          assert(p);
          return p;
        }
      );
      const boost::shared_ptr<Examples> q
        = Create(w);
      assert(q);
      return q;
    }
  );

  return v;

}

#ifndef NDEBUG
void ribi::cmap::ExamplesFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ExamplesFactory().Create();
  const bool verbose{false};
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ExamplesFactory f;
  if (verbose) { TRACE("Create must return a valid Examples"); }
  {
    assert(f.Create());
  }
  if (verbose) { TRACE("Examples -> XML -> Examples "); }
  {
    const auto examples = ExamplesFactory().GetTest(2);
    const auto xml = examples->ToXml();
    const auto new_examples = ExamplesFactory().FromXml(xml);
    const auto new_xml = new_examples->ToXml();
    assert(xml == new_xml);
  }
}
#endif // NDEBUG
