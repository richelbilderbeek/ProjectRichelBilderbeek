#include "trianglecppsyntax.h"

#include <iostream>
#include <sstream>

void ribi::tricpp::Syntax()
{
  std::stringstream s;
  s
    << "triangle [-rq__a__uAcDjevngBPNEIOXzo_YS__iFlsCQVh] input_file\n"
    << "\n"
    << "input_file must be a .poly file\n"
    << "\n"
    << "    -r  Refines a previously generated mesh.\n"
    << "    -q  Quality mesh generation.  A minimum angle may be specified.\n"
    << "    -a  Applies a maximum triangle area constraint.\n"
    << "    -u  Applies a user-defined triangle constraint.\n"
    << "    -A  Applies attributes to identify triangles in certain regions.\n"
    << "    -c  Encloses the convex hull with segments.\n"
    << "    -D  Conforming Delaunay:  all triangles are truly Delaunay.\n"
    << "    -j  Jettison unused vertices from output .node file.\n"
    << "    -e  Generates an edge list.\n"
    << "    -v  Generates a Voronoi diagram.\n"
    << "    -n  Generates a list of triangle neighbors.\n"
    << "    -g  Generates an .off file for Geomview.\n"
    << "    -B  Suppresses output of boundary information.\n"
    << "    -P  Suppresses output of .poly file.\n"
    << "    -N  Suppresses output of .node file.\n"
    << "    -E  Suppresses output of .ele file.\n"
    << "    -I  Suppresses mesh iteration numbers.\n"
    << "    -O  Ignores holes in .poly file.\n"
    << "    -X  Suppresses use of exact arithmetic.\n"
    << "    -z  Numbers all items starting from zero (rather than one).\n"
    << "    -o2 Generates second-order subparametric elements.\n"
    << "    -Y  Suppresses boundary segment splitting.\n"
    << "    -S  Specifies maximum number of added Steiner points.\n"
    << "    -i  Uses incremental method, rather than divide-and-conquer.\n"
    << "    -F  Uses Fortune's sweepline algorithm, rather than d-and-c.\n"
    << "    -l  Uses vertical cuts only, rather than alternating cuts.\n"
    << "    -s  Force segments into mesh by splitting (instead of using CDT).\n"
    << "    -C  Check consistency of final mesh.\n"
    << "    -Q  Quiet:  No terminal output except errors.\n"
    << "    -V  Verbose:  Detailed information on what I'm doing.\n"
    << "    -h  Help:  Detailed instructions for Triangle.\n"
  ;
  std::cout << s;
}
