#include "SPMath.h"
#include <math.h>
#include "SPStructs.h"


#define sqr(x) (x*x)

SF3dVector AddF3dVectors (SF3dVector* u, SF3dVector* v)
{
	SF3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}

GLfloat GetF3dVectorLength( SF3dVector * v)
{
	return (GLfloat)(sqrt(sqr(v->x)+sqr(v->y)+sqr(v->z)));
}


SF3dVector Normalize3dVector( SF3dVector v)
{
	SF3dVector res;
	float l = GetF3dVectorLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v)
{
	SF3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}


SF3dVector GetTurnedVector(SF3dVector v, SF3dVector ex, SF3dVector ey, SF3dVector ez)
{
	SF3dVector res;
	res.x = v.x*ex.x + v.y*ey.x + v.z*ez.x;
	res.y = v.x*ex.y + v.y*ey.y + v.z*ez.y;
	res.z = v.x*ex.z + v.y*ey.z + v.z*ez.z;

	return res;

}


SF3dVector TurnVector(SF3dVector v, SF3dVector angles)
{
	/*> ich habe ein Koordinatensystem, das durch die Vektoren ex = (1,0,0),
> ey = (0,1,0) und ez = (0,0,1) definiert ist.
> Ich möchte das gesamte Koordinatensystem um alle 3 Achsen drehen
> (WinkelX, WinkelY, WinkelZ).
> Kann mir bitte jemand sagen, wie dann die Vektoren ex, ey und ez
> aussehen?

Ich weiß natürlich nicht, wieweit Du "vorbelastet" bist, aber ich fang jetzt
einfach mal an.

Wenn man die 3 Einheitsvektoren ex, ey und ez, die eine Basis des |R^3 sind, und
den Anschauungsraum aufspannen, als Spalten einer Matrix betrachtet, dann sieht
das so aus:

1 0 0
0 1 0
0 0 1

Wenn man dieses Koordinatensystem nun im Raum drehen will, so macht man das
genau so, wie von Dir vorgeschlagen, um jede der 3 Achsen separat. Am
leichtesten kann man das mithilfe von Drehmatrizen schreiben:

Das Koordinatensystem sieht nach einer Drehung um die Winkel wX, wY, wZ um die
zugehörigen Achsen wie folgt aus:

( 1 0 0 ) ( 1     0       0    ) ( cos wY  0   sin wY ) ( cos wZ   - sin wZ  0 )
( 0 1 0 )*( 0  cos wX  -sin wX )*( 0       1    0     )*( sin wZ   cos wZ    0 )
( 0 0 1 ) ( 0  sin wX   cos wX ) (-sin wY  0   cos wY ) (  0        0        1 )

Wenn man das ausrechnet, kommt das hier raus:

    [cos(wY) cos(wZ) , -cos(wY) sin(wZ) , sin(wY)]
	
    [sin(wX) sin(wY) cos(wZ) + cos(wX) sin(wZ) ,
     -sin(wX) sin(wY) sin(wZ) + cos(wX) cos(wZ) ,
	 -sin(wX) cos(wY)]
	 
    [-cos(wX) sin(wY) cos(wZ) + sin(wX) sin(wZ) ,
     cos(wX) sin(wY) sin(wZ) + sin(wX) cos(wZ) ,
	 cos(wX) cos(wY)]

In den eckigen Klammern stehn jeweils die Zeilen der Matrix.

Die von Dir gesuchten Vektoren sind die Spalten der Matrix, d.h ex wurde auf

     ( cos(wY) cos(wZ)                            )
X =  ( sin(wX) sin(wY) cos(wZ) + cos(wX) sin(wZ)  )
     ( -cos(wX) sin(wY) cos(wZ) + sin(wX) sin(wZ) )

abgebildet, etc.

P.S. Diese gedrehten Vektoren haben immer noch die Länge 1.

Probe für den Vektor X (mit Maple ;-)

simplify ((cos(wY)*cos(wZ))^2 + (sin(wX)*sin(wY)*cos(wZ)+cos(wX)*sin(wZ))^2 +
> (-cos(wX)*sin(wY)*cos(wZ)+sin(wX)*sin(wZ))^2);

1

OK, paßt!

Viele Grüsse,
 Simon*/
	SF3dVector ex = F3dVector(1.0f,0.0f,0.0f);
	SF3dVector ey = F3dVector(0.0f,1.0f,0.0f);
	SF3dVector ez = F3dVector(0.0f,0.0f,1.0f);

	//turn ex...
	//around z-axis:
	ex.x = (float)cos(angles.z*PIdiv180);
	ex.y = (float)sin(angles.z*PIdiv180);
	//around y-axis:
	ex.x *= (float)cos(angles.y*PIdiv180);
	ex.z = (float)sin(angles.y*PIdiv180);


	//turn ey...
	//around x-axis:
	ey.y = (float)cos(angles.x*PIdiv180);
	ey.z = (float)sin(angles.x*PIdiv180);
	//around z-axis:
	ey.y *= (float)cos(angles.z*PIdiv180);
	ey.x = (float)sin(angles.z*PIdiv180);

	//turn ez...
	//around x-axis:
	ez.z = (float)cos(angles.x*PIdiv180);
	ez.y = (float)sin(angles.x*PIdiv180);
	//around y-axis:
	ez.x = (float)sin(angles.y*PIdiv180);
	ez.z *= (float)cos(angles.y*PIdiv180);


	//NOT YET COMPLETELY CODED!!
	SF3dVector res;
	float cosy = (float)cos(angles.y*PIdiv180); 
	float siny = (float)sin(angles.y*PIdiv180);
	res.x = (float)(v.x*cosy + v.z*siny);
	res.y = v.y;
	res.z = (float)(-v.x*siny + v.z*cosy);

	return res;
}


bool PointInTriangle( SF2dVector Point, SF2dVector Triangle[3])
{
	SF2dVector t1,t2,t3,a,b,c;
	t1 = Triangle[0];t2 = Triangle[1];t3 = Triangle[2];
	a = Point-t1; b = t3-t2; c = t2-t1;

	float r,s;

	s =-(c.x*a.y-c.y*a.x) 
		/ 
		(b.x*a.y-b.y*a.x);

	r = (c.x*a.y+b.x*a.y*s)
		/ 
		(a.x*a.y);

	bool res = ((r >= 1.0f) && (s >= 0.0f) && (s <= 1.0f));
	return res;
}

bool Intersect2dLines ( SF2dVector p1, SF2dVector d1,
						SF2dVector p2, SF2dVector d2,	 	
						SF2dVector* intersectionPoint)
{
	float denominator = ((d2.y*d1.x)-(d2.x*d1.y));
	if (denominator == 0.0f) return false;

	float s = ((p2.x-p1.x)*d1.y-(p2.y-p1.y)*d1.x)
			  / 
			  denominator;

	float r = (p2.x-p1.x+d2.x*s)
			  /
			  d1.x;

	bool res = ((s>0) && (s <= 1.0f) && (r>0) && (r<=1.0f));
	if (!res) return false;

	intersectionPoint->x = p1.x + d1.x*r;
	intersectionPoint->y = p1.y + d1.y*r;


	return true;



}
