#include "StdAfx.h"
#include "toksim.h"




#pragma comment(lib, "tokamak.lib")


//increase this value to get nicer Spheres and Cylinders (needs more rendering time):
#define SphereSlices 8 


CTokSim::CTokSim(void)
{
	//Init the member variables:
	m_Sim = NULL;
	m_SpringCount = 0;
	m_RigidCount = 0;
	m_AnimatedCount = 0;
	for (int i = 0;i<MAX_RIGID_COUNT;i++)
		m_Rigid[i] = NULL;
	for (int i = 0;i<MAX_ANIMATED_COUNT;i++)
		m_Animated[i] = NULL;

}

CTokSim::~CTokSim(void)
{
	//Clean up:
	if (m_Sim)
    {
        neSimulator::DestroySimulator(m_Sim); //also cleans all bodies etc.
        m_Sim = NULL;
    }
}

void CTokSim::Display(void)
{

	//*****
	//
	// This function displays all tokamak bodies, the terrain mesh and the springs
	// (if created via TokSim::CreateSpring).
	// The results don't look "game-like" but can be used to test
	// the physics engine (or your simulation implementation!).
	//
	//*****

	static GLfloat MatAmbMesh[] = {0.3f,0.5f,0.3f,1.0f};
	static GLfloat MatAmbAnim[] = {0.8f,0.5f,0.5f,1.0f};
	static GLfloat MatAmbRigid[] = {0.5f,0.5f,0.8f,1.0f};
	static GLfloat MatSpec[] = {0.0,0.0,0.0,0.0};
	static GLfloat MatShininess[] = {0.0};

	//Set general material values:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	//*********************
	//** 1.) Draw the mesh:

	glPushMatrix();

	// * a) "wireframe" without lighting
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , MatAmbMesh);


	if (m_NumVertices>0)
	{
		glDrawElements(	GL_TRIANGLES, //mode
				m_NumIndices,  //count, ie. how many indices
				GL_UNSIGNED_INT, //type of the index array
				m_IndexData);
	}

	// * a) solid with lighting (note: there are no normals in this version,
	//      so every polygon has the same color)
	glEnable(GL_LIGHTING);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (m_NumVertices>0)
	{
		glDrawElements(	GL_TRIANGLES, //mode
				m_NumIndices,  //count, ie. how many indices
				GL_UNSIGNED_INT, //type of the index array
				m_IndexData);
	}


	//*********************
	//** 2.) Draw the rigid bodys:


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , MatAmbRigid);


	for (int i = 0; i < m_MaxRigidCount; i++)
	{
		if (m_Rigid[i] == NULL) continue;
		
		glPushMatrix();

		ApplyTransform(m_Rigid[i]->GetTransform());

		m_Rigid[i]->BeginIterateGeometry();
		for  (int geomCount=0;geomCount < m_Rigid[i]->GetGeometryCount();geomCount++)
		{
			neGeometry * geom = m_Rigid[i]->GetNextGeometry();
			RenderGeometry(geom);
			
		}
		glPopMatrix();

	
	}  


	//*********************
	//** 3.) Draw the animated bodies:

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , MatAmbAnim);

	for (int i = 0; i < m_MaxAnimatedCount; i++)
	{
		if (m_Animated[i] == NULL) continue;
	
		glPushMatrix();

		ApplyTransform(m_Animated[i]->GetTransform());

		m_Animated[i]->BeginIterateGeometry();
		for  (int geomCount=0;geomCount < m_Animated[i]->GetGeometryCount();geomCount++)
		{
			neGeometry * geom = m_Animated[i]->GetNextGeometry();
			RenderGeometry(geom);
		}
		glPopMatrix();
	}  

	//*********************
	//** 4.) Draw the springs:
	for (int i = 0; i < m_SpringCount; i++)
	{
		if (m_Spring[i] == NULL) continue;

		RenderSpring(m_Spring[i]);
		
	}  

	
	glPopMatrix();
}

void CTokSim::Init(int MaxRigidCount, int MaxAnimatedCount, neV3 gravity)
{

	//*****
	//Initialize the physics simulation.

	m_MaxAnimatedCount = MaxAnimatedCount;
	m_MaxRigidCount = MaxRigidCount;


	neSimulatorSizeInfo sizeInfo;	


	sizeInfo.rigidBodiesCount = m_MaxRigidCount;
	sizeInfo.animatedBodiesCount = m_MaxAnimatedCount;
	s32 totalBody = sizeInfo.rigidBodiesCount + sizeInfo.animatedBodiesCount;
	sizeInfo.geometriesCount = totalBody;
	//see sdk for this formula:
	sizeInfo.overlappedPairsCount = totalBody * (totalBody - 1) / 2;
	sizeInfo.rigidParticleCount = 0;

	//all information gathered. So create the simulator:
	m_Sim = neSimulator::CreateSimulator(sizeInfo, NULL, &gravity);

}

