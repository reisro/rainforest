//---------------------------------------------------------------------------//
//                                                                           //
// File : rfScene.h                                                          //
//                                                                           //
// Desc : Provides functionality of window creation.                         //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#ifndef RFSCENE_H_
#define RFSCENE_H_

#include "RFGEAPI.h"
#include <d3d9.h>
#include <d3dx9.h>

class RFGE_API rfScene
{
public:
	rfScene();
	~rfScene();

	ID3DXMesh* GetSceneMeshAtIndex(int index);
};

#endif RFSCENE_H_