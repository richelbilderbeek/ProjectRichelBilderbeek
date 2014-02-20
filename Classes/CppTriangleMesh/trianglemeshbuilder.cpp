#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshbuilder.h"

#include <array>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Shiny.h"

#include "trianglemeshcell.h"
#include "trianglemeshface.h"
#include "fileio.h"
#include "openfoamheader.h"
#include "openfoamboundaryfile.h"
#include "openfoamboundaryfileitem.h"
#include "openfoamfilenames.h"
#include "openfoampointindex.h"
#include "php.h"
#include "trianglemeshpoint.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::TriangleMeshBuilder::TriangleMeshBuilder(
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::string& mesh_filename,
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  )
  : m_cells(cells),
    m_faces(SortByBoundary(ExtractFaces(cells))),
    m_points(ExtractPoints(cells))
{
  #ifndef NDEBUG
  Test();
  #endif
  TRACE_FUNC();
  PROFILE_FUNC();

  for (const std::string& folder: GetAllFolders())
  {
    if (!ribi::fileio::IsFolder(folder))
    {
      ribi::fileio::CreateFolder(folder);
    }
    assert(ribi::fileio::IsFolder(folder));
  }

  //Remove cells with less than 8 faces or less than 8 faces with an owner
  m_cells.erase(
    std::remove_if(m_cells.begin(),m_cells.end(),
      [](const boost::shared_ptr<Cell> cell)
      {
        const std::vector<boost::shared_ptr<Face>> faces { cell->GetFaces() };
        assert(faces.size() == 8);
        return std::count_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<Face> face)
          {
            assert(face);
            assert(face->GetOwner()); //Test: is this loop needed?
            return face->GetOwner();
          }
        ) < 8;
      }
    ),
    m_cells.end()
  );


  m_faces.erase(
    std::remove_if(m_faces.begin(),m_faces.end(),
      [](const boost::shared_ptr<const Face> face)
      {
        return !face->GetOwner();
      }
    ),
    m_faces.end()
  );

  //Remove cells with less than 8 faces or less than 8 faces with an owner
  m_cells.erase(
    std::remove_if(m_cells.begin(),m_cells.end(),
      [](const boost::shared_ptr<Cell> cell)
      {
        const std::vector<boost::shared_ptr<Face>> faces { cell->GetFaces() };
        assert(faces.size() == 8);
        return std::count_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<Face> face)
          {
            assert(face);
            assert(face->GetOwner()); //Test: is this loop needed?
            return face->GetOwner();
          }
        ) < 8;
      }
    ),
    m_cells.end()
  );

  //Set all indices
  {
    const int n_cells = static_cast<int>(m_cells.size());
    for (int i=0; i!=n_cells; ++i)
    {
      m_cells[i]->SetIndex(i);
    }
    const int n_faces = static_cast<int>(m_faces.size());
    for (int i=0; i!=n_faces; ++i)
    {
      m_faces[i]->SetIndex(i);
    }
    const int n_points = static_cast<int>(m_points.size());
    for (int i=0; i!=n_points; ++i)
    {
      m_points[i]->SetIndex(i);
    }
  }


  //Check
  #ifndef NDEBUG
  {
    const int cell_usecount = m_cells.empty() ? 0 : m_cells[0].use_count();
    for (const auto& cell: m_cells)
    {
      assert(cell);
      TRACE(cell_usecount);
      TRACE(cell.use_count());
      assert(cell.use_count() == cell_usecount && "Every Cell must have an equal use_count");
      //All Cells must have existing indices
      assert(cell->GetIndex() >= 0);
      assert(cell->GetIndex() <  static_cast<int>(m_cells.size()));
      const int face_usecount = cell->GetFaces().empty() ? 0 : cell->GetFaces()[0].use_count();
      for (const auto& face: cell->GetFaces())
      {
        assert(face);
        TRACE(face_usecount);
        TRACE(face.use_count());
        assert(std::abs(face_usecount - face.use_count()) <= 1 && "Face are used once or twice");
        //All Cells must exist of Faces with an existing index
        assert(face->GetIndex() >= 0);
        assert(face->GetIndex() <  static_cast<int>(m_faces.size()));
        //All Faces must have a Cell that owns them with an existing index
        assert(face->GetOwner()->GetIndex() >= 0);
        assert(face->GetOwner()->GetIndex() <  static_cast<int>(m_cells.size()));
        //All Faces must have either no Neighbout or a Neighbour with an existing index
        assert(!face->GetNeighbour() || face->GetNeighbour()->GetIndex() >= 0);
        assert(!face->GetNeighbour() || face->GetNeighbour()->GetIndex() <  static_cast<int>(m_cells.size()));
        for (const auto point: face->GetPoints())
        {
          assert(point);
          //All Faces must exists of Points with an existing index
          assert(point->GetIndex() >= 0);
          assert(point->GetIndex() <  static_cast<int>(m_points.size()));
        }
      }
    }
  }
  #endif

  const bool verbose = false;
  if (verbose) std::cout << "Writing output...\n";
  //Mesh
  {
    if (verbose) std::cout << "\tGenerating mesh (.ply)\n";

    std::ofstream f(mesh_filename.c_str());
    f << CreateHeader();
    f << this->CreateNodes();
    f << this->CreateFaces();
  }
  {

    std::ofstream f(ribi::foam::Filenames().GetPoints().Get().c_str());
    f << this->CreateOpenFoamHeader("vectorField","points","constant/polyMesh");
    f << CreateOpenFoamNodes();
  }
  {
    std::ofstream fp(ribi::foam::Filenames().GetFaces().Get().c_str());

    fp << this->CreateOpenFoamHeader("faceList","faces","constant/polyMesh");
    fp << this->CreateOpenFoamFaces();
  }
  {
    const int n_cells = static_cast<int>(m_cells.size());
    if (verbose) std::cout << "\tGenerating cells (" << n_cells << ")\n";

    std::ofstream fo(ribi::foam::Filenames().GetOwner().Get().c_str());
    std::ofstream fn(ribi::foam::Filenames().GetNeighbour().Get().c_str());

    std::stringstream fs;
    fs
      << "nPoints: " << m_points.size()
      << " nCells: " << m_cells.size()
      << " nFaces: " << m_faces.size()
    ;

    fo << CreateOpenFoamHeader(
        "labelList",
        "owner",
        "constant/polyMesh",
        fs.str()
      );
    fn << CreateOpenFoamHeader(
      "labelList",
      "neighbour",
      "constant/polyMesh",
      fs.str()
      );

    const std::pair<std::string,std::string> p { this->CreateCells() };
    const std::string& out_owner { p.first };
    const std::string& out_neighbour { p.second};
    fo << out_owner;
    fn << out_neighbour;
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetBoundary().Get().c_str());
    f << CreateBoundary(boundary_to_patch_field_type_function);
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetCase().Get().c_str());
    //Need nothing to stream
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetFvSchemes().Get().c_str());
    f << CreateOpenFoamFvSchemes();
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetFvSolution().Get().c_str());
    f << CreateOpenFoamFvSolution();
  }

  //{
  //  std::ofstream f(ribi::foam::Filenames().GetPressureField().Get().c_str());
  //  f << CreateOpenFoamP();
  //}
  {
    std::ofstream f(ribi::foam::Filenames().GetVelocityField().Get().c_str());
    f << CreateOpenFoamU();
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetControlDict().Get().c_str());
    f << CreateOpenFoamControlDict();
  }

  PROFILER_UPDATE();
}

