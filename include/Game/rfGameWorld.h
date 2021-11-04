//---------------------------------------------------------------------------//
//                                                                           //
// File : rfGameWorld.h                                                      //
//                                                                           //
// Desc : Handles game world actors creation and life cycle management       //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2021.	Rodrigo dos Reis (reiso)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef RF_GAMEWORLD_H_
#define RF_GAMEWORLD_H_

#include "RFGEAPI.h"

class RFGE_API rfGameWorld
{
public:

	rfGameWorld();
	rfGameWorld(int entities);

	~rfGameWorld();

	void LoadActor(LPCSTR actorName);
};

#endif RF_GAMEWORLD_H_