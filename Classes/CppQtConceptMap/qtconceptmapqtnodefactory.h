#ifndef QTCONCEPTMAPQTNODEFACTORY_H
#define QTCONCEPTMAPQTNODEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct QtNodeFactory
{
  QtNodeFactory();

  boost::shared_ptr<QtNode> Create(
    const boost::shared_ptr<Node>& node
  ) const noexcept;


  ///Obtain a Node or CenterNode from an XML std::string
  boost::shared_ptr<Node> FromXml(const std::string& s) const noexcept;

  ///Obtain testing nodes
  int GetNumberOfTests() const noexcept;
  std::vector<boost::shared_ptr<QtNode>> GetTests() const noexcept;
  boost::shared_ptr<QtNode> GetTest(const int test) const noexcept;

  private:
  #ifndef NDEBUG
  void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPQTNODEFACTORY_H
