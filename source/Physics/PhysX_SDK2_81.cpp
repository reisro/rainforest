
#include "Physics/PhysX_SDK2_81.h"

PhysX_2_81_::PhysX_2_81_() :
	_PhysicsSDK(NULL), _Scene(NULL), _DefaultGravity(.0f,-9.8f,.0f)
{
	Init();
}

PhysX_2_81_::~PhysX_2_81_()
{
	if (_Scene)
	{
		while (!_Scene->fetchResults(NX_RIGID_BODY_FINISHED, false));
		_PhysicsSDK->releaseScene(*_Scene);
	}

	if (_PhysicsSDK)
		_PhysicsSDK->release();
}

//-----------------------------------------------------------------------------
// Create the Physics SDK
//-----------------------------------------------------------------------------
bool PhysX_2_81_::CreateSDK()
{
	bool created;

	_PhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	!_PhysicsSDK ? created = true : created = false;

	return created;
}

//-----------------------------------------------------------------------------
// Create the Scene
//-----------------------------------------------------------------------------
bool PhysX_2_81_::Init()
{
	if (!CreateSDK())
		return false;

	_SceneDesc.gravity = _DefaultGravity;
	_SceneDesc.simType = NX_SIMULATION_SW;
	_Scene = _PhysicsSDK->createScene(_SceneDesc);

	return true;
}

//-----------------------------------------------------------------------------
// Set the physics parameters
//-----------------------------------------------------------------------------
void PhysX_2_81_::SetSDKParameters()
{
	_PhysicsSDK->setParameter(NX_SKIN_WIDTH, .01f);
}

//-----------------------------------------------------------------------------
// Set the debug visualization parameters
//-----------------------------------------------------------------------------
void PhysX_2_81_::SetDebugParameters()
{
	_PhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
	_PhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1.0f);
	_PhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1.0f);
}

//-----------------------------------------------------------------------------
// Create the default physical material
//-----------------------------------------------------------------------------
void PhysX_2_81_::CreateDefaultMaterial()
{
	NxMaterial* defaultMaterial = _Scene->getMaterialFromIndex(0);

	defaultMaterial->setRestitution(0.5f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);
}

//-----------------------------------------------------------------------------
// Create the default actor for any physics scene
// which is a plane and a sphere
//-----------------------------------------------------------------------------
void PhysX_2_81_::CreateDefaultActor()
{
	NxPlaneShapeDesc planeDesc;
	NxSphereShapeDesc sphereDesc;

	NxReal sphereStartHeight = 3.5f;

	NxActorDesc actorPDesc;
	NxActorDesc actorSDesc;

	NxBodyDesc bodySDesc;

	sphereDesc.radius = 0.65f;
	sphereDesc.localPose.t = NxVec3(.0f, .0f, .0f);

	// Plane
	actorPDesc.shapes.pushBack(&planeDesc);

	// Sphere
	actorSDesc.shapes.pushBack(&sphereDesc);
	actorSDesc.body = &bodySDesc;
	actorSDesc.density = 10.0f;
	actorSDesc.globalPose.t = NxVec3(3.0f, sphereStartHeight, .0f);

	_Scene->createActor(actorPDesc);
	_Scene->createActor(actorSDesc);
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------
void PhysX_2_81_::Simulate(float DeltaTime)
{
	_Scene->simulate(DeltaTime);
	_Scene->flushStream();
}