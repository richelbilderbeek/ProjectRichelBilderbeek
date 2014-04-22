#include "SPStructs.h"
#include <math.h>

bool operator== (SF3dVector v, SF3dVector u)
{
	return (v.x==u.x) && (v.y==u.y) && (v.z == u.z);
}
bool operator!= (SF3dVector v, SF3dVector u)
{
	return (!(v==u));
}


float operator* (SF3dVector v, SF3dVector u)	//Scalar product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}

SF3dVector operator* (SF3dVector v, float r)
{
	SF3dVector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}
SF3dVector operator* (float r, SF3dVector v)
{
	return v*r;
}

SF3dVector operator/ (SF3dVector v, float r)
{
	return v*(1/r);
}

SF3dVector operator+ (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
SF3dVector operator- (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}


SF2dVector operator+ (SF2dVector v, SF2dVector u)
{
	SF2dVector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	return res;

}

SF2dVector operator- (SF2dVector v, SF2dVector u)
{
	SF2dVector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	return res;
}

SF2dVector F2dVector ( GLfloat x, GLfloat y)
{
	SF2dVector tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}
