#ifndef TRIANGLECPPTRIANGULATEIO_H
#define TRIANGLECPPTRIANGULATEIO_H

namespace ribi {
namespace tricpp {

struct TriangulateIo
{
  TriangulateIo();
  int *m_edgelist; /// Out only
  int *m_edgemarkerlist; /// Not used with Voronoi diagram; out only
  double *m_holelist;/// In / pointer to array copied out
  int *m_neighborlist;/// Out only
  double *m_normlist; /// Used only with Voronoi diagram; out only
  double *m_pointattributelist;  /// In / out
  double *m_pointlist;  /// In / out
  int *m_pointmarkerlist;/// In / out
  double *m_regionlist; /// In / pointer to array copied out
  int *m_segmentlist; /// In / out
  int *m_segmentmarkerlist; /// In / out
  double *m_trianglearealist;  /// In only
  double *m_triangleattributelist;  /// In / out
  int *m_trianglelist;/// In / out
  int m_numberofcorners; /// In / out
  int m_numberofedges; /// Out only
  int m_numberofholes; /// In / copied out
  int m_numberofpointattributes;  /// In / out
  int m_numberofpoints;  /// In / out
  int m_numberofregions; /// In / copied out
  int m_numberofsegments;/// In / out
  int m_numberoftriangleattributes;  /// In / out
  int m_numberoftriangles;  /// In / out
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPTRIANGULATEIO_H
