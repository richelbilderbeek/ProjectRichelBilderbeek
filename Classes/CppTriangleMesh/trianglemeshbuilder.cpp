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
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::TriangleMeshBuilder::TriangleMeshBuilder(
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::string& mesh_filename,
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
  const CreateVerticalFacesStrategy strategy
  )
  : m_cells(cells),
    m_faces(SortByBoundary(ExtractFaces(cells),boundary_to_patch_field_type_function)),
    m_points(ExtractPoints(cells))
{
  #ifndef NDEBUG
  Test();
  #endif


  for (const std::string& folder: GetAllFolders())
  {
    if (!ribi::fileio::FileIo().IsFolder(folder))
    {
      ribi::fileio::FileIo().CreateFolder(folder);
    }
    assert(ribi::fileio::FileIo().IsFolder(folder));
  }

  //Remove cells with less than 8 faces or less than 8 faces with an owner
  m_cells.erase(
    std::remove_if(m_cells.begin(),m_cells.end(),
      [strategy](const boost::shared_ptr<Cell> cell)
      {
        const std::vector<boost::shared_ptr<Face>> faces { cell->GetFaces() };
        const int n_faces_expected {
          strategy == CreateVerticalFacesStrategy::one_face_per_square ? 5 : 8
        };
        assert(static_cast<int>(faces.size()) == n_faces_expected);
        return std::count_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<Face> face)
          {
            assert(face);
            assert(face->GetOwner());
            return face->GetOwner();
          }
        ) < n_faces_expected;
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
      [strategy](const boost::shared_ptr<Cell> cell)
      {
        const std::vector<boost::shared_ptr<Face>> faces { cell->GetFaces() };
        const int n_faces_expected {
          CreateVerticalFacesStrategies().GetFacesPerCell(strategy)
        };

        assert(static_cast<int>(faces.size()) == n_faces_expected);
        return std::count_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<Face> face)
          {
            assert(face);
            assert(face->GetOwner());
            return face->GetOwner();
          }
        ) < n_faces_expected;
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

  for (auto cell: m_cells) { cell->SetCorrectOrder(); }
  for (auto face: m_faces) { face->SetCorrectWinding(); }

  //Check
  #ifndef NDEBUG
  {
    const int cell_usecount = m_cells.empty() ? 0 : m_cells[0].use_count();
    for (const auto& cell: m_cells)
    {
      assert(cell);
      //TRACE(cell_usecount);
      //TRACE(cell.use_count());
      assert(cell.use_count() == cell_usecount && "Every Cell must have an equal use_count");
      //All Cells must have existing indices
      assert(cell->GetIndex() >= 0);
      assert(cell->GetIndex() <  static_cast<int>(m_cells.size()));
      //const int face_usecount = cell->GetFaces().empty() ? 0 : cell->GetFaces()[0].use_count();
      for (const auto& face: cell->GetFaces())
      {
        assert(face);
        //assert(std::abs(face_usecount - face.use_count()) <= 1 && "Face are used once or twice");
        //All Cells must exist of Faces with an existing index
        assert(face->GetIndex() >= 0);
        assert(face->GetIndex() <  static_cast<int>(m_faces.size()));
        //All Faces must have a Cell that owns them with an existing index
        assert(face->GetOwner()->GetIndex() >= 0);
        //assert(face->GetOwner()->GetIndex() <  static_cast<int>(m_cells.size())
        // && "Index actually might be bigger than the size");
        //All Faces must have either no Neighbout or a Neighbour with an existing index
        assert(!face->GetNeighbour() || face->GetNeighbour()->GetIndex() >= 0);
        //assert(!face->GetNeighbour() || face->GetNeighbour()->GetIndex() <  static_cast<int>(m_cells.size())
        // && "Index actually might be bigger than the size");
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
    f << CreateNodes();
    f << CreateFaces();
  }
  {

    std::ofstream f(ribi::foam::Filenames().GetPoints().c_str());
    f << CreateOpenFoamHeader("vectorField","points","constant/polyMesh");
    f << CreateOpenFoamNodes();
  }
  {
    std::ofstream fp(ribi::foam::Filenames().GetFaces().c_str());

    fp << CreateOpenFoamHeader("faceList","faces","constant/polyMesh");
    fp << CreateOpenFoamFaces();
  }
  {
    const int n_cells = static_cast<int>(m_cells.size());
    if (verbose) std::cout << "\tGenerating cells (" << n_cells << ")\n";

    std::ofstream fo(ribi::foam::Filenames().GetOwner().c_str());
    std::ofstream fn(ribi::foam::Filenames().GetNeighbour().c_str());

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

    const std::pair<std::string,std::string> p { CreateCells() };
    const std::string& out_owner { p.first };
    const std::string& out_neighbour { p.second};
    fo << out_owner;
    fn << out_neighbour;
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetBoundary().c_str());
    f << CreateBoundary(boundary_to_patch_field_type_function);
  }
  {
    std::ofstream f(ribi::foam::Filenames().GetCase().c_str());
    //Need nothing to stream
  }

  PROFILER_UPDATE();
}

std::string ribi::trim::TriangleMeshBuilder::CreateBoundary(
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  ) const noexcept
{

  //Tally all boundary names
  std::map<std::string,int> sorted_tally;

  for (auto face: m_faces)
  {
    const std::string s { face->GetBoundaryType() };
    const auto iter(sorted_tally.find(s));
    if (iter == sorted_tally.end())
    {
      sorted_tally.insert(sorted_tally.begin(),std::make_pair(s,1));
    }
    else
    {
      ++(*iter).second;
    }
  }

  //Create a tally sorted as such that the PatchFieldType::no_patch_field comes first
  //so these can be omitted
  typedef std::pair<std::string,int> Pair;
  std::vector<Pair> tally;
  std::copy(sorted_tally.begin(),sorted_tally.end(),std::back_inserter(tally));

  std::sort(tally.begin(),tally.end(),
    [boundary_to_patch_field_type_function](const Pair& lhs, const Pair& rhs)
    {
      return OrderByPatchFieldType(
        lhs.first,
        rhs.first,
        boundary_to_patch_field_type_function(lhs.first),
        boundary_to_patch_field_type_function(rhs.first)
      );
    }
  );

  //Create the items
  std::vector<ribi::foam::BoundaryFileItem> items;
  int start_index = 0;
  for (auto p: tally)
  {
    const std::string boundary_name = p.first;
    const int n_faces = p.second;
    const ribi::foam::BoundaryFileItem item(
      boundary_name,
      boundary_to_patch_field_type_function(boundary_name),
      n_faces,
      ribi::foam::FaceIndex(start_index)
    );
    items.push_back(item);
    start_index += p.second;
  }

  ribi::foam::BoundaryFile file(
    ribi::foam::BoundaryFile::GetDefaultHeader(),
    items
  );

  std::stringstream s;
  s << file;
  return s.str();
}

std::pair<std::string,std::string> ribi::trim::TriangleMeshBuilder::CreateCells() const noexcept
{
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


std::string ribi::trim::TriangleMeshBuilder::CreateFaces() const noexcept
{
  std::stringstream s;
  s << std::setprecision(17);
  for (auto face: m_faces)
  {
    s << face->GetPoints().size();

    face->SetCorrectWinding();

    for (const boost::shared_ptr<const Point> point: face->GetPoints())
    {
      s << " " << point->GetIndex();
    }
    s << "\n";
  }
  return s.str();
}



std::string ribi::trim::TriangleMeshBuilder::CreateHeader() const noexcept
{
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

std::string ribi::trim::TriangleMeshBuilder::CreateNodes() const noexcept
{
  using boost::geometry::get;

  std::string text;
  for (const auto point: m_points)
  {
    std::stringstream s;
    int cnt = 0;
    for (const double p:
      {
        get<0>(*point->GetCoordinat()),
        get<1>(*point->GetCoordinat()),
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

std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamFaces() const noexcept
{
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
      << Implode(" ",points_indices)
      << ")\n";
  }
  s << ")";

  return s.str();
}

std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamHeader(
  const std::string& class_name,
  const std::string& object,
  const std::string& location,
  const std::string& note) const noexcept
{
  std::stringstream s;
  s << "FoamFile\n{\tversion\t2.0;\n\tformat\tascii;\n\tclass\t" << class_name << ";";

  if(!note.empty())
  {
    s << "\n\tnote\t\"" << note << "\";";
  }

  s << "\n\tlocation\t\"" << location << "\";\n\tobject\t" << object << ";\n}\n\n";
  return s.str();
}

std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamNodes() const noexcept
{

  using boost::geometry::get;
  std::stringstream s;
  s
    << std::setprecision(17)
    << m_points.size()
    << "\n(\n";

  //Build a list of nodes
  for (const auto point: m_points)
  {
    const std::array<double,3> co {
      get<0>(*point->GetCoordinat()),
      get<1>(*point->GetCoordinat()),
      point->GetZ().value()
    };
    s <<  "(" << ribi::php::implode(" ",co) << ")\n";
  }

  s << ")";
  return s.str();
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilder::ExtractFaces(
  const std::vector<boost::shared_ptr<Cell>>& cells
) noexcept
{
  std::vector<boost::shared_ptr<Face>> v;
  for (const boost::shared_ptr<Cell>& cell: cells)
  {
    const auto w(cell->GetFaces());
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  TRACE("n_face, non-unique:");
  TRACE(v.size());
  
  std::sort(v.begin(),v.end(),Helper().OrderByIndex());
  const auto new_end = std::unique(v.begin(),v.end());
  v.erase(new_end,v.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);

  TRACE("n_face, unique:");
  TRACE(v.size());
  return v;


}

std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::TriangleMeshBuilder::ExtractPoints(
  const std::vector<boost::shared_ptr<Cell>>& cells
) noexcept
{
  std::vector<boost::shared_ptr<Point>> v;
  for (const boost::shared_ptr<Cell>& cell: cells)
  {
    for (const auto face: cell->GetFaces())
    {
      const std::vector<boost::shared_ptr<Point>> w { face->GetPoints() };
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }
  
  std::sort(v.begin(),v.end(),Helper().OrderByX());
  const auto new_end = std::unique(v.begin(),v.end());
  v.erase(new_end,v.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);

  return v;
}


std::vector<std::string> ribi::trim::TriangleMeshBuilder::GetAllFolders() const noexcept
{
  return {
    "0",
    "constant",
    "constant" + ribi::fileio::FileIo().GetPathSeperator() + "polyMesh",
    "system"
  };
}

std::string ribi::trim::TriangleMeshBuilder::Implode(
  const std::string& seperator,
  const std::vector<ribi::foam::PointIndex>& v) noexcept
{
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

std::string ribi::trim::TriangleMeshBuilder::Implode(
  const std::string& seperator,
  const std::vector<int>& v) noexcept
{
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

bool ribi::trim::TriangleMeshBuilder::OrderByPatchFieldType(
  const std::string lhs_name, const std::string rhs_name,
  const ribi::foam::PatchFieldType lhs_type, const ribi::foam::PatchFieldType rhs_type
) noexcept
{
  if (lhs_type == ribi::foam::PatchFieldType::no_patch_field)
  {
    if (rhs_type == ribi::foam::PatchFieldType::no_patch_field)
    {
      return lhs_name > rhs_name;
    }
    else
    {
      return true;
    }
  }
  if (rhs_type == ribi::foam::PatchFieldType::no_patch_field)
  {
    return false;
  }
  return lhs_name > rhs_name;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilder::SortByBoundary(
  std::vector<boost::shared_ptr<Face>> faces,
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
) noexcept
{


  std::sort(std::begin(faces),std::end(faces),
    [boundary_to_patch_field_type_function](const boost::shared_ptr<const Face> lhs, const boost::shared_ptr<const Face> rhs)
    {
      return OrderByPatchFieldType(
        lhs->GetBoundaryType(),
        rhs->GetBoundaryType(),
        boundary_to_patch_field_type_function(lhs->GetBoundaryType()),
        boundary_to_patch_field_type_function(rhs->GetBoundaryType())
      );
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
  //bool OrderByPatchFieldType(
  //  const std::string lhs_name, const std::string rhs_name,
  //  const ribi::foam::PatchFieldType lhs_type, const ribi::foam::PatchFieldType rhs_type
  //) const noexcept;

  TRACE("Finished ribi::trim::TriangleMeshBuilder::Test successfully");
}
#endif
