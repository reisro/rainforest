#include "Game/rfGameWorld.h"
#include <Physics/rfPhysics.h>

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld rfGameWorld::Singleton = 0;

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfGameWorld::rfGameWorld()
{
	Singleton = *this;
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

	auto rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

#endif // RFGE_DX9_RENDER_SUPPORT  

	for (size_t i = 0; i < actorNames.size(); i++)
	{
		// Create empty rfMesh with no loaded geometry
		worldMeshes.push_back(rfMesh(rendererDX9->GetDevice()));

		// for each mesh loads its corresponding geometry  
		worldMeshes[i].LoadMeshGeometry(actorNames[i], .0f,.0f,.0f);
	}
}

//-----------------------------------------------------------------------------------------
// Once the meshes names are populated it stores all loaded geometry of the game world
//-----------------------------------------------------------------------------------------
void rfGameWorld::LoadPhysicsMeshGeometry(std::vector<LPCSTR>& actorNames, D3DXMATRIX worldLocation)
{
	// Set render device depending on used graphics api
#ifdef RFGE_DX9_RENDER_SUPPORT

	auto rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

#endif // RFGE_DX9_RENDER_SUPPORT  

	for (size_t i = 0; i < actorNames.size(); i++)
	{
		worldPhysicsMeshes.push_back(rfMesh(rendererDX9->GetDevice()));
		worldPhysicsMeshes[i].LoadMeshGeometry(actorNames[i], .0f, .0f, .0f);
	}

	// Populate and send the stack with game world meshes to be rendered by the renderer
	SendMeshDrawStack();
}

//-----------------------------------------------------------------------------
// Set the mesh draw stack to send to the renderer
//-----------------------------------------------------------------------------

void rfGameWorld::SendMeshDrawStack()
{
	// Set render device depending on used graphics api
#if defined RFGE_DX9_RENDER_SUPPORT

	auto rendererDX9 = dynamic_cast<Directx9Renderer*> (rfRenderer::GetInstance());

	for (size_t i = 0; i <= worldMeshes.size()-1; i++)
		rendererDX9->meshes.push_back(worldMeshes[i]);

	for (size_t i = 0; i < worldPhysicsMeshes.size(); i++)
		rendererDX9->physicsMeshes.push_back(worldPhysicsMeshes[i]);

	StoreWorldMeshMap(rendererDX9->sceneRenderMesh);

#endif // RFGE_DX9_RENDER_SUPPORT
}

void rfGameWorld::StoreWorldMeshMap(std::map<int, rfMesh>& sceneMeshes)
{
	int id = 0;

	for (rfMesh mesh : worldPhysicsMeshes)
	{
		sceneMeshes.insert(std::pair<int, rfMesh>{ id, mesh });
		id++;
	}
}

void rfGameWorld::SendPhysicsMeshDrawStack()
{
}

//-----------------------------------------------------------------------------
// Process all related systems tied to the game world
//-----------------------------------------------------------------------------

void rfGameWorld::Build()
{
}

void rfGameWorld::CreateDynamicSphereActor(LPCSTR actorName, rfVector3 position)
{
	rfPhysics::GetInstance()->CreatePhysicsActor(actorName, position, rfVector3::Zero() ,rfPhysics::PhysicsActorType::Sphere);
}

void rfGameWorld::CreateDynamicBoxActor(LPCSTR actorName, rfVector3 position)
{
	rfPhysics::GetInstance()->CreatePhysicsActor(actorName, position, rfVector3::Zero(), rfPhysics::PhysicsActorType::BoxDynamic);
}

void rfGameWorld::CreateStaticBoxActor(LPCSTR actorName, rfVector3 position, rfVector3 size)
{
	rfPhysics::GetInstance()->CreatePhysicsActor(actorName, position, size, rfPhysics::PhysicsActorType::BoxStatic);
}

//-----------------------------------------------------------------------------
// Retrieves the singleton for this class
//-----------------------------------------------------------------------------

rfGameWorld rfGameWorld::GetInstance()
{
	return Singleton;
}