#include "StdAfx.h"
#include ".\tokspring.h"

typedef struct
{
	neV3 Velocity, AngularVelocity;
	neV3 Position;
	neV3 ConnPos, ConnDir;  //in world coordinates
	bool bSpringFixed;
} BodyProperties;

 void CTokSpring::RigidBodyControllerCallback(neRigidBodyController * controller, float timeStep)
 {
	//Get a pointer to the rigid body we will controll here:
	neRigidBody * rigid = controller->GetRigidBody();
	//This method will calculate a force at the connection point, a "center force" and a torque:
	neV3 forceAtConnPos,centerforce,torque;
	forceAtConnPos.SetZero();
	torque.SetZero();
	centerforce.SetZero();

	//This method can be called for the first or the second body which are connected by the spring.
	//Their properties will be used often, so we have a struct to store them locally.
	//The advantage then is, that doesn't matter anymore, if we are controlling body1 or body2.
	//"ThisBody" is the body controlled here, "OtherBody" is the other body connected with this spring.
	BodyProperties ThisBody, OtherBody;

	//first get the properties of body1 and body2:
	BodyProperties Body1, Body2;
	Body1.Position = m_Rigid1->GetPos();
	Body1.ConnPos.Set(Body1.Position);
	Body1.ConnPos+= m_Rigid1->GetRotationM3()*m_ConnPos1;
	Body1.Velocity = m_Rigid1->GetVelocity();
	Body1.AngularVelocity = m_Rigid1->GetAngularVelocity();
	Body1.ConnDir = m_Rigid1->GetRotationM3()*m_Fixation.ConnDir1; 
	Body1.bSpringFixed = m_Fixation.bFixed1;

	if (m_Type == RIGID_TO_RIGID)
	{
		Body2.Position = m_Rigid2->GetPos();		
		Body2.ConnPos.Set(Body2.Position);
		Body2.ConnPos += m_Rigid2->GetRotationM3()*m_ConnPos2;
		Body2.Velocity = m_Rigid2->GetVelocity();
		Body2.AngularVelocity = m_Rigid2->GetAngularVelocity();
		Body2.ConnDir = m_Rigid2->GetRotationM3()*m_Fixation.ConnDir2; 
	} else
	if (m_Type == RIGID_TO_ANIM)
	{
		Body2.Position = m_Anim->GetPos();
		Body2.ConnPos = Body2.Position;
		Body2.ConnPos += m_Anim->GetRotationM3()*m_ConnPos2;
		Body2.Velocity.SetZero(); //this might be wrong if the user moves his anim body. 
						//but this case is not yet supported here.
		Body2.AngularVelocity.SetZero();
		Body2.ConnDir = m_Anim->GetRotationM3()*m_Fixation.ConnDir2; 
		
	} 
	Body2.bSpringFixed = m_Fixation.bFixed2;

	//Assign the "ThisBody" and "OtherBody" structures:
	if (rigid == m_Rigid1)
	{
		ThisBody = Body1;
		OtherBody = Body2;
	}
	else
	{
		ThisBody = Body2;
		OtherBody = Body1;
	}

	neV3 dist = OtherBody.ConnPos-ThisBody.ConnPos;
	neV3 dir = dist;dir.Normalize();
	//how long is the spring right now?
	f32 SpringLength = dist.Length();

	//Ready to calculate the force in the direction of the spring ("contraction/expansion force"):
	forceAtConnPos -= (m_Length-SpringLength)*m_SpringConst*dir;

	//Add a damping force
	//only calculate in the direction of the spring if fixed:	
	if ((m_Fixation.bFixed1) || (m_Fixation.bFixed2))
		forceAtConnPos -= m_DampingFactor*(ThisBody.Velocity-OtherBody.Velocity).Dot(dir)*dir;
	else
		forceAtConnPos -= m_DampingFactor*(ThisBody.Velocity-OtherBody.Velocity);

	//Store the spring length:
	m_LastSpringLength = SpringLength;

	//** Handle Fixation **//
	if (ThisBody.bSpringFixed)
	{
		//fixation at this body will cause a torque
	
		torque += ThisBody.ConnDir.Cross(dir)*m_Fixation.fTorqueFactor;
		//damping torque:
		torque -= m_Fixation.fAngularDamping*(ThisBody.AngularVelocity-OtherBody.AngularVelocity);
	
	}


	neV3 dampforcedir;
	if (OtherBody.bSpringFixed)
	{
		 //Fixation of the spring on the other body causes a force:

		neV3 planeNormal = OtherBody.ConnDir.Cross(dir);
		centerforce -= m_Fixation.fTangentForceFactor*planeNormal.Cross(dir);
		//damping force:
	    dampforcedir = centerforce;dampforcedir.Normalize();
		
	}
	if (ThisBody.bSpringFixed)
	{
		 //Fixation of the spring on this body causes also a force:

		neV3 planeNormal = ThisBody.ConnDir.Cross(dir);
		centerforce += m_Fixation.fTangentForceFactor*planeNormal.Cross(dir);
		//damping force:
		dampforcedir = centerforce;dampforcedir.Normalize();
	}
	if (m_Fixation.bFixed1 || m_Fixation.bFixed2)
		centerforce -= m_Fixation.fTangentDamping*(ThisBody.Velocity-OtherBody.Velocity).Dot(dampforcedir)*dampforcedir;



	neV3 pos;
	pos = rigid->GetPos();

	//That's it. Now apply the force:

	///****
	///*
	///* NOTE: THESE LINES ARE NOT YET 100% CORRECT.
	///* But they still produce working springs...
	///*
	///****
	rigid->SetForce(forceAtConnPos+centerforce,ThisBody.ConnPos);
	rigid->SetTorque(torque);
	


};