const std::string ribi::trim::TriangleMeshBuilder::CreateBoundary(
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  ) const noexcept
{
  PROFILE_FUNC();
  std::vector<ribi::foam::BoundaryFileItem> items;

  const int n_face_indices = static_cast<int>(m_faces.size());
  assert(n_face_indices > 0);

  std::string boundary_name = m_faces[0]->GetBoundaryType();
  int start_index = 0;
  int n_faces = 0;
  for (int i=0; i!=n_face_indices; ++i)
  {
    const boost::shared_ptr<Face> face { m_faces[i] };
    const std::string new_boundary_name = face->GetBoundaryType();
    if (new_boundary_name != boundary_name)
    {
      const ribi::foam::BoundaryFileItem item(
        boundary_name,
        boundary_to_patch_field_type_function(boundary_name),
        n_faces,
        ribi::foam::FaceIndex(start_index)
      );
      items.push_back(item);
      boundary_name = new_boundary_name;
      start_index = i;
      n_faces = 1; //1, because the current face is now/already detected
    }
    else
    {
      ++n_faces;
    }
  }
  //Add the last
  {
    const ribi::foam::BoundaryFileItem item(
      boundary_name,
      boundary_to_patch_field_type_function(boundary_name),
      n_faces,
      ribi::foam::FaceIndex(start_index)
    );
    items.push_back(item);
  }


  ribi::foam::BoundaryFile file(
    ribi::foam::BoundaryFile::GetDefaultHeader(),
    items
  );

  std::stringstream s;
  s << file;
  return s.str();
}

