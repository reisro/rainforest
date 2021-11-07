#include "Game/rfGameWorld.h"
#include <Physics/rfPhysics.h>

#define RFGE_DX9_RENDER_SUPPORT

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

void rfGameWorld::LoadMeshGeometry(std::vector<LPCSTR>& actorNames)
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
		worldMeshes[i]->LoadMeshGeometry(actorNames[i]);
	}

	// Populate and send the stack with game world meshes to be rendered by the renderer
	SendMeshDrawStack();
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------

void rfGameWorld::CreatePhysicsMeshes(std::vector<LPCSTR>& actorPhysicsNames, PhysicsActorType actorType)
{
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

//-----------------------------------------------------------------------------
// Process all related systems tied to the game world
//-----------------------------------------------------------------------------

void rfGameWorld::Build()
{
	// Start physics simulation
	rfPhysics::GetInstance()->Simulate();

	// Render the scene
	rfRenderer::GetInstance()->Render();
}

//-----------------------------------------------------------------------------
// Retrieves the singleton for this class
//-----------------------------------------------------------------------------

rfGameWorld* rfGameWorld::GetInstance()
{
	return Singleton;
}