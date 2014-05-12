#ifndef TRIANGLECPPTRIANGLE_H
#define TRIANGLECPPTRIANGLE_H

namespace tricpp {

/* The triangle data structure.  Each triangle contains three pointers to    */
/*   adjoining triangles, plus three pointers to vertices, plus three        */
/*   pointers to subsegments (declared below; these pointers are usually     */
/*   `dummysub').  It may or may not also contain user-defined attributes    */
/*   and/or a floating-point "area constraint."  It may also contain extra   */
/*   pointers for nodes, when the user asks for high-order elements.         */
/*   Because the size and structure of a `triangle' is not decided until     */
/*   runtime, I haven't simply declared the type `triangle' as a struct.     */

typedef double **Triangle;            /* Really:  typedef triangle *triangle   */

} //~namespace tricpp

#endif // TRIANGLECPPTRIANGLE_H
