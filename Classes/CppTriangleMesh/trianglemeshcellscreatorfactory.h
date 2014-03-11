#ifndef TRIANGLEMESHCELLSCREATORFACTORY_H
#define TRIANGLEMESHCELLSCREATORFACTORY_H

#include <iosfwd>
//#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/quantity.hpp>
#include "trianglemeshfwd.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///The only class to use Cell its constructor
struct CellsCreatorFactory
{
  CellsCreatorFactory();

  boost::shared_ptr<CellsCreator> Create(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy
  ) const noexcept;


  ///Create a cell in the shape of a prism
  /*

      +
     /|\
    +---+
    | | |
    | + |
    |/ \|
    +---+

  */
  boost::shared_ptr<CellsCreator> CreateTestPrism(
    const CreateVerticalFacesStrategy strategy
  ) const noexcept;


  boost::shared_ptr<CellsCreator> CreateTestCube(
    const CreateVerticalFacesStrategy strategy
  ) const noexcept;
  ///Create two prisms-shaped cell to form a cube
  /*

      +---+
     /|\ /|
    +---+ |
    | | | |
    | +-|-+
    |/ \|/
    +---+

  */

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi


#endif // TRIANGLEMESHCELLSCREATORFACTORY_H
