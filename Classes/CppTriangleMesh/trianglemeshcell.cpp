#include "trianglemeshcell.h"

#include <iostream>

#include "Shiny.h"

#include "trianglemeshcellfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trace.h"
#include "xml.h"

ribi::trim::Cell::Cell(
  const std::vector<boost::shared_ptr<Face>>& faces,
  const CellFactory&)
  : m_faces(faces),
    m_index{-1}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(faces.size() == 8);
}

const ribi::Coordinat3D ribi::trim::Cell::CalculateCenter() const noexcept
{
  PROFILE_FUNC();
  ribi::Coordinat3D center;
  int cnt = 0;
  for(boost::shared_ptr<const Face> face: m_faces)
  {

    for(auto point: face->GetPoints())
    {
      const ribi::Coordinat3D coordinat(
        point->GetCoordinat()->GetX(),
        point->GetCoordinat()->GetY(),
        point->GetZ().value()
      );
      center += coordinat;
      ++cnt;
    }
  }
  center /= static_cast<double>(cnt);
  return center;
}


const std::vector<boost::shared_ptr<const ribi::trim::Face>> ribi::trim::Cell::GetFaces() const noexcept
{
  return AddConst(m_faces);
}

#ifndef NDEBUG
void ribi::trim::Cell::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Cell::Test");
  //Do not use the Cell its contructor! Use CellFactory::Create instead!
  const boost::shared_ptr<Cell> prism {
    CellFactory().CreateTestPrism()
  };
  assert(prism);
  assert(prism->GetFaces().size() == 8);
  const std::vector<boost::shared_ptr<Face>> faces {
    prism->GetFaces()
  };
  assert(
    std::count_if(faces.begin(),faces.end(),
      [](const boost::shared_ptr<Face> face)
      {
        assert(face);
        assert(face->GetOwner());
        return face->GetNeighbour().get();
      }
    ) == 0
  );
  TRACE("Finished ribi::trim::Cell::Test successfully");
}
#endif

bool ribi::trim::operator==(const ribi::trim::Cell& lhs, const ribi::trim::Cell& rhs)
{
  return lhs.GetFaces() == rhs.GetFaces();
}

bool ribi::trim::operator!=(const ribi::trim::Cell& lhs, const ribi::trim::Cell& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Cell& cell)
{
  const auto faces = cell.GetFaces();
  os
    << ribi::xml::ToXml("faces",faces.begin(),faces.end())
  ;
  return os;
}
