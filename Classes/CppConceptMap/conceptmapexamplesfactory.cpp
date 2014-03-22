#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "conceptmapexamplesfactory.h"

#include <cassert>

#include <QRegExp>

#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create()
{
  boost::shared_ptr<ribi::cmap::Examples> examples(new Examples( {} ));
  assert(examples);
  return examples;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const boost::shared_ptr<const cmap::Examples>& examples)
{
  assert(examples);
  const boost::shared_ptr<ribi::cmap::Examples> p = Create(examples->Get());
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<boost::shared_ptr<cmap::Example> >& v)
{
  boost::shared_ptr<ribi::cmap::Examples> p(new Examples(v));
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<boost::shared_ptr<const cmap::Example> >& v)
{
  std::vector<boost::shared_ptr<cmap::Example> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const boost::shared_ptr<const cmap::Example>& p)
    {
      boost::shared_ptr<cmap::Example> q
        = ExampleFactory::Create(p->GetText(),p->GetCompetency());
      assert(q);
      return q;
    }
  );

  const boost::shared_ptr<ribi::cmap::Examples> examples(new Examples(w));
  assert(examples);
  return examples;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::Create(
  const std::vector<std::pair<std::string,Competency> >& v)
{
  std::vector<boost::shared_ptr<cmap::Example> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const std::pair<std::string,Competency>& p)
    {
      const boost::shared_ptr<cmap::Example> q
        = ExampleFactory::Create(p.first,p.second);
      assert(q);
      return q;
    }
  );
  const boost::shared_ptr<ribi::cmap::Examples> q = Create(w);
  assert(q);
  return q;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::FromXml(const std::string& s) const
{
  if (s.size() < 20)
  {
    return nullptr;
  }
  if (s.substr(0,10) != "<examples>")
  {
    return nullptr;
  }
  if (s.substr(s.size() - 11,11) != "</examples>")
  {
    return nullptr;
  }
  assert(GetRegexMatches(s,QRegExp("(<examples>)")).size()
      == GetRegexMatches(s,QRegExp("(</examples>)")).size());

  std::vector<boost::shared_ptr<Example> > examples;
  {
    assert(GetRegexMatches(s,QRegExp("(<example>)")).size()
        == GetRegexMatches(s,QRegExp("(</example>)")).size());
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<example>.*</example>)"));
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
  assert(result);
  #ifndef NDEBUG
  if(result->ToXml() != s)
  {
    TRACE("ERROR");
    TRACE(result->ToXml());
    TRACE(s);
    TRACE("BREAK");
  }

  #endif
  //assert(result->ToXml() == s); //TODO RJCB: put back in
  return result;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::ExamplesFactory::GetTest(const int i) const noexcept
{
  assert(i >= 0);
  assert(i < GetNumberOfTests());
  return GetTests()[i];
}

const std::vector<boost::shared_ptr<ribi::cmap::Examples> > ribi::cmap::ExamplesFactory::GetTests() const noexcept
{
  const std::vector<std::vector<int> > is = { {0}, {1}, {0,1,2,3}, {} };
  std::vector<boost::shared_ptr<ribi::cmap::Examples> > v;
  std::transform(is.begin(),is.end(),std::back_inserter(v),
    [](const std::vector<int>& js)
    {
      std::vector<boost::shared_ptr<cmap::Example> > w;
      std::transform(js.begin(),js.end(),std::back_inserter(w),
        [](const int& j)
        {
          const boost::shared_ptr<cmap::Example> p
            = ExampleFactory().GetTest(j);
          assert(p);
          return p;
        }
      );
      const boost::shared_ptr<ribi::cmap::Examples> q
        = ribi::cmap::ExamplesFactory::Create(w);
      assert(q);
      return q;
    }
  );

  return v;

}
