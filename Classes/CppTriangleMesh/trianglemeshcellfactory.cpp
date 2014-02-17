#include "trianglemeshcellfactory.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshtemplate.h"
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
  //Give every Cell some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;

  const boost::shared_ptr<Cell> cell {
    new Cell(faces,n,*this)
  };

  for (auto face: faces)
  {
    assert(face);
    face->AddBelongsTo(cell);
  }

  assert(cell);
  return cell;
}

const std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellFactory::CreateTestCube() const noexcept
{
  const boost::shared_ptr<Template> my_template {
    Template::CreateTest(1)
  };
  assert(my_template->CountFaces() == 2);
  const int n_layers = 2;
  const boost::shared_ptr<CellsCreator> cells_creator {
    CellsCreatorFactory().Create(my_template,n_layers,1.0 * boost::units::si::meter)
  };
  assert(cells_creator->GetCells().size() == 2);
  const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };

  assert(cells.size() == 2 && "A cube consists out of two prisms");
  assert(cells[0]->GetFaces().size() == 8 && "A prism consists out of 8 faces");
  assert(cells[1]->GetFaces().size() == 8 && "A prism consists out of 8 faces");
  #ifndef NDEBUG
  for (int i=0; i!=2; ++i)
  {
    const std::vector<boost::shared_ptr<Face>> faces { cells[i]->GetFaces() };
    for (const auto face: faces)
    {
      assert(face);
      assert(face->GetPoints().size() == 3);
    }
  }
  #endif

  return cells;
}

const boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Face> > faces {
    FaceFactory().CreateTestPrism()
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
  //Create prism
  {
    const boost::shared_ptr<Cell> prism {
      CellFactory().CreateTestPrism()
    };
    assert(prism->GetFaces().size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");
  }
  //Create cube
  {
    const std::vector<boost::shared_ptr<Cell>> cube {
      CellFactory().CreateTestCube()
    };
    assert(cube.size() == 2 && "A cube consists of two prisms");
    assert(cube[0]->GetFaces().size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");
    assert(cube[1]->GetFaces().size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");

  }
  TRACE("Finished ribi::trim::CellFactory::Test successfully");
}
#endif
