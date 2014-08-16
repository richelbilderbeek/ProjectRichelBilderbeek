#ifndef TRIANGLECPPINSERTVERTEXRESULT_H
#define TRIANGLECPPINSERTVERTEXRESULT_H

namespace ribi {
namespace tricpp {

/* Labels that signify the result of vertex insertion.  The result indicates */
/*   that the vertex was inserted with complete success, was inserted but    */
/*   encroaches upon a subsegment, was not inserted because it lies on a     */
/*   segment, or was not inserted because another vertex occupies the same   */
/*   location.                                                               */

enum class InsertVertexResult
{
  SUCCESSFULVERTEX,
  ENCROACHINGVERTEX,
  VIOLATINGVERTEX,
  DUPLICATEVERTEX
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPINSERTVERTEXRESULT_H
