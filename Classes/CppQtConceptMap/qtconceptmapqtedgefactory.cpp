#include "qtconceptmapqtedgefactory.h"

#include <cassert>

#include "conceptmapedgefactory.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapnode.h"
#include "testtimer.h"
#include "trace.h"

ribi::cmap::QtEdgeFactory::QtEdgeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtEdgeFactory::Create(
  const boost::shared_ptr<Edge>& edge,
  QtNode* const from,
  QtNode* const to
) const noexcept
{
  assert(edge);
  boost::shared_ptr<QtEdge> qtedge{new QtEdge(edge,from,to)};
  assert(qtedge);
  return qtedge;
}

int ribi::cmap::QtEdgeFactory::GetNumberOfTests() const noexcept
{
  return EdgeFactory().GetNumberOfTests();
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtEdgeFactory::GetTest(
  const int i,
  const boost::shared_ptr<QtNode>& from,
  const boost::shared_ptr<QtNode>& to
) const noexcept
{
  const auto tests = GetTests(from,to);
  assert(i >= 0);
  #ifndef NDEBUG
  if(i >= static_cast<int>(tests.size()))
  {
    TRACE("BREAK");
  }
  #endif
  assert(i < static_cast<int>(tests.size()));
  return tests[i];
}

std::vector<boost::shared_ptr<ribi::cmap::QtEdge>> ribi::cmap::QtEdgeFactory::GetTests(
  const boost::shared_ptr<QtNode>& from,
  const boost::shared_ptr<QtNode>& to
) const noexcept
{
  std::vector<boost::shared_ptr<QtEdge>> qtedges;
  const auto v = EdgeFactory().GetTests(from->GetNode(),to->GetNode());
  std::transform(v.begin(),v.end(),std::back_inserter(qtedges),
    [from,to](const boost::shared_ptr<Edge>& c)
    {
      const boost::shared_ptr<QtEdge> q{QtEdgeFactory().Create(c,from.get(),to.get())};
      assert(q);
      q->SetX((from->GetX() + to->GetX()) / 2.0);
      q->SetY((from->GetY() + to->GetY()) / 2.0);
      return q;
    }
  );
  assert(GetNumberOfTests() == static_cast<int>(qtedges.size()));
  return qtedges;
}

#ifndef NDEBUG
void ribi::cmap::QtEdgeFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
