#ifndef TRIANGLEMESHTEMPLATE_H
#define TRIANGLEMESHTEMPLATE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Template is a bare-bone layer, consisting of Points and Faces only
///It constructs itself from a TemplateFile its output (.node and .ele) files
///
///The next step will be to create a multiple layers of Cells by CellsCreator
struct Template
{
  Template(
    const std::string& filename_node,
    const std::string& filename_ele
  );

  int CountFaces() const noexcept { return static_cast<int>(m_faces.size() ); }
  int CountNodes() const noexcept { return static_cast<int>(m_points.size()); }

  static const boost::shared_ptr<Template> CreateTest(const int i) noexcept;

  const std::vector<std::pair<int,int>>& GetEdges() const noexcept { return m_edges; }
  const std::vector<boost::shared_ptr<Face>>& GetFaces() const noexcept { return m_faces; }
  const std::vector<std::vector<int>>& GetFacePointIndices() const noexcept { return m_face_point_indices; }
  const std::vector<boost::shared_ptr<Point>>& GetPoints() const noexcept { return m_points; }

  private:
  Template(
    std::vector<std::pair<int,int>> edges,
    std::vector<boost::shared_ptr<Face>> faces,
    std::vector<std::vector<int>> face_point_indices,
    std::vector<boost::shared_ptr<Point>> points
  );

  ///ints are m_points indices
  std::vector<std::pair<int,int>> m_edges;
  std::vector<boost::shared_ptr<Face>> m_faces;
  std::vector<std::vector<int>> m_face_point_indices;
  std::vector<boost::shared_ptr<Point>> m_points;

  static const boost::shared_ptr<Template> CreateTest2x2() noexcept;
  static const boost::shared_ptr<Template> CreateTest2x3() noexcept;
  static const boost::shared_ptr<Template> CreateTest3x3() noexcept;

  //Split a string
  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input) noexcept;
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHTEMPLATE_H
