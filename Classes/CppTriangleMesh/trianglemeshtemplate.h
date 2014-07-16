#ifndef RIBI_TRIANGLEMESHTEMPLATE_H
#define RIBI_TRIANGLEMESHTEMPLATE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Template is a two-dimensional mesh, consisting of Points, Edges and Faces only
///It constructs itself from a TemplateFile its output (.node and .ele) files
///
///The next step will be to create a multiple layers of Cells by CellsCreator
struct Template
{
  //friend class CellsCreator;
  //friend class CellsCreatorFactory;
  //friend class CellFactory;
  //friend class Dialog;

  typedef boost::geometry::model::d2::point_xy<double> ConstCoordinat2D;

  Template(
    const std::string& filename_node,
    const std::string& filename_ele,
    const bool verbose
  );

  int CountFaces() const noexcept { return static_cast<int>(m_faces.size() ); }
  int CountNodes() const noexcept { return static_cast<int>(m_points.size()); }

  static boost::shared_ptr<Template> CreateTest(const int i) noexcept;

  const std::vector<std::pair<int,int>>& GetEdges() const noexcept { return m_edges; }
  const std::vector<boost::shared_ptr<Face>>& GetFaces() const noexcept { return m_faces; }
  const std::vector<std::vector<int>>& GetFacePointIndices() const noexcept { return m_face_point_indices; }
  const std::vector<boost::shared_ptr<Point>>& GetPoints() const noexcept { return m_points; }

  private:
  Template(
    const std::vector<std::pair<int,int>>& edges,
    const std::vector<boost::shared_ptr<Face>>& faces,
    const std::vector<std::vector<int>>& face_point_indices,
    const std::vector<boost::shared_ptr<Point>>& points
  );
  Template(const Template& ) = delete;
  //Template(      Template&&) = delete;
  Template& operator=(const Template& ) = delete;
  //Template& operator=(      Template&&) = delete;
  ~Template() noexcept {}

  ///ints are m_points indices
  std::vector<std::pair<int,int>> m_edges;
  std::vector<boost::shared_ptr<Face>> m_faces;
  std::vector<std::vector<int>> m_face_point_indices;
  std::vector<boost::shared_ptr<Point>> m_points;

  //No idea why Triangle started using the Dutch numbering system...
  static std::string ConvertNumbersToEnglish(const std::string& s) noexcept;

  static boost::shared_ptr<Template> CreateTest2x3() noexcept;
  static boost::shared_ptr<Template> CreateTest3x3() noexcept;
  static boost::shared_ptr<Template> CreateTestSquare2x2() noexcept;
  static boost::shared_ptr<Template> CreateTestTriangle2x2() noexcept;

  static std::vector<std::string> CleanAndSplitString(
    const std::string& input) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend void boost::checked_delete<>(      Template*);
  friend void boost::checked_delete<>(const Template*);
  friend class boost::detail::sp_ms_deleter<      Template>;
  friend class boost::detail::sp_ms_deleter<const Template>;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHTEMPLATE_H
