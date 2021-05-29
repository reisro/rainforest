#include "Resources/Platform/Directx9VertexBuffer.h"
#include "Renderer/Platform/Directx9Renderer.h"

Directx9VertexBuffer::Directx9VertexBuffer()
{
    vertexBuffer = 0;

    Create();
}

Directx9VertexBuffer::~Directx9VertexBuffer()
{
}

bool Directx9VertexBuffer::Create()
{
    HRESULT hr;

    bool ret;

    // Get the dynamic part of the renderer
    Directx9Renderer* renderer = dynamic_cast<Directx9Renderer*>(rfRenderer::GetInstance());
    
    // Create the vertex buffer passing the values 
    hr = renderer->GetDevice()->CreateVertexBuffer(
        8 * sizeof(rfVertex::Vertex),
        D3DUSAGE_WRITEONLY,
        rfVertex::Vertex::FVF,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        0);

    // Get the answer from the operation and return the value
    FAILED(hr) ? ret = false : ret = true;

    return rfVertexBuffer::Create();
}

void Directx9VertexBuffer::AccessMemory()
{

}

void Directx9VertexBuffer::Lock()
{
    
}

IDirect3DVertexBuffer9* Directx9VertexBuffer::GetBuffer()
{
    return vertexBuffer;
}
