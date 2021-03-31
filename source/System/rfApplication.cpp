#include "System/rfApplication.h"

static rfConfig engineConfig;
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

	engineConfig = config;

	RFGE_LOG("Setup Configuration.\n");
}

//-----------------------------------------------------------------------------
// Init the Application Instance
//-----------------------------------------------------------------------------
bool rfApplication::Init()
{
	RFGE_LOG("\n  Initiating sub systems");
	RFGE_LOG("------------------------------\n");

	InitWindow()? RFGE_LOG("\n  Initiated window system..."): Stop();
	InitRenderer()? RFGE_LOG("\n  Initiated render system...") : Stop();

	return !subSystemsInitiated;
}

//-----------------------------------------------------------------------------
// Init the window system
//-----------------------------------------------------------------------------
bool rfApplication::InitWindow()
{
	RFGE_LOG("\n  Initiating window system...");

	rfWindowSystem::CreateInstance();

	return rfWindowSystem::Initialized();
}

//-----------------------------------------------------------------------------
// Init the render system
//-----------------------------------------------------------------------------
bool rfApplication::InitRenderer()
{
	RFGE_LOG("\n  Initiating renderer...");

	rfRenderer::CreateInstance();

	return rfRenderer::GetInstance()->Initialize();
}

//-----------------------------------------------------------------------------
// Instructions to render the scene frame
//-----------------------------------------------------------------------------
void rfApplication::Run()
{
	RFGE_LOG("\n  Rendering frame...");

	// Draw the scene
	rfRenderer::GetInstance()->Render();

	RFGE_LOG("\n  Finalized rendering frame...");
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
void rfApplication::Stop()
{
	subSystemsInitiated = false;
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
void rfApplication::ShutDown()
{
}

rfConfig& rfApplication::GetEngineConfig()
{
	return engineConfig;
}