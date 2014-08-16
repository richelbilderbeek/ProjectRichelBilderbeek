#ifndef TRIANGLECPPGLOBALS_H
#define TRIANGLECPPGLOBALS_H

#include <utility>

namespace ribi {
namespace tricpp {
///TODO: Remove these

struct Global
{
  Global() : Global(CreateEpsilonAndSplitter()) {}
  const double m_ccwerrboundA;
  const double m_ccwerrboundB;
  const double m_ccwerrboundC;

  ///  `epsilon' is the largest power of two such that 1.0 + epsilon = 1.0 in
  ///  floating-point arithmetic.  `epsilon' bounds the relative roundoff
  ///  error.  It is used for floating-point error analysis.
  const double m_epsilon;
  const double m_iccerrboundA;
  const double m_iccerrboundB;
  const double m_iccerrboundC;
  const double m_o3derrboundA;
  const double m_o3derrboundB;
  const double m_o3derrboundC;
  const double m_resulterrbound;

  ///  `splitter' is used to split floating-point numbers into two half-
  ///  length significands for exact multiplication.
  const double m_splitter; /// Used to split double factors for exact multiplication

  private:
  Global(const std::pair<double,double>& p);
  static std::pair<double,double> CreateEpsilonAndSplitter() noexcept;
};



/* Maximum number of characters in a line read from a file (including the    */
/*   null).                                                                  */

const int g_max_inputline_size = 1024;

/* For efficiency, a variety of data structures are allocated in bulk.  The  */
/*   following constants determine how many of each structure is allocated   */
/*   at once.                                                                */

const int g_triangles_per_block = 4092;           /* Number of triangles allocated at once. */
const int SUBSEGPERBLOCK = 508;       /* Number of subsegments allocated at once. */
const int VERTEXPERBLOCK = 4092;         /* Number of vertices allocated at once. */
const int VIRUSPERBLOCK = 1020;   /* Number of virus triangles allocated at once. */
/* Number of encroached subsegments allocated at once. */
const int BADSUBSEGPERBLOCK = 252;
/* Number of skinny triangles allocated at once. */
const int g_bad_triangles_per_block = 4092;
/* Number of flipped triangles allocated at once. */
const int FLIPSTACKERPERBLOCK = 252;
/* Number of splay tree nodes allocated at once. */
const int SPLAYNODEPERBLOCK = 508;

/* Two constants for algorithms based on random sampling.  Both constants    */
/*   have been chosen empirically to optimize their respective algorithms.   */

/* Used for the point location scheme of Mucke, Saias, and Zhu, to decide    */
/*   how large a random sample of triangles to inspect.                      */

#define SAMPLEFACTOR 11

/* Used in Fortune's sweepline Delaunay algorithm to determine what fraction */
/*   of boundary edges should be maintained in the splay tree for point      */
/*   location on the front.                                                  */

const int SAMPLERATE = 10;

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPGLOBALS_H
