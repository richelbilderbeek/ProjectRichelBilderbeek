#ifndef OPENFOAMFILENAMES_H
#define OPENFOAMFILENAMES_H

#include <string>
#include <vector>

#include "filename.h"

namespace ribi {
namespace foam {

///Filenames used for OpenFOAM
struct Filenames
{
  const std::vector<ribi::fileio::Filename> GetAll() const noexcept;

  ///The filename the resulting boundary (needed by OpenFoam) will be written to
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetBoundary() const noexcept;

  ///The filename the resulting faces will be written to
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetFaces() const noexcept;

  ///The filename the resulting neighbour (needed by OpenFOAM) will be written to
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetNeighbour() const noexcept;

  ///The filename that indicates that this is an OpenFOAM case
  const ribi::fileio::Filename GetOpenFoamCase() const noexcept;

  ///The filename for the OpenFOAM its controlDict
  const ribi::fileio::Filename GetOpenFoamControlDict() const noexcept;

  ///The filename of the OpenFOAM solver schemes
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetOpenFoamFvSchemes() const noexcept;

  ///The filename of the OpenFOAM solver solution
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetOpenFoamFvSolution() const noexcept;

  ///The filename for the OpenFOAM its case its pressure field
  const ribi::fileio::Filename GetOpenFoamPressureField() const noexcept;

  ///The filename for the OpenFOAM its case its TransportProperties
  const ribi::fileio::Filename GetOpenFoamTransportProperties() const noexcept;

  ///The filename for the OpenFOAM its case its velocity field
  const ribi::fileio::Filename GetOpenFoamVelocityField() const noexcept;

  ///The filename the resulting owner (needed by OpenFOAM) will be written to
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetOwner() const noexcept;

  ///The filename the resulting nodes will be written to
  ///Must use Win32 backslashes
  const ribi::fileio::Filename GetPoints() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const Filenames& filenames);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFILENAMES_H
