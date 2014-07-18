#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshbuilder.h"

#include <cassert>

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
) : m_impl{}
{
  #ifndef NDEBUG
  Test();
  #endif
  boost::shared_ptr<TriangleMeshBuilderImpl> impl{
    new TriangleMeshBuilderImpl(
      cells,
      mesh_filename,
      boundary_to_patch_field_type_function,
      strategy,
      verbose
    )
  };
  m_impl = impl;
  assert(m_impl);
}

ribi::trim::TriangleMeshBuilder::~TriangleMeshBuilder() noexcept
{
  //OK
}

int ribi::trim::TriangleMeshBuilder::CountCells() const noexcept
{
  assert(m_impl);
  return m_impl->CountCells();
}

int ribi::trim::TriangleMeshBuilder::CountFaces() const noexcept
{
  assert(m_impl);
  return m_impl->CountFaces();
}

#ifndef NDEBUG
void ribi::trim::TriangleMeshBuilder::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::TriangleMeshBuilder::Test");
  TRACE("Finished ribi::trim::TriangleMeshBuilder::Test successfully");
}
#endif


