#ifndef RIBI_TRIANGLEMESHCELLSCHECK_H
#define RIBI_TRIANGLEMESHCELLSCHECK_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Checks if Cells are OK
void CellsCheck(const std::vector<boost::shared_ptr<Cell>>& cells) noexcept;

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHCELLSCHECK_H
