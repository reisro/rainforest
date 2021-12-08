
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

#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)

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
    renderCamera = new rfCamera();
    renderCamera->SetPosition(D3DXVECTOR3(-1427.39f,505.599f,2435.707f));
    renderCamera->SetRight(D3DXVECTOR3(-0.898f, .0f, -0.438f));
    renderCamera->SetUp(D3DXVECTOR3(.0f, 1.0f, .0f));
    renderCamera->SetLookAt(D3DXVECTOR3(0.522f, .0f, -0.852f));

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
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(rfWindowSystem::GetInstance()->Window());
    ImGui_ImplDX9_Init(device);

    //vertexBuffer = new Directx9VertexBuffer();
    //indexBuffer = new Directx9IndexBuffer();
    
    //LockVertexBufferMemory();

    // Assign the indices for the default cube
    //LockIndexBufferMemory();

    // Default device initialization render
    rfVertex::VertexColor vertexColor;
    D3DMATERIAL9 defaultMaterial;

    // Set the index primitive default values
    IndexedPrimitiveSize defaultIndexedPrimitive;
    defaultIndexedPrimitive.numberVertices = 8;
    defaultIndexedPrimitive.totalVertices = 12;

    // Stack Default Values initialization
    clearColorStack.push({ rfRenderCommand::CommandType::ClearColor, 0x333333 });
    defaultPrimitiveStack.push({ rfRenderCommand::PrimitiveType::Cube, vertexColor });
    primitiveMaterialStack.push({ rfRenderCommand::CommandType::CreateMaterial, defaultMaterial });
    primitiveTextureStack.push({ rfRenderCommand::CommandType::CreateTexture, dsrScene._Texture});
    sceneIndexedPrimitiveStack.push({ rfRenderCommand::CommandType::DrawIndexedPrimitive, defaultIndexedPrimitive });

    // Buffer data structure that holds the default rendering scene types
    dsrScene._NumberVertices = defaultIndexedPrimitive.numberVertices;
    dsrScene._TotalVertices = defaultIndexedPrimitive.totalVertices;
    dsrScene._ClearColor = clearColorStack.top().second;
    dsrScene._Material = primitiveMaterialStack.top().second;
    dsrScene._Texture = primitiveTextureStack.top().second;
    dsrScene._IsRenderingIndexedPrimitive = true;
    dsrScene._NumberMeshes = 5;

    // Data structure that holds light information data
    dsrLight._AngleX = -255.292f;
    dsrLight._AngleY = 293.29f;
    dsrLight._AngleZ = 382.70f;
    dsrLight._Direction = D3DXVECTOR3(dsrLight._AngleX, dsrLight._AngleY, dsrLight._AngleZ);
    dsrLight._Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // Data structure that holds light information data
    dsrLightSecond._AngleX = -0.7070f;
    dsrLightSecond._AngleY = 0.7070f;
    dsrLightSecond._AngleZ = 0.7070f;
    dsrLightSecond._Direction = D3DXVECTOR3(dsrLightSecond._AngleX, dsrLightSecond._AngleY, dsrLightSecond._AngleZ);
    dsrLightSecond._Color = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

    dsrScene._Light = CreateD3DLight(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL, dsrLight._Direction, dsrLight._Color);
    dsrScene._LightAux = CreateD3DLight(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL, dsrLightSecond._Direction, dsrLightSecond._Color);
   
    // Data structure that holds camera configuration
    dsrCamera._Position = new rfVector3(0.0f, 0.0f, 0.0f);
    dsrCamera._Target =   new rfVector3(0.0f, 0.0f, 0.0f);
    dsrCamera._Up =       new rfVector3(0.0f, 1.0f, 0.0f);
    dsrCamera._RatioWidth = 1920;
    dsrCamera._RatioHeight = 1080;
    dsrCamera._NearPlane = 1.0f;
    dsrCamera._FarPlane = 10000.0f;

    // Initialize the font
    ZeroMemory(&dsrCamera._DebugFPS, sizeof(D3DXFONT_DESC));

    // Data structure that holds font configuration
    // All values can be modified and set by a setter function
    // to be written later
    dsrCamera._DebugFPS.Height = 25;    // in logical units
    dsrCamera._DebugFPS.Width = 12;    // in logical units
    dsrCamera._DebugFPS.Weight = 500;   // boldness, range 0(light) - 1000(bold)
    dsrCamera._DebugFPS.MipLevels = D3DX_DEFAULT;
    dsrCamera._DebugFPS.Italic = false;
    dsrCamera._DebugFPS.CharSet = ANSI_CHARSET;
    dsrCamera._DebugFPS.OutputPrecision = 0;
    dsrCamera._DebugFPS.Quality = 0;
    dsrCamera._DebugFPS.PitchAndFamily = 0;
    strcpy_s(dsrCamera._DebugFPS.FaceName, "Arial"); // font style

    ShowFPS();

    // Create the default cube for the render scene
    //CreateDefaultPrimitive();

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

    bool show_simple_window = true;

    rfPhysics::GetInstance()->GetPhysicsResults();
    rfPhysics::GetInstance()->Simulate();

    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    {
        static int corner = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (corner != -1)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("Volleyball Court", &show_simple_window, window_flags))
        {
            ImGui::Text("         Demo Features Overview              \n");
            ImGui::Separator();
            ImGui::Text("Rendering API DirectX 9\n" "Physics API NVidia PhysX ver 2.8.1\n" "Dear imgui ver 1.6\n");
            ImGui::Text("Application ms/frame %.3f (%.1f FPS)\n", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
                if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
                if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
                if (&show_simple_window && ImGui::MenuItem("Close")) show_simple_window = false;
                ImGui::EndPopup();
            }
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("            Demo Objective              \n");
            ImGui::Separator();
            ImGui::Text("Hit all cones with the brazilian ball.\n");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("        Camera Navigation Controls \n");
            ImGui::Separator();
            ImGui::Text("W Move Forward\n" "S Move Backward\n" "A Strafe Left\n" "D Strafe Right\n" "Q Move Up\n" "Z Move Down\n");
            ImGui::Text("MLB Down + Mouse Forward Pitch Up \n");
            ImGui::Text("MLB Down + Mouse Backward Pitch Down \n");
            ImGui::Text("MLB Down + Mouse Left Rotate Left \n");
            ImGui::Text("MLB Down + Mouse Right Rotate Right \n");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("            Game Controls \n");
            ImGui::Separator();
            ImGui::Text("V Raise Ball \n");
            ImGui::Text("B Spike Ball Long \n");
            ImGui::Text("Left Arrow Key Spike Ball Left \n");
            ImGui::Text("Right Arrow Key Spike Ball Right \n");
            ImGui::Text("Down Arrow Key Spike Ball Down \n");
            ImGui::Text("M Reset Game \n");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("            Ambient Controls \n");
            ImGui::Separator();
            ImGui::Text("R Increase Ambient Lighting \n");
            ImGui::Text("E Decrease Ambient Lighting \n");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("            Render Controls \n");
            ImGui::Separator();
            ImGui::Text("1 Wireframe Mode \n");
            ImGui::Text("2 Lit Mode \n");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("            Application Controls \n");
            ImGui::Separator();
            ImGui::Text("Alt + F4 Quit \n");
            ImGui::Separator();
        }
        ImGui::End();
    }
    
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

    // Camera navigation controls
    if (::GetAsyncKeyState('W') & 0x8000f)
        renderCamera->Move(500.0f * timeDelta);

    if (::GetAsyncKeyState('S') & 0x8000f)
        renderCamera->Move(-500.0f * timeDelta);

    if (::GetAsyncKeyState('A') & 0x8000f)
        renderCamera->RotateYaw(-1.5f * timeDelta);

    if (::GetAsyncKeyState('D') & 0x8000f)
        renderCamera->RotateYaw(1.5f * timeDelta);

    if (::GetAsyncKeyState('Q') & 0x8000f)
        renderCamera->MoveUp(100.0f * timeDelta);

    if (::GetAsyncKeyState('Z') & 0x8000f)
        renderCamera->MoveUp(-100.0f * timeDelta);
    if (::GetAsyncKeyState('V') & 0x8000f)
        rfPhysics::GetInstance()->ApplyForceToPhysicsActor("Ball");
    if (::GetAsyncKeyState('1') & 0x8000f)
        SetRenderState(WIREFRAME);
    if (::GetAsyncKeyState('2') & 0x8000f)
        SetRenderState();

    // Build camera view matrix according to keyboard input
    CameraView = renderCamera->BuildViewMatrix();

    device->SetTransform(D3DTS_VIEW, &CameraView);

    // Adjust the light rotation using wasd keyboard keys
    AdjustLight();

    ImGui::EndFrame();

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
    !dsrScene._IsRenderingIndexedPrimitive ?
        drawIndexedPrimitive(dsrScene._NumberVertices, dsrScene._TotalVertices,
            sizeof(rfVertex::Vertex), rfVertex::Vertex::FVF) :
        RFGE_LOG("Rendering builtin primitive or rendering directx mesh .X file");

    static char FPSString[32];
    RECT rect = { 5, 5, 1280, 720 };
    sprintf_s(FPSString, "FPS = %.1f", rfPhysics::Singleton->GetFPS());

    static char NavigationString[32];
    RECT rect_ = { 5, 30, 1900, 720 };
    sprintf_s(NavigationString, "Navigation Controls");

    for (size_t i = 0; i < meshes.size() - 1; i++)
    {
        device->SetTransform(D3DTS_WORLD, &meshes[i].worldPosition);

        for (int j = 0; j < meshes[i].GetNumberMaterials(); j++)
        {
            device->SetMaterial(&meshes[i].GetMaterial()[j]);
            meshes[i].GetGeometry()->DrawSubset(j);
        }
    }

    // Update matrix position of physics actors 
    PostRender(&rfPhysics::UpdateGlobalPosition);

    // End rendering scene
    device->EndScene();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    readyToPresent = true;

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

