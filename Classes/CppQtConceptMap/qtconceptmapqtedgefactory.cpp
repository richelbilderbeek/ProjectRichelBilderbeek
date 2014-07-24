#include "qtconceptmapqtedgefactory.h"

#include <cassert>

#include "conceptmapedgefactory.h"
#include "qtconceptmapedge.h"

#include "trace.h"

ribi::cmap::QtEdgeFactory::QtEdgeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtEdgeFactory::Create(
  const boost::shared_ptr<Edge>& edge
) const noexcept
{
  assert(edge);
  boost::shared_ptr<QtEdge> qtedge{new QtEdge(edge)};
  assert(qtedge);
  return qtedge;
}

boost::shared_ptr<ribi::cmap::QtEdge> ribi::cmap::QtEdgeFactory::GetTest(const int i) const noexcept
{
  const auto tests = GetTests();
  assert(i >= 0);
  assert(i < static_cast<int>(tests.size()));
  return tests[i];
}

std::vector<boost::shared_ptr<ribi::cmap::QtEdge>> ribi::cmap::QtEdgeFactory::GetTests() const noexcept
{
  std::vector<boost::shared_ptr<QtEdge>> qtedges;
  const auto v = EdgeFactory().GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(qtedges),
    [](const boost::shared_ptr<Edge>& c)
    {
      const boost::shared_ptr<QtEdge> q{QtEdgeFactory().Create(c)};
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