const std::pair<std::string,std::string> ribi::trim::TriangleMeshBuilder::CreateCells() const noexcept
{
  PROFILE_FUNC();

  std::stringstream out_owner;
  out_owner
    << static_cast<int>(m_faces.size())
    << "\n(\n";

  std::stringstream out_neighbour;
  out_neighbour
    << m_faces.size()
    << "\n(\n";

  for (auto face: m_faces)
  {
    assert(face);
    assert(face->GetOwner());
    out_owner << face->GetOwner()->GetIndex() << "\n";
    if(!face->GetNeighbour())
    {
      out_neighbour << "-1\n";
    }
    else
    {
      out_neighbour << face->GetNeighbour()->GetIndex() << "\n";
    }
  }

  out_owner << ")";
  out_neighbour << ")";
  return std::make_pair(out_owner.str(),out_neighbour.str());
}


const std::string ribi::trim::TriangleMeshBuilder::CreateFaces() const noexcept
{
  PROFILE_FUNC();

  std::stringstream s;
  s << std::setprecision(17);
  TRACE(m_faces.size());

  for (auto face: m_faces)
  {
    s << face->GetPoints().size();
    //TRACE(face->GetPoints().size());

    for (const boost::shared_ptr<const Point> point: face->GetPoints())
    {

      s << " " << point->GetIndex();
    }
    s << "\n";
  }
  return s.str();
}



const std::string ribi::trim::TriangleMeshBuilder::CreateHeader() const noexcept
{
  PROFILE_FUNC();
  std::stringstream s;
  s << ""
    << "ply\n"
    << "format ascii 1.0\n"
    << "element vertex " << m_points.size() << "\n"
    << "property float x\n"
    << "property float y\n"
    << "property float z\n"
    << "element face " << m_faces.size() << "\n"
    << "property list uchar int vertex_index\n"
    << "end_header\n";
  return s.str();
}

const std::string ribi::trim::TriangleMeshBuilder::CreateNodes() const noexcept
{
  PROFILE_FUNC();

  std::string text;
  for (const auto point: m_points)
  {
    std::stringstream s;
    int cnt = 0;
    for (const double p:
      {
        point->GetCoordinat()->GetX(),
        point->GetCoordinat()->GetY(),
        point->GetZ().value()
      }
    )
    {
      s << std::setprecision(cnt != 2 ? 17 : 3);
      s << p << " ";
      ++cnt;
    }
    std::string t = s.str();
    assert(t[t.size() - 1] == ' '); //Replace last space
    t[t.size() - 1] = '\n';
    text += t;

  }
  return text;
}



