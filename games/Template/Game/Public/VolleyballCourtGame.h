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
#include "Game/Elements/rfGame.h"

#ifndef _VOLLEYBALLCOURTGAME_H_
#define _VOLLEYBALLCOURTGAME_H_

class VolleyballCourtGame: public rfGame
{
public:
	VolleyballCourtGame();
	~VolleyballCourtGame();

	void Setup() override;
	void Run() override;
	void ImportAssetsToGameWorld();

private:
	std::vector<LPCSTR>    gameMeshes;
};

#endif _VOLLEYBALLCOURTGAME_H_