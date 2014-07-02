#include "trianglemeshbuilderimpl.h"

#include <fstream>
#include <sstream>

#include "trianglemeshcell.h"
#include "trianglemeshface.h"
#include "fileio.h"
#include "openfoamboundaryfile.h"
#include "openfoamboundaryfileitem.h"
#include "openfoamfilenames.h"
#include "openfoamfaceindex.h"
#include "openfoampointindex.h"
#include "php.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"

ribi::trim::TriangleMeshBuilderImpl::TriangleMeshBuilderImpl(
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::string& mesh_filename,
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
  const CreateVerticalFacesStrategy
  #ifndef NDEBUG
    strategy
  #endif
  ,
  const bool verbose
) : m_cells(cells),
    //#1: Partition faces in boundaries
    m_faces(SortByBoundary(ExtractFaces(cells),boundary_to_patch_field_type_function)),
    m_points(ExtractPoints(cells))
{
  #ifndef NDEBUG
  Test();
  #endif
  const bool verbose_show_faces = false;
  const bool verbose_show_cell_indices = false;
  //const bool verbose = true;

  for (const std::string& folder: GetAllFolders())
  {
    if (!ribi::fileio::FileIo().IsFolder(folder))
    {
      ribi::fileio::FileIo().CreateFolder(folder);
    }
    assert(ribi::fileio::FileIo().IsFolder(folder));
  }

  if (verbose) { TRACE("Remove cells with less than 8 faces or less than 8 faces with an owner"); }

  assert(
    std::count_if(m_cells.begin(),m_cells.end(),
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
            assert(face->GetConstOwner());
            return face->GetConstOwner();
          }
        ) < n_faces_expected;
      }
    ) == 0
    && "So the code below can be removed #1"
  );
  #define SO_THIS_CAN_BE_REMOVED_1
  #ifndef SO_THIS_CAN_BE_REMOVED_1
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
            assert(face->GetConstOwner());
            return face->GetConstOwner();
          }
        ) < n_faces_expected;
      }
    ),
    m_cells.end()
  );
  #endif

  if (verbose) { TRACE("Remove faces without owners"); }
  assert(
    std::count_if(m_faces.begin(),m_faces.end(),
      [](const boost::shared_ptr<const Face> face)
      {
        return !face->GetConstOwner();
      }
    ) == 0
    && "So the code below can be removed #2"
  );

  #define SO_THIS_CAN_BE_REMOVED_2
  #ifndef SO_THIS_CAN_BE_REMOVED_2
  m_faces.erase(
    std::remove_if(m_faces.begin(),m_faces.end(),
      [](const boost::shared_ptr<const Face> face)
      {
        return !face->GetConstOwner();
      }
    ),
    m_faces.end()
  );
  #endif // SO_THIS_CAN_BE_REMOVED_2

  if (verbose) { TRACE("Remove cells with less than 8 faces or less than 8 faces with an owner"); }
  assert(
    std::count_if(m_cells.begin(),m_cells.end(),
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
            assert(face->GetConstOwner());
            return face->GetConstOwner();
          }
        ) < n_faces_expected;
      }
    ) == 0
    && "So the code below can be removed #3"
  );

  #define SO_THIS_CAN_BE_REMOVED_2
  #ifndef SO_THIS_CAN_BE_REMOVED_2
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
            assert(face->GetConstOwner());
            return face->GetConstOwner();
          }
        ) < n_faces_expected;
      }
    ),
    m_cells.end()
  );
  #endif // SO_THIS_CAN_BE_REMOVED_2

  #ifndef NDEBUG
  if (verbose) { TRACE("Check that all Faces know they belong to their Cell"); }
  for (const auto cell: m_cells)
  {
    for (const auto face: cell->GetFaces())
    {
      assert(face->GetConstOwner() == cell
        || face->GetNeighbour() == cell
      );
    }
  }
  #endif

  #ifndef NDEBUG
  if (verbose) { TRACE("Check that all Cells know they own their Faces"); }
  for (const auto face: m_faces)
  {
    assert(face);
    const auto owner = face->GetConstOwner();
    assert(owner);
    const auto neighbour = face->GetNeighbour();
    if (!neighbour)
    {
      const auto owner_faces = owner->GetFaces();
      assert(std::count(owner_faces.begin(),owner_faces.end(),face) == 1);
    }
    else
    {
      const auto owner_faces = owner->GetFaces();
      const auto neighbour_faces = neighbour->GetFaces();
      assert(
          std::count(owner_faces.begin(),owner_faces.end(),face)
        + std::count(neighbour_faces.begin(),neighbour_faces.end(),face)
        != 0 && "A Face with a neighbour is known by two cells, instead of zero"
      );
      assert(
          std::count(owner_faces.begin(),owner_faces.end(),face)
        + std::count(neighbour_faces.begin(),neighbour_faces.end(),face)
        != 1 && "A Face with a neighbour is known by two cells, instead of one"
      );
      assert(
          std::count(owner_faces.begin(),owner_faces.end(),face)
        + std::count(neighbour_faces.begin(),neighbour_faces.end(),face)
        == 2
      );
    }
  }
  #endif

  //Start setting the indices
  //Unset all Cell indices
  for (auto cell: m_cells) { cell->SetIndex(Cell::sm_cell_no_index); }

  //Unset all Face indices
  for (auto face: m_faces) { face->SetIndex(Face::sm_face_no_index); }

  //#2: For each face, find its owner (a cell), and assign these increasing cell indices
  //Set all Cell indices, following the Face order:
  //The faces are ordered correctly, by the boundary.
  //The faces' owners must be an increasing value, to prevent
  //'upper triangular order' errors
  {
    int cell_index = 0;
    const int n_faces = static_cast<int>(m_faces.size());
    for (int i=0; i!=n_faces; ++i)
    {
      //+---+---+---+---+---------------------------------------------------+
      //| S | 1 | 2 | 3 | Action                                            |
      //+---+---+---+---+---------------------------------------------------+
      //| A | N | Y | - | Assume owner's index is less then index           |
      //| B |   | N | - | Assign index to owner                             |
      //+---+---+---+---+---------------------------------------------------+
      //| C | Y | Y | N | Assign index to neighbour, transfer ownership if  |
      //|   |   |   |   |   neighbour's index is less than owner's index    |
      //| D |   | Y | Y | Assume owner's index is less than neighbour's     |
      //|   |   |   |   |   index, assume owner's index is less then index  |
      //| E |   | N | Y | Assign index to owner, transfer ownership if      |
      //|   |   |   |   |   neighbour's index is less than owner's index    |
      //| F |   | N | N | Assign index to owner                             |
      //+---+---+---+---+---------------------------------------------------+
      // * S = Scenario
      // * 1 = Does it have a neighbour?
      // * 2 = Assigned owner index yes/no?
      // * 3 = Assigned neighbour index yes/no?
      auto this_face = m_faces[i];
      if (this_face->GetNeighbour())
      {
        const int owner_index = this_face->GetConstOwner()->GetIndex();
        const int neighbour_index = this_face->GetNeighbour()->GetIndex();
        if (owner_index == Cell::sm_cell_no_index)
        {
          //Scenario E or F
          if (neighbour_index == Cell::sm_cell_no_index)
          {
            //Scenario F: No owner index, no neighbour index
            assert(owner_index == Cell::sm_cell_no_index);
            //Assign index to owner
            this_face->GetNonConstOwner()->SetIndex(cell_index);
            ++cell_index;
          }
          else
          {
            //Scenario E: No owner index, a neighbour index
            assert(owner_index == Cell::sm_cell_no_index);
            assert(neighbour_index != Cell::sm_cell_no_index);
            //Assign index to owner, transfer ownership if
            //neighbour's index is less than owner's index
            this_face->GetNonConstOwner()->SetIndex(cell_index);
            ++cell_index;
          }
        }
        else
        {
          //Scenario C or D
          assert(owner_index != Cell::sm_cell_no_index);
          if (neighbour_index == Cell::sm_cell_no_index)
          {
            //Scenario C: An owner index, no neighbour index
            //Assign index to neighbour, transfer ownership if
            //neighbour's index is less than owner's index
            this_face->GetNonConstNeighbour()->SetIndex(cell_index);
            ++cell_index;
          }
          else
          {
            //Scenario D: An owner index, a neighbour index
            //Assume owner's index is less than neighbour's
            //index, assume owner's index is less then index
            assert(neighbour_index != Cell::sm_cell_no_index);
            assert(owner_index < neighbour_index);
          }
        }
      }
      else
      {
        //Scenario A or B
        //No neighbour at all
        assert(!this_face->GetNeighbour());

        auto owner = this_face->GetNonConstOwner();
        assert(owner);
        if (owner->GetIndex() == Cell::sm_cell_no_index)
        {
          //Scenario B: no owner index
          //Assign index to owner
          owner->SetIndex(cell_index);
          ++cell_index;
        }
        else
        {
          //Scenario A: an owner index
          //Assume owner's index is less then index
          assert(owner->GetIndex() < cell_index);
        }
      }
      assert(this_face->GetConstOwner()->GetIndex() != Cell::sm_cell_no_index);
    }

    //Fixed #221:
    //Assign the cells without an index an index
    for (auto& cell: m_cells)
    {
      if(cell->GetIndex() == Cell::sm_cell_no_index)
      {
        cell->SetIndex(cell_index);
        ++cell_index;
      }
    }
  }

  #ifndef NDEBUG
  for (auto cell: m_cells)
  {
    assert(cell->GetIndex() != Cell::sm_cell_no_index
      && "All cells must have been assigned an index, #221");
  }
  #endif

  //Show all cells' indices
  if (verbose_show_cell_indices)
  {
    const int n_cells = static_cast<int>(m_cells.size());
    TRACE(n_cells);
    for (int i=0; i!=n_cells; ++i)
    {
      assert(m_cells[i]);
      {
        std::stringstream s;
        s << "m_cells[" << i << "] has index " << m_cells[i]->GetIndex()
          << " and " << m_cells[i]->GetFaces().size() << " faces:";
        TRACE(s.str());
      }
      for (auto face: m_cells[i]->GetFaces())
      {
        std::stringstream s;
        s << "owner: " << face->GetConstOwner()->GetIndex()
          << ", neighbour: " << (face->GetNeighbour() ? face->GetNeighbour()->GetIndex() : -1)
        ;
        TRACE(s.str());
      }
    }
  }

  //Order all cells by their index
  {
    //const int n_cells = static_cast<int>(m_cells.size());
    for (int i=0; i!=static_cast<int>(m_cells.size()); ++i)
    {
      while (1)
      {
        assert(i >= 0);
        assert(i < static_cast<int>(m_cells.size()));
        assert(m_cells[i]);
        const auto this_index = m_cells[i]->GetIndex();
        #ifndef NDEBUG
        if (this_index == Cell::sm_cell_no_index)
        {
          TRACE("ERROR");
          TRACE(m_cells.size());
          TRACE(m_faces.size());
          TRACE(m_cells.max_size());
          TRACE(m_faces.max_size());
          TRACE(i);
          TRACE(m_cells[i]->GetFaces().size());
          for (auto face: m_cells[i]->GetFaces())
          {
            std::stringstream s;
            s << "owner: " << face->GetConstOwner()->GetIndex()
              << ", neighbour: " << (face->GetNeighbour() ? face->GetNeighbour()->GetIndex() : -1)
            ;
            TRACE(s.str());
          }
          TRACE("BREAK"); //#221
        }
        #endif
        assert(this_index != Cell::sm_cell_no_index);
        if (i != this_index)
        {
          assert(this_index >= 0);
          assert(this_index < static_cast<int>(m_cells.size()));
          if (verbose_show_cell_indices)
          {
            std::stringstream s;
            s << "i != this_index <-> " << i << " != " << this_index;
            TRACE(s.str());
          }
          std::swap(m_cells[i],m_cells[this_index]);
        }
        else
        {
          assert(i == this_index);
          if (verbose_show_cell_indices)
          {
            std::stringstream s;
            s << "i == this_index == " << i;
            TRACE(s.str());
          }
          //Everything is OK
          break; //Next
        }
      }
    }
  }

  //#3: Go though all cells by increasing index. For each cell,
  //find the faces it owns, assign an increasing face index
  {
    int face_index = 0;
    const int max_cell_index
      = m_cells.empty()
      ? 0
      : (*std::max_element(m_cells.begin(),m_cells.end(),
          [](const boost::shared_ptr<Cell>& a, const boost::shared_ptr<Cell>& b)
          {
            return a->GetIndex() < b->GetIndex();
          }
          )
        )->GetIndex() + 1;

    for (int cell_index=0; cell_index!=max_cell_index; ++cell_index)
    {
      for (auto cell: m_cells)
      {
        if (cell->GetIndex() != cell_index) continue;
        for (auto face: cell->GetFaces())
        {
          if (face->GetIndex() == Face::sm_face_no_index)
          {
            face->SetIndex(face_index);
            ++face_index;
          }
        }
      }
    }
  }
  //#4: Within each boundary, sort the faces by
  // 1) boundary type
  // 2) its owner its (cell)index
  // 3) its neighbour its (cell)index
  if (!m_faces.empty())
  {
    const auto f = [](
      const boost::shared_ptr<Face>& lhs,
      const boost::shared_ptr<Face>& rhs) -> bool
    {
      if (!lhs && (rhs || !rhs)) return false;
      if (!rhs) return true;
      assert(lhs);
      assert(rhs);
      {
        const auto lhs_boundary_type = lhs->GetBoundaryType();
        const auto rhs_boundary_type = rhs->GetBoundaryType();
        if (lhs_boundary_type != rhs_boundary_type)
        {
          return lhs_boundary_type < rhs_boundary_type;
        }
      }
      {
        const auto lhs_owner_index = lhs->GetConstOwner()->GetIndex();
        const auto rhs_owner_index = rhs->GetConstOwner()->GetIndex();
        if (lhs_owner_index != rhs_owner_index)
        {
          return lhs_owner_index < rhs_owner_index;
        }
      }
      const auto lhs_neighbour = lhs->GetNeighbour();
      const auto rhs_neighbour = lhs->GetNeighbour();
      if ( lhs_neighbour && !rhs_neighbour) return true;
      if (!lhs_neighbour && (rhs_neighbour || !rhs_neighbour)) return false;
      return lhs_neighbour->GetIndex() < rhs_neighbour->GetIndex();
    };
    std::sort(std::begin(m_faces),std::end(m_faces),f);
  }

  //#5: Set the Faces' indices equal to their position in the vector
  {
    const int n_faces = static_cast<int>(m_faces.size());
    for (int i=0; i!=n_faces; ++i)
    {
      m_faces[i]->SetIndex(i);
    }
  }
  //Order all faces by their index
  /*
  {
    const int n_faces = static_cast<int>(m_faces.size());
    for (int i=0; i!=n_faces; ++i)
    {
      while (1)
      {
        const int this_index = m_faces[i]->GetIndex();
        if (i == this_index) break;
        std::swap(m_faces[i],m_faces[this_index]);
      }
    }
  }
  */

  //Set the Points in the correct order
  for (auto face: m_faces)
  {
    face->SetCorrectWinding();
  }

  //Set all Point indices
  {
    const int n_points = static_cast<int>(m_points.size());
    for (int i=0; i!=n_points; ++i)
    {
      m_points[i]->SetIndex(i);
    }
  }


  //Show the faces
  if (verbose_show_faces)
  {
    const int n_faces = static_cast<int>(m_faces.size());
    TRACE(n_faces);
    for (int i=0; i!=n_faces; ++i)
    {
      std::stringstream s;
      s
        << "#" << i << ": boundary type: "
        << m_faces[i]->GetBoundaryType() << ", owner index: "
        << m_faces[i]->GetConstOwner()->GetIndex()
        << ", neighbour index: "
      ;
      if (m_faces[i]->GetNeighbour())
      {
        s << m_faces[i]->GetNeighbour()->GetIndex();
      }
      else
      {
        s << "[no neighbour]";
      }
      TRACE(s.str());
    }
  }

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
        assert(face->GetConstOwner()->GetIndex() >= 0);
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

    const auto p = CreateCells();
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
}

