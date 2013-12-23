#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapexamples.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <QRegExp>
#include "conceptmaphelper.h"
#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Examples::Examples(const std::vector<boost::shared_ptr<cmap::Example> >& v)
  : m_signal_examples_changed{},
    m_v(v)
{
  #ifndef NDEBUG
  Test();
  #endif

  std::for_each(m_v.begin(),m_v.end(),
    [this](const boost::shared_ptr<cmap::Example>& example)
    {
      assert(example);
      example->m_signal_competency_changed.connect(
        boost::bind(
          &Examples::OnExampleChanged,
          this
        )
      );
      example->m_signal_text_changed.connect(
        boost::bind(
          &Examples::OnExampleChanged,
          this
        )
      );
    }
  );

  assert(std::count_if(m_v.begin(),m_v.end(),
    [](const boost::shared_ptr<cmap::Example>& e) { return !e; }
    ) == 0 && "All Example instances must be initialized");
}

void ribi::cmap::Examples::Add(const boost::shared_ptr<cmap::Example>& example)
{
  assert(example);
  //Connect the example
  example->m_signal_competency_changed.connect(
    boost::bind(
      &Examples::OnExampleChanged,
      this
    )
  );
  example->m_signal_text_changed.connect(
    boost::bind(
      &Examples::OnExampleChanged,
      this
    )
  );
  //Add the example and notify this change
  m_v.push_back(example);
  m_signal_examples_changed(this);
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::Examples::FromXml(const std::string& s)
{
  assert(s.size() >= 20);
  assert(s.substr(0,10) == std::string("<examples>"));
  assert(s.substr(s.size() - 11,11) == std::string("</examples>"));

  std::vector<boost::shared_ptr<cmap::Example> > examples;
  //m_questions
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<example>.*</example>)"));
    std::transform(v.begin(),v.end(),std::back_inserter(examples),
      [](const std::string& s)
      {
        return Example::FromXml(s);
      }
    );
  }
  return ExamplesFactory::Create(examples);
}

const std::vector<boost::shared_ptr<const ribi::cmap::Example> > ribi::cmap::Examples::Get() const
{
  return AddConst(m_v);
}

void ribi::cmap::Examples::OnExampleChanged()
{
  m_signal_examples_changed(this);
}

