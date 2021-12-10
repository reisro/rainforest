
#include "Physics/API/PhysX_SDK2_81.h"
#include <Renderer/Platform/Directx9Renderer.h>

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
PhysX_2_81_::PhysX_2_81_() :
	_PhysicsSDK(NULL), _Scene(NULL), _DefaultGravity(.0f,-160.0f,.0f)
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

	CreateDefaultPlane();

	CreateDefaultMaterial();
	
	UpdateTime();

	// Get processor freq
	QueryPerformanceFrequency((LARGE_INTEGER*) &_Frequency);

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
	_PhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	_PhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	_PhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
}

//-----------------------------------------------------------------------------
// Create the default physical material
//-----------------------------------------------------------------------------
void PhysX_2_81_::CreateDefaultMaterial()
{
	NxMaterial* defaultMaterial = _Scene->getMaterialFromIndex(0);

	defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.7);
	defaultMaterial->setDynamicFriction(0.5);
}

//-----------------------------------------------------------------------------
// Create the default actor for any physics scene
//-----------------------------------------------------------------------------
void PhysX_2_81_::CreateDynamicSphere()
{
	NxReal sphereStartHeight = 200.0f;

	NxSphereShapeDesc sphereDesc;
	NxActorDesc actorSphereDesc;
	NxBodyDesc bodySDesc;

	//sphereDesc.radius = 2.6000001430511475f;
	sphereDesc.radius = 13.0f;
	sphereDesc.group = 2;
	sphereDesc.localPose.t = NxVec3(160.4639739990234375f, 10.6821098327636719f, 0.0000140282072607f);
	
	// Sphere
	actorSphereDesc.shapes.pushBack(&sphereDesc);
	actorSphereDesc.body = &bodySDesc;
	actorSphereDesc.density = 0.1;
	actorSphereDesc.globalPose.t = NxVec3(0.0f, sphereStartHeight, 0.0f);

	assert(actorSphereDesc.isValid());

	// Store physics mesh actor for update later
	physicsDynamicActors.push_back(_Scene->createActor(actorSphereDesc));
}

void PhysX_2_81_::CreatePhysicsActor(LPCSTR actorName, PhysicsActorType type)
{
	if (type == PhysicsActorType::Sphere)
	{
		CreateDynamicSphere();

		physicsMeshMap.insert(std::pair<LPCSTR, NxActor*>(actorName, _defaultSphere));
	}
}

void PhysX_2_81_::ApplyForceToPhysicsActor(LPCSTR actorName)
{
	std::map <LPCSTR, NxActor*>::iterator it;

	it = physicsMeshMap.find(actorName);
	{
		NxVec3 Force2(0.0f, 800000.0f, 0000.0f);
		physicsDynamicActors[0]->addForceAtPos(Force2, NxVec3(0.0f, 0.0f, 0.0f), NX_FORCE, true);
		physicsDynamicActors[0]->setAngularVelocity(NxVec3(0.0f, 0.0f, 200.0f));
		physicsDynamicActors[0]->setLinearVelocity(NxVec3(-20.0f, 100.0f, 0.0f));
	}
}

void PhysX_2_81_::UpdateActorPosition()
{

}

//-----------------------------------------------------------------------------
// Create the default plane for any physics scene
//-----------------------------------------------------------------------------
void PhysX_2_81_::CreateDefaultPlane()
{
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorPlaneDesc;

	//planeDesc.localPose.t = NxVec3(0.0f, 5.0f, 0.0f);
	//planeDesc.normal = NxVec3(0.0f, 1.0f, 0.0f);

	// Plane
	actorPlaneDesc.shapes.pushBack(&planeDesc);

	actorPlaneDesc.globalPose.t = NxVec3(0.0f, 30.0f, 0.0f);

	assert(actorPlaneDesc.isValid());

	_defaultActor = _Scene->createActor(actorPlaneDesc);
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

//--------------------------------------------------------------------------------------
// Return the updated matrix for physics mesh under simulation by the physics engine
//--------------------------------------------------------------------------------------
D3DXMATRIX PhysX_2_81_::UpdateGlobalPosition(int physicsMeshID)
{
	NxMat34 world = physicsDynamicActors[physicsMeshID]->getGlobalPose();
	world.getColumnMajor44((float*)&_WorldMatrix);

	return _WorldMatrix;
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
	planeDesc.normal = NxVec3(0.0f, 3.0f, 0.0f);
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