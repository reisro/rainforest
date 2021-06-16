#include "Physics/rfPhysics.h"
#include "Physics/PhysX_SDK2_81.h"
#include "System/rfConfig.h"

rfPhysics* rfPhysics::Singleton=0;

rfPhysics::rfPhysics()
{
}

rfPhysics::~rfPhysics()
{
	
}

void rfPhysics::CreateInstance()
{
	if (rfConfig::Instance.physicsAPI == EngineConfig::PhysicsAPI::PhysX_ver2_81)
		Singleton = new PhysX_2_81_();
}

bool rfPhysics::Initialized()
{
	return true;
}