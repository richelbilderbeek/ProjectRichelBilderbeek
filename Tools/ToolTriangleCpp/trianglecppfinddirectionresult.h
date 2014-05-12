#ifndef TRIANGLECPPFINDDIRECTIONRESULT_H
#define TRIANGLECPPFINDDIRECTIONRESULT_H

namespace tricpp {

/* Labels that signify the result of direction finding.  The result          */
/*   indicates that a segment connecting the two query points falls within   */
/*   the direction triangle, along the left edge of the direction triangle,  */
/*   or along the right edge of the direction triangle.                      */

enum FindDirectionResult {WITHIN, LEFTCOLLINEAR, RIGHTCOLLINEAR};

} //~namespace tricpp

#endif // TRIANGLECPPFINDDIRECTIONRESULT_H
