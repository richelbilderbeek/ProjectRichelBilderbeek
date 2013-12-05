#include "openfoamfilenames.h"

#include "parameterfilenamesopenfoam.h"

#include <cassert>
#include <sstream>

#include "fileio.h"
#include "xml.h"

const std::vector<ribi::fileio::Filename> ParameterFilenamesOpenFoam::GetAll() const noexcept
{
  return {
    this->GetBoundary(),
    this->GetFaces(),
    this->GetNeighbour(),
    this->GetNodes(),
    this->GetOpenFoamCase(),
    this->GetOwner()
  };
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetBoundary() const noexcept
{
  return ribi::fileio::Filename("constant\\polyMesh\\boundary");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetBoundaryPostprocessed() const noexcept
{
  return ribi::fileio::Filename(GetBoundary().Get() + "_post");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetFaces() const noexcept
{
  return ribi::fileio::Filename("constant\\polyMesh\\faces");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetFacesPostprocessed() const noexcept
{
  return ribi::fileio::Filename(GetFaces().Get() + "_post");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetNeighbour() const noexcept
{
  return ribi::fileio::Filename("constant\\polyMesh\\neighbour");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetNeighbourPostprocessed() const noexcept
{
  return ribi::fileio::Filename(GetNeighbour().Get() + "_post");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetNodes() const noexcept
{
  return ribi::fileio::Filename("constant\\polyMesh\\points");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetNodesPostprocessed() const noexcept
{
  return ribi::fileio::Filename(GetNodes().Get() + "_post");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamCase() const noexcept
{
  return ribi::fileio::Filename("case.foam");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamControlDict() const noexcept
{
  return ribi::fileio::Filename("system\\controlDict");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamFvSchemes() const noexcept
{
  return ribi::fileio::Filename("system\\fvSchemes");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamFvSolution() const noexcept
{
  return ribi::fileio::Filename("system\\fvSolution");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamPressureField() const noexcept
{
  return ribi::fileio::Filename("0\\p");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamTransportProperties() const noexcept
{
  return ribi::fileio::Filename("constant\\transportProperties");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOpenFoamVelocityField() const noexcept
{
  return ribi::fileio::Filename("0\\U");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOwner() const noexcept
{
  return ribi::fileio::Filename("constant\\polyMesh\\owner");
}

const ribi::fileio::Filename ParameterFilenamesOpenFoam::GetOwnerPostprocessed() const noexcept
{
  return ribi::fileio::Filename(GetOwner().Get() + "_post");
}

std::ostream& operator<<(std::ostream& os, const ParameterFilenamesOpenFoam& filenames)
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("filename_boundary",filenames.GetBoundary())
    << ribi::xml::ToXml("filename_faces",filenames.GetFaces())
    << ribi::xml::ToXml("filename_neightbour",filenames.GetNeighbour())
    << ribi::xml::ToXml("filename_nodes",filenames.GetNodes())
    << ribi::xml::ToXml("filename_openfoam",filenames.GetOpenFoamCase())
    << ribi::xml::ToXml("filename_owner",filenames.GetOwner())
  ;

  os << ribi::xml::ToXml("parameter_filenames_openfoam",s.str());
  return os;
}
