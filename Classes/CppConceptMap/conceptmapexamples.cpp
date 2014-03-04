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
    [this](const boost::shared_ptr<Example>& example)
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
    [](const boost::shared_ptr<Example>& e) { return !e; }
    ) == 0 && "All Example instances must be initialized");
}

/*
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
*/


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
    const int sz = ExamplesFactory().GetNumberOfTests();
    for (int i=0; i!=sz; ++i)
    {
      boost::shared_ptr<const Examples> a = ExamplesFactory().GetTest(i);
      boost::shared_ptr<      Examples> b = ExamplesFactory().GetTest(i);
      assert(*a == *a);
      assert(*a == *b);
      assert(*b == *a);
      assert(*b == *b);
      for (int j=0; j!=sz; ++j)
      {
        boost::shared_ptr<const Examples> c = ExamplesFactory().GetTest(j);
        boost::shared_ptr<      Examples> d = ExamplesFactory().GetTest(j);
        assert(*c == *c);
        assert(*c == *d);
        assert(*d == *c);
        assert(*d == *d);
        if (i==j)
        {
          assert(*a == *c); assert(*a == *d);
          assert(*b == *c); assert(*b == *d);
          assert(*c == *a); assert(*c == *b);
          assert(*d == *a); assert(*d == *b);
        }
        else
        {
          assert(*a != *c); assert(*a != *d);
          assert(*b != *c); assert(*b != *d);
          assert(*c != *a); assert(*c != *b);
          assert(*d != *a); assert(*d != *b);
        }
      }
    }
  }
  //Conversion between class and XML, test for equality
  {
    const std::vector<boost::shared_ptr<const Examples> > v = AddConst(ExamplesFactory().GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const Examples>& e)
      {
        assert(e);
        const std::string s { e->ToXml() };
        const boost::shared_ptr<const Examples> f(ExamplesFactory().FromXml(s));
        assert(*e == *f);
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const Examples> > v = AddConst(ExamplesFactory().GetTests());
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const Examples>& e = v[i];
      const std::string s { e->ToXml() };
      for (int j=0; j!=sz; ++j)
      {
        const boost::shared_ptr<const Examples>& f = v[j];
        const std::string t { f->ToXml() };
        if (i == j)
        {
          assert(*e == *f);
          assert( s ==  t);
        }
        else
        {
          assert(*e != *f);
          assert( s !=  t);
        }
      }
    }
  }
  //Test if unrated and rated examples are noticed as different
  {
    const boost::shared_ptr<Example> a = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<Example> b = ExampleFactory::Create("1",Competency::misc);
    const boost::shared_ptr<Example> c = ExampleFactory::Create("1",Competency::uninitialized);
    assert(*a == *a); assert(*a == *b); assert(*a != *c);
    assert(*b == *a); assert(*b == *b); assert(*b != *c);
    assert(*c != *a); assert(*c != *b); assert(*c == *c);
    std::vector<boost::shared_ptr<const Example> > v; v.push_back(a);
    std::vector<boost::shared_ptr<const Example> > w; w.push_back(b);
    std::vector<boost::shared_ptr<const Example> > x; x.push_back(c);
    const boost::shared_ptr<Examples> d = ExamplesFactory::Create(v);
    const boost::shared_ptr<Examples> e = ExamplesFactory::Create(w);
    const boost::shared_ptr<Examples> f = ExamplesFactory::Create(x);
    assert(*d == *d); assert(*d == *e); assert(*d != *f);
    assert(*e == *d); assert(*e == *e); assert(*e != *f);
    assert(*f != *d); assert(*f != *e); assert(*f == *f);
  }
  TRACE("Examples::Test finished successfully");
}

const std::string ribi::cmap::Examples::ToXml() const noexcept
{
  std::stringstream s;
  s << "<examples>";

  //const std::vector<boost::shared_ptr<const Example> > examples = c->GetExamples();
  const auto example = Get();
  std::for_each(example.begin(),example.end(),
    [&s](const boost::shared_ptr<const Example>& t)
    {
      s << t->ToXml();
    }
  );
  s << "</examples>";

  const std::string r = s.str();
  assert(r.size() >= 20);
  assert(r.substr(0,10) == "<examples>");
  assert(r.substr(r.size() - 11,11) == "</examples>");
  return r;
}

bool ribi::cmap::operator==(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  if (lhs.Get().size() != rhs.Get().size())
  {
    return false;
  }
  if (lhs.Get().empty()) { assert(rhs.Get().empty()); return true; }
  const std::vector<boost::shared_ptr<const Example> > v = lhs.Get();
  const std::vector<boost::shared_ptr<const Example> > w = rhs.Get();
  return std::equal(v.begin(),v.end(),w.begin(),
    [](const boost::shared_ptr<const Example>& a, const boost::shared_ptr<const Example>& b)
    {
      return *a == *b;
    }
  );
}

bool ribi::cmap::operator!=(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  return !(lhs == rhs);
}

bool ribi::cmap::operator<(const cmap::Examples& lhs, const cmap::Examples& rhs)
{
  if (lhs.Get().size() < rhs.Get().size()) return true;
  if (lhs.Get().size() > rhs.Get().size()) return false;
  assert(lhs.Get().size() == rhs.Get().size());
  const int sz = lhs.Get().size();
  for (int i = 0; i!=sz; ++i)
  {
    if (lhs.Get()[i] < rhs.Get()[i]) return true;
    if (lhs.Get()[i] > rhs.Get()[i]) return false;
  }
  return false;
}
