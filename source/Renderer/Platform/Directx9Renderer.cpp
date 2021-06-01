
//---------------------------------------------------------------------------//
//                                                                           //
// File : Directx9Renderer.h                                                 //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#include "Renderer/Platform/Directx9Renderer.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
Directx9Renderer::Directx9Renderer():
    d3d9(0),
    windowed(true),
    device(0),
    deviceType(D3DDEVTYPE_HAL)
{
    msg = {};
    renderCmdStack = {};
    Singleton = this;
    renderCamera = new Camera();

    vertexBuffer = 0;
    indexBuffer = 0;

    SetRenderWindow(rfWindowSystem::GetInstance());
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
Directx9Renderer::~Directx9Renderer()
{
    Cleanup();
}

//-----------------------------------------------------------------------------
// Initialization of device and capabilities
//-----------------------------------------------------------------------------
bool Directx9Renderer::Initialize()
{
    HRESULT hr = 0;

    // Create the d3d object
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    // Check if the device creation fails
    if (!d3d9)
    {
        ::MessageBox(0, L"Direct3DCreate9()-FAILED", 0, 0);
        return false;
    }

    d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &dx9deviceCaps.caps);

    int vp = 0;

    // Check if hardware is capable
    if (dx9deviceCaps.caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    
    // Fill out device capabilities
    dx9deviceCaps.presentParameters.BackBufferWidth = width;
    dx9deviceCaps.presentParameters.BackBufferHeight = height;
    dx9deviceCaps.presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    dx9deviceCaps.presentParameters.BackBufferCount = 1;
    dx9deviceCaps.presentParameters.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    dx9deviceCaps.presentParameters.MultiSampleQuality = 0;
    dx9deviceCaps.presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    dx9deviceCaps.presentParameters.hDeviceWindow = renderWindow;
    dx9deviceCaps.presentParameters.Windowed = windowed;
    dx9deviceCaps.presentParameters.EnableAutoDepthStencil = true;
    dx9deviceCaps.presentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
    dx9deviceCaps.presentParameters.Flags = 0;
    dx9deviceCaps.presentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    dx9deviceCaps.presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Create the physical device
    hr = d3d9->CreateDevice(
        D3DADAPTER_DEFAULT,
        deviceType,
        renderWindow,
        vp,
        &dx9deviceCaps.presentParameters,
        &device);

    // Handle if device is not initialized
    if (FAILED(hr))
    {
        d3d9->Release();
        ::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
        return false;
    }

    d3d9->Release();

    // Finish initialization by calling post init commands
    return Directx9Renderer::PostInit();
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
bool Directx9Renderer::PostInit()
{
    vertexBuffer = new Directx9VertexBuffer();
    
    //LockVertexBufferMemory();

    // Create the default cube for the render scene
    CreateDefaultPrimitive();

    // Once Primitive has been setup unlock the buffer
    vertexBuffer->GetBuffer()->Unlock();

    indexBuffer = new Directx9IndexBuffer();

    // Assign the indices for the default cube
    LockIndexBufferMemory();
   
    // Once Primitive has been setup unlock the buffer
    indexBuffer->GetBuffer()->Unlock();

    // Default device initialization render
    //rfVertex::VertexColor vertexColor;
    //D3DMATERIAL9 defaultMaterial;
    //LPCWSTR filename = L"crate.jpg";

    // Set the index primitive default values
    IndexedPrimitiveSize defaultIndexedPrimitive;
    defaultIndexedPrimitive.numberVertices = 24;
    defaultIndexedPrimitive.totalVertices = 12;

    // Stack Default Values initialization
    //clearColorStack.push({ rfRenderCommand::CommandType::ClearColor, 0x333333 });
    //defaultPrimitiveStack.push({ rfRenderCommand::PrimitiveType::Cube, vertexColor });
    //primitiveMaterialStack.push({ rfRenderCommand::CommandType::CreateMaterial, defaultMaterial });
    //primitiveTextureStack.push({ rfRenderCommand::CommandType::CreateTexture, dsrScene.texture});
    //sceneIndexedPrimitiveStack.push({ rfRenderCommand::CommandType::DrawIndexedPrimitive, defaultIndexedPrimitive });

    // Buffer data structure that holds the default rendering scene types
    //dsrScene.numberVertices = defaultIndexedPrimitive.numberVertices;
    //dsrScene.totalVertices = defaultIndexedPrimitive.totalVertices;
    //dsrScene.clearColor = clearColorStack.top().second;
    //dsrScene.material = primitiveMaterialStack.top().second;
    //dsrScene.texture = primitiveTextureStack.top().second;
    //dsrScene.isRenderingIndexedPrimitive = true;
    //dsrScene.light = CreateD3DLight(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL, D3DXVECTOR3(.0f,.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

    // Data structure that holds camera configuration
    dsrCamera._Position = new rfVector3(0.0f, 2.0f, 1.0f);
    dsrCamera._Target =   new rfVector3(0.0f, 0.0f, 0.0f);
    dsrCamera._Up =       new rfVector3(0.0f, 1.0f, 0.0f);
    dsrCamera._ratioWidth = 640;
    dsrCamera._ratioHeight = 480;
    dsrCamera._nearPlane = 1.0f;
    dsrCamera._farPlane = 1000.0f;

    // Set configuration camera to render scene
    CameraSetup();

    // Set the material for the default primitive that is going to be rendered
    //SetDefaultMaterial();

    // Generate the texture for the default primitive
    //CreateTextureFromFile(filename);
    
    // Turn on the light in the render scene
    //EnableLight(dsrScene.light, true);

    // Set the render state of the world
    SetRenderState();

    // Set texture filter states
    //SetSamplerState();

    return true;
}

//-----------------------------------------------------------------------------
// List that can be sent to render loop with commands to the render buffer
//-----------------------------------------------------------------------------
void Directx9Renderer::SendRenderCmdList(const std::vector<rfRenderCommand>& list)
{
}

bool Directx9Renderer::CreateVertexBuffer()
{
    return vertexBuffer->Create();
}

bool Directx9Renderer::CreateIndexBuffer()
{
    return indexBuffer->Create();
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
bool Directx9Renderer::beginFrame()
{
    RFGE_LOG("Begin Frame Render.");

    // Initialization checks
    if (initialized)
    {
        RFGE_LOG("Renderer not initialized properly.");
        return false;
    }

    // Renderer device check
    if (device == NULL)
        return false;

    // Instruct the device to set each pixel on the back buffer with default clear color
    device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x333333, 1.0f, 0);

    // Begin scene rendering
    device->BeginScene();

    return rfRenderer::beginFrame();
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
bool Directx9Renderer::endFrame()
{
    RFGE_LOG("End Frame Render.");

    // call base class implementation
    rfRenderer::endFrame();

    // Removing data from all stacks
    //while (clearColorStack.size() > 1)
        //clearColorStack.pop();

    // Removing data from all stacks
    //while (defaultPrimitiveStack.size() > 0)
        //defaultPrimitiveStack.pop();

    // Removing data from all stacks
    //while (primitiveMaterialStack.size() > 0)
        //primitiveMaterialStack.pop();

    // Removing data from all stacks
    //while (primitiveTextureStack.size() > 0)
        //primitiveTextureStack.pop();

    //device->SetMaterial(&dsrScene.material);
    //device->SetTexture(0, dsrScene.texture);

    D3DXMATRIX Ry;

    device->SetTransform(D3DTS_WORLD, &Ry);

    // Check engine rendering draw mode
    !dsrScene.isRenderingIndexedPrimitive ? 
        drawIndexedPrimitive(dsrScene.numberVertices, dsrScene.totalVertices,
        sizeof(rfVertex::VertexCoordinates), rfVertex::VertexCoordinates::FVF):
        RFGE_LOG("Rendering builtin primitive or rendering directx mesh .X file");

    // End rendering scene
    device->EndScene();

    readyToPresent = true;

    // Present render frame
    if (readyToPresent)
        device->Present(0, 0, 0, 0);

    return rfRenderer::endFrame();
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::Render()
{
    ::ZeroMemory(&msg, sizeof(MSG));

    // Get the system time in milliseconds
    static float lastTime = (float)timeGetTime();

    // Waiting for Quit Window Message
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message != WM_QUIT)
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        else // as long user does not quit engine window, process the begin and end frames
        {
            float currTime = (float)timeGetTime();
            timeDelta = (currTime - lastTime) * 0.001f;

            beginFrame();
            endFrame();

            lastTime = currTime;
        }
    }
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::SetRenderWindow(rfWindowSystem* windowSystem)
{
    renderWindow = windowSystem->Window();
}

void Directx9Renderer::SetRenderState()
{
    device->SetRenderState(WIREFRAME.RenderStateType, WIREFRAME.Value);
    device->SetRenderState(NORMALIZENORMALS.RenderStateType, NORMALIZENORMALS.Value);
    device->SetRenderState(SPECULARENABLEOFF.RenderStateType, SPECULARENABLEOFF.Value);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::Cleanup()
{
    d3d9->Release();
    device->Release();
}

void Directx9Renderer::CameraSetup()
{
    D3DXMATRIX CameraView;

    // Position and aim the camera
    D3DXMatrixLookAtLH(&CameraView, (D3DXVECTOR3*) &dsrCamera._Position, (D3DXVECTOR3*) &dsrCamera._Target, (D3DXVECTOR3*) &dsrCamera._Up);
    device->SetTransform(D3DTS_VIEW, &CameraView);

    D3DXMATRIX Projection;

    // Set the perspective projection matrix
    D3DXMatrixPerspectiveFovLH(&Projection, D3DX_PI * 0.5f, // 90 degrees
        (float)dsrCamera._ratioWidth / (float)dsrCamera._ratioHeight, dsrCamera._nearPlane, dsrCamera._farPlane);

    device->SetTransform(D3DTS_PROJECTION, &Projection);
}

void Directx9Renderer::SetDefaultMaterial()
{
    dsrScene.material = CreateD3DMaterial((D3DXCOLOR) WHITE.Red, (D3DXCOLOR)WHITE.Red, (D3DXCOLOR)WHITE.Red, (D3DXCOLOR)NOEMISSIVE.Red, 5.0f);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
HRESULT Directx9Renderer::CreateDevice()
{
    return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::CreateDefaultPrimitive()
{
    vertexBuffer->GetBuffer()->Lock(0, 0, (void**)&vertex, 0);

    // fill in the front face vertex data
    vertex[0] = rfVertex::VertexCoordinates(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
    vertex[1] = rfVertex::VertexCoordinates(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
    vertex[2] = rfVertex::VertexCoordinates(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
    vertex[3] = rfVertex::VertexCoordinates(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

    // fill in the back face vertex data
    vertex[4] = rfVertex::VertexCoordinates(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    vertex[5] = rfVertex::VertexCoordinates(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    vertex[6] = rfVertex::VertexCoordinates(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    vertex[7] = rfVertex::VertexCoordinates(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    // fill in the top face vertex data
    vertex[8] = rfVertex::VertexCoordinates(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    vertex[9] = rfVertex::VertexCoordinates(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    vertex[10] = rfVertex::VertexCoordinates(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
    vertex[11] = rfVertex::VertexCoordinates(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

    // fill in the bottom face vertex data
    vertex[12] = rfVertex::VertexCoordinates(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
    vertex[13] = rfVertex::VertexCoordinates(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    vertex[14] = rfVertex::VertexCoordinates(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
    vertex[15] = rfVertex::VertexCoordinates(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

    // fill in the left face vertex data
    vertex[16] = rfVertex::VertexCoordinates(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    vertex[17] = rfVertex::VertexCoordinates(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    vertex[18] = rfVertex::VertexCoordinates(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    vertex[19] = rfVertex::VertexCoordinates(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // fill in the right face vertex data
    vertex[20] = rfVertex::VertexCoordinates(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    vertex[21] = rfVertex::VertexCoordinates(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    vertex[22] = rfVertex::VertexCoordinates(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    vertex[23] = rfVertex::VertexCoordinates(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::LockVertexBufferMemory()
{
   
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::LockIndexBufferMemory()
{
    WORD* _indices = 0;
    indexBuffer->GetBuffer()->Lock(0, 0, (void**)&_indices, 0);

    // front side
    _indices[0] = 0; _indices[1] = 1; _indices[2] = 2;
    _indices[3] = 0; _indices[4] = 2; _indices[5] = 3;

    // back side
    _indices[6] = 4; _indices[7] = 5; _indices[8] = 6;
    _indices[9] = 4; _indices[10] = 6; _indices[11] = 7;

    // left side
    _indices[12] = 8; _indices[13] = 9; _indices[14] = 10;
    _indices[15] = 8; _indices[16] = 10; _indices[17] = 11;

    // right side
    _indices[18] = 12; _indices[19] = 13; _indices[20] = 14;
    _indices[21] = 12; _indices[22] = 14; _indices[23] = 15;

    // top
    _indices[24] = 16; _indices[25] = 17; _indices[26] = 18;
    _indices[27] = 16; _indices[28] = 18; _indices[29] = 19;

    // bottom
    _indices[30] = 20; _indices[31] = 21; _indices[32] = 22;
    _indices[33] = 20; _indices[34] = 22; _indices[35] = 23;
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::SetRenderState(rfgeDX9RenderState _renderState)
{
    device->SetRenderState(_renderState.RenderStateType, _renderState.Value);
}

void Directx9Renderer::SetSamplerState()
{
    device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

D3DLIGHT9 Directx9Renderer::CreateD3DLight(D3DLIGHTTYPE _type, D3DXVECTOR3 _direction, D3DXCOLOR _color)
{
    D3DLIGHT9 light;
    ::ZeroMemory(&light, sizeof(light));

    light.Type = _type;
    light.Direction = _direction;
    light.Ambient = _color * 0.5f;
    light.Diffuse = _color;
    light.Specular = _color * 0.2f;

    return light;
}

void Directx9Renderer::EnableLight(D3DLIGHT9 _light, bool value)
{
    device->SetLight(0, &_light);
    device->LightEnable(0, value);
}

D3DMATERIAL9 Directx9Renderer::CreateD3DMaterial(D3DXCOLOR _ambient, D3DXCOLOR _diffuse, D3DXCOLOR _specular, D3DXCOLOR _emissive, float _power)
{
    D3DMATERIAL9 mat;
    ::ZeroMemory(&mat, sizeof(mat));

    mat.Ambient = _ambient;
    mat.Diffuse = _diffuse;
    mat.Specular = _specular;
    mat.Emissive = _emissive;
    mat.Power = _power;

    return mat;
}

void Directx9Renderer::SetMaterial(D3DMATERIAL9* _mat)
{
}

void Directx9Renderer::CreateTextureFromFile(LPCWSTR filename)
{
    D3DXCreateTextureFromFile(device, filename, &dsrScene.texture);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------
void Directx9Renderer::drawIndexedPrimitive(UINT _numberVertices, UINT _totalVertices, UINT _stride, DWORD _FVF)
{
    device->SetStreamSource(0, vertexBuffer->GetBuffer(), 0, _stride);
    device->SetIndices(indexBuffer->GetBuffer());
    device->SetFVF(_FVF);

    // Draw primitive
    device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numberVertices, 0, _totalVertices);
}

IDirect3DDevice9* Directx9Renderer::GetDevice() const
{
    return device;
}

IDirect3DVertexBuffer9* Directx9Renderer::GetVertexBuffer() const
{
    return nullptr;
}

IDirect3DIndexBuffer9* Directx9Renderer::GetIndexBuffer() const
{
    return nullptr;
}