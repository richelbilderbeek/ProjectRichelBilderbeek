#include "StdAfx.h"
#include ".\simpletoksim.h"
#include "TokSim.h"

#define FLOORSIZE 20.0f


SimpleTokSim::SimpleTokSim(void)
{
	CTokSim::CTokSim();
}

SimpleTokSim::~SimpleTokSim(void)
{
}

void SimpleTokSim::Init()
{
	

	neGeometry *geom;
    neV3 boxSize1;
    neV3 gravity;
    neV3 pos;
	gravity.Set(0.0f, -10.0f, 0.0f);

	//Init the simulation:
	CTokSim::Init(100,2,gravity);

	//Create rigid bodies. use boxes, spheres, and cylinders:
	for (int i=0; i<m_MaxRigidCount; i++)
    {
        // Create a rigid body using the CTokSim class:
        neRigidBody * rigid = CreateRigidBody();
		
		rigid->SetMass(0.01f);
		
		// Add geometry to the body and set it to be a box of dimensions 1, 1, 1
        geom = rigid->AddGeometry();
        boxSize1.Set(1.0f, 1.0f, 1.0f);
		if (i%3 == 0)
		{
			geom->SetBoxSize(boxSize1[0], boxSize1[1], boxSize1[2]);
			rigid->SetInertiaTensor(neBoxInertiaTensor(boxSize1[0], boxSize1[1], boxSize1[2],rigid->GetMass()));
		}
		if (i%3 == 1)
		{
			geom->SetSphereDiameter(1.0f);
			rigid->SetInertiaTensor(neSphereInertiaTensor(1.0f,rigid->GetMass()));
		}
		if (i%3 == 2)
		{
			static float Height = 1.0f;
			static float Diameter = 1.0f;
			geom->SetCylinder(Diameter,Height);
			rigid->SetInertiaTensor(neCylinderInertiaTensor(Diameter,Height,rigid->GetMass()));
		}
		
		// Update the bounding info of the object -- must always call this
        // after changing a body's geometry.
        rigid->UpdateBoundingInfo();
		

	    // Vary the position so the cubes don't all exactly stack on top of each other
        pos.Set((float)(rand()%10) / 100, 4.0f + i*2.0f, (float)(rand()%10) / 100);
        rigid->SetPos(pos);
    }
	    
	
	
	// Create an animated body for the floor
    neAnimatedBody * animated =  CreateAnimatedBody();
    geom = animated->AddGeometry();
    boxSize1.Set(FLOORSIZE, 0.5f, FLOORSIZE);
    geom->SetBoxSize(boxSize1[0],boxSize1[1],boxSize1[2]);
    animated->UpdateBoundingInfo();
    pos.Set(0.0f, -6.0f, 0.0f);
	animated->SetPos(pos);




   

	
}
