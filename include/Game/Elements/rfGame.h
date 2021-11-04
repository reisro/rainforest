//---------------------------------------------------------------------------//
//                                                                           //
// File : rfGame.h                                                           //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Mange 2020.	Rodrigo dos Reis (reisro)			                     //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFGAME_H
#define _RFGAME_H

#include "RFGEAPI.h"
#include <string>

class RFGE_API rfGame
{
public:
	rfGame();
	~rfGame();

	void Setup();
	void Start();
	void End();

	struct gameInfo
	{
		std::string Name;
	};

private:

};

#endif // !_RFGAME_H