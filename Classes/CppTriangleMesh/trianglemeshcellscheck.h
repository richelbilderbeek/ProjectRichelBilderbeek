#ifndef TRIANGLEMESHCELLSCHECK_H
#define TRIANGLEMESHCELLSCHECK_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Checks if Cells are OK
void CellsCheck(const std::vector<boost::shared_ptr<Cell>>& cells);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHCELLSCHECK_H
