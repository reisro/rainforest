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

	return rfWindowSystem::initialized;
}

//-----------------------------------------------------------------------------
// Init the render system
//-----------------------------------------------------------------------------
bool rfApplication::InitRenderer()
{
	RFGE_LOG("\n  Initiating renderer...");

	rfRenderer::CreateInstance();

	return renderer->Initialize();
}

//-----------------------------------------------------------------------------
// Instructions to render the scene frame
//-----------------------------------------------------------------------------
void rfApplication::RenderFrame()
{
	RFGE_LOG("\n  Rendering frame...");

	// Get the dynamic part of the renderer
	//Directx9Renderer* dx9Renderer = dynamic_cast<Directx9Renderer*>(rfRenderer::GetInstance());
	// Draw the scene
	renderer->Draw();

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