#include "Physics/rfPhysics.h"
#include "Physics/API/PhysX_SDK2_81.h"
#include "System/rfConfig.h"

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

rfPhysics::~rfPhysics()
{
}

bool rfPhysics::Initialized()
{
	return Singleton->Initialize();
}

bool rfPhysics::Initialize()
{
	return true;
}