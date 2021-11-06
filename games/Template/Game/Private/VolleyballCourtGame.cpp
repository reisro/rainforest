#include "..\Public\VolleyballCourtGame.h"
#include <RainForest.h>

VolleyballCourtGame::VolleyballCourtGame()
{
}

VolleyballCourtGame::~VolleyballCourtGame()
{
}

void VolleyballCourtGame::Setup()
{
	ImportAssetsToGameWorld();
}

void VolleyballCourtGame::Run()
{
}

void VolleyballCourtGame::ImportAssetsToGameWorld()
{
	// The Game World class is needed to create actors in the game world
	rfGameWorld* gameWorld = new rfGameWorld();
	
    // Loading  World Game Actors
    gameMeshes.push_back("D:\\DirectX\\rainforest\\games\\Assets\\ball_br2.x");
	gameMeshes.push_back("D:\\DirectX\\rainforest\\games\\Assets\\arena_Walls.x");

	// Pass to Game World to create the game actors in the world
	gameWorld->LoadMeshGeometry(gameMeshes);
}