const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamFaces() const noexcept
{
  PROFILE_FUNC();

  std::stringstream s;
  s
    << std::setprecision(17)
    << m_faces.size()
    << "\n(\n";

  //Build a list of nodes
  for (auto face: m_faces)
  {
    assert(face);
    std::vector<int> points_indices;
    for (auto point: face->GetPoints())
    {
      points_indices.push_back(point->GetIndex());
    }

    s
      << points_indices.size()
      << "("
      << Implode(std::string(" "),points_indices)
      << ")\n";
  }
  s << ")";

  return s.str();
}

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamHeader(
  const std::string& class_name,
  const std::string& object,
  const std::string& location,
  const std::string& note) const noexcept
{
  PROFILE_FUNC();
  std::stringstream s;
  s << "FoamFile\n{\tversion\t2.0;\n\tformat\tascii;\n\tclass\t" << class_name << ";";

  if(!note.empty())
  {
    s << "\n\tnote\t\"" << note << "\";";
  }

  s << "\n\tlocation\t\"" << location << "\";\n\tobject\t" << object << ";\n}\n\n";
  return s.str();
}

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamNodes() const noexcept
{
  PROFILE_FUNC();

  std::stringstream s;
  s
    << std::setprecision(17)
    << m_points.size()
    << "\n(\n";

  //Build a list of nodes
  for (const auto point: m_points)
  {
    const std::array<double,3> co {
      point->GetCoordinat()->GetX(),
      point->GetCoordinat()->GetY(),
      point->GetZ().value()
    };
    s <<  "(" << ribi::php::implode(" ",co) << ")\n";
  }

  s << ")";
  return s.str();
}

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilder::ExtractFaces(
  const std::vector<boost::shared_ptr<Cell>>& cells
) noexcept
{
  PROFILE_FUNC();
  std::vector<boost::shared_ptr<Face>> v;
  for (const boost::shared_ptr<Cell>& cell: cells)
  {
    const std::vector<boost::shared_ptr<Face>> w { cell->GetFaces() };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  TRACE("n_face, non-unique:");
  TRACE(v.size());
  std::sort(v.begin(),v.end());
  const auto new_end = std::unique(v.begin(),v.end());
  v.erase(new_end,v.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);

  TRACE("n_face, unique:");
  TRACE(v.size());
  return v;


}

const std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::TriangleMeshBuilder::ExtractPoints(
  const std::vector<boost::shared_ptr<Cell>>& cells
) noexcept
{
  PROFILE_FUNC();
  std::vector<boost::shared_ptr<Point>> v;
  for (const boost::shared_ptr<Cell>& cell: cells)
  {
    for (const auto face: cell->GetFaces())
    {
      const std::vector<boost::shared_ptr<Point>> w { face->GetPoints() };
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }

  std::sort(v.begin(),v.end());
  const auto new_end = std::unique(v.begin(),v.end());
  v.erase(new_end,v.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);

  return v;
}


const std::vector<std::string> ribi::trim::TriangleMeshBuilder::GetAllFolders() const noexcept
{
  return {
    "0",
    "constant",
    "constant" + ribi::fileio::GetPathSeperator() + "polyMesh",
    "system"
  };
}

const std::string ribi::trim::TriangleMeshBuilder::Implode(
  const std::string& seperator,
  const std::vector<ribi::foam::PointIndex>& v) noexcept
{
  PROFILE_FUNC();
  std::stringstream s;
  s << std::setprecision(17);

  if (v.empty()) return s.str();
  s << v[0];
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s << seperator << v[i];
  }
  return s.str();
}

const std::string ribi::trim::TriangleMeshBuilder::Implode(
  const std::string& seperator,
  const std::vector<int>& v) noexcept
{
  PROFILE_FUNC();
  std::stringstream s;
  s << std::setprecision(17);

  if (v.empty()) return s.str();
  s << v[0];
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s << seperator << v[i];
  }
  return s.str();
}

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilder::SortByBoundary(
  std::vector<boost::shared_ptr<Face>> faces
) noexcept
{
  PROFILE_FUNC();

  std::sort(std::begin(faces),std::end(faces),
    [](const boost::shared_ptr<const Face> lhs, const boost::shared_ptr<const Face> rhs)
    {
      if (lhs->GetBoundaryType() < rhs->GetBoundaryType()) return true;
      if (lhs->GetBoundaryType() > rhs->GetBoundaryType()) return false;
      return lhs < rhs;
    }
  );
  return faces;
}

#ifndef NDEBUG
void ribi::trim::TriangleMeshBuilder::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::TriangleMeshBuilder::Test");
  TRACE("Finished ribi::trim::TriangleMeshBuilder::Test successfully");
}
#endif
