#include "qtconceptmapqtnodefactory.h"

#include <cassert>

#include "conceptmapnodefactory.h"
#include "qtconceptmapnode.h"

#include "trace.h"

ribi::cmap::QtNodeFactory::QtNodeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtNodeFactory::Create(
  const boost::shared_ptr<Node>& node
) const noexcept
{
  assert(node);
  boost::shared_ptr<QtNode> qtnode{new QtNode(node)};
  assert(qtnode);
  return qtnode;
}

boost::shared_ptr<ribi::cmap::QtNode> ribi::cmap::QtNodeFactory::GetTest(const int i) const noexcept
{
  const auto tests = GetTests();
  assert(i >= 0);
  assert(i < static_cast<int>(tests.size()));
  return tests[i];
}

std::vector<boost::shared_ptr<ribi::cmap::QtNode>> ribi::cmap::QtNodeFactory::GetTests() const noexcept
{
  std::vector<boost::shared_ptr<QtNode>> qtnodes;
  const auto v = NodeFactory().GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(qtnodes),
    [](const boost::shared_ptr<Node>& c)
    {
      const boost::shared_ptr<QtNode> q{QtNodeFactory().Create(c)};
      assert(q);
      return q;
    }
  );
  return qtnodes;
}

#ifndef NDEBUG
void ribi::cmap::QtNodeFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtNodeFactory::Test");
  TRACE("Finished ribi::cmap::QtNodeFactory successfully");
}
#endif
