#ifndef RIBI_TRIANGLEMESHBUILDER_H
#define RIBI_TRIANGLEMESHBUILDER_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "openfoamfwd.h"
#include "openfoampatchfieldtype.h"
#include "trianglemeshfwd.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///TriangleMeshBuilder creates all files needed by OpenFOAM
///(in the correct folder) from a collection of Cells
///These Cells can be created by TriangleMeshCellCreator
///The Cells' Faces are assigned a Boundary, but these
///may be reassigned before feeding the cells to TriangleMeshBuilder
///Use the pimpl idiom, implementation is in TriangleMeshBuilderImpl
class TriangleMeshBuilder
{
  friend class Dialog;

  explicit TriangleMeshBuilder(
    const std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells,
    const std::string& mesh_filename,
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
    const CreateVerticalFacesStrategy strategy,
    const bool verbose
  );

  int CountCells() const noexcept;
  int CountFaces() const noexcept;

  private:
  TriangleMeshBuilder(const TriangleMeshBuilder& ) = delete;
  //TriangleMeshBuilder(      TriangleMeshBuilder&&) = delete;
  TriangleMeshBuilder& operator=(const TriangleMeshBuilder& ) = delete;
  //TriangleMeshBuilder& operator=(      TriangleMeshBuilder&&) = delete;
  ~TriangleMeshBuilder() noexcept;

  boost::shared_ptr<TriangleMeshBuilderImpl> m_impl;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend void boost::checked_delete<>(      TriangleMeshBuilder*);
  friend void boost::checked_delete<>(const TriangleMeshBuilder*);
  friend class boost::detail::sp_ms_deleter<      TriangleMeshBuilder>;
  friend class boost::detail::sp_ms_deleter<const TriangleMeshBuilder>;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHBUILDER_H