bool CTokSim::CalculateNextFrame(float dtime)
{
	m_Sim->Advance(dtime);

	return true;
}

void CTokSim::RenderGeometry(neGeometry * geom)
{
	//Renders boxes, spheres, or "cylinders" (which are capsules):
	neV3 boxSize;
	float SphereDiameter;
	float CylDiameter, CylHeight;
	if (geom->GetBoxSize(boxSize))
	{
		RenderBox(geom->GetTransform(),boxSize);
	}
	if (geom->GetSphereDiameter(SphereDiameter))
	{
		RenderSphere(geom->GetTransform(),SphereDiameter);
	}
	if (geom->GetCylinder(CylDiameter,CylHeight))
	{
		RenderCylinder(geom->GetTransform(),CylDiameter,CylHeight);
	}
}


void CTokSim::ApplyTransform(neT3 TransformMatrix)
{
	//Apply a tokamak transformation matrix to opengl:
	neT3 t = TransformMatrix;
	GLfloat matrix[] = { t.rot[0][0], t.rot[0][1], t.rot[0][2], 0.0f, 
                    t.rot[1][0], t.rot[1][1], t.rot[1][2], 0.0f, 
                    t.rot[2][0], t.rot[2][1], t.rot[2][2], 0.0f, 
                    t.pos[0],t.pos[1], t.pos[2], 1.0f };
	glMultMatrixf((GLfloat*)&matrix);
}


void CTokSim::RenderSphere(neT3 TransformMatrix, float Diameter)
{
	//Renders a sphere. See the SphereSlices definition on top of this file.
	glPushMatrix();
	ApplyTransform(TransformMatrix);

	glutSolidSphere(Diameter/2.0f,SphereSlices,SphereSlices);
	glPopMatrix();
}

void CTokSim::RenderCylinder(neT3 TransformMatrix, float Diameter, float Height)
{
	//Tokamak cylinders are not really cylinders.
	//They have half a sphere on top and on there bottom.
	//As the half of the sphere disappears inside (normally...), we render
	//just two normal spheres.

	glPushMatrix();
	ApplyTransform(TransformMatrix);
	
	//A gluCylinder "lies", a Tokamak Cylinder "stands", so rotated:
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,-Height/2.0f);
	gluCylinder(gluNewQuadric(),Diameter/2.0f,Diameter/2.0f,Height,SphereSlices,SphereSlices);
	glutSolidSphere(Diameter/2.0f,SphereSlices,SphereSlices);

	glTranslatef(0.0f,0.0f,+Height);
	glutSolidSphere(Diameter/2.0f,SphereSlices,SphereSlices);
	
	glPopMatrix();
}


void CTokSim::RenderBox(neT3 TransformMatrix, neV3 Size)
{
	//Render a simple solid box:
	glPushMatrix();
	ApplyTransform(TransformMatrix);
	
	glScalef(Size[0],Size[1],Size[2]);
	glutSolidCube(1.0f);
	glPopMatrix();
}


