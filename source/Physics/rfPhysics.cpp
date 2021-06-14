#include "Physics/rfPhysics.h"

rfPhysics::rfPhysics() :
	_PhysicsSDK(NULL), _DefaultGravity(0, -9.8, 0), _Scene(NULL)
{
}

rfPhysics::~rfPhysics()
{
	_PhysicsSDK = 0;
}

void rfPhysics::CreateInstance()
{
}

bool rfPhysics::Initialized()
{
	return true;
}

bool rfPhysics::CreateSDK()
{
	bool created;

	_PhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	!_PhysicsSDK ? created = true : created = false;

	return created;
}

bool rfPhysics::Init()
{
	if (!CreateSDK())
		return false;

	_SceneDesc.gravity = _DefaultGravity;
	_Scene = _PhysicsSDK->createScene(_SceneDesc);

	return true;
}