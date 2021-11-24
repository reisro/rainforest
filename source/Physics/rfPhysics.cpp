#include "Physics/rfPhysics.h"
#include "Physics/API/PhysX_SDK2_81.h"
#include "System/rfConfig.h"
#include <d3dx9.h>

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------

rfPhysics* rfPhysics::Singleton=0;

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------
void rfPhysics::CreateInstance()
{
	if (rfConfig::Instance.physicsAPI == EngineConfig::PhysicsAPI::PhysX_ver2_81)
		Singleton = new PhysX_2_81_();
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------
bool rfPhysics::Init()
{
	return Singleton ? Singleton->Initialized() : 0;
}

//-----------------------------------------------------------------------------
// Instance Member Definitions.
//-----------------------------------------------------------------------------

rfPhysics::rfPhysics()
{
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------

rfPhysics::~rfPhysics()
{
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------

bool rfPhysics::Initialized()
{
	return Singleton->Initialize();
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------

bool rfPhysics::Initialize()
{
	return true;
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------

void rfPhysics::Simulate()
{
	Singleton->Simulate();
}

//-----------------------------------------------------------------------------
// Create Instance based on engine configuration
//-----------------------------------------------------------------------------

float rfPhysics::GetFPS()
{
	return Singleton->GetFPS();
}

void rfPhysics::GetPhysicsResults()
{
	Singleton->GetPhysicsResults();
}

D3DXMATRIX rfPhysics::UpdateGlobalPosition()
{
	return Singleton->UpdateGlobalPosition();
}

void rfPhysics::CreateDefaultPlane()
{
	Singleton->CreateDefaultPlane();
}

void rfPhysics::CreateDynamicSphere()
{
	Singleton->CreateDynamicSphere();
}

void rfPhysics::CreatePhysicsActor(LPCSTR actorName, PhysicsActorType type)
{
	Singleton->CreatePhysicsActor(actorName, type);
}

void rfPhysics::UpdateActorPosition()
{
}

rfPhysics* rfPhysics::GetInstance()
{
	return Singleton;
}
