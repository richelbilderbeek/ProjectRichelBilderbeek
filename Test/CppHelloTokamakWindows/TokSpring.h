#pragma once

#include "tokamak.h"

//Spring type definition:
typedef enum 
{
	RIGID_TO_RIGID,
	RIGID_TO_ANIM
} eSpringType;

//Fixation information definition:
typedef struct
{
	bool bFixed1, bFixed2;		//indicate, if the spring is fixed
	neV3 ConnDir1, ConnDir2;	//direction vector of the spring relative to the body
	//required only if spring is fixed (bFixed1 or bFixed2):
	float fTangentForceFactor;
	float fTangentDamping;
	float fTorqueFactor;
	float fAngularDamping;
} SFixationInfo;


class CTokSpring: public neRigidBodyControllerCallback
{
protected:
	//Which types of objects are connected with this spring?
	eSpringType m_Type;
	
	//Pointers to the bodies possibly connected:
	neRigidBody * m_Rigid1, * m_Rigid2;
	neAnimatedBody * m_Anim;
	//Position relative to the body's position: Where is the spring connected with the body?
	neV3 m_ConnPos1, m_ConnPos2;

	//Spring parameters:
	float m_Length;			//this is the length at which no force is created
	float m_SpringConst;	//how "strong" the spring is
	float m_DampingFactor;  //used to damp the spring
	
	//used if spring is "fixed":
	SFixationInfo m_Fixation;

	neV3 m_LastForce;
	bool m_bLastForceAssigned;
	float m_LastSpringLength;
    //the controller callback function
	virtual void RigidBodyControllerCallback(neRigidBodyController * controller, float timeStep);

	//Init the spring:
	void Initialize();

	
public:
	CTokSpring(neRigidBody * rigid1, neRigidBody * rigid2);
	CTokSpring(neRigidBody * rigid, neAnimatedBody * anim);
	~CTokSpring(void);
	
	void SetDefaultLength(float length);
	float GetDefaultLength();
	
	void SetSpringConst(float SpringConst);
	float GetSpringConst();
	
	void SetDampingFactor(float DampingFactor);
	float GetDampingFactor();

	void SetConnPos1(neV3 pos);
	neV3 GetConnPos1();
	void SetConnPos2(neV3 pos);
	neV3 GetConnPos2();

	void FixSpring(SFixationInfo fixationInfo);
	SFixationInfo GetFixationInfo();


	eSpringType GetSpringType();
	neRigidBody * GetRigid1();
	neRigidBody * GetRigid2();
	neAnimatedBody * GetAnimated();
	
	float GetCurrentLength();


	
	

};
