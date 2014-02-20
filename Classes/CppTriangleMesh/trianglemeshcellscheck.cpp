#include "trianglemeshcellscheck.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshtemplate.h"
#include "trace.h"

void ribi::trim::CellsCheck(
  const std::vector<boost::shared_ptr<Cell>>& cells
)
{
  if (cells.empty()) return;

  //All Cells must be in use as much time
  {
    const int use_count = cells[0].use_count();
    assert(use_count == 1);
    for (const auto& cell: cells)
    {
      assert(cell.use_count() == use_count
        && "All Cells must have an equal use_count");
    }
  }

  for (const auto cell: cells)
  {
    assert(cell);
    assert(cell->GetFaces().size() == 8);
    for (const auto face: cell->GetFaces())
    {
      assert(face);
      assert(face->GetPoints().size() == 3);
      for (const auto point: face->GetPoints())
      {
        assert(point);
      }
    }
  }
}