CTokSpring::CTokSpring(neRigidBody * rigid1, neRigidBody * rigid2)
{
	//Set default values:
	Initialize();
	//Store the pointers to the conntected bodies:
	m_Rigid1 = rigid1;
	m_Rigid2 = rigid2;
	m_Anim = NULL;
	//We have a rigid-rigid spring:
	m_Type =  RIGID_TO_RIGID;
	//add the controller callback function:
	m_Rigid1->AddController(this,0.0f);
	m_Rigid2->AddController(this,0.0f);
}

CTokSpring::CTokSpring(neRigidBody * rigid, neAnimatedBody * anim)
{
	//Set default values:
	Initialize();
	//Store the pointers to the conntected bodies:
	m_Rigid1 = rigid;
	m_Rigid2 = NULL;
	m_Anim= anim;
	//We have a rigid-anim spring:
	m_Type =  RIGID_TO_ANIM;
	//add the controller callback function:
	m_Rigid1->AddController(this,0.0f);
}

CTokSpring::~CTokSpring(void)
{
}

void CTokSpring::Initialize()
{
	//set default values:
	m_Length = 1.0f;
	m_SpringConst = 1.0f;
	m_DampingFactor = 0.0f;
	m_ConnPos1.SetZero();
	m_ConnPos2.SetZero();
	m_Fixation.bFixed1 = false;
	m_Fixation.bFixed2 = false;
	m_bLastForceAssigned = false;
}

void CTokSpring::SetDefaultLength(float length)
{
	m_Length = length;
}
float CTokSpring::GetDefaultLength()
{
	return m_Length;
}


void CTokSpring::SetSpringConst(float SpringConst)
{
	m_SpringConst = SpringConst;
}
float CTokSpring::GetSpringConst()
{
	return m_SpringConst;
}
eSpringType CTokSpring::GetSpringType()
{
	return m_Type;
}
neRigidBody * CTokSpring::GetRigid1()
{
	return m_Rigid1;
}
neRigidBody * CTokSpring::GetRigid2()
{
	return m_Rigid2;
}
neAnimatedBody * CTokSpring::GetAnimated()
{
	return m_Anim;
}
float CTokSpring::GetCurrentLength()
{
	return m_LastSpringLength;
}

void CTokSpring::SetDampingFactor(float DampingFactor)
{
	m_DampingFactor = DampingFactor;
}
float CTokSpring::GetDampingFactor()
{
	return m_DampingFactor;
}
void CTokSpring::SetConnPos1(neV3 pos)
{
	m_ConnPos1.Set(pos);
}

neV3 CTokSpring::GetConnPos1()
{
	return m_ConnPos1;
}

void CTokSpring::FixSpring(SFixationInfo fixInfo)
{
	m_Fixation = fixInfo;
	if (fixInfo.bFixed1)
	{
		m_Fixation.ConnDir1.Normalize();
	}
	if (fixInfo.bFixed2)
	{
		m_Fixation.ConnDir2.Normalize();
	}
}

SFixationInfo CTokSpring::GetFixationInfo()
{
	return m_Fixation;
}

void CTokSpring::SetConnPos2(neV3 pos)
{
	m_ConnPos2.Set(pos);
}
neV3 CTokSpring::GetConnPos2()
{
	return m_ConnPos2;
}

