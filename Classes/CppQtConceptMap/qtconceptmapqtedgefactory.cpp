#include "qtconceptmapqtedgefactory.h"

#include <cassert>

#include "conceptmapedgefactory.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapnode.h"
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

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtEdgeFactory::GetTest(
  const int i,
  const boost::shared_ptr<QtNode>& from,
  const boost::shared_ptr<QtNode>& to
) const noexcept
{
  const auto tests = GetTests(from,to);
  assert(i >= 0);
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
      return q;
    }
  );
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
  TRACE("Started ribi::cmap::QtEdgeFactory::Test");
  TRACE("Finished ribi::cmap::QtEdgeFactory successfully");
}
#endif
