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
#include <Resources/rfMesh.h>

class RFGE_API rfPhysics: public IStartup
{
public:

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
	virtual D3DXMATRIX	CreatePhysicsActor();

	static rfPhysics* GetInstance();
	
	static rfPhysics* Singleton;

protected:

	// Define declaration types
	RFGE_QUEUE_DECLARE(LPCSTR, bool, rfPhysicsActor)

	rfPhysicsActor		scenePhysicsActor;
};

#endif _RFPHYSICS_