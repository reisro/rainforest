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

#include <d3d9.h>
#include <d3dx9.h>
#include <d3d9types.h>
#include <stack>
#include <string>
#include <stdio.h>
#include <exception>
#include "Game/Elements/rfCamera.h"
#include "Math/rfVector3.h"
#include "Math/rfMatrix.h"
#include "Renderer/rfRenderer.h"
#include "Renderer/rfRenderCommand.h"
#include "Game/Elements/rfVertex.h"
#include "Resources/Platform/Directx9VertexBuffer.h"
#include "Resources/Platform/Directx9IndexBuffer.h"
#include "Resources/rfMesh.h"
#include "System/rfApplication.h"

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
	rfgeDX9Color(rfFloat r, rfFloat g, rfFloat b, rfFloat a)
	{	
		Red = r; Green = g; Blue = b; Alpha = a;

		Color.r = Red;
		Color.g = Green;
		Color.b = Blue;
		Color.a = Alpha;
	}

	rfFloat Red;
	rfFloat Green;
	rfFloat Blue;
	rfFloat Alpha;

	D3DXCOLOR Color;

} rfgeDX9Color;

typedef struct rfgeDX9Light
{
	rfgeDX9Light(rfFloat r, rfFloat g, rfFloat b, rfFloat a)
	{
		Red = r; Green = g; Blue = b; Alpha = a;
		D3DCOLOR_COLORVALUE(Red, Green, Blue, Alpha);
	}

	rfFloat Red;
	rfFloat Green;
	rfFloat Blue;
	rfFloat Alpha;

} rfgeDX9Light;

typedef struct rfgeDX9Material
{
	rfgeDX9Material(rfgeDX9Color a, rfgeDX9Color d, rfgeDX9Color s, rfgeDX9Color e, rfFloat p)
	{
		ambient = a.Color;
		diffuse = d.Color;
		specular = s.Color;
		emissive = e.Color;
		power = p;
		
		material.Ambient = ambient;
		material.Diffuse = diffuse;
		material.Specular = specular;
		material.Emissive = emissive;
		material.Power = power;
	}

	D3DXCOLOR    ambient;
	D3DXCOLOR    diffuse;
	D3DXCOLOR    specular;
	D3DXCOLOR    emissive;
	rfFloat	     power;
	D3DMATERIAL9 material;

} rfgeDX9Material;

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

const rfgeDX9Color WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const rfgeDX9Color BLACK(.18f, .18f, .18f, 1.0f);
const rfgeDX9Color RED(1.0f, .0f, .0f, 0.5f);
const rfgeDX9Color GREEN(.0f, 1.0f, .0f, 1.0f);
const rfgeDX9Color BLUE(.0f, .0f, 1.0f,1.0f);
const rfgeDX9Color OCEANBLUE(51.0f/255.0f, 153.0f/255.0f, 102/255.0f, 1.0f);
const rfgeDX9Color YELLOW(1.0f, 1.0f, .0f, 1.0f);
const rfgeDX9Color CYAN(.0f, 1.0f, 1.0f,1.0f);
const rfgeDX9Color MAGENTA(1.0f, .0f, 1.0f, 1.0f);

//-----------------------------------------------------------------------------
// Constant Light Colors
//-----------------------------------------------------------------------------

const rfgeDX9Light REDAMBIENT(1.0f, 0.0f, 0.0f, 1.0f);
const rfgeDX9Light GREENAMBIENT(.0f, 1.0f, .0f, 1.0f);
const rfgeDX9Light BLUEAMBIENT(.0f, .0f, 1.0f, 1.0f);
const rfgeDX9Light NOEMISSIVE(.0f, .0f, .0f, 1.0f);

//-----------------------------------------------------------------------------
// Constant Material Values
//-----------------------------------------------------------------------------

