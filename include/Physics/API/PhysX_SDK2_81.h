//---------------------------------------------------------------------------//
//                                                                           //
// File : rfPhysics.h														 //
//                                                                           //
// Desc : Provides physics simulation using the NVidia PhysX SDK             //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFPHYSICX_2_81_H
#define _RFPHYSICX_2_81_H

#include "Physics/rfPhysics.h"
#include "NxPhysics.h"

class PhysX_2_81_: public rfPhysics
{
public:
	PhysX_2_81_();
	~PhysX_2_81_();

	float GetFPS() override;

	bool CreateSDK();
	bool Initialize();
	void Release();
	void SetSDKParameters();
	void SetDebugParameters();
	void CreateDefaultMaterial();
	void CreateDefaultActor();
	void Simulate(float DeltaTime);
	void UpdateTime();
	void GetPhysicsResults();
	void Reset();
	NxActor* CreateGroundPlane();

private:

	NxPhysicsSDK* _PhysicsSDK;
	NxReal		  _DeltaTime;
	NxVec3		  _DefaultGravity;
	NxScene*      _Scene;
	NxSceneDesc   _SceneDesc;
	float		  _Seconds;
	__int64       _LastTime;
	__int64		  _Time;
	__int64		  _Frequency;
};

#endif _RFPHYSICX_2_81_H