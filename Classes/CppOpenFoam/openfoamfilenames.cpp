#include "openfoamfilenames.h"

//#include "parameterfilenamesopenfoam.h"

#include <cassert>
#include <sstream>

#include "fileio.h"
#include "xml.h"

const std::vector<ribi::fileio::Filename> ribi::foam::Filenames::GetAll() const noexcept
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

ribi::fileio::Filename ribi::foam::Filenames::GetAlphat() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "alphat"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetBoundary() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "boundary"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetFaces() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "faces"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetNeighbour() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "neighbour"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetCase() const noexcept
{
  return ribi::fileio::Filename("case.foam");
}

ribi::fileio::Filename ribi::foam::Filenames::GetControlDict() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "controlDict"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetFvSchemes() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "fvSchemes"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetFvSolution() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::FileIo().GetPathSeperator()
    + "fvSolution"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetOwner() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "owner"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetPoints() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "polyMesh"
    + fileio::FileIo().GetPathSeperator()
    + "points"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetPressureField() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "p"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetTemperatureField() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::FileIo().GetPathSeperator()
    + "T"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetThermophysicalProperties() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "thermophysicalProperties"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetTransportProperties() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "transportProperties"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetTurbulenceProperties() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::FileIo().GetPathSeperator()
    + "turbulenceProperties"
  );
}

ribi::fileio::Filename ribi::foam::Filenames::GetVelocityField() const noexcept
{
  return ribi::fileio::Filename(
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
