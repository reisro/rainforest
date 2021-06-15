#include "rfRenderer.h"
#include "Renderer/Platform/Directx9Renderer.h"
#include "System/rfConfig.h"

//-----------------------------------------------------------------------------
// Static Member Definitions.
//-----------------------------------------------------------------------------
rfRenderer* rfRenderer::Singleton = 0;

void rfRenderer::CreateInstance()
{
    if (rfConfig::Instance.graphicsAPI == EngineConfig::GraphicsAPI::DirectX9)
        Singleton = new Directx9Renderer();
}

bool rfRenderer::Initialize()
{
    return true;
}

bool rfRenderer::PostInit()
{
    return false;
}

bool rfRenderer::CreateVertexBuffer()
{
    return false;
}

bool rfRenderer::CreateIndexBuffer()
{
    return false;
}

bool rfRenderer::beginFrame()
{
    return true;
}

bool rfRenderer::endFrame()
{
    return true;
}

void rfRenderer::Render()
{
}

void rfRenderer::SendRenderCmdList(const std::vector<rfRenderCommand>& list)
{
}

void rfRenderer::SetRenderWindow(rfWindowSystem* windowSystem)
{
}

void rfRenderer::SetRenderState()
{
    RFGE_LOG("Setting render state...");
}

void rfRenderer::Cleanup()
{
}

void rfRenderer::CameraSetup()
{
}

rfRenderer* rfRenderer::GetInstance()
{
    return Singleton;
}
