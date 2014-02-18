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

const ribi::fileio::Filename ribi::foam::Filenames::GetAlphat() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::GetPathSeperator()
    + "alphat"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetBoundary() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "polyMesh"
    + fileio::GetPathSeperator()
    + "boundary"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetFaces() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "polyMesh"
    + fileio::GetPathSeperator()
    + "faces"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetNeighbour() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "polyMesh"
    + fileio::GetPathSeperator()
    + "neighbour"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetCase() const noexcept
{
  return ribi::fileio::Filename("case.foam");
}

const ribi::fileio::Filename ribi::foam::Filenames::GetControlDict() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::GetPathSeperator()
    + "controlDict"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetFvSchemes() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::GetPathSeperator()
    + "fvSchemes"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetFvSolution() const noexcept
{
  return ribi::fileio::Filename(
      "system"
    + fileio::GetPathSeperator()
    + "fvSolution"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetOwner() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "polyMesh"
    + fileio::GetPathSeperator()
    + "owner"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetPoints() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "polyMesh"
    + fileio::GetPathSeperator()
    + "points"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetPressureField() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::GetPathSeperator()
    + "p"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetThermophysicalProperties() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "thermophysicalProperties"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetTransportProperties() const noexcept
{
  return ribi::fileio::Filename(
      "constant"
    + fileio::GetPathSeperator()
    + "transportProperties"
  );
}

const ribi::fileio::Filename ribi::foam::Filenames::GetVelocityField() const noexcept
{
  return ribi::fileio::Filename(
      "0"
    + fileio::GetPathSeperator()
    + "U"
  );
}


std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Filenames& filenames)
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
