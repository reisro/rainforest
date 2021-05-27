//---------------------------------------------------------------------------//
//                                                                           //
// File : Directx9Renderer.h                                                 //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef RFGE_DIRECT3D9_SDK_H_
#define RFGE_DIRECT3D9_SDK_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d9types.h>
#include <stack>
#include "Game/Elements/Camera.h"
#include "Math/rfVector3.h"
#include "Math/rfMatrix.h"
#include "Renderer/rfRenderer.h"
#include "Game/Elements/rfVertex.h"
#include "Resources/Platform/Directx9VertexBuffer.h"
#include "Resources/Platform/Directx9IndexBuffer.h"
#include "System/rfApplication.h"
#include "System/rfConfig.h"

//-----------------------------------------------------------------------------
// Enum (Vertex Processing)
// Types of vertex processing when using graphics card
//-----------------------------------------------------------------------------

enum D3DVERTEXPROCESSING
{
	SOFTWARE = 1,
	HARDWARE = 2
};

//-----------------------------------------------------------------------------
// Typedefs Struct
//-----------------------------------------------------------------------------

typedef struct rfgeDX9RenderState
{
	rfgeDX9RenderState(D3DRENDERSTATETYPE _renderStatetype, DWORD _value)
	{
		RenderStateType = _renderStatetype;
		Value = _value;
	}
	
	D3DRENDERSTATETYPE RenderStateType;
	DWORD Value;
} rfgeDX9RenderState;

typedef struct rfgeDX9Color
{
	rfgeDX9Color(int r, int g, int b)
	{	
		Red = r; Green = g; Blue = b; 
		D3DCOLOR_XRGB(Red, Green, Blue); 
	}

	int Red;
	int Green;
	int Blue;
} rfgeDX9Color;

typedef struct rfgeDX9Light
{
	rfgeDX9Light(int r, int g, int b)
	{
		Red = r; Green = g; Blue = b;
		D3DCOLOR_XRGB(Red, Green, Blue);
	}

	int Red;
	int Green;
	int Blue;
} rfgeDX9Light;

//-----------------------------------------------------------------------------
// Render States Drawing Modes
//-----------------------------------------------------------------------------

