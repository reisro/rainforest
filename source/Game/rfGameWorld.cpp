#include "Game/rfGameWorld.h"
#include <Renderer/rfRenderer.h>
#include <Renderer/Platform/Directx9Renderer.h>

rfGameWorld::rfGameWorld()
{
}

rfGameWorld::rfGameWorld(int entities)
{
}

rfGameWorld::~rfGameWorld()
{
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------

void rfGameWorld::LoadMeshGeometry(std::vector<LPCSTR>& actorNames)
{
	for (size_t i = 0; i < actorNames.size(); i++)
	{
		// Create empty rfMesh with no loaded geometry
		worldMeshes.push_back(new rfMesh());

		// Set render device depending on used graphics api
		#if defined RFGE_DX9_RENDER_SUPPORT

		Directx9Renderer* renderer = dynamic_cast<Directx9Renderer*>(rfRenderer::GetInstance());
		worldMeshes[i]->SetRenderDevice(renderer->GetDevice());

		#endif // RFGE_DX9_RENDER_SUPPORT

		// for each mesh loads its corresponding geometry
		worldMeshes[i]->LoadMeshGeometry(actorNames[i]);
	}
}

//-----------------------------------------------------------------------------
// Set the mesh draw stack to send to the renderer
//-----------------------------------------------------------------------------

void rfGameWorld::SendMeshDrawStack()
{
	// Set render device depending on used graphics api
	//#if defined RFGE_DX9_RENDER_SUPPORT

	Directx9Renderer* renderer = dynamic_cast<Directx9Renderer*>(rfRenderer::GetInstance());

	renderer->meshDrawStack.push({ rfRenderCommand::CommandType::DrawMesh, worldMeshes[0] });

	//#endif // RFGE_DX9_RENDER_SUPPORT
}

//-----------------------------------------------------------------------------
// Process the physics and render system of the game world
//-----------------------------------------------------------------------------

void rfGameWorld::Render()
{
}