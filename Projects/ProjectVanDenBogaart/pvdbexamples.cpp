#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbexamples.h"

#include <cassert>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <QRegExp>
#include "pvdbhelper.h"
#include "pvdbexample.h"
#include "pvdbexamplefactory.h"
#include "pvdbexamplesfactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Examples::Examples(const std::vector<boost::shared_ptr<pvdb::Example> >& v)
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

void pvdb::Examples::Add(const boost::shared_ptr<pvdb::Example>& example)
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

const boost::shared_ptr<pvdb::Examples> pvdb::Examples::FromXml(const std::string& s)
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

const std::vector<boost::shared_ptr<const pvdb::Example> > pvdb::Examples::Get() const
{
  return AddConst(m_v);
}

void pvdb::Examples::OnExampleChanged()
{
  m_signal_examples_changed(this);
}

void pvdb::Examples::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started pvdb::Examples::Test");
  //Test of operator== and operator!=
  {
    const int sz = static_cast<int>(ExamplesFactory::GetTests().size());
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const pvdb::Examples> a = ExamplesFactory::GetTests().at(i);
      boost::shared_ptr<      Examples> b = ExamplesFactory::GetTests().at(i);
      assert(a==a); assert(a==b); assert(b==a); assert(b==b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const pvdb::Examples> c = ExamplesFactory::GetTests().at(j);
        boost::shared_ptr<      Examples> d = ExamplesFactory::GetTests().at(j);
        assert(c==c); assert(c==d); assert(d==c); assert(d==d);
        if (i==j)
        {
          assert(a==c); assert(a==d);
          assert(b==c); assert(b==d);
          assert(c==a); assert(c==b);
          assert(d==a); assert(d==b);
        }
        else
        {
          assert(a!=c); assert(a!=d);
          assert(b!=c); assert(b!=d);
          assert(c!=a); assert(c!=b);
          assert(d!=a); assert(d!=b);
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
        const std::string s = pvdb::Examples::ToXml(e);
        const boost::shared_ptr<const pvdb::Examples> f(Examples::FromXml(s));
        assert(e == f);
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const pvdb::Examples> > v = AddConst(ExamplesFactory::GetTests());
    const int sz = static_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const pvdb::Examples>& e = v[i];
      const std::string s = pvdb::Examples::ToXml(e);
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const pvdb::Examples>& f = v[j];
        const std::string t = pvdb::Examples::ToXml(f);
        if (i == j)
        {
          assert(e == f);
          assert(s == t);
        }
        else
        {
          assert(e != f);
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
    assert(a == a); assert(a == b); assert(a != c);
    assert(b == a); assert(b == b); assert(b != c);
    assert(c != a); assert(c != b); assert(c == c);
    std::vector<boost::shared_ptr<const pvdb::Example> > v; v.push_back(a);
    std::vector<boost::shared_ptr<const pvdb::Example> > w; w.push_back(b);
    std::vector<boost::shared_ptr<const pvdb::Example> > x; x.push_back(c);
    const boost::shared_ptr<pvdb::Examples> d = ExamplesFactory::Create(v);
    const boost::shared_ptr<pvdb::Examples> e = ExamplesFactory::Create(w);
    const boost::shared_ptr<pvdb::Examples> f = ExamplesFactory::Create(x);
    assert(d == d); assert(d == e); assert(d != f);
    assert(e == d); assert(e == e); assert(e != f);
    assert(f != d); assert(f != e); assert(f == f);
  }
  TRACE("Examples::Test finished successfully");
}

const std::string pvdb::Examples::ToXml(const boost::shared_ptr<const pvdb::Examples> &c)
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

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::Examples& lhs, const pvdb::Examples& rhs)
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
      return a == b;
    }
  );
}

bool operator==(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return boost::shared_ptr<const pvdb::Examples>(lhs) == boost::shared_ptr<const pvdb::Examples>(rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return boost::shared_ptr<const pvdb::Examples>(lhs) == boost::shared_ptr<const pvdb::Examples>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return boost::shared_ptr<const pvdb::Examples>(lhs) == boost::shared_ptr<const pvdb::Examples>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return !(lhs==rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return !(lhs==rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return !(lhs==rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<pvdb::Examples>& rhs)
{
  assert(lhs && rhs);
  return !(lhs==rhs);
}


bool operator<(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs)
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

} //~namespace pvdb

