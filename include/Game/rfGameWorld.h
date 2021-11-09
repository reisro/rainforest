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
#include <Resources/rfMesh.h>
#include <Renderer/rfRenderer.h>
#include <Renderer/Platform/Directx9Renderer.h>
#include <System/rfConfig.h>

class RFGE_API rfGameWorld
{
public:

	enum class PhysicsActorType
	{
		Ground,
		Box,
		Sphere,
		Capsule
	};

	rfGameWorld();
	rfGameWorld(int entities);

	~rfGameWorld();

	void LoadMeshGeometry(std::vector<LPCSTR>& actorNames, D3DXMATRIX worldLocation = rfMatrix::Identity());
	void CreatePhysicsActor(PhysicsActorType actorType);
	void CreatePhysicsMesh(std::vector<LPCSTR>& actorPhysicsName, PhysicsActorType actorType);
	void UpdatePhysicsMeshPositioning(std::vector<LPCSTR>& actorPhysics);
	void SendMeshDrawStack();
	void SendPhysicsMeshDrawStack();
	void Build();

	static rfGameWorld* GetInstance();

protected:

	static rfGameWorld* Singleton;

private:

	std::vector<rfMesh*> worldMeshes;

	rfRenderer* renderer;
};

#endif RF_GAMEWORLD_H_