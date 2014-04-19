#include "trianglemeshcellscreatorfactory.h"
#include <cassert>

#include "trianglemeshcell.h"
#include "trianglemeshcellfactory.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshtemplate.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"

ribi::trim::CellsCreatorFactory::CellsCreatorFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::trim::CellsCreator> ribi::trim::CellsCreatorFactory::Create(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  assert(t);
  const boost::shared_ptr<CellsCreator> creator(
    new CellsCreator(t,n_layers,layer_height,strategy,*this)
  );
  assert(creator);
  return creator;
}

boost::shared_ptr<ribi::trim::CellsCreator> ribi::trim::CellsCreatorFactory::CreateTestCube(
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  const boost::shared_ptr<Template> my_template {
    Template::CreateTest(1)
  };
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
  #ifndef NDEBUG
  const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };
  assert(cells.size() == 2 && "A cube consists out of two prisms");
  for (int i=0; i!=2; ++i)
  {
    const std::vector<boost::shared_ptr<Face>> faces { cells[i]->GetFaces() };
    for (const auto face: faces)
    {
      assert(face);
    }
  }
  #endif
  return cells_creator;
}

boost::shared_ptr<ribi::trim::CellsCreator> ribi::trim::CellsCreatorFactory::CreateTestPrism(
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  const CellsCreatorFactory cells_creator_factory;
  const boost::shared_ptr<Template> my_template
   = Template::CreateTest(0);
  assert(my_template);
  assert(my_template->CountFaces() == 1);
  const int n_layers = 2;
  const boost::shared_ptr<CellsCreator> cells_creator
    = cells_creator_factory.Create(
      my_template,
      n_layers,
      1.0 * boost::units::si::meter,
      strategy
  );
  assert(cells_creator);
  #ifndef NDEBUG
  const std::vector<boost::shared_ptr<Cell>> cells
    = cells_creator->GetCells();
  assert(cells.size() == 1 && "A prism consists out of 1 prisms");
  for (int i=0; i!=1; ++i)
  {
    const std::vector<boost::shared_ptr<Face>> faces
      = cells[i]->GetFaces();
    for (const auto face: faces)
    {
      assert(face);
    }
  }
  #endif
  return cells_creator;
}

#ifndef NDEBUG
void ribi::trim::CellsCreatorFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::CellsCreatorFactory::Test");
  const CellsCreatorFactory cells_creator;
  const CreateVerticalFacesStrategies create_vertical_faces_strategies;
  //Create prism
  for (CreateVerticalFacesStrategy strategy: create_vertical_faces_strategies.GetAll())
  {
    const boost::shared_ptr<CellsCreator> prism
      = cells_creator.CreateTestPrism(strategy);
    assert(prism);
    const std::vector<boost::shared_ptr<Cell>> cells
      = prism->GetCells();
    TRACE(cells.size());
    assert(cells.size() == 1 && "A prism consists of 1 prisms");
    assert(cells[0]);
  }
  //Create cube
  for (CreateVerticalFacesStrategy strategy: create_vertical_faces_strategies.GetAll())
  {
    boost::shared_ptr<CellsCreator> cube
      = cells_creator.CreateTestCube(strategy);
    assert(cube);
    const std::vector<boost::shared_ptr<ribi::trim::Cell>> cells
      = cube->GetCells();
    assert(cells.size() == 2 && "A cube consists of 2 prisms");
    assert(cells[0]);
    assert(cells[1]);
  }
  TRACE("Finished ribi::trim::CellsCreatorFactory::Test successfully");
}
#endif
