#include "Game/rfGameWorld.h"
#include <Physics/rfPhysics.h>

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld* rfGameWorld::Singleton = 0;

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld::rfGameWorld()
{
}

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld::rfGameWorld(int entities)
{
}

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld::~rfGameWorld()
{
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------

void rfGameWorld::LoadMeshGeometry(std::vector<LPCSTR>& actorNames, D3DXMATRIX worldLocation)
{
	// Set render device depending on used graphics api
#ifdef RFGE_DX9_RENDER_SUPPORT

	Directx9Renderer* rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

#endif // RFGE_DX9_RENDER_SUPPORT  

	for (size_t i = 0; i < actorNames.size(); i++)
	{
		// Create empty rfMesh with no loaded geometry
		worldMeshes.push_back(new rfMesh(rendererDX9->GetDevice()));

		// for each mesh loads its corresponding geometry
		worldMeshes[i]->LoadMeshGeometry(actorNames[i], .0f,.0f,.0f);
	}

	// Populate and send the stack with game world meshes to be rendered by the renderer
	SendMeshDrawStack();
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------
void rfGameWorld::CreatePhysicsActor(PhysicsActorType actorType)
{
	if (actorType == PhysicsActorType::Ground)
		rfPhysics::GetInstance()->CreateDefaultPlane();
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------

void rfGameWorld::CreatePhysicsMesh(PhysicsActorType actorType)
{
	if (actorType == PhysicsActorType::Sphere) rfPhysics::GetInstance()->CreateDynamicSphere();
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------

bool rfGameWorld::UpdatePhysicsMeshPositioning()
{
	D3DXMATRIX matrix;

	matrix = rfPhysics::GetInstance()->UpdateGlobalPosition();

	Directx9Renderer* rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

	// Create empty rfMesh with no loaded geometry
	worldMeshes.push_back(new rfMesh(rendererDX9->GetDevice()));

	int32_t size = worldMeshes.size() - 1;

	worldMeshes[size]->LoadMeshGeometry("D:\\DirectX\\rainforest\\games\\Assets\\ball_br2.x", matrix._41, matrix._42, matrix._43);

	rendererDX9->meshDrawStack.push({ rfRenderCommand::CommandType::DrawMesh, worldMeshes[size] });

	
}

//-----------------------------------------------------------------------------
// Set the mesh draw stack to send to the renderer
//-----------------------------------------------------------------------------

void rfGameWorld::SendMeshDrawStack()
{
	// Set render device depending on used graphics api
#if defined RFGE_DX9_RENDER_SUPPORT

	Directx9Renderer* rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

	for (size_t i = 0; i < worldMeshes.size(); i++)
		rendererDX9->meshDrawStack.push({ rfRenderCommand::CommandType::DrawMesh, worldMeshes[i] });

#endif // RFGE_DX9_RENDER_SUPPORT
}

void rfGameWorld::SendPhysicsMeshDrawStack()
{
}

//-----------------------------------------------------------------------------
// Process all related systems tied to the game world
//-----------------------------------------------------------------------------

void rfGameWorld::Build()
{
	// Start physics simulation
	rfPhysics::GetInstance()->Simulate();

	// Render the game scene
	rfRenderer::GetInstance()->Render();

	//while (rfApplication::gameLoop)
	//{
		
	//}
}

//-----------------------------------------------------------------------------
// Retrieves the singleton for this class
//-----------------------------------------------------------------------------

rfGameWorld* rfGameWorld::GetInstance()
{
	return Singleton;
}