void CTokSim::RenderSpring(CTokSpring * spring)
{
	//Render a spring as a line connecting the two bodies.
	//The color is dependent from the spring's length.
	neV3 ConnPos1,ConnPos2;
	
	ConnPos1 = spring->GetRigid1()->GetPos();
	if (spring->GetSpringType() == RIGID_TO_RIGID)
		ConnPos2 = spring->GetRigid2()->GetPos();
	else
		ConnPos2 = spring->GetAnimated()->GetPos();

	ConnPos1+= spring->GetRigid1()->GetRotationM3()*spring->GetConnPos1();
	if (spring->GetSpringType() == RIGID_TO_RIGID)
        ConnPos2+= spring->GetRigid2()->GetRotationM3()*spring->GetConnPos2();
	else
		ConnPos2+= spring->GetAnimated()->GetRotationM3()*spring->GetConnPos2();

	//Set the color of the spring according to its length:
	float r,g,b;
	r = (spring->GetCurrentLength()/spring->GetDefaultLength()-1);
	g = 0.0f;
	b = 1.0f-r;
	if (r<0.0f) r = 0.0f; if (r>1.0f) r = 1.0f;
	if (b<0.0f) b = 0.0f; if (b>1.0f) b = 1.0f;
	
	
	glDisable(GL_LIGHTING);
	glColor3f(r,g,b);

	glBegin(GL_LINE_STRIP);

	glVertex3f(ConnPos1[0],ConnPos1[1],ConnPos1[2]);
	glVertex3f(ConnPos2[0],ConnPos2[1],ConnPos2[2]);
	
	glEnd();

	//Render the "fixation vector(s)", if spring is fixed:
	SFixationInfo fixation = spring->GetFixationInfo();
	neV3 Fix1Point;
	if (fixation.bFixed1)
	{
		Fix1Point = ConnPos1 + spring->GetRigid1()->GetRotationM3()*fixation.ConnDir1*spring->GetDefaultLength()/5.0f;

		glColor3f(0.8f,0.8f,0.0f);

		glBegin(GL_LINE_STRIP);

		glVertex3f(ConnPos1[0],ConnPos1[1],ConnPos1[2]);
		glVertex3f(Fix1Point[0],Fix1Point[1],Fix1Point[2]);

		glEnd();
	}

	neV3 Fix2Point;
	if (fixation.bFixed2)
	{
		
		Fix2Point = ConnPos2 ;
		if (spring->GetSpringType() == RIGID_TO_RIGID)
			Fix2Point += spring->GetRigid2()->GetRotationM3()*fixation.ConnDir2*spring->GetDefaultLength()/5.0f;
		else
			Fix2Point += spring->GetAnimated()->GetRotationM3()*fixation.ConnDir2*spring->GetDefaultLength()/5.0f;

		glColor3f(0.8f,0.8f,0.0f);

		glBegin(GL_LINE_STRIP);

		glVertex3f(ConnPos2[0],ConnPos2[1],ConnPos2[2]);
		glVertex3f(Fix2Point[0],Fix2Point[1],Fix2Point[2]);

		glEnd();
	}






	
}


void CTokSim::SetTerrainMesh(neTriangleMesh* Mesh)
{
	//1.) Tell Tokamak about the mesh:
	m_Sim->SetTerrainMesh(Mesh);


	//2.) Store the Mesh as Vertex Array
	glEnableClientState(GL_VERTEX_ARRAY);
	m_NumVertices = Mesh->vertexCount;
	m_NumIndices = Mesh->triangleCount*3;
	m_VertexData = new GLfloat[m_NumVertices*3]; //3 components per vector
	m_IndexData = new GLuint[m_NumIndices];		
	
	for (int i=0;i<m_NumVertices;i++)
	{
		for (int j=0;j<3;j++)
			m_VertexData[i*3+j] = Mesh->vertices[i][j];
		
	}
	for (int i=0;i<Mesh->triangleCount;i++)
	{
		for (int j=0;j<3;j++)
			m_IndexData[i*3+j] = Mesh->triangles[i].indices[j];
	}
	

	glVertexPointer(	3,   //3 components per vertex (x,y,z)
						GL_FLOAT,
						sizeof(GLfloat)*3,
						m_VertexData);


}

CTokSpring * CTokSim::CreateSpring(neRigidBody * rigid1, neRigidBody * rigid2)
{
	if (m_SpringCount >= MAX_SPRING_COUNT)
		return NULL;


	m_Spring[m_SpringCount++] = new CTokSpring(rigid1,rigid2);

	return m_Spring[m_SpringCount-1];

}

CTokSpring * CTokSim::CreateSpring(neRigidBody * rigid, neAnimatedBody * anim)
{
	if (m_SpringCount >= MAX_SPRING_COUNT)
		return NULL;

	

	m_Spring[m_SpringCount++] = new CTokSpring(rigid,anim);

	return m_Spring[m_SpringCount-1];
}

neRigidBody * CTokSim::CreateRigidBody()
{
	if (m_RigidCount>= MAX_RIGID_COUNT)
		return NULL;
    
	neRigidBody * rigid = m_Sim->CreateRigidBody();
	m_Rigid[m_RigidCount++] = rigid;
	return rigid;
}
	
neAnimatedBody * CTokSim::CreateAnimatedBody()
{
	if (m_AnimatedCount>= MAX_ANIMATED_COUNT)
		return NULL;
    
	neAnimatedBody * animated = m_Sim->CreateAnimatedBody();
	m_Animated[m_AnimatedCount++] = animated;
	return animated;
}
neSimulator * CTokSim::GetSimulator()
{
	return m_Sim;
}