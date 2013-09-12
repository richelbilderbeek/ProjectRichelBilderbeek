#pragma once

///********************************************************************
///* CTokSim
///*
///* CTokSim is a base class for OpenGL applications
///* using the Tokamak physics engine (http://www.tokamakphysics.com).
///* It can display all basic simulation scenes and handle
///* springs.
///* 
///* Author: Philipp Crocoll 
///* philipp.crocoll@web.de
///* www.codecolony.de
///* 
///* This class maybe used freely. I am glad
///* to here where it ends up!
///* 
///* If you have suggestions or improvements,
///* please e-mail me!
///* 
///********************************************************************

#include "tokamak.h"
#include "TokSpring.h"

//Define the max number of objects the simulation can handle.
//This is not the number which is passed the tokamak! (see "Init()")
#define MAX_RIGID_COUNT 1000
#define MAX_ANIMATED_COUNT 1000
#define MAX_SPRING_COUNT 1000



class CTokSim
{
protected:
	//Tokamak variables:
	neSimulator *m_Sim;
	neRigidBody *m_Rigid[MAX_RIGID_COUNT];
	neAnimatedBody *m_Animated[MAX_ANIMATED_COUNT];
	//Springs:
	CTokSpring	*m_Spring[MAX_SPRING_COUNT];
	//Number of max objects passed to tokamak:
	int			m_MaxRigidCount;
	int			m_MaxAnimatedCount;
	//Number of objects created:
	int			m_AnimatedCount, m_RigidCount, m_SpringCount;

	//used for terrain meshes:
	int			m_NumVertices;
	int			m_NumIndices;
	GLfloat		* m_VertexData;
	GLuint		* m_IndexData;
	
	//Internal rendering functions:
	void RenderSphere(neT3 TransformMatrix, float Diameter);
	void RenderCylinder(neT3 TransformMatrix, float Diameter, float Height);
	void RenderBox(neT3 TransformMatrix, neV3 Size);
	void ApplyTransform(neT3 TransformMatrix);
	void RenderGeometry(neGeometry * geom);
	void RenderSpring(CTokSpring * spring);

	//Use this function, then the class will display the mesh
	void SetTerrainMesh(neTriangleMesh* Mesh);

public:
	//Constructor
	CTokSim(void);
	//Destructor
	~CTokSim(void);
	//displays the scene:
	void Display(void);
	//Initialize the class:
	void Init(int MaxRigidCount, int MaxAnimatedCount, neV3 gravity);

	//Create objects:
	CTokSpring * CreateSpring(neRigidBody * rigid1, neRigidBody * rigid2);
	CTokSpring * CreateSpring(neRigidBody * rigid, neAnimatedBody * anim);
	neRigidBody * CreateRigidBody();
	neAnimatedBody * CreateAnimatedBody();
	//returns a pointer to the tokamak simulator object:
	neSimulator * GetSimulator();
	
	//calls the tokamak advance function:
	bool CalculateNextFrame(float dtime);

	
};
