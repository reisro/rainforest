#include "..\Public\VolleyballCourtGame.h"
#include <RainForest.h>

VolleyballCourtGame::VolleyballCourtGame()
{
}

VolleyballCourtGame::~VolleyballCourtGame()
{
}

void VolleyballCourtGame::LoadAssets()
{
    // The Game World class is needed to create actors in the game world
    rfGameWorld gameWorld;

	ImportAssetsToGameWorld(gameWorld);

    CreatePhysicsAssets(gameWorld);
}

void VolleyballCourtGame::Run()
{
}

void VolleyballCourtGame::ImportAssetsToGameWorld(rfGameWorld gameWorld)
{
    // Loading  World Game Actors
    gameMeshes.push_back("Assets\\bench_table.x");
    gameMeshes.push_back("Assets\\long_bench.x");
    gameMeshes.push_back("Assets\\long_bench_left.x");
    gameMeshes.push_back("Assets\\bench_center.x");
    gameMeshes.push_back("Assets\\seats_w.x");
    gameMeshes.push_back("Assets\\standsBase_plates.x");
    gameMeshes.push_back("Assets\\arena_Walls.x");
    gameMeshes.push_back("Assets\\base_Ground.x");
    gameMeshes.push_back("Assets\\court_Inner.x");
    gameMeshes.push_back("Assets\\court_GameOutter.x");
    gameMeshes.push_back("Assets\\Net.x");
    gameMeshes.push_back("Assets\\net_Frame.x");
    gameMeshes.push_back("Assets\\net_Antenna.x");
    gameMeshes.push_back("Assets\\net_Bench.x");
    gameMeshes.push_back("Assets\\net_Pillars.x");
    gameMeshes.push_back("Assets\\net_SafetyPillars.x");
    gameMeshes.push_back("Assets\\hook_Bindings.x");
    gameMeshes.push_back("Assets\\lights.x");
    gameMeshes.push_back("Assets\\chair_stand.x");
    gameMeshes.push_back("Assets\\ball_br2.x");
    
	// Pass to Game World to create the game actors in the world
	gameWorld.LoadMeshGeometry(gameMeshes);
}

void VolleyballCourtGame::CreatePhysicsAssets(rfGameWorld gameWorld)
{
    gameWorld.CreateSphere();
}