#include "trianglemeshcellfactory.h"

#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshtemplate.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"

ribi::trim::CellFactory::CellFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::Create(
  const std::vector<boost::shared_ptr<Face>>& faces,
  const CreateVerticalFacesStrategy
  #ifndef NDEBUG
    strategy
  #endif
)
{
  //Give every Cell some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;

  #ifndef NDEBUG
  if (strategy == CreateVerticalFacesStrategy::one_face_per_square ) { assert(faces.size() == 5 && "A cell (in the shape of a prism) consists out of 5 faces"); }
  if (strategy == CreateVerticalFacesStrategy::two_faces_per_square) { assert(faces.size() == 8 && "A cell (in the shape of a prism) consists out of 8 faces"); }
  #endif
  const boost::shared_ptr<Cell> cell {
    new Cell(faces,n,*this)
  };
  assert(cell);

  for (auto face: faces)
  {
    assert(face);
    face->AddBelongsTo(cell);
  }

  return cell;
}

std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellFactory::CreateTestCube(
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  const boost::shared_ptr<Template> my_template {
    Template::CreateTest(1)
  };
  assert(my_template);
  assert(my_template->CountFaces() == 2);
  const int n_layers = 2;
  const boost::shared_ptr<CellsCreator> cells_creator {
    CellsCreatorFactory().Create(
      my_template,
      n_layers,
      1.0 * boost::units::si::meter,
      strategy
    )
  };
  const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };

  assert(cells.size() == 2 && "A cube consists out of two prisms");
  #ifndef NDEBUG
  for (int i=0; i!=2; ++i)
  {
    const std::vector<boost::shared_ptr<Face>> faces { cells[i]->GetFaces() };
    for (const auto face: faces)
    {
      assert(face);
      assert(face->GetPoints().size() == 3 || face->GetPoints().size() == 4);
    }
  }
  #endif

  return cells;
}

boost::shared_ptr<ribi::trim::Cell> ribi::trim::CellFactory::CreateTestPrism(
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  const std::vector<boost::shared_ptr<Face> > faces {
    FaceFactory().CreateTestPrism(strategy)
  };
  const boost::shared_ptr<Cell> prism {
    CellFactory().Create(faces,strategy)
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
  #ifdef ISSUE_168
  for (const auto strategy: CreateVerticalFacesStrategies().GetAll())
  {
    const boost::shared_ptr<Cell> prism {
      CellFactory().CreateTestPrism(strategy)
    };
    if (strategy == CreateVerticalFacesStrategy::one_face_per_square ) { assert(prism->GetFaces().size() == 5 && "A prism has 5 faces (as the vertical faces square)"); }
    if (strategy == CreateVerticalFacesStrategy::two_faces_per_square) { assert(prism->GetFaces().size() == 8 && "A prism has 5 or 8 faces (as the vertical faces are split into 2 triangles)"); }
    for (auto& face: prism->GetFaces())
    {
      face->SetCorrectWinding();
    }
  }
  #endif //~#ifdef ISSUE_168
  //Create cube
  for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
  {
    const std::vector<boost::shared_ptr<Cell>> cube {
      CellFactory().CreateTestCube(strategy)
    };
    assert(cube.size() == 2 && "A cube consists of two prisms");

  }
  TRACE("Finished ribi::trim::CellFactory::Test successfully");
}
#endif
