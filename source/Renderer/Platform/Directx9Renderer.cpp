
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
#include <Physics/rfPhysics.h>

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
    renderCamera->SetPosition(rfVector3::Zero()->toD3DVECTOR3());

    vertexBuffer = 0;
    indexBuffer = 0;
    Font = 0;

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
        ::MessageBoxA(0, "Direct3DCreate9()-FAILED", 0, 0);
        return false;
    }

    d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &dx9deviceCaps.caps);

    int vp = 0;

    // Check if hardware is capable
    // Using Hardware Vertex Processing for faster performance
    if (dx9deviceCaps.caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    
    // Fill out device capabilities
    dx9deviceCaps.presentParameters.BackBufferWidth = width;
    dx9deviceCaps.presentParameters.BackBufferHeight = height;
    dx9deviceCaps.presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    dx9deviceCaps.presentParameters.BackBufferCount = 1;
    dx9deviceCaps.presentParameters.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
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
        ::MessageBoxA(0, "CreateDevice() - FAILED", 0, 0);
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
    indexBuffer = new Directx9IndexBuffer();
    
    LockVertexBufferMemory();

    // Assign the indices for the default cube
    LockIndexBufferMemory();

    // Default device initialization render
    rfVertex::VertexColor vertexColor;
    D3DMATERIAL9 defaultMaterial;
    LPCWSTR filename = L"crate.jpg";

    // Set the index primitive default values
    IndexedPrimitiveSize defaultIndexedPrimitive;
    defaultIndexedPrimitive.numberVertices = 8;
    defaultIndexedPrimitive.totalVertices = 12;

    // Stack Default Values initialization
    clearColorStack.push({ rfRenderCommand::CommandType::ClearColor, 0x333333 });
    defaultPrimitiveStack.push({ rfRenderCommand::PrimitiveType::Cube, vertexColor });
    primitiveMaterialStack.push({ rfRenderCommand::CommandType::CreateMaterial, defaultMaterial });
    primitiveTextureStack.push({ rfRenderCommand::CommandType::CreateTexture, dsrScene.texture});
    sceneIndexedPrimitiveStack.push({ rfRenderCommand::CommandType::DrawIndexedPrimitive, defaultIndexedPrimitive });

    // Buffer data structure that holds the default rendering scene types
    dsrScene.numberVertices = defaultIndexedPrimitive.numberVertices;
    dsrScene.totalVertices = defaultIndexedPrimitive.totalVertices;
    dsrScene.clearColor = clearColorStack.top().second;
    dsrScene.material = primitiveMaterialStack.top().second;
    dsrScene.texture = primitiveTextureStack.top().second;
    dsrScene.isRenderingIndexedPrimitive = true;
    dsrScene.numberMeshes = 5;

    // Data structure that holds light information data
    dsrLight.angleX = 0.707f;
    dsrLight.angleY = -0.707f;
    dsrLight.angleZ = 0.707f;
    dsrLight._Direction = D3DXVECTOR3(dsrLight.angleX, dsrLight.angleY, dsrLight.angleZ);
    dsrLight._Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    dsrScene.light = CreateD3DLight(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL, dsrLight._Direction, dsrLight._Color);
   
    // Data structure that holds camera configuration
    dsrCamera._Position = new rfVector3(0.0f, 0.0f, 0.0f);
    dsrCamera._Target =   new rfVector3(0.0f, 0.0f, 0.0f);
    dsrCamera._Up =       new rfVector3(0.0f, 1.0f, 0.0f);
    dsrCamera._ratioWidth = 1920;
    dsrCamera._ratioHeight = 1080;
    dsrCamera._nearPlane = 1.0f;
    dsrCamera._farPlane = 10000.0f;

    // Initialize the font
    ZeroMemory(&dsrCamera._debugFPS, sizeof(D3DXFONT_DESC));

    // Data structure that holds font configuration
    // All values can be modified and set by a setter function
    // to be written later
    dsrCamera._debugFPS.Height = 25;    // in logical units
    dsrCamera._debugFPS.Width = 12;    // in logical units
    dsrCamera._debugFPS.Weight = 500;   // boldness, range 0(light) - 1000(bold)
    dsrCamera._debugFPS.MipLevels = D3DX_DEFAULT;
    dsrCamera._debugFPS.Italic = false;
    dsrCamera._debugFPS.CharSet = ANSI_CHARSET;
    dsrCamera._debugFPS.OutputPrecision = 0;
    dsrCamera._debugFPS.Quality = 0;
    dsrCamera._debugFPS.PitchAndFamily = 0;
    strcpy_s(dsrCamera._debugFPS.FaceName, "Arial"); // font style

    ShowFPS();

    // Create the default cube for the render scene
    CreateDefaultPrimitive();

    // Set configuration camera to render scene
    CameraSetup();

    // Set the material for the default primitive that is going to be rendered
    SetDefaultMaterial();

    // Generate the texture for the default primitive
    //CreateTextureFromFile(filename);

    // Set the render state of the world
    SetRenderState();

    // Set texture filter states
    SetSamplerState();

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

    D3DXMATRIX CameraView;

    if (::GetAsyncKeyState('W') & 0x8000f)
        renderCamera->Move(300.0f * timeDelta);

    if (::GetAsyncKeyState('S') & 0x8000f)
        renderCamera->Move(-300.0f * timeDelta);

    if (::GetAsyncKeyState('A') & 0x8000f)
        renderCamera->Yaw(-1.5f * timeDelta);

    if (::GetAsyncKeyState('D') & 0x8000f)
        renderCamera->Yaw(1.5f * timeDelta);

    if (::GetAsyncKeyState('Q') & 0x8000f)
        renderCamera->MoveUp(100.0f * timeDelta);

    if (::GetAsyncKeyState('Z') & 0x8000f)
        renderCamera->MoveUp(-100.0f * timeDelta);

    // Build camera view matrix according to keyboard input
    CameraView = renderCamera->BuildViewMatrix();
    device->SetTransform(D3DTS_VIEW, &CameraView);

    // Adjust the light rotation using wasd keyboard keys
    AdjustLight();

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

    // Removing data from all stacks
    while (clearColorStack.size() > 1)
        clearColorStack.pop();

    // Removing data from all stacks
    while (defaultPrimitiveStack.size() > 0)
        defaultPrimitiveStack.pop();

    // Removing data from all stacks
    while (primitiveMaterialStack.size() > 0)
        primitiveMaterialStack.pop();

    // Removing data from all stacks
    while (primitiveTextureStack.size() > 0)
        primitiveTextureStack.pop();

    // Check engine rendering draw mode
    !dsrScene.isRenderingIndexedPrimitive ? 
        drawIndexedPrimitive(dsrScene.numberVertices, dsrScene.totalVertices,
        sizeof(rfVertex::Vertex), rfVertex::Vertex::FVF):
        RFGE_LOG("Rendering builtin primitive or rendering directx mesh .X file");

    static char FPSString[32];
    RECT rect = { 5, 5, 1280, 720 };
    SetRect(&rect, 0, 0,500,30);
    //sprintf_s(FPSString, "FPS = %.1f", rfPhysics::Singleton->7);

    Font->DrawTextA(
        NULL,
        FPSString,
        -1, // size of string or -1 indicates null terminating string
        &rect,            // rectangle text is to be formatted to in windows coords
        DT_TOP | DT_LEFT, // draw in the top left corner of the viewport
        0xffffffff);      // black text

    device->SetTransform(D3DTS_WORLD, &defaultMeshWorldMat);

    defaultMesh->DrawSubset(0);

    for (int i = 0; i < meshes.size(); i++)
    {
        device->SetTransform(D3DTS_WORLD, &meshes[i]->worldPosition);

        for (int j = 0; j < meshes[i]->GetNumberMaterials(); j++)
        {
            device->SetMaterial(&meshes[i]->GetMaterial()[j]);
            meshes[i]->GetGeometry()->DrawSubset(j);
        }
    }

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
    device->SetRenderState(GOURAUDSHADING.RenderStateType, GOURAUDSHADING.Value);
    device->SetRenderState(NORMALIZENORMALS.RenderStateType, NORMALIZENORMALS.Value);
    device->SetRenderState(SPECULARENABLEOFF.RenderStateType, SPECULARENABLEOFF.Value);
    device->SetRenderState(D3DRS_AMBIENT, TRUE);
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
    D3DXMATRIX Projection = renderCamera->GetProjectionMatrix();

    // Set the perspective projection matrix
    D3DXMatrixPerspectiveFovLH(&Projection, D3DX_PI * 0.25f, // 45 degrees
        (float)dsrCamera._ratioWidth / (float)dsrCamera._ratioHeight, dsrCamera._nearPlane, dsrCamera._farPlane);

    device->SetTransform(D3DTS_PROJECTION, &Projection);
}

