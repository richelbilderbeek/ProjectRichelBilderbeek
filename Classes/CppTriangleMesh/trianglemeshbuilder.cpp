#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshbuilder.h"

#include <boost/make_shared.hpp>

#include "trace.h"
#include "trianglemeshbuilderimpl.h"

#pragma GCC diagnostic pop

ribi::trim::TriangleMeshBuilder::TriangleMeshBuilder(
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::string& mesh_filename,
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
  const CreateVerticalFacesStrategy strategy,
  const bool verbose
) : m_impl(
      //boost::make_shared<TriangleMeshBuilderImpl>(
      new TriangleMeshBuilderImpl(
        cells,
        mesh_filename,
        boundary_to_patch_field_type_function,
        strategy,
        verbose
      )
    )
{
  #ifndef NDEBUG
  Test();
  #endif

}

int ribi::trim::TriangleMeshBuilder::CountCells() const noexcept
{
  return m_impl->CountCells();
}

int ribi::trim::TriangleMeshBuilder::CountFaces() const noexcept
{
  return m_impl->CountFaces();
}

#ifndef NDEBUG
void ribi::trim::TriangleMeshBuilder::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::TriangleMeshBuilder::Test");
  TRACE("Finished ribi::trim::TriangleMeshBuilder::Test successfully");
}
#endif


