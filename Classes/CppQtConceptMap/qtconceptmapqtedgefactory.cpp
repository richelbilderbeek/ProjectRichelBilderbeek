#include "qtconceptmapqtedgefactory.h"

#include <cassert>

#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapnode.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtnodefactory.h"
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
  const QtEdge::From& from,
  const QtEdge::From& to
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
      //const boost::shared_ptr<QtEdge> q{QtEdgeFactory().Create(c,from.get(),to.get())};
      const boost::shared_ptr<QtEdge> q{QtEdgeFactory().Create(c,from,to)};
      assert(q);
      q->GetEdge()->GetNode()->SetX((from->GetCenterX() + to->GetCenterX()) / 2.0);
      q->GetEdge()->GetNode()->SetY((from->GetCenterY() + to->GetCenterY()) / 2.0);
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
  QtNodeFactory();
  QtNodeFactory().GetTest(0);
  QtEdgeFactory().GetTest(0,QtNodeFactory().GetTest(0),QtNodeFactory().GetTest(0));
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
