#ifndef RIBI_POLYFILE_H
#define RIBI_POLYFILE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/quantity.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///PolyFile allows for conversion between
///multiple polygons to a .poly file
///
///Does not allow holes
struct PolyFile
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Polygon> Polygons;

  typedef std::pair<int,int> Edge; //An Edge has exactly two Vertex indices
  typedef std::vector<Edge> Edges;
  typedef Coordinat Vertex;
  typedef std::vector<Vertex> Vertices;

  ///Start from data members
  PolyFile(const Vertices& vertices,const Edges& edges);

  ///Start from polygons
  PolyFile(
    const Polygons& shapes
  ) : PolyFile(ToVertices(shapes),ToEdges(shapes)) { }

  ///Start from filename
  PolyFile(
    const std::string& poly_filename
  ) : PolyFile(Parse(poly_filename)) {}

  static Polygon CreateShapeHeart(const double scale = 1.0) noexcept;
  static Polygon CreateShapeHouse(const double scale = 1.0) noexcept;
  static Polygon CreateShapePolygon(const int n, const double rotation = 0.0, const double scale = 0.0) noexcept;
  static Polygon CreateShapeTriangle(const double scale = 1.0) noexcept;

  ///Obtain all pair of vertex indices that form an edge
  ///For example '{{0,1},{1,2},{2,0}}', for a triangle
  const Edges& GetEdges() const noexcept { return m_edges; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain all vertex coordinats
  ///For example '{{0.0,0.0},{0.0,1.0},{1.0,0.0}}'
  const Vertices& GetVertices() const noexcept { return m_vertices; }

  ///Convert the vertices and edges to a .poly file its content
  std::string ToStr() const noexcept;

  private:
  const Edges m_edges;
  const Vertices m_vertices;


  PolyFile(const std::pair<Vertices,Edges>& p)
    : PolyFile(p.first,p.second) {}

  static std::vector<std::string> FileToNoCommentVector(const std::string& filename) noexcept;

  static std::pair<Vertices,Edges> Parse(const std::string& filename);

  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static Edges ToEdges(const Polygons& polygons) noexcept;
  static Vertices ToVertices(const Polygons& polygons) noexcept;
};

///Convert the vertices and edges to a .poly file its content
std::ostream& operator<<(std::ostream& os, const PolyFile& file) noexcept;

} //~namespace ribi

/*
From http://people.sc.fsu.edu/~jburkardt/data/poly/poly.html :

Comments are prefixed by the character '#'. Everything from the comment character to the end of the line is ignored.

Vertices, segments, holes, and regions must be numbered and listed consecutively, starting from either 1 or 0.

The first line lists

    The number of vertices (this is sometimes set to 0, to indicate that the vertices should be read from a NODE file);
    The spatial dimension, which must be 2;
    The number of vertex attributes;
    The number of vertex boundary markers, which must be 0 or 1.

The vertex records must follow, with the format:

    vertex index (these must be consecutive, starting either from 0 or 1);
    X and Y coordinates;
    The vertex attributes (if any);
    The vertex boundary marker (if any).

The next line lists

    The number of segments;
    The number of segment boundary markers (0 or 1).

Segments should not cross each other; vertices should only lie on the ends of segments, and are never contained inside a segment.

The segments records must follow, with the format:

    segment index;
    start vertex, end vertex;
    Boundary marker (if any).

The third section lists holes (and concavities, if -c is selected) in the triangulation. Holes are specified by identifying a point inside each hole. After the triangulation is formed, Triangle creates holes by eating triangles, spreading out from each hole point until its progress is blocked by PSLG segments; you must be careful to enclose each hole in segments, or your whole triangulation might be eaten away. If the two triangles abutting a segment are eaten, the segment itself is also eaten. Do not place a hole directly on a segment; if you do, Triangle chooses one side of the segment arbitrarily.

The next line lists

    The number of holes.

The hole records must follow, with the format:

    hole index;
    X coordinate, Y coordinate of some point within the hole.

The optional fourth section lists regional attributes (to be assigned to all triangles in a region) and regional constraints on the maximum triangle area. Triangle reads this section only if the -A switch is used or the -a switch is used without a number following it, and the -r switch is not used. Regional attributes and area constraints are propagated in the same manner as holes; you specify a point for each attribute and/or constraint, and the attribute and/or constraint affects the whole region (bounded by segments) containing the point. If two values are written on a line after the x and y coordinate, the first such value is assumed to be a regional attribute (but is only applied if the -A switch is selected), and the second value is assumed to be a regional area constraint (but is only applied if the -a switch is selected). You may specify just one value after the coordinates, which can serve as both an attribute and an area constraint, depending on the choice of switches. If you are using the -A and -a switches simultaneously and wish to assign an attribute to some region without imposing an area constraint, use a negative maximum area.

The next line is optional. If given, it lists

    The number of region attributes.

The optional regional attributes records must follow, with the format:

    region index;
    X coordinate, Y coordinate of a point in the region;
    Attributes (if any);
    Maximum area of triangles in the region;

A Sample POLY file:

Here is a sample file box.poly describing a square with a square hole.

    # A box with eight vertices in 2D, no attributes, one boundary marker.
    8 2 0 1
     # Outer box has these vertices:
     1   0 0   0
     2   0 3   0
     3   3 0   0
     4   3 3   33     # A special marker for this vertex.
     # Inner square has these vertices:
     5   1 1   0
     6   1 2   0
     7   2 1   0
     8   2 2   0
    # Five segments with boundary markers.
    5 1
     1   1 2   5      # Left side of outer box.
     # Square hole has these segments:
     2   5 7   0
     3   7 8   0
     4   8 6   10
     5   6 5   0
    # One hole in the middle of the inner square.
    1
     1   1.5 1.5


*/

#endif // RIBI_POLYFILE_H
