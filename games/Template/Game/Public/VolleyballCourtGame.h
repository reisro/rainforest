//---------------------------------------------------------------------------//
//                                                                           //
// File : VolleyballCourtGame.h                                              //
//                                                                           //
// Desc : Game entry point									                 //
//                                                                           //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest game engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#pragma once
#include <wtypes.h>
#include <vector>
#include "Math/rfVector3.h"
#include "Game/Elements/rfGame.h"
#include "RainForest.h"

#ifndef _VOLLEYBALLCOURTGAME_H_
#define _VOLLEYBALLCOURTGAME_H_

class VolleyballCourtGame: public rfGame
{
public:
	VolleyballCourtGame();
	~VolleyballCourtGame();

	void LoadAssets() override;
	void Run() override;
	void ImportAssetsToGameWorld(rfGameWorld gameWorld);
	void CreatePhysicsAssets(rfGameWorld gameWorld);

private:
	std::vector<LPCSTR>    gameMeshes;
	std::vector<LPCSTR>    gamePhysicsMeshes;
};

#endif _VOLLEYBALLCOURTGAME_H_