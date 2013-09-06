#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbexamples.h"

#include <cassert>
#include <sstream>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <QRegExp>
#include "pvdbhelper.h"
#include "pvdbexample.h"
#include "pvdbexamplefactory.h"
#include "pvdbexamplesfactory.h"
#include "trace.h"

ribi::pvdb::Examples::Examples(const std::vector<boost::shared_ptr<pvdb::Example> >& v)
  : m_v(v)
{
  #ifndef NDEBUG
  Test();
  #endif

  std::for_each(m_v.begin(),m_v.end(),
    [this](const boost::shared_ptr<pvdb::Example>& example)
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
    [](const boost::shared_ptr<pvdb::Example>& e) { return !e; }
    ) == 0 && "All Example instances must be initialized");
}

void ribi::pvdb::Examples::Add(const boost::shared_ptr<pvdb::Example>& example)
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

const boost::shared_ptr<ribi::pvdb::Examples> ribi::pvdb::Examples::FromXml(const std::string& s)
{
  assert(s.size() >= 20);
  assert(s.substr(0,10) == std::string("<examples>"));
  assert(s.substr(s.size() - 11,11) == std::string("</examples>"));

  std::vector<boost::shared_ptr<pvdb::Example> > examples;
  //m_questions
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<example>.*</example>)"));
    std::transform(v.begin(),v.end(),std::back_inserter(examples),
      [](const std::string& s)
      {
        return Example::FromXml(s);
      }
    );
  }
  return ExamplesFactory::Create(examples);
}

const std::vector<boost::shared_ptr<const ribi::pvdb::Example> > ribi::pvdb::Examples::Get() const
{
  return AddConst(m_v);
}

void ribi::pvdb::Examples::OnExampleChanged()
{
  m_signal_examples_changed(this);
}

void ribi::pvdb::Examples::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  TRACE("Started ribi::pvdb::Examples::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(ExamplesFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const pvdb::Examples> a = ExamplesFactory::GetTests().at(i);
      boost::shared_ptr<      Examples> b = ExamplesFactory::GetTests().at(i);
      assert(IsEqual(*a,*a));
      assert(IsEqual(*a,*b));
      assert(IsEqual(*b,*a));
      assert(IsEqual(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const pvdb::Examples> c = ExamplesFactory::GetTests().at(j);
        boost::shared_ptr<      Examples> d = ExamplesFactory::GetTests().at(j);
        assert(IsEqual(*c,*c));
        assert(IsEqual(*c,*d));
        assert(IsEqual(*d,*c));
        assert(IsEqual(*d,*d));
        if (i==j)
        {
          assert(IsEqual(*a,*c)); assert(IsEqual(*a,*d));
          assert(IsEqual(*b,*c)); assert(IsEqual(*b,*d));
          assert(IsEqual(*c,*a)); assert(IsEqual(*c,*b));
          assert(IsEqual(*d,*a)); assert(IsEqual(*d,*b));
        }
        else
        {
          assert(!IsEqual(*a,*c)); assert(!IsEqual(*a,*d));
          assert(!IsEqual(*b,*c)); assert(!IsEqual(*b,*d));
          assert(!IsEqual(*c,*a)); assert(!IsEqual(*c,*b));
          assert(!IsEqual(*d,*a)); assert(!IsEqual(*d,*b));
        }
      }
    }
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const pvdb::Examples> > v = AddConst(ExamplesFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::Examples>& e)
      {
        assert(e);
        const std::string s = ribi::pvdb::Examples::ToXml(e);
        const boost::shared_ptr<const pvdb::Examples> f(Examples::FromXml(s));
        assert(IsEqual(*e,*f));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const pvdb::Examples> > v = AddConst(ExamplesFactory::GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const pvdb::Examples>& e = v[i];
      const std::string s = ribi::pvdb::Examples::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const pvdb::Examples>& f = v[j];
        const std::string t = ribi::pvdb::Examples::ToXml(f);
        if (i == j)
        {
          assert(IsEqual(*e,*f));
          assert(s == t);
        }
        else
        {
          assert(!IsEqual(*e,*f));
          assert(s != t);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<pvdb::Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<pvdb::Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert( IsEqual(*a,*a)); assert( IsEqual(*a,*b)); assert(!IsEqual(*a,*c));
    assert( IsEqual(*b,*a)); assert( IsEqual(*b,*b)); assert(!IsEqual(*b,*c));
    assert(!IsEqual(*c,*a)); assert(!IsEqual(*c,*b)); assert( IsEqual(*c,*c));
    std::vector<boost::shared_ptr<const pvdb::Example> > v; v.push_back(a);
    std::vector<boost::shared_ptr<const pvdb::Example> > w; w.push_back(b);
    std::vector<boost::shared_ptr<const pvdb::Example> > x; x.push_back(c);
    const boost::shared_ptr<ribi::pvdb::Examples> d = ExamplesFactory::Create(v);
    const boost::shared_ptr<ribi::pvdb::Examples> e = ExamplesFactory::Create(w);
    const boost::shared_ptr<ribi::pvdb::Examples> f = ExamplesFactory::Create(x);
    assert( IsEqual(*d,*d)); assert( IsEqual(*d,*e)); assert(!IsEqual(*d,*f));
    assert( IsEqual(*e,*d)); assert( IsEqual(*e,*e)); assert(!IsEqual(*e,*f));
    assert(!IsEqual(*f,*d)); assert(!IsEqual(*f,*e)); assert( IsEqual(*f,*f));
  }
  TRACE("Examples::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

const std::string ribi::pvdb::Examples::ToXml(const boost::shared_ptr<const pvdb::Examples> &c)
{
  std::stringstream s;
  s << "<examples>";

  //const std::vector<boost::shared_ptr<const pvdb::Example> > examples = c->GetExamples();
  const auto example = c->Get();
  std::for_each(example.begin(),example.end(),
    [&s](const boost::shared_ptr<const pvdb::Example>& t)
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

bool ribi::pvdb::IsEqual(const pvdb::Examples& lhs, const pvdb::Examples& rhs)
{
  if (lhs.Get().size() != rhs.Get().size())
  {
    return false;
  }
  if (lhs.Get().empty()) { assert(rhs.Get().empty()); return true; }
  const std::vector<boost::shared_ptr<const pvdb::Example> > v = lhs.Get();
  const std::vector<boost::shared_ptr<const pvdb::Example> > w = rhs.Get();
  return std::equal(v.begin(),v.end(),w.begin(),
    [](const boost::shared_ptr<const pvdb::Example>& a, const boost::shared_ptr<const pvdb::Example>& b)
    {
      return IsEqual(*a,*b);
    }
  );
}

bool ribi::pvdb::operator<(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
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
