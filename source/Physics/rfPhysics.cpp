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

D3DXMATRIX rfPhysics::UpdateGlobalPosition(int physicsMeshID)
{
	return Singleton->UpdateGlobalPosition(physicsMeshID);
}

void rfPhysics::CreateDefaultPlane()
{
	Singleton->CreateDefaultPlane();
}

void rfPhysics::CreateDynamicSphere()
{
	Singleton->CreateDynamicSphere();
}

void rfPhysics::CreateDynamicBox(rfVector3 position)
{
	Singleton->CreateDynamicSphere();
}

void rfPhysics::CreatePhysicsActor(LPCSTR actorName, rfVector3 position, PhysicsActorType type)
{
	Singleton->CreatePhysicsActor(actorName, position, type);
}

void rfPhysics::ApplyForceToPhysicsActor(LPCSTR actorName, rfVector3 force, rfVector3 position, bool torque, rfVector3 angularVelocity, rfVector3 linearVelocity)
{
	Singleton->ApplyForceToPhysicsActor(actorName, force, position, torque, angularVelocity, linearVelocity);
}

void rfPhysics::UpdateActorPosition()
{
}

rfPhysics* rfPhysics::GetInstance()
{
	return Singleton;
}
