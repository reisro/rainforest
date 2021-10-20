
#include "Physics/API/PhysX_SDK2_81.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
PhysX_2_81_::PhysX_2_81_() :
	_PhysicsSDK(NULL), _Scene(NULL), _DefaultGravity(.0f,-9.8f,.0f)
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
PhysX_2_81_::~PhysX_2_81_()
{
	Release();
}

//-----------------------------------------------------------------------------
// Create the Physics SDK
//-----------------------------------------------------------------------------
bool PhysX_2_81_::CreateSDK()
{
	bool created;

	_PhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	_PhysicsSDK ? created = true : created = false;

	return created;
}

//-----------------------------------------------------------------------------
// Create the Scene
//-----------------------------------------------------------------------------
bool PhysX_2_81_::Initialize()
{
	if (!CreateSDK())
		return false;

	SetSDKParameters();
	SetDebugParameters();

	_SceneDesc.gravity = _DefaultGravity;
	_SceneDesc.simType = NX_SIMULATION_SW;
	_Scene = _PhysicsSDK->createScene(_SceneDesc);

	CreateDefaultMaterial();
	CreateDefaultActor();

	if (_Scene) Simulate();

	return true;
}

//-----------------------------------------------------------------------------
// Create the Scene
//-----------------------------------------------------------------------------

void PhysX_2_81_::Release()
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

	NxReal sphereStartHeight = 0.0f;

	NxActorDesc actorPlaneDesc;
	NxActorDesc actorSphereDesc;

	NxBodyDesc bodySDesc;

	planeDesc.normal = NxVec3(0.0f, 1.0f, 0.0f);

	// Plane
	actorPlaneDesc.shapes.pushBack(&planeDesc);

	sphereDesc.radius = 4.0f;
	sphereDesc.localPose.t = NxVec3(.0f, .0f, .0f);
	
	// Sphere
	actorSphereDesc.shapes.pushBack(&sphereDesc);
	actorSphereDesc.body = &bodySDesc;
	actorSphereDesc.density = 10.0f;
	actorSphereDesc.globalPose.t = NxVec3(0.0f, sphereStartHeight, .0f);

	assert(actorSphereDesc.isValid());

	_defaultActor =  _Scene->createActor(actorPlaneDesc);
	_defaultSphere = _Scene->createActor(actorSphereDesc);
}

//-----------------------------------------------------------------------------
// Visualize wireframe actors in physics simulation
//-----------------------------------------------------------------------------

void PhysX_2_81_::DebugWireframeMode()
{
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

void PhysX_2_81_::RenderDefaultActors()
{
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------
void PhysX_2_81_::Simulate()
{
	UpdateTime();

	_Scene->simulate(_DeltaTime);
	_Scene->flushStream();
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

void PhysX_2_81_::UpdateTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*) &_Time);
	_DeltaTime = (NxReal)(_Time - _LastTime) / (NxReal)_Frequency;
	_LastTime = _Time;
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

void PhysX_2_81_::GetPhysicsResults()
{
	// Get results from Scene->simulate(DeltaTime)
	while (!_Scene->fetchResults(NX_RIGID_BODY_FINISHED, false));
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

void PhysX_2_81_::Reset()
{
	Release();
	Initialize();
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

NxActor* PhysX_2_81_::CreateGroundPlane()
{
	// Create a plane with default descriptor
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	planeDesc.normal = NxVec3(0.0f, 0.0f, 0.0f);
	actorDesc.shapes.pushBack(&planeDesc);
	
	return _Scene->createActor(actorDesc);
}

//-----------------------------------------------------------------------------
// Start collision and dynamics for delta time since last frame
//-----------------------------------------------------------------------------

float PhysX_2_81_::GetFPS()
{
	return 1.0f/_DeltaTime;
}