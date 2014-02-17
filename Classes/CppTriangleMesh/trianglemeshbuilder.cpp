#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshbuilder.h"

#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Shiny.h"

#include "trianglemeshcell.h"
#include "trianglemeshface.h"
#include "fileio.h"
#include "openfoamfilenames.h"
#include "openfoampointindex.h"
#include "php.h"
#include "trianglemeshpoint.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::TriangleMeshBuilder::TriangleMeshBuilder(
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::string& mesh_filename
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

  //Clean all weakened data
  m_faces.erase(
    std::remove_if(m_faces.begin(),m_faces.end(),
      [](const boost::shared_ptr<const Face> face)
      {
        return !face->GetOwner();
      }
    ),
    m_faces.end()
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
    f << CreateBoundary();
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamCase().Get().c_str());
    //Need nothing to stream
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamFvSchemes().Get().c_str());
    f << CreateOpenFoamFvSchemes();
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamFvSolution().Get().c_str());
    f << CreateOpenFoamFvSolution();
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamPressureField().Get().c_str());
    f << CreateOpenFoamP();
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamVelocityField().Get().c_str());
    f << CreateOpenFoamU();
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetOpenFoamControlDict().Get().c_str());
    f << CreateOpenFoamControlDict();
  }

  PROFILER_UPDATE();
}

const std::string ribi::trim::TriangleMeshBuilder::CreateBoundary() const noexcept
{
  PROFILE_FUNC();

  std::stringstream s;
  s << this->CreateOpenFoamHeader("polyBoundaryMesh","boundary","constant/polyMesh");

  const int n_face_indices = static_cast<int>(m_faces.size());
  assert(n_face_indices > 0);

  // { boundary_type, start indices, n_faces }
  typedef std::tuple<std::string,int,int> Row;
  std::vector<Row> v;
  std::string type = m_faces[0]->GetBoundaryType();
  int start_index = 0;
  int n_faces = 0;
  for (int i=0; i!=n_face_indices; ++i)
  {
    const auto face = m_faces[i];
    const std::string new_type = face->GetBoundaryType();
    if (new_type != type)
    {
      v.push_back(std::make_tuple(type,start_index,n_faces));
      type = new_type;
      start_index = i;
      n_faces = 1; //1, because the current face is now/already detected
    }
    else
    {
      ++n_faces;
    }
  }
  v.push_back(std::make_tuple(type,start_index,n_faces));

  const int sum_n_faces {
    std::accumulate(v.begin(),v.end(),0,
      [](const int init,const Row& row)
      {
        return init + std::get<2>(row);
      }
    )
  };
  if (sum_n_faces != n_face_indices)
  {
    TRACE("ERROR");
    TRACE(sum_n_faces);
    TRACE(n_face_indices);
    for (auto row: v)
    {
      std::stringstream s;
      s
        << std::get<0>(row) << '\t'
        << std::get<1>(row) << '\t'
        << std::get<2>(row)
        << std::endl
      ;
      TRACE(s.str());
    }
  }
  assert(sum_n_faces == n_face_indices);


  s << v.size() << "\n(";
  for(const auto row: v)
  {
    s << "\n\t" << std::get<0>(row) << "\n\t{\n"
      << "\t\t" << "type\tpatch;\n"
      << "\t\t" << "nFaces\t" << std::get<2>(row) << ";\n"
      << "\t\t" << "startFace\t" << std::get<1>(row) << ";\n"
      << "\t}\n";
  }
  s << ")";
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
