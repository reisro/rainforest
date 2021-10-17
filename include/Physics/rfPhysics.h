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

#include "RFGEAPI.h"
#include "System/Interfaces/IStartup.h"

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
	
	static rfPhysics* Singleton;
};

#endif _RFPHYSICS_