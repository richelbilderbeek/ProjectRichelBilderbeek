#include "trianglemeshcellfactory.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshface.h"
#include "trace.h"

ribi::trim::CellFactory::CellFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::Create(
  const std::vector<boost::shared_ptr<Face>>& faces
)
{
  const boost::shared_ptr<Cell> cell {
    new Cell(faces,*this)
  };

  for (auto face: faces)
  {
    assert(face);
    face->AddBelongsTo(cell);
  }

  assert(cell);
  return cell;
}

const boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Face> > faces {
    Face::CreateTestPrism()
  };
  const boost::shared_ptr<Cell> prism {
    CellFactory().Create(faces)
  };
  assert(prism);
  return prism;
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
