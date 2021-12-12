//---------------------------------------------------------------------------//
//                                                                           //
// File : rfPhysics.h														 //
//                                                                           //
// Desc : Handles physics simulation using the NVidia PhysX SDK             //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFPHYSICS_
#define _RFPHYSICS_

#include "RFGEAPI.h"
#include "Math/rfVector3.h"
#include "System/Interfaces/IStartup.h"
#include "System/rfConfig.h"
#include <Resources/rfMesh.h>

class NxActor;

class RFGE_API rfPhysics: public IStartup
{
	friend class rfGameWorld;

public:

	enum class PhysicsActorType
	{
		Default,
		Ground,
		Box,
		Sphere,
		Capsule
	};

	rfPhysics();
	~rfPhysics();

	static void			CreateInstance();
	static bool			Init();

	// interface
	bool				Initialized();

	virtual bool		Initialize();
	virtual void		Simulate();
	virtual float		GetFPS();
	virtual void		GetPhysicsResults();
	virtual D3DXMATRIX	UpdateGlobalPosition(int physicsMeshID);
	virtual void		CreateDefaultPlane();
	virtual void        CreateDynamicSphere();
	virtual void		CreateDynamicBox(rfVector3 position);
	virtual void		CreatePhysicsActor(LPCSTR actorName, rfVector3 position, PhysicsActorType type);
	virtual void		ApplyForceToPhysicsActor(LPCSTR actorName, rfVector3 force, rfVector3 position, bool torque, rfVector3 angularVelocity, rfVector3 linearVelocity);
	virtual void		UpdateActorPosition();

	static rfPhysics*   GetInstance();
	
	static rfPhysics*   Singleton;

protected:

	// Define declaration types
	RFGE_QUEUE_DECLARE(LPCSTR, PhysicsActorType, rfPhysicsActor)
	RFGE_MAP_DECLARE(LPCSTR, NxActor*, rfPhysicsActorMesh)

	rfPhysicsActor		scenePhysicsActor;
	rfPhysicsActorMesh  physicsMeshMap;
};

#endif _RFPHYSICS_