const rfgeDX9RenderState WIREFRAME(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
const rfgeDX9RenderState SOLID(D3DRS_FILLMODE, D3DFILL_SOLID);
const rfgeDX9RenderState NORMALIZENORMALS(D3DRS_NORMALIZENORMALS, true);
const rfgeDX9RenderState LIGHTINGON(D3DRS_LIGHTING, true);
const rfgeDX9RenderState LIGHTINGOFF(D3DRS_LIGHTING, false);
const rfgeDX9RenderState SPECULARENABLEON(D3DRS_SPECULARENABLE, true);
const rfgeDX9RenderState SPECULARENABLEOFF(D3DRS_SPECULARENABLE, false);

//-----------------------------------------------------------------------------
// Render States Shading Modes
//-----------------------------------------------------------------------------

const rfgeDX9RenderState FLATSHADING(D3DRS_SHADEMODE, D3DSHADE_FLAT);
const rfgeDX9RenderState GOURAUDSHADING(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
const rfgeDX9RenderState PHONGSHADING(D3DRS_SHADEMODE, D3DSHADE_PHONG);

//-----------------------------------------------------------------------------
// Constant Colors
//-----------------------------------------------------------------------------

const rfgeDX9Color WHITE(255, 255, 255);
const rfgeDX9Color BLACK(0, 0, 0);
const rfgeDX9Color RED(255, 0, 0);
const rfgeDX9Color GREEN(0, 255, 0);
const rfgeDX9Color BLUE(0, 0, 255);
const rfgeDX9Color OCEANBLUE(51, 153, 102);
const rfgeDX9Color YELLOW(255, 255, 0);
const rfgeDX9Color CYAN(0, 255, 255);
const rfgeDX9Color MAGENTA(255, 0, 255);

//-----------------------------------------------------------------------------
// Constant Light Colors
//-----------------------------------------------------------------------------

const rfgeDX9Light REDAMBIENT(255, 0, 0);
const rfgeDX9Light GREENAMBIENT(0, 255, 0);
const rfgeDX9Light BLUEAMBIENT(0, 0, 255);

//-----------------------------------------------------------------------------
// Class (mgeDeviceCaps)
//-----------------------------------------------------------------------------

typedef struct rfgeDX9DeviceCaps
{
	D3DCAPS9 caps;
	_D3DPRESENT_PARAMETERS_ presentParameters;
} rfgeDX9DeviceCaps;

class Directx9Renderer: public rfRenderer
{
public:

		Directx9Renderer();
		~Directx9Renderer();
		
		bool			  Initialize() override;
		bool			  PostInit() override;
		void			  SendRenderCmdList(const std::vector<rfRenderCommand>& list) override;
		bool			  CreateVertexBuffer() override;
		bool			  CreateIndexBuffer() override;
		bool			  beginFrame() override;
		bool			  endFrame() override;
		void			  Render() override;
		void			  SetRenderWindow(rfWindowSystem* windowSystem) override;
		void			  SetRenderState() override;
		void			  Cleanup() override;

		void			  CameraSetup() override;
		
		HRESULT           CreateDevice();
		void			  CreateDefaultPrimitive();
		void			  LockVertexBufferMemory();
		void			  LockIndexBufferMemory();
		void			  SetRenderState(rfgeDX9RenderState _renderState);
		D3DLIGHT9		  CreateD3DLight(D3DLIGHTTYPE _type, D3DXVECTOR3 _direction, D3DXCOLOR _color);
		void			  EnableLight(D3DLIGHT9 _light, bool value);
		void              CreateD3DMaterial(D3DXCOLOR _ambient, D3DXCOLOR _diffuse, D3DXCOLOR _specular, D3DXCOLOR _emissive, float _power);
		void              SetMaterial(D3DMATERIAL9* _mat);
		void			  CreateTextureFromFile(LPCWSTR filename);

		void			  drawIndexedPrimitive(UINT _numberVertices, UINT _totalVertices, UINT _stride, DWORD _FVF);

		IDirect3DVertexBuffer9*			GetVertexBuffer() const;
		IDirect3DIndexBuffer9*			GetIndexBuffer() const;

protected:
		
		// Define render based struct types
		struct IndexedPrimitiveSize
		{
			UINT numberVertices;
			UINT totalVertices;
		};

		// Define declaration types
		RFGE_STACK_DECLARE(rfRenderCommand, int, ClearColorStack)
		RFGE_STACK_DECLARE(rfRenderCommand::PrimitiveType, rfVertex::VertexColor, rfIndexedPrimitive)
		RFGE_STACK_DECLARE(rfRenderCommand, D3DMATERIAL9*, rfSceneMaterial)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DTexture9*, rfSceneTexture)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DVertexBuffer9*, rfVertexBuffer)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DIndexBuffer9*, rfIndexBuffer)
		RFGE_STACK_DECLARE(rfRenderCommand, IndexedPrimitiveSize, rfIndexedPrimitiveSize)
	
		// Stack strucutures that store default values
		ClearColorStack			clearColorStack;
		rfIndexedPrimitive		defaultPrimitiveStack;
		rfSceneMaterial			primitiveMaterialStack;
		rfSceneTexture			primitiveTextureStack;
		rfVertexBuffer			sceneVertexBufferStack;
		rfIndexBuffer			sceneIndexBufferStack;
		rfIndexedPrimitiveSize	sceneIndexedPrimitiveStack;

		// Data structure that holds rendering scene buffer constants
		struct dsRenderScene
		{
			int clearColor;
			D3DMATERIAL9* material;
			IDirect3DTexture9* texture;
			D3DLIGHT9 light;
			UINT numberVertices;
			UINT totalVertices;
			bool isRenderingIndexedPrimitive;
		};

		struct dsRenderCamera
		{
			rfVector3*    _Position;
			rfVector3*    _Direction;
			rfVector3*    _Target;
			rfVector3*    _Up;
			rfVector3*    _Right;
			rfVector3*    _Forward;
			D3DXMATRIX    _View;
			D3DXMATRIX    _Proj;
			rfInt        _ratioWidth;
			rfInt        _ratioHeight;
			rfFloat      _nearPlane;
			rfFloat      _farPlane;
		};

private:

		int							width;
		int							height;
		float						timeDelta;
		bool						windowed;
		bool						initialized;
		bool						readyToPresent;
		IDirect3D9*					d3d9;
		IDirect3DDevice9*			device;
		Directx9VertexBuffer*		vertexBuffer;
		Directx9IndexBuffer*		indexBuffer;
		HWND						renderWindow;
		rfgeDX9DeviceCaps			dx9deviceCaps;
		Camera*                     renderCamera;
		D3DDEVTYPE					deviceType;
		MSG							msg;
		dsRenderScene				dsrScene;
		dsRenderCamera				dsrCamera;

		std::stack<rfRenderCommand> renderCmdStack;

		rfVertex::VertexCoordinates* vertex;
};

#endif RFGE_DIRECT3D9_SDK_H_