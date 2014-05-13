#include "trianglecpptriangulateio.h"

ribi::tricpp::TriangulateIo::TriangulateIo()
  : m_edgelist{nullptr},
    m_edgemarkerlist{nullptr},
    m_holelist{nullptr},
    m_neighborlist{nullptr},
    m_normlist{nullptr},
    m_pointattributelist{nullptr},
    m_pointlist{nullptr},
    m_pointmarkerlist{nullptr},
    m_regionlist{nullptr},
    m_segmentlist{nullptr},
    m_segmentmarkerlist{nullptr},
    m_trianglearealist{nullptr},
    m_triangleattributelist{nullptr},
    m_trianglelist{nullptr},
    m_numberofcorners{0},
    m_numberofedges{0},
    m_numberofholes{0},
    m_numberofpointattributes{0},
    m_numberofpoints{0},
    m_numberofregions{0},
    m_numberofsegments{0},
    m_numberoftriangleattributes{0},
    m_numberoftriangles{0}
{

}
