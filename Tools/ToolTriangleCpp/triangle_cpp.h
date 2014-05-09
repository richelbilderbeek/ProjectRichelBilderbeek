#ifndef TRIANGLE_CPP_H
#define TRIANGLE_CPP_H
#include <string>
#include <vector>

int triangle_cpp_main(
  const std::vector<std::string>& args
);

struct triangulateio_cpp {
  double *pointlist;                                               /* In / out */
  double *pointattributelist;                                      /* In / out */
  int *pointmarkerlist;                                          /* In / out */
  int numberofpoints;                                            /* In / out */
  int numberofpointattributes;                                   /* In / out */

  int *trianglelist;                                             /* In / out */
  double *triangleattributelist;                                   /* In / out */
  double *trianglearealist;                                         /* In only */
  int *neighborlist;                                             /* Out only */
  int numberoftriangles;                                         /* In / out */
  int numberofcorners;                                           /* In / out */
  int numberoftriangleattributes;                                /* In / out */

  int *segmentlist;                                              /* In / out */
  int *segmentmarkerlist;                                        /* In / out */
  int numberofsegments;                                          /* In / out */

  double *holelist;                        /* In / pointer to array copied out */
  int numberofholes;                                      /* In / copied out */

  double *regionlist;                      /* In / pointer to array copied out */
  int numberofregions;                                    /* In / copied out */

  int *edgelist;                                                 /* Out only */
  int *edgemarkerlist;            /* Not used with Voronoi diagram; out only */
  double *normlist;                /* Used only with Voronoi diagram; out only */
  int numberofedges;                                             /* Out only */
};

void triangulate(
  const char * const ,
  const triangulateio_cpp * const ,
  const triangulateio_cpp * const ,
  const triangulateio_cpp * const
);

#endif // TRIANGLE_CPP_H
