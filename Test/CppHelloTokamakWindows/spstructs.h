#ifndef SP_STRUCTS_H_INCLUDED
#define SP_STRUCTS_H_INCLUDED

#include "gl/glut.h"

#define PI 3.1415926535897932384626433832795
#define PIdiv180 PI/180.0f

#define NULL_VECTOR F3dVector(0.0f,0.0f,0.0f)

struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
struct SF2dVector
{
	GLfloat x,y;
};

struct SF4dVector
{
	GLfloat a[4];
};


//********************
// 3d-Vectors
//
SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z );
SF3dVector AddF3dVectors ( SF3dVector * u, SF3dVector * v);
SF3dVector operator* (SF3dVector v, float r);
SF3dVector operator* (float r, SF3dVector v);
SF3dVector operator/ (SF3dVector v, float r);
float operator* (SF3dVector v, SF3dVector u);	//Scalar product
SF3dVector operator+ (SF3dVector v, SF3dVector u);
SF3dVector operator- (SF3dVector v, SF3dVector u);

bool operator== (SF3dVector v, SF3dVector u);
bool operator!= (SF3dVector v, SF3dVector u);

GLfloat GetF3dVectorLength( SF3dVector * v);
void AddF3dVectorToVector	( SF3dVector * Dst, SF3dVector * V2);

//********************
// 2d-Vectors
//

SF2dVector F2dVector ( GLfloat x, GLfloat y);
SF2dVector operator+ (SF2dVector v, SF2dVector u);
SF2dVector operator- (SF2dVector v, SF2dVector u);



struct S3dModelVertex
{
	SF3dVector Position;
	SF2dVector TexCoordinates;
	SF3dVector NormalVector; 
};

struct SSPMaterial
{
//not everything in use!
	GLfloat	m_fAmbient[4]; 
	GLfloat	m_fDiffuse[4]; 
	GLfloat	m_fSpecular[4];
	GLfloat	m_fEmissive[4];
	GLfloat	m_fShininess;
	GLfloat	m_fTransparency;
};

struct SSPForce
{
	SF3dVector		m_Direction;  //also indicates the amount
	SF3dVector		m_Position;  //relative to the center of gravity
	bool			m_bInUse;  //make the calculations more performant by easily dropping non-used forces
};

struct SSPMomentum
{
	SF3dVector		m_Momentum;
	SF3dVector		m_Position;
};

//data structure to store on which node/plate of a track a vehicle resides.
struct SSPVehicleTrackPosition
{
	int m_iNodeIndex; 
	int m_iPlateIndex;
};

struct SSPBottomPoint
{
	int				  m_VertexIndex;  //in MODEL0! (which vertex is used as bottom point)
	SF3dVector		  m_TurnedPosition; //vertex pos turned around center
	SF3dVector		  m_GlobalPosition; //turned pos + center pos
	SF3dVector		  m_FormerGlobalPosition;  //one frame before
	float			  m_TrackYDist;	  //yDist to the track
	SSPVehicleTrackPosition  m_TrackPosition; //Plate/Node
};

#endif