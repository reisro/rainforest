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
#include "System/Interfaces/IStartup.h"
#include "System/rfConfig.h"
#include <Resources/rfMesh.h>

class RFGE_API rfPhysics: public IStartup
{
	friend class rfGameWorld;

public:

	enum class PhysicsActorType
	{
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
	virtual D3DXMATRIX	UpdateGlobalPosition();
	virtual void		CreateDefaultPlane();
	virtual void        CreateDynamicSphere();
	virtual void		CreatePhysicsActor(LPCSTR actorName, PhysicsActorType type);
	virtual void		UpdateActorPosition();

	static rfPhysics*   GetInstance();
	
	static rfPhysics*   Singleton;

protected:

	// Define declaration types
	RFGE_QUEUE_DECLARE(LPCSTR, PhysicsActorType, rfPhysicsActor)
	RFGE_MAP_DECLARE(LPCSTR, rfMesh*, rfPhysicsActorMesh)

	rfPhysicsActor		scenePhysicsActor;
	rfPhysicsActorMesh  physicsMeshMap;
};

#endif _RFPHYSICS_