const rfgeDX9Material WHITEMATERIAL(WHITE, WHITE, WHITE, BLACK, 1.0f);

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
	friend class rfGameWorld;

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
		void			  SetDefaultMaterial();
		void			  DrawMeshData();
		
		HRESULT           CreateDevice();
		void			  CreateDefaultPrimitive();
		void			  LockVertexBufferMemory();
		void			  LockIndexBufferMemory();
		void			  SetRenderState(rfgeDX9RenderState _renderState);
		void			  SetSamplerState();
		D3DLIGHT9		  CreateD3DLight(D3DLIGHTTYPE _type, D3DXVECTOR3 _direction, D3DXCOLOR _color);
		void			  AdjustLight();
		void			  EnableLight(D3DLIGHT9 _light, bool value);
		D3DMATERIAL9      CreateD3DMaterial(D3DXCOLOR _ambient, D3DXCOLOR _diffuse, D3DXCOLOR _specular, D3DXCOLOR _emissive, float _power);
		void              SetMaterial(D3DMATERIAL9* _mat);
		void			  CreateTextureFromFile(LPCSTR filename);

		void			  drawIndexedPrimitive(UINT _numberVertices, UINT _totalVertices, UINT _stride, DWORD _FVF);
		void			  ShowFPS();

		IDirect3DDevice9*               GetDevice()	const;
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
		RFGE_STACK_DECLARE(rfRenderCommand::CommandType, rfMesh, rfMeshDrawStack)
		RFGE_STACK_DECLARE(rfRenderCommand, D3DMATERIAL9, rfSceneMaterial)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DTexture9*, rfSceneTexture)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DVertexBuffer9*, rfVertexBuffer)
		RFGE_STACK_DECLARE(rfRenderCommand, IDirect3DIndexBuffer9*, rfIndexBuffer)
		RFGE_STACK_DECLARE(rfRenderCommand, IndexedPrimitiveSize, rfIndexedPrimitiveSize)
		RFGE_QUEUE_DECLARE(LPCSTR, bool, rfRenderPhysicsMesh)
	
		// Stack strucutures that store default values
		ClearColorStack			clearColorStack;
		rfIndexedPrimitive		defaultPrimitiveStack;
		rfMeshDrawStack			meshDrawStack;
		rfSceneMaterial			primitiveMaterialStack;
		rfSceneTexture			primitiveTextureStack;
		rfVertexBuffer			sceneVertexBufferStack;
		rfIndexBuffer			sceneIndexBufferStack;
		rfIndexedPrimitiveSize	sceneIndexedPrimitiveStack;
		rfRenderPhysicsMesh	    sceneRenderPhysicsMesh;

		// Data structure that holds rendering scene buffer constants
		struct dsRenderScene
		{
			int					clearColor;
			D3DMATERIAL9		material;
			IDirect3DTexture9*	texture;
			D3DLIGHT9			light;
			D3DLIGHT9			lightAux;
			UINT				numberVertices;
			UINT				totalVertices;
			int					numberMeshes;
			bool				isRenderingIndexedPrimitive;
		};

		struct dsRenderCamera
		{
			rfVector3*      _Position;
			rfVector3*      _Direction;
			rfVector3*      _Target;
			rfVector3*      _Up;
			rfVector3*      _Right;
			rfVector3*      _Forward;
			D3DXMATRIX      _View;
			D3DXMATRIX      _Proj;
			rfInt           _ratioWidth;
			rfInt           _ratioHeight;
			rfFloat         _nearPlane;
			rfFloat         _farPlane;
			D3DXFONT_DESCA  _debugFPS;
		};

		struct dsRenderLight
		{
			rfFloat		angleX;
			rfFloat		angleY;
			rfFloat		angleZ;
			D3DXVECTOR3 _Direction;
			D3DCOLOR	_Color;
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
		ID3DXMesh*                  defaultMesh;
		D3DXMATRIX					defaultMeshWorldMat;
		Directx9VertexBuffer*		vertexBuffer;
		Directx9IndexBuffer*		indexBuffer;
		HWND						renderWindow;
		ID3DXFont*                  Font;
		rfgeDX9DeviceCaps			dx9deviceCaps;
		rfCamera*                   renderCamera;
		D3DDEVTYPE					deviceType;
		MSG							msg;
		dsRenderScene				dsrScene;
		dsRenderCamera				dsrCamera;
		dsRenderLight				dsrLight;
		dsRenderLight				dsrLightSecond;

		std::stack<rfRenderCommand> renderCmdStack;
		std::vector<rfMesh>         meshes;
		std::vector<LPCSTR>         meshNames;

		rfVertex::Vertex* vertex;
};

#endif RFGE_DIRECT3D9_SDK_H_