void ribi::cmap::Examples::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::Examples::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(ExamplesFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const cmap::Examples> a = ExamplesFactory::GetTests().at(i);
      boost::shared_ptr<      Examples> b = ExamplesFactory::GetTests().at(i);
      assert(operator==(*a,*a));
      assert(operator==(*a,*b));
      assert(operator==(*b,*a));
      assert(operator==(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const cmap::Examples> c = ExamplesFactory::GetTests().at(j);
        boost::shared_ptr<      Examples> d = ExamplesFactory::GetTests().at(j);
        assert(operator==(*c,*c));
        assert(operator==(*c,*d));
        assert(operator==(*d,*c));
        assert(operator==(*d,*d));
        if (i==j)
        {
          assert(operator==(*a,*c)); assert(operator==(*a,*d));
          assert(operator==(*b,*c)); assert(operator==(*b,*d));
          assert(operator==(*c,*a)); assert(operator==(*c,*b));
          assert(operator==(*d,*a)); assert(operator==(*d,*b));
        }
        else
        {
          assert(!operator==(*a,*c)); assert(!operator==(*a,*d));
          assert(!operator==(*b,*c)); assert(!operator==(*b,*d));
          assert(!operator==(*c,*a)); assert(!operator==(*c,*b));
          assert(!operator==(*d,*a)); assert(!operator==(*d,*b));
        }
      }
    }
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const cmap::Examples> > v = AddConst(ExamplesFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const cmap::Examples>& e)
      {
        assert(e);
        const std::string s = ribi::cmap::Examples::ToXml(e);
        const boost::shared_ptr<const cmap::Examples> f(Examples::FromXml(s));
        assert(operator==(*e,*f));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const cmap::Examples> > v = AddConst(ExamplesFactory::GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const cmap::Examples>& e = v[i];
      const std::string s = ribi::cmap::Examples::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const cmap::Examples>& f = v[j];
        const std::string t = ribi::cmap::Examples::ToXml(f);
        if (i == j)
        {
          assert(operator==(*e,*f));
          assert(s == t);
        }
        else
        {
          assert(!operator==(*e,*f));
          assert(s != t);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<cmap::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<cmap::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert( operator==(*a,*a)); assert( operator==(*a,*b)); assert(!operator==(*a,*c));
    assert( operator==(*b,*a)); assert( operator==(*b,*b)); assert(!operator==(*b,*c));
    assert(!operator==(*c,*a)); assert(!operator==(*c,*b)); assert( operator==(*c,*c));
    std::vector<boost::shared_ptr<const cmap::Example> > v; v.push_back(a);
    std::vector<boost::shared_ptr<const cmap::Example> > w; w.push_back(b);
    std::vector<boost::shared_ptr<const cmap::Example> > x; x.push_back(c);
    const boost::shared_ptr<ribi::cmap::Examples> d = ExamplesFactory::Create(v);
    const boost::shared_ptr<ribi::cmap::Examples> e = ExamplesFactory::Create(w);
    const boost::shared_ptr<ribi::cmap::Examples> f = ExamplesFactory::Create(x);
    assert( operator==(*d,*d)); assert( operator==(*d,*e)); assert(!operator==(*d,*f));
    assert( operator==(*e,*d)); assert( operator==(*e,*e)); assert(!operator==(*e,*f));
    assert(!operator==(*f,*d)); assert(!operator==(*f,*e)); assert( operator==(*f,*f));
  }
  TRACE("Examples::Test finished successfully");
}

const std::string ribi::cmap::Examples::ToXml(const boost::shared_ptr<const cmap::Examples> &c)
{
  std::stringstream s;
  s << "<examples>";

  //const std::vector<boost::shared_ptr<const cmap::Example> > examples = c->GetExamples();
  const auto example = c->Get();
  std::for_each(example.begin(),example.end(),
    [&s](const boost::shared_ptr<const cmap::Example>& t)
    {
      s << Example::ToXml(t);
    }
  );
  s << "</examples>";

  const std::string r = s.str();
  assert(r.size() >= 20);
  assert(r.substr(0,10) == std::string("<examples>"));
  assert(r.substr(r.size() - 11,11) == std::string("</examples>"));
  return r;
}

bool ribi::cmap::operator==(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  if (lhs.Get().size() != rhs.Get().size())
  {
    return false;
  }
  if (lhs.Get().empty()) { assert(rhs.Get().empty()); return true; }
  const std::vector<boost::shared_ptr<const cmap::Example> > v = lhs.Get();
  const std::vector<boost::shared_ptr<const cmap::Example> > w = rhs.Get();
  return std::equal(v.begin(),v.end(),w.begin(),
    [](const boost::shared_ptr<const cmap::Example>& a, const boost::shared_ptr<const cmap::Example>& b)
    {
      return operator==(*a,*b);
    }
  );
}

bool ribi::cmap::operator<(const boost::shared_ptr<const cmap::Examples>& lhs, const boost::shared_ptr<const cmap::Examples>& rhs)
{
  assert(lhs && rhs);
  if (lhs->Get().size() < rhs->Get().size()) return true;
  if (lhs->Get().size() > rhs->Get().size()) return false;
  assert(lhs->Get().size() == rhs->Get().size());
  const int sz = lhs->Get().size();
  for (int i = 0; i!=sz; ++i)
  {
    if (lhs->Get()[i] < rhs->Get()[i]) return true;
    if (lhs->Get()[i] > rhs->Get()[i]) return false;
  }
  return false;
}
