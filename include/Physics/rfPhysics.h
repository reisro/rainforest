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

#ifndef _RFPHYSICS_
#define _RFPHYSICS_

#include "NxPhysics.h"

class rfPhysics
{
public:

	rfPhysics();
	~rfPhysics();
	
	static void	CreateInstance();
	static bool	Initialized();

	bool CreateSDK();
	bool Init();

private:
	NxPhysicsSDK* _PhysicsSDK;
	NxVec3		  _DefaultGravity;
	NxScene*      _Scene;
	NxSceneDesc   _SceneDesc;

	static rfPhysics* Singleton;
};

#endif _RFPHYSICS_