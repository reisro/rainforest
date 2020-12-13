#include "Resources/Platform/Directx9IndexBuffer.h"

Directx9IndexBuffer::Directx9IndexBuffer()
{
}

Directx9IndexBuffer::~Directx9IndexBuffer()
{
}

bool Directx9IndexBuffer::Create()
{
    HRESULT hr;

    bool ret;

    // Get the dynamic part of the renderer
    Directx9Renderer* renderer = dynamic_cast<Directx9Renderer*>(rfRenderer::GetInstance());

    // Get the vertex buffer from renderer
    IDirect3DIndexBuffer9* ib = renderer->GetIndexBuffer();

    // Create the vertex buffer passing the values 
    hr = renderer->GetDevice()->CreateIndexBuffer(
        36 * sizeof(WORD),
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &ib,
        0);

    // Get the answer from the operation and return the value
    FAILED(hr) ? ret = false : ret = true;

    return rfIndexBuffer::Create();
}

IDirect3DIndexBuffer9* Directx9IndexBuffer::GetBuffer()
{
    return indexBuffer;
}
