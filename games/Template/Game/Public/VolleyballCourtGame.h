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

#ifndef _VOLLEYBALLCOURTGAME_H_
#define _VOLLEYBALLCOURTGAME_H_

class VolleyballCourtGame
{
public:
	VolleyballCourtGame();
	~VolleyballCourtGame();

	void RunGame();
	void ImportAssetsToGameWorld();

private:
	std::vector<LPCSTR>    gameMeshes;
};

#endif _VOLLEYBALLCOURTGAME_H_