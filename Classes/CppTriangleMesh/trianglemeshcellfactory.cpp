#include "trianglemeshcellfactory.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshface.h"

const boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::Create(
  const std::vector<boost::shared_ptr<Face>>& faces
)
{
  #ifndef NDEBUG
  Test();
  #endif
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

#ifndef NDEBUG
void ribi::trim::CellFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::CellFactory::Test");
  TRACE("Finished ribi::trim::CellFactory::Test successfully");
}
#endif