void Directx9Renderer::SetDefaultMaterial()
{
   dsrScene.material = CreateD3DMaterial(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(.5f, .5f, .5f, 1.0f), D3DXCOLOR(.0f, .0f, .0f, 0.0f), 8.5f);
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
    vertex[0] = rfVertex::Vertex(-1.0f, -1.0f, -1.0f);
    vertex[1] = rfVertex::Vertex(-1.0f, 1.0f, -1.0f);
    vertex[2] = rfVertex::Vertex(1.0f, 1.0f, -1.0f);
    vertex[3] = rfVertex::Vertex(1.0f, -1.0f, -1.0f);
    vertex[4] = rfVertex::Vertex(-1.0f, -1.0f, 1.0f);
    vertex[5] = rfVertex::Vertex(-1.0f, 1.0f, 1.0f);
    vertex[6] = rfVertex::Vertex(1.0f, 1.0f, 1.0f);
    vertex[7] = rfVertex::Vertex(1.0f, -1.0f, 1.0f);

    // Once Primitive has been setup unlock the buffer
    vertexBuffer->GetBuffer()->Unlock();

    D3DXCreateBox(
        device,
        2.0f, // width
        2.0f, // height
        2.0f, // depth
        &defaultMesh,
        0);

    // Loading  Resources
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_table.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\long_bench.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\long_bench_left.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_center.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_center_centerright.x");
    //meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\stands.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\seats_w.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\standsBase_plates.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\arena_Walls.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\base_Ground.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\court_Inner.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\court_GameOutter.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\Net.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\net_Frame.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\net_Antenna.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\net_Bench.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\net_Pillars.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\net_SafetyPillars.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\hook_Bindings.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\lights.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\chair_stand.x");

    for (int i = 0; i < meshNames.size(); i++)
    {
        meshes.push_back(new rfMesh(device));
        meshes[i]->LoadMeshGeometry(meshNames[i]);
    }
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
    _indices[6] = 4; _indices[7] = 6; _indices[8] = 5;
    _indices[9] = 4; _indices[10] = 7; _indices[11] = 6;

    // left side
    _indices[12] = 4; _indices[13] = 5; _indices[14] = 1;
    _indices[15] = 4; _indices[16] = 1; _indices[17] = 0;

    // right side
    _indices[18] = 3; _indices[19] = 2; _indices[20] = 6;
    _indices[21] = 3; _indices[22] = 6; _indices[23] = 7;

    // top
    _indices[24] = 1; _indices[25] = 5; _indices[26] = 6;
    _indices[27] = 1; _indices[28] = 6; _indices[29] = 2;

    // bottom
    _indices[30] = 4; _indices[31] = 0; _indices[32] = 3;
    _indices[33] = 4; _indices[34] = 3; _indices[35] = 7;

    // Once Primitive has been setup unlock the buffer
    indexBuffer->GetBuffer()->Unlock();
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------

void Directx9Renderer::SetRenderState(rfgeDX9RenderState _renderState)
{
    device->SetRenderState(_renderState.RenderStateType, _renderState.Value);
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------

void Directx9Renderer::SetSamplerState()
{
    device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------

D3DLIGHT9 Directx9Renderer::CreateD3DLight(D3DLIGHTTYPE _type, D3DXVECTOR3 _direction, D3DXCOLOR _color)
{
    D3DLIGHT9 light;
    ::ZeroMemory(&light, sizeof(light));

    light.Type = _type;
    light.Direction = _direction;
    light.Ambient = _color * 0.4f;
    light.Diffuse = _color;
    light.Specular = _color * 0.6f;
    light.Falloff = 0.5f;

    return light;
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------

void Directx9Renderer::AdjustLight()
{
    if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
        dsrLight.angleX += 2.0f;

    if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
        dsrLight.angleX -= 2.0f;

    if (::GetAsyncKeyState(VK_UP) & 0x8000f)
        dsrLight.angleZ -= 2.0f;

    if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
        dsrLight.angleZ += 2.0f;

    if (::GetAsyncKeyState('E') & 0x8000f)
        dsrLight.angleY -= 2.0f;

    if (::GetAsyncKeyState('R') & 0x8000f)
        dsrLight.angleY += 2.0f;

    dsrScene.light.Direction = D3DXVECTOR3(dsrLight.angleX, dsrLight.angleY, dsrLight.angleZ);

    // Turn on the light in the render scene
    EnableLight(dsrScene.light, true);
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
void Directx9Renderer::EnableLight(D3DLIGHT9 _light, bool value)
{
    device->SetLight(0, &_light);
    device->LightEnable(0, value);
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
void Directx9Renderer::SetMaterial(D3DMATERIAL9* _mat)
{
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
void Directx9Renderer::CreateTextureFromFile(LPCSTR filename)
{
    D3DXCreateTextureFromFileA(device, filename, &dsrScene.texture);
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

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
void Directx9Renderer::ShowFPS()
{
    HRESULT hr;

    hr = (D3DXCreateFontA(device, 20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &Font));

    //hr = (D3DXCreateFontIndirectA(device, &dsrCamera._debugFPS, &Font));
    
    if (FAILED(hr))
    {
        ::MessageBoxA(0, "D3DXCreateFontIndirect() - FAILED", 0, 0);
        ::PostQuitMessage(0);
    }
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------
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