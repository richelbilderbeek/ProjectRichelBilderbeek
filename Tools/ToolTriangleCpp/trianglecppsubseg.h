#ifndef TRIANGLECPPSUBSEG_H
#define TRIANGLECPPSUBSEG_H

namespace tricpp {

/* The subsegment data structure.  Each subsegment contains two pointers to  */
/*   adjoining subsegments, plus four pointers to vertices, plus two         */
/*   pointers to adjoining triangles, plus one boundary marker, plus one     */
/*   segment number.                                                         */

typedef double **SubSeg;                  /* Really:  typedef subseg *subseg   */

} //~namespace tricpp

#endif // TRIANGLECPPSUBSEG_H
