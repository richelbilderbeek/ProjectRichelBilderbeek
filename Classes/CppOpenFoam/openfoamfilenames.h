#ifndef OPENFOAMFILENAMES_H
#define OPENFOAMFILENAMES_H

#include <string>
#include <vector>

#include "fileio.h"
//

namespace ribi {
namespace foam {

///Filenames used for OpenFOAM
struct Filenames
{
  const std::vector<std::string> GetAll() const noexcept;

  ///The filename for the OpenFOAM its case its velocity field
  std::string GetAlphat() const noexcept;

  ///The filename the resulting boundary (needed by OpenFoam) will be written to
  ///Must use Win32 backslashes
  std::string GetBoundary() const noexcept;

  ///The filename that indicates that this is an OpenFOAM case
  std::string GetCase() const noexcept;

  ///The filename for the OpenFOAM its controlDict
  std::string GetControlDict() const noexcept;

  ///The filename the resulting faces will be written to
  ///Must use Win32 backslashes
  std::string GetFaces() const noexcept;

  ///The filename of the OpenFOAM solver schemes
  ///Must use Win32 backslashes
  std::string GetFvSchemes() const noexcept;

  ///The filename of the OpenFOAM solver solution
  ///Must use Win32 backslashes
  std::string GetFvSolution() const noexcept;

  ///The filename the resulting neighbour (needed by OpenFOAM) will be written to
  ///Must use Win32 backslashes
  std::string GetNeighbour() const noexcept;

  ///The filename that indicates that this is an OpenFOAM case
  std::string GetOpenFoamCase() const noexcept { return GetCase(); }

  ///The filename for the OpenFOAM its controlDict
  std::string GetOpenFoamControlDict() const noexcept { return GetControlDict(); }

  ///The filename of the OpenFOAM solver schemes
  std::string GetOpenFoamFvSchemes() const noexcept { return GetFvSchemes(); }

  ///The filename of the OpenFOAM solver solution
  std::string GetOpenFoamFvSolution() const noexcept { return GetFvSolution(); }

  ///The filename for the OpenFOAM its case its pressure field
  std::string GetOpenFoamPressureField() const noexcept { return GetPressureField(); }

  ///The filename for the OpenFOAM its case its TransportProperties
  std::string GetOpenFoamTransportProperties() const noexcept { return GetTransportProperties(); }

  ///The filename for the OpenFOAM its case its velocity field
  std::string GetOpenFoamVelocityField() const noexcept { return GetVelocityField(); }

  ///The filename the resulting owner (needed by OpenFOAM) will be written to
  ///Must use Win32 backslashes
  std::string GetOwner() const noexcept;

  ///The filename the resulting nodes will be written to
  ///Must use Win32 backslashes
  std::string GetPoints() const noexcept;

  ///The filename for the OpenFOAM its case its pressure field
  std::string GetPressureField() const noexcept;

  ///The filename for the OpenFOAM its case its pressure field
  std::string GetTemperatureField() const noexcept;

  ///The filename for the OpenFOAM its case its thermophysicalProperties
  std::string GetThermophysicalProperties() const noexcept;

  ///The filename for the OpenFOAM its case its TransportProperties
  std::string GetTransportProperties() const noexcept;

  ///The filename for the OpenFOAM its case its TransportProperties
  std::string GetTurbulenceProperties() const noexcept;

  ///The filename for the OpenFOAM its case its velocity field
  std::string GetVelocityField() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const Filenames& filenames) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFILENAMES_H
