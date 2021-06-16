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



class rfPhysics
{
public:

	rfPhysics();
	~rfPhysics();
	
	static void	CreateInstance();
	static bool	Initialized();

private:
	

	static rfPhysics* Singleton;
};

#endif _RFPHYSICS_