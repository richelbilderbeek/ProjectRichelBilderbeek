#include "trianglemeshcellfactory.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshface.h"

const boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::Create(
  const std::vector<boost::shared_ptr<Face>>& faces
)
{
  const boost::shared_ptr<Cell> cell {
    new Cell(faces)
  };

  for (auto face: faces)
  {
    assert(face);
    face->AddBelongsTo(cell);
  }

  assert(cell);
  return cell;
}
