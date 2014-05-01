#include "openfoamfilenames.h"

//#include "parameterfilenamesopenfoam.h"

#include <cassert>
#include <sstream>

#include "fileio.h"
#include "xml.h"

std::vector<std::string> ribi::foam::Filenames::GetAll() const noexcept
{
  return {
    this->GetBoundary(),
    this->GetFaces(),
    this->GetNeighbour(),
    this->GetCase(),
    this->GetOwner(),
    this->GetPoints()
  };
}

std::string ribi::foam::Filenames::GetAlphat() const noexcept
{
  return std::string(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "alphat"
  );
}

std::string ribi::foam::Filenames::GetBoundary() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "boundary"
  );
}

std::string ribi::foam::Filenames::GetFaces() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "faces"
  );
}

std::string ribi::foam::Filenames::GetNeighbour() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "neighbour"
  );
}

std::string ribi::foam::Filenames::GetCase() const noexcept
{
  return std::string("case.foam");
}

std::string ribi::foam::Filenames::GetControlDict() const noexcept
{
  return std::string(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "controlDict"
  );
}

std::string ribi::foam::Filenames::GetFvSchemes() const noexcept
{
  return std::string(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "fvSchemes"
  );
}

std::string ribi::foam::Filenames::GetFvSolution() const noexcept
{
  return std::string(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "fvSolution"
  );
}

std::string ribi::foam::Filenames::GetOwner() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "owner"
  );
}

std::string ribi::foam::Filenames::GetPoints() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "points"
  );
}

std::string ribi::foam::Filenames::GetPressureField() const noexcept
{
  return std::string(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "p"
  );
}

std::string ribi::foam::Filenames::GetTemperatureField() const noexcept
{
  return std::string(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "T"
  );
}

std::string ribi::foam::Filenames::GetThermophysicalProperties() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "thermophysicalProperties"
  );
}

std::string ribi::foam::Filenames::GetTransportProperties() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "transportProperties"
  );
}

std::string ribi::foam::Filenames::GetTurbulenceProperties() const noexcept
{
  return std::string(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "turbulenceProperties"
  );
}

std::string ribi::foam::Filenames::GetVelocityField() const noexcept
{
  return std::string(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "U"
  );
}


std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Filenames& filenames) noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("filename_boundary",filenames.GetBoundary())
    << ribi::xml::ToXml("filename_faces",filenames.GetFaces())
    << ribi::xml::ToXml("filename_neightbour",filenames.GetNeighbour())
    << ribi::xml::ToXml("filename_openfoam",filenames.GetCase())
    << ribi::xml::ToXml("filename_owner",filenames.GetOwner())
    << ribi::xml::ToXml("filename_points",filenames.GetPoints())
  ;

  os << ribi::xml::ToXml("parameter_filenames_openfoam",s.str());
  return os;
}
