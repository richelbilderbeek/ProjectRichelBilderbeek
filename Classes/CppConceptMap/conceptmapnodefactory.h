#ifndef CONCEPTMAPNODEFACTORY_H
#define CONCEPTMAPNODEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct Node;

///Factory for creating Node instances
struct NodeFactory
{
  NodeFactory();

  const boost::shared_ptr<Node> Create(
    const boost::shared_ptr<Concept>& concept,
    const double x = 0.0,
    const double y = 0.0
  ) const noexcept;

  const boost::shared_ptr<Node> CreateFromStrings(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0
  ) const noexcept;

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  const boost::shared_ptr<Node> DeepCopy(
    const boost::shared_ptr<const cmap::Node>& node
  ) const noexcept;
  #endif

  ///Obtain a Node or CenterNode from an XML std::string
  const boost::shared_ptr<Node> FromXml(const std::string& s) const noexcept;

  ///Obtain testing nodes
  const std::vector<boost::shared_ptr<Node> > GetTests() const noexcept;
  const boost::shared_ptr<Node> GetTest(const int test) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPNODEFACTORY_H
