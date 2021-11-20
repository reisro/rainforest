#include "System/rfApplication.h"
#include <Game/rfGameWorld.h>

rfConfig rfConfig::Instance;
static rfWindowSystem* windowSystem;
static rfRenderer* renderer = NULL;
static bool	subSystemsInitiated;

rfApplication::rfApplication()
{
	subSystemsInitiated = true;
}

rfApplication::~rfApplication()
{
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
void rfApplication::Setup(const rfConfig& config)
{
	RFGE_LOG("\n  Rain Forest Game Engine");
	RFGE_LOG("------------------------------\n");

	rfConfig::Instance = config;

	RFGE_LOG("Setup Configuration.\n");
}

//-----------------------------------------------------------------------------
// Init the Application Instance
//-----------------------------------------------------------------------------
bool rfApplication::Init()
{
	RFGE_LOG("\n  Initiating sub systems");
	RFGE_LOG("------------------------------\n");

	InitWindow()   ? RFGE_LOG("\n  Success initiating window system..."):   Abort();
	InitRenderer() ? RFGE_LOG("\n  Success initiating render system..."):   Abort();
	InitPhysics()  ? RFGE_LOG("\n  Success initiating physics system..."):  Abort();

	return !subSystemsInitiated;
}

//-----------------------------------------------------------------------------
// Init the window system
//-----------------------------------------------------------------------------
bool rfApplication::InitWindow()
{
	RFGE_LOG("\n  Initiating window system...");

	rfWindowSystem::CreateInstance();

	return rfWindowSystem::Init();
}

//-----------------------------------------------------------------------------
// Init the render system
//-----------------------------------------------------------------------------
bool rfApplication::InitRenderer()
{
	RFGE_LOG("\n  Initiating renderer...");

	rfRenderer::CreateInstance();
	
	return rfRenderer::Init();
}

//-----------------------------------------------------------------------------
// Instructions to render the scene frame
//-----------------------------------------------------------------------------
bool rfApplication::InitPhysics()
{
	RFGE_LOG("\n  Initiating physics...");

	rfPhysics::CreateInstance();

	return rfPhysics::Init();
}

//-----------------------------------------------------------------------------
// Instructions to render the scene frame
//-----------------------------------------------------------------------------
void rfApplication::Run()
{
	RFGE_LOG("\n  Running application...");

	// Build the game world
	// Initializing the rendering of the game world meshes
	// And simulating the physics properties of the dynamic actors lying in the world

	// Start physics simulation
	rfPhysics::GetInstance()->Simulate();

	// Render the game scene
	rfRenderer::GetInstance()->Render();

	RFGE_LOG("\n  Finalized running application...");
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
void rfApplication::Abort()
{
	subSystemsInitiated = false;
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
void rfApplication::ShutDown()
{
}