void Directx9Renderer::PostRender(postRenderPt postRenderFunc)
{
    this->postRenderFunc = postRenderFunc;

    auto mat = (rfPhysics::GetInstance()->*postRenderFunc)();
    
    device->SetTransform(D3DTS_WORLD, &mat);

    for (int j = 0; j < meshes[29].GetNumberMaterials(); j++)
    {
        device->SetMaterial(&meshes[29].GetMaterial()[j]);
        meshes[29].GetGeometry()->DrawSubset(j);
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
    device->SetRenderState(SOLID.RenderStateType, SOLID.Value);
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
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    _RFGE_SAFE_RELEASE(d3d9);
    _RFGE_SAFE_RELEASE(device);
    _RFGE_SAFE_RELEASE(Font);
    _RFGE_SAFE_DELETE(Font);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------

void Directx9Renderer::CameraSetup()
{
    D3DXMATRIX Projection = renderCamera->GetProjectionMatrix();

    // Set the perspective projection matrix
    D3DXMatrixPerspectiveFovLH(&Projection, D3DX_PI * 0.25f, // 45 degrees
        (float)dsrCamera._RatioWidth / (float)dsrCamera._RatioHeight, dsrCamera._NearPlane, dsrCamera._FarPlane);

    device->SetTransform(D3DTS_PROJECTION, &Projection);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------

void Directx9Renderer::SetDefaultMaterial()
{
   dsrScene._Material = CreateD3DMaterial(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(.5f, .5f, .5f, 1.0f), D3DXCOLOR(.0f, .0f, .0f, 0.0f), 8.5f);
}

//-----------------------------------------------------------------------------
// After initialization, fill out with default constants for rendering
//-----------------------------------------------------------------------------

void Directx9Renderer::DrawMeshData()
{
    for (size_t i = 0; i < meshes.size()-1; i++)
    {
        device->SetTransform(D3DTS_WORLD, &meshes[i].worldPosition);

        for (int j = 0; j < meshes[i].GetNumberMaterials(); j++)
        {
            device->SetMaterial(&meshes[i].GetMaterial()[j]);
            meshes[i].GetGeometry()->DrawSubset(j);
        }
    }
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
    //vertexBuffer->GetBuffer()->Lock(0, 0, (void**)&vertex, 0);

    // fill in the front face vertex data
    //vertex[0] = rfVertex::Vertex(-1.0f, -1.0f, -1.0f);
    //vertex[1] = rfVertex::Vertex(-1.0f, 1.0f, -1.0f);
    //vertex[2] = rfVertex::Vertex(1.0f, 1.0f, -1.0f);
    //vertex[3] = rfVertex::Vertex(1.0f, -1.0f, -1.0f);
    //vertex[4] = rfVertex::Vertex(-1.0f, -1.0f, 1.0f);
    //vertex[5] = rfVertex::Vertex(-1.0f, 1.0f, 1.0f);
    //vertex[6] = rfVertex::Vertex(1.0f, 1.0f, 1.0f);
    //vertex[7] = rfVertex::Vertex(1.0f, -1.0f, 1.0f);

    // Once Primitive has been setup unlock the buffer
    //vertexBuffer->GetBuffer()->Unlock();

    // Loading  Resources
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_table.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\long_bench.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\long_bench_left.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_center.x");
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\bench_center_centerright.x");
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
    meshNames.push_back("D:\\DirectX\\rainforest\\games\\Assets\\ball_br2.x");

    for (int i = 0; i < meshNames.size(); i++)
    {
        meshes.push_back(rfMesh(device));
        meshes[i].LoadMeshGeometry(meshNames[i],.0f,.0f,.0f);
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
    light.Position = D3DXVECTOR3(100.0f, 29.0f, 79.0f);
    light.Ambient = _color * 0.4f;
    light.Diffuse = _color;
    light.Specular = _color * 0.1f;
    light.Falloff = 0.2f;
    light.Range = 5.0f;

    return light;
}

//--------------------------------------------------------------------------------------
// Updates the frames/sec stat once per second
//--------------------------------------------------------------------------------------

void Directx9Renderer::AdjustLight()
{
    if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
        dsrLight._AngleX += 2.0f;

    if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
        dsrLight._AngleX -= 2.0f;

    if (::GetAsyncKeyState(VK_UP) & 0x8000f)
        dsrLight._AngleZ -= 2.0f;

    if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
        dsrLight._AngleZ += 2.0f;

    if (::GetAsyncKeyState('E') & 0x8000f)
        dsrLight._AngleY -= 2.0f;

    if (::GetAsyncKeyState('R') & 0x8000f)
        dsrLight._AngleY += 2.0f;

    dsrScene._Light.Direction = D3DXVECTOR3(dsrLight._AngleX, dsrLight._AngleY, dsrLight._AngleZ);

    // Turn on the light in the render scene
    EnableLight(dsrScene._Light, true);
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
    D3DXCreateTextureFromFileA(device, filename, &dsrScene._Texture);
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

    hr = (D3DXCreateFontA(device, 24, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Sitka Display Regular", &Font));
    
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