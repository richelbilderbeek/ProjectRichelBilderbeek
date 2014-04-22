#ifndef SP_MATH_INCLUDED_

#define SP_MATH_INCLUDED_

#include "SPStructs.H"


SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v);
SF3dVector TurnVector ( SF3dVector v, SF3dVector angles);
SF3dVector GetTurnedVector(SF3dVector v, SF3dVector ex, SF3dVector ey, SF3dVector ez);
SF3dVector Normalize3dVector( SF3dVector v);


bool PointInTriangle( SF2dVector Point, SF2dVector Triangle[3]);
bool Intersect2dLines ( SF2dVector p1, SF2dVector d1,
						SF2dVector p2, SF2dVector d2,	 	
						SF2dVector* intersectionPoint);


#endif