int ribi::trim::TriangleMeshBuilderImpl::CountCells() const noexcept
{
  return static_cast<int>(m_cells.size());
}

int ribi::trim::TriangleMeshBuilderImpl::CountFaces() const noexcept
{
  return static_cast<int>(m_faces.size());
}

std::string ribi::trim::TriangleMeshBuilderImpl::CreateBoundary(
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

std::pair<std::string,std::string> ribi::trim::TriangleMeshBuilderImpl::CreateCells() const noexcept
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
    assert(face->GetConstOwner());
    out_owner << face->GetConstOwner()->GetIndex() << "\n";
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


std::string ribi::trim::TriangleMeshBuilderImpl::CreateFaces() const noexcept
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



std::string ribi::trim::TriangleMeshBuilderImpl::CreateHeader() const noexcept
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

std::string ribi::trim::TriangleMeshBuilderImpl::CreateNodes() const noexcept
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

std::string ribi::trim::TriangleMeshBuilderImpl::CreateOpenFoamFaces() const noexcept
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

std::string ribi::trim::TriangleMeshBuilderImpl::CreateOpenFoamHeader(
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

std::string ribi::trim::TriangleMeshBuilderImpl::CreateOpenFoamNodes() const noexcept
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

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilderImpl::ExtractFaces(
  const std::vector<boost::shared_ptr<Cell>>& cells
) noexcept
{
  const bool verbose = false;

  std::vector<boost::shared_ptr<Face>> v;
  for (const boost::shared_ptr<Cell>& cell: cells)
  {
    const auto w(cell->GetFaces());
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  if (verbose)
  {
    TRACE("n_face, non-unique:");
    TRACE(v.size());
  }

  std::sort(v.begin(),v.end(),Helper().OrderByIndex());
  const auto new_end = std::unique(v.begin(),v.end());
  v.erase(new_end,v.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);

  if (verbose)
  {
    TRACE("n_face, unique:");
    TRACE(v.size());
  }
  return v;


}

std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::TriangleMeshBuilderImpl::ExtractPoints(
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


std::vector<std::string> ribi::trim::TriangleMeshBuilderImpl::GetAllFolders() const noexcept
{
  return {
    "0",
    "constant",
    "constant" + ribi::fileio::FileIo().GetPathSeperator() + "polyMesh",
    "system"
  };
}

std::string ribi::trim::TriangleMeshBuilderImpl::Implode(
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

std::string ribi::trim::TriangleMeshBuilderImpl::Implode(
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

bool ribi::trim::TriangleMeshBuilderImpl::OrderByPatchFieldType(
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

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::TriangleMeshBuilderImpl::SortByBoundary(
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
void ribi::trim::TriangleMeshBuilderImpl::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::TriangleMeshBuilderImpl::Test");
  TRACE("Finished ribi::trim::TriangleMeshBuilderImpl::Test successfully");
}
#endif
