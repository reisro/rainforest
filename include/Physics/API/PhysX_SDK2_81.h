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
#include "Renderer/rfRenderer.h"
#include "NxPhysics.h"
#include <d3dx9.h>

class PhysX_2_81_: public rfPhysics
{
public:
	PhysX_2_81_();
	~PhysX_2_81_();

	void       Simulate() override;
	float      GetFPS() override;
	void       GetPhysicsResults() override;
	D3DXMATRIX UpdateGlobalPosition() override;
	void       CreateDefaultPlane() override;
	void       CreateDynamicSphere() override;
	void	   CreatePhysicsActor(LPCSTR actorName, PhysicsActorType type) override;

	bool       CreateSDK();
	bool       Initialize();
	void       Release();
	void       SetSDKParameters();
	void       SetDebugParameters();
	void       CreateDefaultMaterial();
	void       DebugWireframeMode();
	void       RenderDefaultActors();
	void       UpdateTime();
	void       Reset();

	NxActor*   CreateGroundPlane();

private:

	NxPhysicsSDK* _PhysicsSDK;
	NxReal		  _DeltaTime;
	NxVec3		  _DefaultGravity;
	NxScene*      _Scene;
	NxSceneDesc   _SceneDesc;
	NxActor*      _defaultActor;
	NxActor*      _defaultSphere;
	NxMat34       _World;
	D3DXMATRIX	  _WorldMatrix;
	float		  _Seconds;
	__int64       _LastTime;
	__int64		  _Time;
	__int64		  _Frequency;

	std::vector<LPCSTR> physicsMesh;
};

#endif _RFPHYSICX_2_81_H