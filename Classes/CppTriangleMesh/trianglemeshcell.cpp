#include "trianglemeshcell.h"

#include <iostream>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshcellfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"
#include "xml.h"

ribi::trim::Cell::Cell(
  const std::vector<boost::shared_ptr<Face>>& faces,
  const int index,
  const CellFactory&)
  : m_faces(faces),
    m_index{index}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(faces.size() == 5 || faces.size() == 8);
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Cell::CalculateCenter() const noexcept
{
  PROFILE_FUNC();
  Coordinat3D center(0.0,0.0,0.0);
  int cnt = 0;
  for(const boost::shared_ptr<const Face> face: m_faces)
  {
    assert(face);
    for(const auto point: face->GetPoints())
    {
      assert(point);
      center += point->GetCoordinat3D();
      ++cnt;
    }
  }
  center /= static_cast<double>(cnt);
  return center;
}


std::vector<boost::shared_ptr<const ribi::trim::Face>> ribi::trim::Cell::GetFaces() const noexcept
{
  return AddConst(m_faces);
}

void ribi::trim::Cell::SetCorrectOrder() noexcept
{
  std::sort(m_faces.begin(), m_faces.end(),
    [](const boost::shared_ptr<Face>& lhs, const boost::shared_ptr<Face>& rhs)
    {
      const int priority_lhs { lhs->CalcPriority() };
      const int priority_rhs { rhs->CalcPriority() };
      if (priority_lhs < priority_rhs) return true;
      if (priority_lhs > priority_rhs) return false;
      //Sort on Face indices
      assert(lhs->GetIndex() != rhs->GetIndex());
      return lhs->GetIndex() < rhs->GetIndex();
    }
  );

  #ifndef NDEBUG
  //for (const auto face: m_faces) TRACE(face->CalcPriority());
  #endif
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
  //Test that in a prism-shaped Cell, all Faces are owned, and no faces have a neighbour
  {
    const boost::shared_ptr<Cell> prism {
      CellFactory().CreateTestPrism()
    };
    assert(prism);
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
  }
  //Test that in a prism-shaped Cell, all Faces are owned, and no faces have a neighbour
  for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
  {
    const std::vector<boost::shared_ptr<Cell>> cube {
      CellFactory().CreateTestCube(strategy)
    };
    assert(cube.size() == 2 && "A cube consists out of two prisms");
    //Concatenate the faces
    std::vector<boost::shared_ptr<Face>> faces {
      cube[0]->GetFaces()
    };
    const std::vector<boost::shared_ptr<Face>> other_faces { cube[1]->GetFaces() };
    std::copy(std::begin(other_faces),std::end(other_faces),
      std::back_inserter(faces)
    );
    std::sort(faces.begin(),faces.end());

    TRACE(faces.size());
    assert(
      (
           (strategy == CreateVerticalFacesStrategy::one_face_per_square  && faces.size() == 10)
        || (strategy == CreateVerticalFacesStrategy::two_faces_per_square && faces.size() == 16)
      )
      && "One or two faces are in both Cells, and must be made unique"
    );
    assert(std::count(std::begin(faces),std::end(faces),nullptr) == 0);
    assert(std::unique(faces.begin(),faces.end()) != faces.end() && "Two faces must be present twice");
    faces.erase(std::unique(std::begin(faces),std::end(faces)),faces.end());
    faces.erase(std::remove(std::begin(faces),std::end(faces),nullptr),faces.end()); //OBLIGATORY! std::unique creates nullptrs!
    TRACE(faces.size());
    assert(
      (
           (strategy == CreateVerticalFacesStrategy::one_face_per_square  && faces.size() ==  9)
        || (strategy == CreateVerticalFacesStrategy::two_faces_per_square && faces.size() == 14)
      )
      && "One or two faces were in both Cells, and are now present only once"
    );

    const int n_faces_with_neighbours {
      std::count_if(faces.begin(),faces.end(),
        [](const boost::shared_ptr<Face> face)
        {
          assert(face);
          assert(face->GetOwner());
          return face->GetNeighbour().get();
        }
      )
    };
    assert(n_faces_with_neighbours == 1 || n_faces_with_neighbours == 2);
  }

  //Test that CalcCenter returns the same value each time
  //Failed once...
  {
    const auto center(CellFactory().CreateTestPrism()->CalculateCenter());
    assert(Geometry().IsEqual(center,CellFactory().CreateTestPrism()->CalculateCenter()));
    assert(Geometry().IsEqual(center,CellFactory().CreateTestPrism()->CalculateCenter()));
    assert(Geometry().IsEqual(center,CellFactory().CreateTestPrism()->CalculateCenter()));
    assert(Geometry().IsEqual(center,CellFactory().CreateTestPrism()->CalculateCenter()));
    assert(Geometry().IsEqual(center,CellFactory().CreateTestPrism()->CalculateCenter()));
  }

  TRACE("Finished ribi::trim::Cell::Test successfully");
}
#endif

bool ribi::trim::operator==(const ribi::trim::Cell& lhs, const ribi::trim::Cell& rhs) noexcept
{
  return lhs.GetFaces() == rhs.GetFaces();
}

bool ribi::trim::operator!=(const ribi::trim::Cell& lhs, const ribi::trim::Cell& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Cell& cell) noexcept
{
  const auto faces = cell.GetFaces();
  std::stringstream s;
  s
    << ribi::xml::ToXml("cell_index",cell.GetIndex())
  ;
  {
    std::stringstream t;
    const int n_faces { static_cast<int>(faces.size()) };
    for (int i=0; i!=n_faces; ++i)
    {
      t << ribi::xml::ToXml("face" + boost::lexical_cast<std::string>(i),faces[i]->GetIndex());
    }
    s << ribi::xml::ToXml("faces",t.str());
  }
  const std::vector<std::string> v { ribi::xml::XmlToPretty(s.str()) };
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));

  return os;
}
